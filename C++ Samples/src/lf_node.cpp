#include "lfnode.h"

/*
 * Deletes every node after and including the current node
 */
lf_node::~lf_node() {
    delete next_n;
    next_n = NULL;
    prev_n = NULL;
}

/*
 * Prints the list of block addresses
 */
void lf_node::print_out() {
    cout << id * b_size;
    if (this->next_n) {
        cout << "->";
        (this->next_n)->print_out();
    } else {
        cout << endl; 
    }
}

/*
 * Gets the root fo the linked list
 */
lf_node *lf_node::get_root() {
    lf_node *temp = this;

    while(temp->prev_n) {
        temp = temp->prev_n;
    }

    return temp;
}

/*
 * Inserts a node at the end of the list
 * node: The node to insert at the end
 */
lf_node *lf_node::insert_at_end(lf_node *node) {
    lf_node *last = this;
    if (node) {
        while (last->next_n) {
            last = last->next_n;
        }

        last->next_n = node;
        node->prev_n = last;
        node->next_n = NULL;
    }

    return this->get_root();
}

/*
 * Inserts a node after the current node
 * node: The node to insert
 */
lf_node *lf_node::insert_after(lf_node *node) {

    if (node) {
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
 * Inserts a node before the current node
 * node: The node to insert before the current node
 */
lf_node *lf_node::insert_before(lf_node *node) {
    if (node) {
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
 * Removes the previous node
 */
lf_node *lf_node::remove_prev() {

    if (this->prev_n) {
        return (this->prev_n)->remove();
    }

    return this->get_root();
}

/*
 * Removes the next node
 */
lf_node *lf_node::remove_next() {

    if (this->next_n) {
        return (this->next_n)->remove();
    }

    return this->get_root();
}

/*
 * Removes the current node
 */
lf_node *lf_node::remove() {
    lf_node *temp = NULL;
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
 * Gets the last node in the list
 */
lf_node *lf_node::get_last() {
    lf_node *tmp = this;

    for (; tmp->get_next(); tmp = tmp->get_next())
        ;

    return tmp;
}
