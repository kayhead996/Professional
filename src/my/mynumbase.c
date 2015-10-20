#include "my.h"

void my_num_base(int input, char *alpha)
{
    if (alpha)
    {
        long num = 0;
        unsigned int base = 0, i = 0;

        if (input < 0)
        {
            my_char('-');
            if (input == INT_MIN)
                num = (long)INT_MAX + 1;
            else
            {   
                input *= -1;
                num = (long)input;
            }
        }
        else
            num = (long)input;
        if (num > 0)
        {
            for (base = 0; alpha[base] != '\0'; base++)
                ;
            if (base > 1)
                my_num_base_rec(num, base, alpha);
            else
                for (i = 0; i < num; i++)
                    my_char(alpha[0]);
        }
        else
            my_char(alpha[0]);
    }
}
