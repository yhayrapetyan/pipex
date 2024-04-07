#include "pipex.h"

int	get_descriptor(char *file_name, char c)
{
	int	descriptor;

	descriptor = -1;
	if (c == 'H')
		descriptor = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (c == 'O')
		descriptor = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (c == 'I')
		descriptor = open(file_name, O_RDONLY);
	if (descriptor == -1)
		ft_error("Can't open the file\n", 17);
	return (descriptor);
}