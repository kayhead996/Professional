#include "assign3.h"

/*
 * Runs the full filesystem simulation
 * arg_list: List of arguments from the command line, parsed in the main function
 */
void run_sim(string **arg_list) {
    string input;
    string dir = string("./");
    vector<string> input_split = vector<string>();
    vector<int> block_ids = vector<int>();
    vector<tr_node*> children = vector<tr_node*>();
    vector<tr_node*>::iterator trit;
    int d_size = stoi(*(arg_list[DISK_SIZE_IND]));
    int b_size = stoi(*(arg_list[BLK_SIZE_IND]));
    int b_used = 0, d_used = 0, num_blocks = 0, num_bytes = 0, to_remove = 0, frag = 0, tmp_size = 0;
    int max_blocks = 1 + ((d_size - 1)/b_size);
    bool success = false;
    ld_node *ldisk = init_disk(d_size, b_size);
    ld_node *tmp_disk = NULL;
    tr_node *dtree = init_dir_tree(*(arg_list[DIR_NAME_IND]));
    lf_node *lfile = NULL;
    tr_node *curr = dtree;
    tr_node *tmp = NULL;
    init_files(*(arg_list[FILE_NAME_IND]), dtree, ldisk, b_size, d_size, b_used, d_used);
    ldisk->print_out();

    cout << dir << "> ";
    getline(cin, input);
    split(input, " ", input_split);



    while (input.compare("exit") != 0) { 
        if (input_split[0].compare("cd") == 0) {
            if (input_split[1].compare("..") == 0) { 
                tmp = dtree->get_child(get_parent_from_path(dir, 1));
            } else if (input_split[1].compare(".") == 0) {
                tmp = dtree->get_child(dir);
            } else {
                if (input_split[1].back() != '/') {
                    input_split[1].append("/");
                }
                tmp = dtree->get_child((dir + input_split[1]));

                if (!tmp) {
                    tmp = dtree->get_child(input_split[1]);
                }
            }

            if (tmp && tmp->is_dir()) {
                dir = tmp->get_name();
                curr = tmp;
            } else if (!tmp) {
                cout << "cd: \'" << input_split[1] << "\': No such file or directory" << endl;
            } else {
                cout << "cd: \'" << input_split[1] << "\': Not a directory " << endl;
            }
        } else if (input_split[0].compare("ls") == 0) {
            children = curr->get_children();

            for (trit = children.begin(); trit != children.end(); ++trit) {
                cout << (*trit)->get_name() << endl;
            }
        } else if (input_split[0].compare("mkdir") == 0) {
            if (input_split[1].back() != '/') {
                input_split[1].append("/");
            }

            if (dtree->get_child((dir + input_split[1]))) {
                cout << "mkdir: cannot create \'" << input_split[1] << "\': file exists" << endl;
            } else {
                tmp = dtree->get_child(dir);
                tmp->add_child(new tr_node((dir + input_split[1]), 1));
            }

        } else if (input_split[0].compare("create") == 0) {
            if (input_split[1].back() != '/') {
                if (dtree->get_child((dir + input_split[1]))) {
                    cout << "create: cannot create \'" << input_split[1] << "\': file exists" << endl;
                } else {
                    tmp = dtree->get_child(dir);
                    tmp->add_child(new tr_node((dir + input_split[1]), false));
                    tmp->set_time(clock());
                }
            } else {
                cout << "create: cannot create \'" << input_split[1] << "\': invalid file name" << endl;
            }

        } else if (input_split[0].compare("append") == 0) { 
            if (input_split.size() == 3 && input_split[1].back() != '/') {
                tmp = dtree->get_child((dir + input_split[1]));
                num_bytes = stoi(input_split[2]);
                num_blocks = 1 + ((num_bytes - 1)/b_size);

                if (tmp) {
                    if ((num_blocks + b_used) <= max_blocks && (d_used + num_bytes) <= d_size) {
                        d_used += num_bytes;
                        tmp_disk = ldisk;

                        lfile = tmp->get_lfile();
                        if (lfile) {
                            lfile = lfile->get_last();
                            tmp_disk = ldisk->get(lfile->get_id());

                            if (tmp_disk->get_used_space() < b_size) {
                                tmp_size = min(num_bytes, b_size - tmp_disk->get_used_space());
                                tmp_disk->set_used_space(tmp_disk->get_used_space() + tmp_size);
                                num_bytes -= tmp_size;
                                num_blocks -= 1;
                            }
                        }
                        


                        for (; num_blocks > 0; --num_blocks) {
                            for (; tmp_disk; tmp_disk = tmp_disk->get_next()) {
                                if (!(tmp_disk->get_used())) {
                                    tmp_disk->set_used(true);
                                    tmp_disk->set_used_space(min(num_bytes, b_size));
                                    num_bytes -= min(num_bytes, b_size);
                                    b_used += 1;
                                    block_ids.push_back(tmp_disk->get_start());
                                    break;
                                }
                            }
                        }

                        tmp->add_blocks(block_ids, b_size);
                        block_ids.clear();
                        tmp->set_time(clock());
                    } else {
                        cout << "append: Out of space" << endl;
                    }
                } else {
                    cout << "append: \'" << input_split[1] << "\': file not found" << endl;
                }
            } else {
                cout << "append <filename> <bytes> " << endl;
            }
        } else if (input_split[0].compare("remove") == 0) {
            if (input_split.size() == 3 && input_split[1].back() != '/') {
                tmp = dtree->get_child((dir + input_split[1]));
                num_bytes = stoi(input_split[2]);

                if (tmp) {
                    lfile = tmp->get_lfile();

                    for (; lfile->get_next(); lfile = lfile->get_next())
                        ;


                    while (num_bytes > 0) {
                        tmp_disk = ldisk->get(lfile->get_id());
                        to_remove = min(num_bytes, tmp_disk->get_used_space());

                        if (to_remove == tmp_disk->get_used_space()) {
                            tmp_disk->set_used_space(0);
                            tmp_disk->set_used(false);
                            lfile = lfile->get_prev();
                            lfile->remove_next();
                        } else {
                            tmp_disk->set_used_space(tmp_disk->get_used_space() - to_remove);
                        }
                        num_bytes -= to_remove;
                    }
                    d_used -= num_bytes;
                    b_used -= 1 + ((num_bytes - 1)/b_size);

                    tmp->set_size(num_bytes);
                    tmp->set_time(clock());
                } else {
                    cout << "remove: \'" << input_split[1] << "\': file not found" << endl;
                }
            }
        } else if (input_split[0].compare("delete") == 0) {
            tmp = dtree->get_child((dir + input_split[1]));

            if (tmp) {
                children = tmp->get_children();

                if (children.empty()) {
                    num_bytes = tmp->get_size();
                    for (lfile = tmp->get_lfile(); lfile; lfile = lfile->get_next()) {
                        tmp_disk = ldisk->get(lfile->get_id());
                        tmp_disk->set_used(false);
                        tmp_disk->set_used_space(0);
                    }
                    d_used -= num_bytes;
                    b_used -= 1 + ((num_bytes - 1)/b_size);
                    d_used -= num_bytes;
                    success = curr->remove_child((dir + input_split[1]));
                    if (!success) {
                        cout << "delete: cannot remove \'" << (dir + input_split[1]) << "\': No such file" << endl;
                    } else {
                        curr->set_time(clock());
                    }
                } else {
                    cout << "delete: cannot remove \'" << (dir + input_split[1]) << "\': Directory not empty" << endl;
                }
            } else {
                cout << "delete: cannot remove \'" << (dir + input_split[1]) << "\': No such file" << endl;
            }

        } else if (input_split[0].compare("dir") == 0) {
            dtree->print_out();
            cout << endl;
        } else if (input_split[0].compare("prfiles") == 0) {
            dtree->print_files();
        } else if (input_split[0].compare("prdisk") == 0) {
            for (tmp_disk = ldisk; tmp_disk; tmp_disk = tmp_disk->get_next()) {
                if (tmp_disk->get_used() && tmp_disk->get_used_space() < b_size) {
                    frag += (b_size - tmp_disk->get_used_space());
                }
            }

            ldisk->print_out();
            cout << "Fragmentation: " << frag << endl;
            frag = 0;

        }
        input_split.clear();
        cout << dir << "> ";
        getline(cin, input);
        split(input, " ", input_split);
    }

    if (dtree) {
        delete dtree;
    }

    if (ldisk) {
        for (tmp_disk = ldisk; tmp_disk->get_next(); ) {
            tmp_disk->remove_next();
        }

        delete ldisk;
    }

}

/*
 * Splits a string by spaces
 * s: The string to split
 * delim: The character to split on
 * parts: The split string as a vector
 */
void split(const string& s, const string& delim, vector<string>& parts) {
    size_t start, end = 0;
    while (end < s.size()) {
        start = end;
        while (start < s.size() && (delim.find(s[start]) != string::npos)) {
            start++;  // skip initial whitespace
        }
        end = start;
        while (end < s.size() && (delim.find(s[end]) == string::npos)) {
            end++; // skip to end of word
        }
        if (end-start != 0) {
            parts.push_back(string(s, start, end-start));
        }
    }
}
