#include "pipex.h"

static Quotes	get_quotes_count(char *command)
{
	Quotes	quotes;
	int		i;

	quotes.single_q = 0;
	quotes.double_q = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '"')
			quotes.double_q++;
		if (command[i] == '\'')
			quotes.single_q++;
		i++;
	}
	return (quotes);
}

char	**get_name(char *command)
{
	Quotes	quotes_count;
	char	**name;

	quotes_count = get_quotes_count(command);
	if (quotes_count.single_q > 1 || quotes_count.double_q > 1)
		name = quotes_parse(command);
	else
		name = simple_parse(command);
	return (name);
}
