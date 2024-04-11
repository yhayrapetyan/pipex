#ifndef PIPEX_UTILS_H
# define PIPEX_UTILS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>//delete
# include <stdlib.h>
# include <sys/wait.h>

# define RED "\033[1;31m"
# define YELLOW "\033[1;33m"
# define RESET_COLOR "\033[0m"
# define GREEN "\033[1;32m"

typedef struct quotes_s
{
	int	single_q;
	int	double_q;
}				t_Quotes;

typedef struct q_vars
{
	char	*content;
	char	*bslash_temp;
	char	*command_name;
	char	**temp;
	char	**cwo;
	char	**name;
}				t_Qvars;

typedef struct e_vars
{
	char	**cmd_args;
	char	*cmd_path;
	char	**bin_paths;
	int		is_path_allocated;
}				t_Evars;

typedef struct c_vars
{
	int		start;
	int		end;
	int		real_end;
	char	quote;
	char	first_quote;
}				t_Cvars;

typedef struct p_vars
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;
}				t_Pvars;

typedef struct o_vars
{
	char	**result;
	int		len;
	int		i;
}				t_Ovars;

typedef struct b_vars
{
	int		in_file;
	int		out_file;
	int		i;
	int		j;
	int		status;
	pid_t	*status_arr;

}				t_Bvars;
#endif