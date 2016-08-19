#include "my.h"

char **my_str2vect(char *str)
{
    int size = 0, i = 0, j = 0, k = 0;
    char **vect = NULL;

    if (str)
    {
        for (i = 0; str[i] != '\0'; i++)
            if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
                size++;

        if (size > 0)
        {
            size++;

            vect = (char **)malloc(size * sizeof(char *));
            for (i = 0; str[i] != '\0'; i++) 
            {
                if (i == 0 || str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
                    for (j = i; str[j] != ' ' && str[j] != '\t' && str[j] != '\n' && str[j] != '\0'; j++)
                        ;
                vect[i] = (char *)malloc(j * sizeof(char));
            }
            for (i = 0, j = 0; i < size; i++, j++)
            {
                for (k = 0; str[j] != ' ' && str[j] != '\t' && str[j] != '\n' && str[j] != '\0'; j++, k++)
                        *(*(vect + i) + k) = str[j];
                *(*(vect + i) + k) = '\0';
            }
            vect[i] = NULL;
        }
    }

    return vect;
}
