/*
 * Keyur Ved
 * CS 182-A
 * "I pledge my honor that I have abided by the Stevens Honor System"
 */
#include<iostream>
#include<cstring>
#include "MySBBST.hh"
#include "student.hh"
#include<climits>
using namespace std;

/*
 * Tests the tree with student input values
 * Precondition: None
 * Postcondition: All functions are tested
 */
void studentTest()
{
    student zero;
    MySBBST<student, unsigned int, studentStudentComp, uintStudentComp> tree1(zero);
    student s1("Lionel", "Messi", 10);
    student s2("Neymar", "Jr", 11);
    student s3("Luis", "Suarez", 9);
    student s4("Andres", "Iniesta", 8);
    student s5("Ivan", "Rakitic", 4);
    student s6("Gerard", "Pique", 3);
    student s7("Marc", "Andre Ter-Stegen", 1);
    student s8("Sergio", "Busquets", 5);
    student s9("Dani", "Alves", 22);
    student s10("Jordi", "Alba", 18);
    student s11("Javier", "Mascherano", 14);

    cout<<"Printing empty tree: ";
    tree1.printout();

    tree1.add(s1);
    tree1.add(s2);
    tree1.add(s3);
    tree1.add(s4);
    tree1.add(s5);
    tree1.add(s6);
    tree1.add(s7);
    tree1.add(s8);
    tree1.add(s9);
    tree1.add(s10);
    tree1.add(s11);
    tree1.add(zero);
    cout<<"Printing tree with values: "<<endl;
    tree1.printout();
    cout<<"Removed: "<<tree1.remove(11)<<endl;
    cout<<"Tried to remove 19: "<<tree1.remove(19)<<endl;
    tree1.printout();
    cout<<"Searched for 9: "<<tree1.search(9)<<endl;
    cout<<"Searched for 11: "<<tree1.search(11)<<endl;
    cout<<"Tried to remove 0 "<<tree1.remove(0)<<endl;
    cout<<"Tried to remove 12 "<<tree1.remove(12)<<endl;
    tree1.printout();
}

/*
 * Tests the tree with int input values
 * Precondition: None
 * Postcondition: All functions are tested
 */
void intTest()
{
    MySBBST<int, int, intintCompare, intintCompare> tree2(0);
    

    cout<<"Tried to remove 1"<<tree2.remove(1)<<endl;
    cout<<"Printing empty tree: ";
    tree2.printout();

    int arr[] = {1, 3, 2, 3, 9, 10, 34, 90, 35, 234, 54, 5}; 
    for (int i = 0; i < 12; i++)
        tree2.add(arr[i]);
    cout<<"Printing tree with values: "<<endl;
    tree2.printout();
    cout<<"Searching for 10"<<endl;
    cout<<"Found "<<tree2.search(10)<<endl;
    cout<<"Searching for 14"<<endl;
    cout<<"Found "<<tree2.search(14)<<endl;
    cout<<"Removed: "<<tree2.remove(34)<<endl;
    tree2.printout();
}

int main(void)
{   
    cout<<"\nTesting student case"<<endl;
    studentTest();
    cout<<"\nTesting integer case"<<endl;
    intTest();

    return 0;

}
