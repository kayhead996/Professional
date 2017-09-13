#ifndef _TRNODE_H_
#define _TRNODE_H_

#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <time.h>
#include "lfnode.h"

using namespace std;

class tr_node {
    private:
        vector<tr_node*> children;
        lf_node *lfile;
        int size;
        clock_t time_stamp;
        bool dir;
        string name;
    public:
        tr_node() { dir = true; name = "/"; size = 0; }
        tr_node(string n, bool d);
        tr_node(string n, bool d, int s, int b_size, vector<int> block_list, clock_t t);
        vector<tr_node*> get_children() { return children; }
        bool is_dir() { return dir; }
        string get_name() { return name; }
        int get_size() { return size; }
        clock_t get_time() { return time_stamp; }
        void set_name(string n) { name = n; }
        void set_time(clock_t t) { time_stamp = t; }
        void set_size(int s) { size = s; }
        bool add_child(tr_node *c);
        bool remove_child(string c_name);
        tr_node *get_child(string c_name);
        lf_node *get_lfile() { return lfile; }
        void add_blocks(vector<int> block_ids, int b_size);
        void print_out();
        void print_files();
        ~tr_node();
};

#endif
