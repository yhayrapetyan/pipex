#include "pipex.h"

char	*get_quotes_content(char *command)
{
	int		start;
	int		end;
	int		real_end;
	char	quote;

	start = 0;
	end = ft_strlen(command) - 1;
	while (start <= end)
	{
		while (command[start] && start < end)
		{
			if (is_quote(command[start]))
			{
				quote = command[start];
				start++;
				break ;
			}
			start++;
		}
		while (command[end])
		{
			if (command[end] == quote)
			{
				end--;
				break ;
			}
			end--;
		}
		if (end + 1 != start)
			real_end = end;
		if (!is_quote(command[start]))
			break ;
	}
	return (ft_strndup(command + start, real_end - start + 1));
}