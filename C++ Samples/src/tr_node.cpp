#include "trnode.h"

/*
 * Contructor for a trnode object
 * n: Name of node
 * d: Whether it is a directory or not
 */
tr_node::tr_node(string n, bool d) {
    if (d && n.back() == '/') {
        dir = d;
        name = n;
        size = 0;
        children = vector<tr_node *>();
    } else if (!d) {
        name = n;
        dir = d;
        size = 0;
        time_stamp = clock();
        lfile = NULL;
    } else {
        throw invalid_argument("Directory names should end in /");
    }
}

/*
 * Contructor for a trnode object used for files
 * n: Name of node
 * d: Whether it is a directory or not
 * block_list: List of blocks to allocate for the file
 * t: Time-stamp
 */
tr_node::tr_node(string n, bool d, int s, int b_size, vector<int> block_list, clock_t t) {
    vector<int>::iterator it = block_list.begin();
    int used = 0;

    if (!dir) {
        if (name.find("/") != string::npos) {
            throw invalid_argument("Error: file names cannot contain /");
        }
        name = n;
        dir = d;
        size = s;
        time_stamp = t;

        if (size > 0) {
            used = min(size, b_size);
            lfile = new lf_node((*it), b_size);
            ++it;
            s -= used;
        
            while (s > 0) {
                if (it == block_list.end()) {
                    throw invalid_argument("Not enough blocks allocated");
                }

                used = min(size, b_size);
                
                if (used > 0) {
                    lfile->insert_at_end(new lf_node((*it), b_size));
                    s -= used;
                    ++it;
                }
            }
        }

    } else {
        throw invalid_argument("Use constructor for creating directories");
    }

}


/*
 * Destructor for a trnode object, deletes all the children and the lfile
 */
tr_node::~tr_node() {
    vector<tr_node*>::iterator it = children.begin();

    for (; it != children.end(); ++it) {
        delete (*it);
    }

    if (!dir) {
        if (lfile) {
            delete lfile;
        }
    }
}

/*
 * Adds a child to a trnode
 * c: a node to add as a child
 */
bool tr_node::add_child(tr_node *c) {
    vector<tr_node*>::iterator it = children.begin();
    string n = "";

    for (; it != children.end(); ++it) {
        n= (*it)->name;
        if (n.compare(c->name) == 0 || c == (*it)) {
            return 0;
        }
    }

    children.push_back(c);
    return 1;
}

/*
 * Removes a child from a trnode
 * c_name: The name of the node to delete
 */
bool tr_node::remove_child(string c_name) {
    vector<tr_node*>::iterator it = children.begin();
    string n = "";

    for (; it != children.end(); ++it) {
        n= (*it)->name;
        if (n.compare(c_name) == 0) {
            delete (*it);
            children.erase(it);
            return 1;
        }
    }

    return 0;
}

/*
 * Gets a child from a trnode
 * c_name: The name of the node to retrieve 
 */
tr_node *tr_node::get_child(string c_name) {
    queue<tr_node*> q;
    vector<tr_node*>::iterator it;
    q.push(this);

    while (!(q.empty())) {
        tr_node *temp = q.front();
        q.pop();
        if (temp->name.compare(c_name) == 0) {
            return temp;
        }
        it = temp->children.begin();
        for (; it != temp->children.end(); ++it) {
            q.push((*it));
        }
    }

    return NULL;

}

/*
 * Prints the whole directory tree
 */
void tr_node::print_out() {
    cout << "Dir: " << endl;
    queue<tr_node*> q;
    vector<tr_node*>::iterator it;
    q.push(this);

    while (!(q.empty())) {
        tr_node *temp = q.front();
        q.pop();

        cout << temp->name << endl;

        it = temp->children.begin();

        for (; it != temp->children.end(); ++it) {
            q.push((*it));
        }
    }
}

/*
 * Prints every file node from the tree
 */
void tr_node::print_files() {
    queue<tr_node*> q;
    vector<tr_node*>::iterator it;
    q.push(this);
    cout << "File name\tTimestamp\tFilesize" << endl;

    while (!(q.empty())) {
        tr_node *temp = q.front();
        q.pop();

        if (!(temp->dir)) {
            cout << temp->name << "\t";
            cout << temp->time_stamp << "\t";
            cout << temp->size << "\n";
            if (temp->lfile) {
                cout << "Block addresses ";
                temp->lfile->print_out();
            }
            cout << endl;

        }
        it = temp->children.begin();

        for (; it != temp->children.end(); ++it) {
            q.push((*it));
        }
    }
}

/*
 * Adds blocks to a file node
 */
void tr_node::add_blocks(vector<int> block_ids, int b_size) {
    vector<int>::iterator it = block_ids.begin();
    size += block_ids.size() * b_size;
    if (lfile) { 
        for (it = block_ids.begin(); it != block_ids.end(); ++it) {
            lfile->insert_at_end(new lf_node((*it), b_size));
        }
    } else {
        lfile = new lf_node((*it), b_size);
        for (it = it + 1; it != block_ids.end(); ++it) {
            lfile->insert_at_end(new lf_node((*it), b_size));
        }
    }
}
