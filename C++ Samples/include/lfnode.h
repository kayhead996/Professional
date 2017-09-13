#ifndef _LFNODE_H_
#define _LFNODE_H_

#include <iostream>

using namespace std;

class lf_node {
    private:
        int id;
        int b_size;
        lf_node *prev_n;
        lf_node *next_n;
        lf_node *get_root();
    public:
        lf_node() { id = 0; b_size = 0; prev_n = NULL; next_n = NULL; }
        lf_node(int i, int b) { id = i; b_size = b; prev_n = NULL; next_n = NULL; }
        int get_id() { return id; }
        lf_node *get_next() { return next_n; }
        lf_node *get_last();
        lf_node *get_prev() { return prev_n; }
        lf_node *insert_after(lf_node *node);
        lf_node *insert_before(lf_node *node);
        lf_node *insert_at_end(lf_node *node);
        lf_node *remove();
        lf_node *remove_prev();
        lf_node *remove_next();
        void print_out();
        ~lf_node();

};

#endif
