#include "MySBBST.hh"

/**
 * Precondtition: x and y are integers.
 * Postcondtion: returns whether x is less than y or not.
 */
bool intintCompare::lt(int x, int y)
{
    if (x && y)
        return x < y;
    return false;
}
/**
 * Precondtition: x and y are integers.
 * Postcondtion: returns whether x is greater than y or not.
 */
bool intintCompare::gt(int x, int y)
{
    if (x && y)
        return x > y;
    return false;
}
/**
 * Precondtition: x and y are integers.
 * Postcondtion: returns whether x is equal to y or not.
 */
bool intintCompare::eq(int x, int y)
{
    if (x && y)
        return (x == y);
    return false;
}
/**
 * Precondtition: s1 and s2 are non null char pointers.
 * Postcondtion: returns whether s1 is less than s2 or not.
 */
bool charcharComp::lt(char c1, char c2)
{
    if (c1 && c2)
        return c1 < c2;
    return false;
}
/**
 * Precondtition: s1 and s2 are non null char pointers.
 * Postcondtion: returns whether s1 is greater than s2 or not.
 */
bool charcharComp::gt(char c1, char c2)
{
    if (c1 && c2)
        return c1 > c2;
    return false;
}
/**
 * Precondtition: s1 and s2 are non null char. 
 * Postcondtion: returns whether s1 is equal to s2 or not.
 */
bool charcharComp::eq(char c1, char c2)
{
    if (c1 && c2)
        return c1 == c2;
    return false;
}
