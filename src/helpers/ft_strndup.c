#include "pipex.h"

char	*ft_strndup(const char *str, int n)
{
	int		i;
	char	*copy;

	copy = (char *)malloc(sizeof(char) * (n + 1));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
