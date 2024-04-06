#include "pipex.h"

static int	get_bslash_count(char *quote)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (quote[i])
	{
		i++;
		if (quote[i] == '\\')
			continue ;
		count++;
	}
	return (count);
}

char	*remove_back_slash(char *quote)
{
	int		i;
	int		j;
	int		count;
	char	*res;

	count = get_bslash_count(quote);
	res = (char *)malloc(sizeof(char *) * (count + 1));
	if (!res)
		NULL;
	i = 0;
	j = 0;
	while (quote[i])
	{
		if (quote[i] != '\\')
		{
			res[j] = quote[i];
			j++;
		}
		i++;
	}
	res[i] = '\0';
	return (res);
}