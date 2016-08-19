#include "MySBBST.hh"
#include "student.hh"

template bool MySBBST<int, int, intintCompare, intintCompare>::add(MySBBSTNode *&, int);
template bool MySBBST<char, char, charcharComp, charcharComp>::add(MySBBSTNode *&, char);
template bool MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::add(MySBBSTNode *&, student); 

template<class Elem, class Key, class EEComp, class KEComp>
bool MySBBST<Elem, Key, EEComp, KEComp>::add(MySBBSTNode *&sr, Elem e) 
{
    bool ret = true;
    if (sr == NULL)
    {
        sr = new MySBBSTNode(e);
    }
    else 
    {
        if (EEComp::lt(e, sr -> val))
        {
            ret = add(sr -> lc, e);
        }
        else
        {
            ret = add(sr -> rc, e);
        }
        checkOrder(sr);
    }
    return ret;
}

template bool MySBBST<int, int, intintCompare, intintCompare>::add(int);
template bool MySBBST<char, char, charcharComp, charcharComp>::add(char);
template bool MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::add(student);

/*
 * Adds a new item to the tree
 * Precondition: The new item is not the zero value of the tree
 * Postcondition: The new item is added to the tree and the tree remains balanced
*/

template<class Elem, class Key, class EEComp, class KEComp>
bool MySBBST<Elem, Key, EEComp, KEComp>::add(Elem e)
{
    if (!EEComp::eq(e, zero))
    {
        add(root, e);
        calcHeight(root);
    }
    return true;
}

