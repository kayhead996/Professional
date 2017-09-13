#include "assign3.h"

/*
 * inits the ldisk
 * d_size: the disk size
 * b_size: the block size
 */
ld_node *init_disk(int d_size, int b_size) {
    int num_blocks = 1 + ((d_size - 1) / b_size);
    ld_node *ldisk = new ld_node(0, 0, false, 0);

    for (int i = 1; i <= num_blocks; i++) {
        ldisk->insert_at_end(new ld_node(i, i, false, 0));
    }

    return ldisk;
}

/*
 * inits the files from input file list
 * file_fname: name of the file
 * dtree: previously initialized dir tree
 * ldisk: prev init block list
 * b_size: block size
 * d_size: disk size
 * block_used: num of blocks used
 * d_used: disk space used
 */
void init_files(string file_fname, tr_node *&dtree, ld_node *&ldisk, int b_size, int d_size, int &block_used, int &d_used) {
    ifstream filelist(file_fname);
    vector<int> block_list;
    string temp, fname;
    int i = 0, tmp_size = 0, size = 0, num_blocks = 0, used = 0, b_used = 0, sp_used = 0;
    int total_blocks = 1 + ((d_size - 1) / b_size);
    ld_node *temp_node = ldisk;
    tr_node *parent = NULL;

    while (filelist >> temp) {
        if (i == 6) {
            size = stoi(temp);
        } else if (i == 10) {
            fname = temp;
            i = -1;

            if ((used + size) < d_size) {
                num_blocks = 1 + ((size - 1) / b_size);

                if ((b_used + num_blocks) < total_blocks) {
                    used += size;
                    tmp_size = size;
                    b_used += num_blocks;
                    for (temp_node = ldisk; num_blocks > 0 && temp_node != NULL; temp_node = temp_node->get_next()) {
                        if (!temp_node->get_used()) {
                            sp_used = min(b_size, tmp_size);
                            temp_node->set_used(true);
                            temp_node->set_used_space(sp_used);
                            tmp_size -= sp_used;
                            block_list.push_back(temp_node->get_start());
                            num_blocks--;
                        }
                    }

                    parent = dtree->get_child(get_parent_from_path(fname, false));
                    parent->add_child(new tr_node(fname, false, size, b_size, block_list, clock()));
                }
            }
            block_list.clear();
        }


        ++i;
    }

    block_used = b_used;
    d_used = used;

}

/*
 * initializes the directory tree
 * dir_fname: name of the directory list file
 */
tr_node *init_dir_tree(string dir_fname) {
    ifstream dirfile(dir_fname);
    vector<string> dirs; 
    vector<string>::iterator it;
    string::iterator sit;
    string dname;
    tr_node *dir_tree = NULL;
    tr_node *parent = NULL;

    while (dirfile >> dname) {
        if (dname.back() != '/') {
            dname.append("/");
        }
        dirs.push_back(dname);
    }
    dirfile.close();


    dir_tree = new tr_node(dirs[0], 1);


    for (it = dirs.begin() + 1; it != dirs.end(); ++it) {
        dname = get_parent_from_path((*it), true);

        if (dname.back() != '/') {
            dname.append("/");
        }
        parent = dir_tree->get_child(dname);
        parent->add_child(new tr_node((*it), 1));
    }

    dirs.clear();


    return dir_tree;

}

/*
 * parses string to get parent directory from path
 * dstring: directory string
 * dir: if its a directory or not
 */
string get_parent_from_path(string dstring, bool dir) {
    string::iterator sit = dstring.end();
    int num_found = 0;

    for (; sit != dstring.begin() - 1; --sit) {
        if (*sit == '/') {
            ++num_found;
        }

        if (dir && num_found == 2) {
            return string(dstring.begin(), sit + 1);
        } else if (!dir && num_found == 1) {
            return string(dstring.begin(), sit + 1);
        }
    }

    return NULL;
}
