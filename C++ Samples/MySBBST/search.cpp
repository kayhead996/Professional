#include "MySBBST.hh"
#include "student.hh"

template int MySBBST<int, int, intintCompare, intintCompare>::search(MySBBSTNode*, int);
template char MySBBST<char, char, charcharComp, charcharComp>::search(MySBBSTNode*, char);
template student MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::search(MySBBSTNode*, unsigned int);

template<class Elem, class Key, class EEComp, class KEComp>
Elem MySBBST<Elem, Key, EEComp, KEComp>::search(MySBBSTNode* sr, Key k)
{
    Elem item = zero;

    if (KEComp::eq(k, sr -> val))
        item = sr -> val;
    else if (KEComp::lt(k, sr -> val))
    {   
        if (sr -> lc)
            item = search(sr -> lc, k);
    } else if (KEComp::gt(k, sr -> val)) 
    {
        if (sr -> rc)
            item = search(sr -> rc, k);
    }

    return item;

}

template int MySBBST<int, int, intintCompare, intintCompare>::search(int);
template char MySBBST<char, char, charcharComp, charcharComp>::search(char);
template student MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::search(unsigned int);

/* 
 * Searches for a value in the tree
 * Precondition: The Key passed is a valid Key and the tree exists.
 * Postcondition: The tree is not changed, the value with Key k is returned.
 */
template<class Elem, class Key, class EEComp, class KEComp>
Elem MySBBST<Elem, Key, EEComp, KEComp>::search(Key k)
{
    if (k && root)
        return search(root, k);
    return zero;
         
}
