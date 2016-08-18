#include "my.h"

char *my_strreplace(char *orig, char *replace, char *to)
{
    int totalLength = 0, startIndex = 0, endIndex = 0, foundStart = 0, i = 0, j = 0, k = 0;
    char *ret;

    totalLength = my_strlen(orig) - my_strlen(replace) + my_strlen(to) + 1;


    for (i = 0; orig[i] != '\0'; i++)
    {
        if (replace[j] == '\0')
            break;
        if (replace[0] == orig[i] && !foundStart)
        {
            startIndex = i;
            foundStart = 1;
        }
        if (foundStart && replace[j] == orig[i])
        {
            endIndex++;
            j++;
        }
        else if (replace[j] != orig[i])
        {
            endIndex = 0;
            j = 0;
            foundStart = 0;
        }
    }

    if (endIndex > startIndex && (endIndex - startIndex) >= my_strlen(replace))
    {
        ret = (char *)malloc(totalLength * sizeof(char));
    
        for (i = 0, j = 0, k = 0; orig[i] != '\0'; i++)
        {
            if (i >= startIndex && i < endIndex)
                for (; to[k] != '\0'; k++)
                    ret[j++] = to[k];
            else
                ret[j++] = orig[i];
        }
    }

    return ret;
}
