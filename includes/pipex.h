/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:07:30 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/03/20 18:07:31 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define RED "\033[1;31m"
# define YELLOW "\033[1;33m"
# define RESET_COLOR "\033[0m"
# define GREEN "\033[1;32m"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>//delete
# include <stdlib.h>
#include <sys/wait.h>

typedef struct	quotes_s
{
	int	single_q;
	int	double_q;
}				Quotes;

typedef struct	q_vars
{
	char	*content;
	char	*bslash_temp;
	char	*command_name;
	char	**temp;
	char	**cwo;
	char	**name;
}				Qvars;

typedef struct	e_vars
{
	char	**cmd_args;
	char	*cmd_path;
	char	**bin_paths;
	int		is_allocated;
}				Evars;

typedef struct	c_vars
{
	int		start;
	int		end;
	int		real_end;
	char	quote;
	char	first_quote;
}				Cvars;

typedef struct	p_vars
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;
}				Pvars;

// HELPERS
void	clean_and_exit(char **content, char ***temp, char ***result, char ***name);
void	clean_vars(char **content, char ***temp, char ***result, char ***name);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	*ft_strstr(char *str, char *to_find);
void	ft_error(char *message, int status);
char	*ft_strndup(const char *str, int n);
void	execute(char *command, char **env);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
int		ft_strchr(char *s, int c);
void	free_split(char **str);
int     ft_strlen(char *str);
int		is_quote(char ch);

//PARSING
char	**get_command_with_options(char *command_name, char **arr);
char	*get_bin_path(Evars *e_vars, char **env);
void	get_args(Evars *e_vars, char *command);
void	get_path(Evars *e_vars, char **env);
char	*get_quotes_content(char *command);
char	*remove_back_slash(char *quote);
char	**quotes_parse(char *command);
char	**simple_parse(char *command);
char	*get_joined_name(char **arr);
Qvars	init_vars(void);

// VALIDATION
char    *check_command_access(Evars *e_vars);

// BONUS
pid_t	out_process(char *command, char **env, int file_out);
pid_t	in_processes(char *command, char **env);
int		get_descriptor(char *file_name, char c);
void	here_doc(char *limiter, int argc);

// GNL
char	*gnl_strjoin(char *s1, char *s2);
char	*get_new_left_str(char *str);
char	*get_next_line(int fd);
char	*get_line(char *str);

#endif
