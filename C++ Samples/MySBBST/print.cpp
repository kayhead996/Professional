#include "MySBBST.hh"
#include "student.hh"

template void MySBBST<int, int, intintCompare, intintCompare>::printOut(MySBBSTNode *);
template void MySBBST<char, char, charcharComp, charcharComp>::printOut(MySBBSTNode *);
template void MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::printOut(MySBBSTNode *);


template<class Elem, class Key, class EEComp, class KEComp>
void MySBBST<Elem, Key, EEComp, KEComp>::printOut(MySBBSTNode *sr)
{
    if (sr)
    {
      
        if (sr != root)
            cout<<"(";
        printOut(sr -> lc);
        cout<<" "<<sr -> val<<":"<<calcOrder(sr)<<" ";
        printOut(sr -> rc);
        if (sr != root)
            cout<<")";
    }
        
}

template void MySBBST<int, int, intintCompare, intintCompare>::printout();
template void MySBBST<char, char, charcharComp, charcharComp>::printout();
template void MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::printout();

/* Prints the whole tree using in order traversal
 * Precondition: The tree is not null.
 * Postcondition: The tree will remain the same as before.
 */
template<class Elem, class Key, class EEComp, class KEComp>
void MySBBST<Elem, Key, EEComp, KEComp>::printout()
{
    if (root)
        printOut(root);
    cout<<endl;
}
