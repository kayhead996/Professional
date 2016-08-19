#ifndef _MYSBBST_H_
#define _MYSBBST_H_

#include <iostream>
#include <cstring>
using namespace std;

template<class Elem, class Key, class EEComp, class KEComp>
class MySBBST
{
    private:
        class MySBBSTNode
        {
            public:
                MySBBSTNode *lc;
                MySBBSTNode *rc;
                Elem val;
                int height;
                MySBBSTNode(Elem e) { lc = NULL; rc = NULL; val = e; height = 0;}
        };
        Elem zero;
        MySBBSTNode *root;
        bool add(MySBBSTNode *&sr, Elem e);
        Elem search(MySBBSTNode *sr, Key k);
        Elem remove(MySBBSTNode *&sr, Key k);
        Elem removeMin(MySBBSTNode *&sr);
        void printOut(MySBBSTNode *sr);
        void rotateRight(MySBBSTNode *&sr);
        void rotateLeft(MySBBSTNode *&sr);
        void checkOrder(MySBBSTNode *&sr);
        int calcHeight(MySBBSTNode *&sr);
        int calcOrder(MySBBSTNode *sr);
    public:
        MySBBST(Elem z) { root = NULL; zero = z; }
        bool add(Elem e);
        Elem search(Key k);
        Elem remove(Key k);
        void printout();
};

class intintCompare
{
    public:
        static bool lt(int, int);
        static bool gt(int, int);
        static bool eq(int, int);
        static int max(int, int);
};

class charcharComp
{
    public:
        static bool lt(char, char);
        static bool gt(char, char);
        static bool eq(char, char);
};
#endif

