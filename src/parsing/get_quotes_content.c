#include "pipex.h"

static Cvars	init_cvars(char *command)
{
	Cvars	c_vars;

	c_vars.start = 0;
	c_vars.end = ft_strlen(command);
	c_vars.first_quote = '\0';
	return(c_vars);
}

char	*get_quotes_content(char *command)
{
	Cvars	c_vars;

	c_vars = init_cvars(command);
	while (c_vars.start <= c_vars.end)
	{
		while (command[c_vars.start] && c_vars.start < c_vars.end)
		{
			if (is_quote(command[c_vars.start]))
			{
				if (c_vars.first_quote == '\0')
					c_vars.first_quote = command[c_vars.start];
				if (command[c_vars.start] != c_vars.first_quote)
					return (ft_strndup(command + c_vars.start, c_vars.end - c_vars.start + 1));
				c_vars.quote = command[c_vars.start];
				c_vars.start++;
				break ;
			}
			c_vars.start++;
		}
		while (--c_vars.end >= 0 && command[c_vars.end] == c_vars.quote);//idk about this :)
		if (c_vars.end + 1 != c_vars.start)
			c_vars.real_end = c_vars.end;
		if (!is_quote(command[c_vars.start]))
			break ;
	}
	return (ft_strndup(command + c_vars.start, c_vars.real_end - c_vars.start + 1));
}