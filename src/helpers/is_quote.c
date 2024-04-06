#include "pipex.h"

int	is_quote(char ch)
{
	if (ch == '"' || ch == '\'')
		return (1);
	return (0);
}