#include "MySBBST.hh"
#include "student.hh"

template int MySBBST<int, int, intintCompare, intintCompare>::removeMin(MySBBSTNode *&);
template char MySBBST<char, char, charcharComp, charcharComp>::removeMin(MySBBSTNode *&);
template student MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::removeMin(MySBBSTNode *&);

template<class Elem, class Key, class EEComp, class KEComp>
Elem MySBBST<Elem, Key, EEComp, KEComp>::removeMin(MySBBSTNode *&sr)
{
    Elem ret;

    if (sr -> lc)
    {
        ret = removeMin(sr -> lc);
    }
    else
    {
        ret = sr -> val;
        sr = NULL;
    }
    return ret;
}


