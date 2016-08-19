#include "MySBBST.hh"
#include "student.hh"

template int MySBBST<int, int, intintCompare, intintCompare>::remove(MySBBSTNode *&, int);
template char MySBBST<char, char, charcharComp, charcharComp>::remove(MySBBSTNode *&, char);
template student MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::remove(MySBBSTNode *&, unsigned int);

template<class Elem, class Key, class EEComp, class KEComp>
Elem MySBBST<Elem, Key, EEComp, KEComp>::remove(MySBBSTNode *&sr, Key k) 
{
    Elem tmp = zero;
    if (KEComp::eq(k, (sr -> val)))
    {
        if (sr -> rc && sr -> lc)
        {
            tmp = sr -> val;
            sr -> val = removeMin(sr -> rc);
        }
        else if (sr -> rc)
        {
            tmp = sr -> val;
            sr = sr -> rc;
        }
        else if (sr -> lc)
        {
            tmp = sr -> val;
            sr = sr -> rc;
        } else {
            tmp = sr -> val;
            sr = NULL;
        }
        calcOrder(sr);
    } else if (KEComp::gt(k, (sr -> val)))
    {
        if (sr -> rc)
            tmp = remove(sr -> rc, k);
    } else if (KEComp::lt(k, (sr -> val)))
    {
        if (sr -> lc)
            tmp = remove(sr -> lc, k);
    }
        

    return tmp;
        
}
template int MySBBST<int, int, intintCompare, intintCompare>::remove(int);
template char MySBBST<char, char, charcharComp, charcharComp>::remove(char);
template student MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::remove(unsigned int);

/*
 * Removes a value from the tree and keeps the tree balanced
 * Precondition: The Key passed is not null and the tree exists
 * Postcondition: The value with Key k is removed and returned, the tree remains balanced.
 */

template<class Elem, class Key, class EEComp, class KEComp>
Elem MySBBST<Elem, Key, EEComp, KEComp>::remove(Key k)
{
    Elem e = zero;
    if (k && root)
    {
        e = remove(root, k);
        calcHeight(root);
    }

    return e;
}

