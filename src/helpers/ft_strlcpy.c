#include "pipex.h"

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
    int	i;
    int	j;

    i = 0;
    j = 0;
    while (src[j])
        j++;
    if (dstsize != 0)
    {
        while (src[i] && (i < (dstsize - 1)))
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    }
    return (j);
}