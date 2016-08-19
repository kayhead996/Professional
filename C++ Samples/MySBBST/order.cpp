#include "MySBBST.hh"
#include "student.hh"

template void MySBBST<int, int, intintCompare, intintCompare>::checkOrder(MySBBSTNode *&);
template void MySBBST<char, char, charcharComp, charcharComp>::checkOrder(MySBBSTNode *&);
template void MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::checkOrder(MySBBSTNode *&);

template<class Elem, class Key, class EEComp, class KEComp>
void MySBBST<Elem, Key, EEComp, KEComp>::checkOrder(MySBBSTNode *&sr)
{
    calcHeight(root);
    if (sr)
    {
        int order = calcOrder(sr);
        int orderLC = 0;
        int orderRC = 0;

        if (sr -> lc)
            orderLC = calcOrder(sr -> lc);
        if (sr -> rc)
            orderRC = calcOrder(sr -> rc);

        if (order < -1 && orderLC < 0)
        {
            /*cout<<"LL Issue"<<endl;
            cout<<"Value: "<<sr -> val<<" Order: "<<order<<endl;*/
            rotateRight(sr);
        }
        else if (order > 1 && orderRC > 0)
        {
            /*cout<<"RR Issue"<<endl;
            cout<<"Value: "<<sr -> val<<" Order: "<<order<<endl;*/
            rotateLeft(sr);
        }
        else if (order < -1 && orderLC > 0) 
        {
           // cout<<"LR Issue"<<endl;
            rotateLeft(sr -> lc);
            rotateRight(sr);
        }
        else if (order > 1 && orderRC < 0)
        {
           // cout<<"RL Issue"<<endl;
            rotateRight(sr -> rc);
            rotateLeft(sr);
        }
    }

}

template int MySBBST<int, int, intintCompare, intintCompare>::calcOrder(MySBBSTNode *);
template int MySBBST<char, char, charcharComp, charcharComp>::calcOrder(MySBBSTNode *);
template int MySBBST<student, unsigned int, studentStudentComp, uintStudentComp>::calcOrder(MySBBSTNode *);

template<class Elem, class Key, class EEComp, class KEComp>
int MySBBST<Elem, Key, EEComp, KEComp>::calcOrder(MySBBSTNode *sr)
{
    int order = 0;

    if (sr && sr -> lc && sr -> rc)
    {
        order = ((sr -> rc) -> height - (sr -> lc) -> height);
    }
    else if (sr && sr -> lc) 
    {
        order = -((sr -> lc) -> height) - 1;
    }
    else if (sr && sr -> rc)
    {
        order = ((sr -> rc) -> height) + 1;
    }

    return order;
}
