/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:15:29 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/15 11:15:31 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define WAIT_ERR 			"Waitpid Failed\n"
# define MALLOC_ERR 		"Allocation Failed\n"
# define ARG_ERR			"Invalid number of arguments\n"
# define WRT_PERM_ERR		"No write permission\n"
# define FILE_OPEN_ERR		"Can't open the file\n"
# define PIPE_CLOSE_ERR		"Can't close the pipe\n"
# define PIPE_CREATE_ERR	"Can't create the pipe\n"
# define FORK_CREATE_ERR	"Can't create the child process\n"
# define DUP_ERR			"Can't duplicate the descriptor\n"
# define EXEC_ERR			"Can't execute the command\n"
# define CMD_NOT_FOUND_ERR	"Command not found\n"

# define WAIT_STAT 			2
# define MALLOC_STAT 		3
# define ARG_STAT			4
# define WRT_PERM_STAT		1
# define FILE_OPEN_STAT		6
# define PIPE_CLOSE_STAT	7
# define PIPE_CREATE_STAT	8
# define FORK_CREATE_STAT	9
# define DUP_STAT			10
# define EXEC_STAT			126
# define CMD_NOT_FOUND_STAT	127

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
