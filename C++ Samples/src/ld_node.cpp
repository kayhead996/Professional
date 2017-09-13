#include "ldnode.h"

/*
 * Destructor for ld_node
 */
ld_node::~ld_node() {
    next_n = NULL;
    prev_n = NULL;
}

/*
 * returns the node with the id that was requested
 * id: the id of the node to retrieve
 */
ld_node *ld_node::get(int id) {
    for (ld_node *tmp = this; tmp; tmp = tmp->next_n) {
        if (tmp->start == id) {
            return tmp;
        }
    }

    return NULL;
}

/*
 * prints every block and whether it is used or free
 */
void ld_node::print_every_block() {
    ld_node *temp = this;

    for (; temp; temp = temp->get_next()) {
        cout << temp->start << ": " << (temp->used? " used": "free") << "->";
    }

}

/*
 * prints every block
 */
void ld_node::print_out() {
    ld_node *temp = this;
    int s = temp->start;
    int e = temp->end;
    bool u = temp->used;

    for (; temp != NULL; temp = temp->get_next()) {
        if (u == temp->used) {
            e = temp->end; 
        } else {
            if (s != e) {
                cout << "Blocks " << s << "-" << e << (u? " used": " free") << "->";
            } else {
                cout << "Block " << s << (u? " used": " free") << "->";
            }
            u = temp->used;
            s = temp->start;
            e = temp->end;
        }
    }
    if (s != e) {
        cout << "Blocks " << s << "-" << e << (u? " used": " free");
    } else {
        cout << "Block " << s << (u? " used": " free");
    }

    cout << endl;
}

/*
 * returns the root of the linked list
 */
ld_node *ld_node::get_root() {
    ld_node *root = this;

    while (root->prev_n) {
        root = root ->prev_n;
    }

    return root;
}

/* 
 * inserts a node at the end of the linked list
 * node: the node to insert
 */
ld_node *ld_node::insert_at_end(ld_node *node) {
    ld_node *last = this;
    if (node) {
        while (last->next_n) {
            last = last->next_n;
        }

        if (node->start <= last->end) {
            node->start = last->end+ 1;
        }

        if (node->start > node->end) {
            cout << "Error: invalid block start and end values" << endl;
            return this->get_root();
        }

        last->next_n = node;
        node->prev_n = last;
        node->next_n = NULL;
    }

    return this->get_root();
}

/*
 * inserts a node after the current node
 * node: the node to insert
 */
ld_node *ld_node::insert_after(ld_node *node) {

    if (node) {
        if (node->start <= this->end) {
            node->start = this->end+ 1;
        }

        if ((this->next_n) && node->end >= (this->next_n)->start) {
            node->end = (this->next_n)->start - 1;
        }


        if (node->start > node->end) {
            cout << "Error: invalid block start and end values" << endl;
            return this->get_root();
        }

        if (this->next_n) {
            (this->next_n)->prev_n = node;
        }

        node->prev_n = this;
        node->next_n = this->next_n;
        this->next_n = node;
    }

    return this->get_root();
}

/*
 * inserts a node before the current node
 * node: the node to insert
 */
ld_node *ld_node::insert_before(ld_node *node) {
    if (node) {
        if (node->end >= this->start) {
            node->end = this->start - 1;
        }

        if ((this->prev_n) && node->start <= (this->prev_n)->end) {
            node->start = (this->prev_n)->end + 1;
        }

        if (node->start > node->end) {
            cout << "Error: invalid block start and end values" << endl;
            return this->get_root();
        }

        if (this->prev_n) {
            (this->prev_n)->next_n = node;
        }

        node->next_n = this;
        node->prev_n = this->prev_n;
        this->prev_n = node;
    }

    return this->get_root();
}

/*
 * removes the node that is previous to the current node
 */
ld_node *ld_node::remove_prev() {

    if (this->prev_n) {

        return (this->prev_n)->remove();
    }

    return this->get_root();
}

/*
 * removes the node that is next to the current node
 */
ld_node *ld_node::remove_next() {

    if (this->next_n) {
        return (this->next_n)->remove();
    }

    return this->get_root();
}

/*
 * removes the current node
 */
ld_node *ld_node::remove() {
    ld_node *temp = NULL;
    if (this->prev_n) {
        (this->prev_n)->next_n = this->next_n;
        temp = this->prev_n;
    }

    if (this->next_n) {
        (this->next_n)->prev_n = this->prev_n;
        temp = this->next_n;
    }

    delete this;
    return temp->get_root();
}

/*
 * allocates space for a new node by id
 * s: id of the node
 * sp: space needed for the node
 */
ld_node *ld_node::allocate(unsigned int s, int sp) {
    ld_node *temp = this->get_root();
    unsigned int start = 0;
    unsigned int end = 0;
    bool used = false;

    while (temp) {
        start = temp->start;
        end = temp->end;
        used = temp->used;
        if (!(temp->used) && s >= start && s <= end) {
            if (start == s && end == s) {
                sp_used = sp;
                used = true;
                return this->get_root();
            } else if (start == s) { 
                sp_used = sp;
                temp->start = s + 1;
                return temp->insert_before(new ld_node(s, s, true, sp));
            } else if (end == s) {
                sp_used = sp;
                temp->end = s - 1;
                return temp->insert_after(new ld_node(s, s, true, 0));
            } else {
                temp->start = s;
                temp->end = s;
                temp->used = true;
                temp->insert_before(new ld_node(start, s - 1, used, sp));
                temp->start = s;
                temp->end = s;
                temp->used = true;
                return temp->insert_after(new ld_node(s + 1, end, used, 0));
            }
        }
        temp = temp->next_n;
    }

    return this->get_root();
}
