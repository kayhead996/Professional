#include "MySBBST.hh"
#include "student.hh"

template int MySBBST<int, int, intintCompare, intintCompare>::calcHeight(MySBBSTNode *&);
template int MySBBST<char, char, charcharComp, charcharComp>::calcHeight(MySBBSTNode *&);
template int MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::calcHeight(MySBBSTNode *&);

template<class Elem, class Key, class EEComp, class KEComp>
int MySBBST<Elem, Key, EEComp, KEComp>::calcHeight(MySBBSTNode *&sr)
{

    if (sr -> lc && sr -> rc)
        sr -> height = max(calcHeight(sr -> lc), calcHeight(sr -> rc)) + 1;
    else if (sr -> lc)
        sr -> height = calcHeight(sr -> lc) + 1; 
    else if (sr -> rc)
    {
        sr -> height = calcHeight(sr -> rc) + 1; 
    }
    else
    {
        sr -> height = 0;
    }

    return sr -> height;
}
