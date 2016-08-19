#include "MySBBST.hh"
#include "student.hh"

template void MySBBST<int, int, intintCompare, intintCompare>::rotateLeft(MySBBSTNode *&sr);
template void MySBBST<char, char, charcharComp, charcharComp>::rotateLeft(MySBBSTNode *&sr);
template void MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::rotateLeft(MySBBSTNode *&sr);

template<class Elem, class Key, class EEComp, class KEComp>
void MySBBST<Elem, Key, EEComp, KEComp>::rotateLeft(MySBBSTNode *&sr)
{
    MySBBSTNode *tmp = sr -> rc;
    if (tmp -> lc)
        sr -> rc = tmp -> lc;
    else
        sr -> rc = NULL;

    tmp -> lc = sr;

    sr = tmp;

}

template void MySBBST<int, int, intintCompare, intintCompare>::rotateRight(MySBBSTNode *&sr);
template void MySBBST<char, char, charcharComp, charcharComp>::rotateRight(MySBBSTNode *&sr);
template void MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::rotateRight(MySBBSTNode *&sr);

template<class Elem, class Key, class EEComp, class KEComp>
void MySBBST<Elem, Key, EEComp, KEComp>::rotateRight(MySBBSTNode *&sr)
{
    MySBBSTNode *tmp = sr -> lc;
    
    if (tmp -> rc)
        sr -> lc = tmp -> rc;
    else 
        sr -> lc = NULL;

    tmp -> rc = sr;

    sr = tmp;
}
