#include "my.h"

void my_int(int i)
{
    int tmp = i, base = 1, digit = 0;
    if (i < 0) 
        my_char('-');
    for (; tmp; tmp /= 10)
        base = (tmp > 10 || tmp < -10)? base * 10: base;
    for (; base > 0; base /= 10)
    {
        digit = (i < 0)? -1 * (i / base): (i / base);
        i = (i < 0)? -1 * (i % (-1 * base)): i % base;
        my_char('0' + digit);
    }
}
