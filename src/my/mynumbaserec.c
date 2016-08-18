#include "my.h"

void my_num_base_rec(long input, int base, char *alpha)
{
    if (input > 0)
    {
        my_num_base_rec(input / base, base, alpha);
        my_char(alpha[input % base]);
    }
}
