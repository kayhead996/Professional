#ifndef _LDNODE_H_
#define _LDNODE_H_

#include <iostream>

using namespace std;

class ld_node {
    private:
        int start;
        int end;
        bool used;
        int sp_used;
        ld_node *prev_n;
        ld_node *next_n;
        ld_node *get_root();
    public:
        ld_node() { start = 0; end = 0; used = false; next_n = NULL; prev_n = NULL; }
        ld_node(int s, int e, bool u, int sp) { start = s; end = e; used = u; next_n = NULL; prev_n = NULL; sp_used = sp;}
        int get_start() { return start; }
        int get_end() { return end; }
        int get_used_space() { return sp_used; }
        bool get_used() { return used; };
        ld_node *get(int id);
        void set_used_space(int sp) { sp_used = sp; }
        ld_node *set_used(bool u) { used = u; return get_root(); }
        ld_node *get_next() { return next_n; }
        ld_node *get_prev() { return prev_n; }
        ld_node *insert_after(ld_node *node);
        ld_node *insert_before(ld_node *node);
        ld_node *insert_at_end(ld_node *node);
        ld_node *remove();
        ld_node *remove_prev();
        ld_node *remove_next();
        ld_node *allocate(unsigned int s, int sp);
        void print_out();
        void print_every_block();
        ~ld_node();

};

#endif
