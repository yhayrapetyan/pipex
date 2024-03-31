#include "pipex.h"

static int	is_in_set(char const ch, char const *set)
{
    int	i;

    i = 0;
    while (set[i])
    {
        if (set[i] == ch)
            return (1);
        i++;
    }
    return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
    char	*ch;
    int		i;
    int		len;

    if (s1 == NULL)
        return (NULL);
    i = 0;
    while (s1[i] && is_in_set(s1[i], set))
        i++;
    len = ft_strlen(s1) - 1;
    while (len > 0 && is_in_set(s1[len], set))
        len--;
    if (len < i)
    {
        ch = (char *)malloc(1);
        ch[0] = '\0';
        return (ch);
    }
    ch = (char *)malloc(sizeof(char) * (len - i + 2));
    if (ch == NULL)
        return (NULL);
    ft_strlcpy(ch, &s1[i], len - i + 2);
    return (ch);
}