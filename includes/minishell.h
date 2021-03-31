/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:29:42 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/31 17:52:20 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/types.h>
# include <dirent.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define GNL_SUCCESS 1
# define GNL_EOF 0
# define GNL_ERROR -1

# define COMMON 0
# define SPACE 1
# define SINGLE 2
# define DOUBLE 3
# define LEFT 4
# define RIGHT 5
# define DOUBLERIGHT 6
# define SEMICOLON 7
# define PIPE 8
# define BACKSLASH 9

# define ERROR 0
# define FALSE 0
# define TRUE 1

typedef struct s_path
{
		char			*path;
		struct s_path	*next;
}					t_path;

typedef struct s_cmd
{
	char			**av;
	int				ac;
	int				type;
	int				pip[2];
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				has_equal;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct s_state
{
	t_token			*token_head;
	t_env			*env_head;
	t_cmd			*cmd;
	t_path			*path_head;
	char			*input;
	int				ret;
}					t_state;

/*
**	main
*/
void	init_state(t_state *state);

/*
**	signal
*/
void	handle_signal(int signo);

/*
**	prompt
*/
void	prompt(t_state *state);

/*
**	tokenizer
*/
void	tokenizer(t_state *state);
int		make_token(t_state *state, int count, int i, int type);
void	add_token_back(t_token **head, char *str, int type);
t_token	*create_token(char *str, int type);
/*
**	token_util
*/
int		is_operator(char *c, int i);
int		get_len(char *input, int i);
int		find_end(char *input, int type, int i);

/*
**	env
*/
void	parse_env(char **envp, t_state *state);
void	add_env_back(t_env **head, char *key, char *value, int has_equal);
t_env	*create_env(char *key, char *value, int has_equal);
t_env	*find_env(t_env *head, char *key);
void	print_env_all(t_env *head);
char	*find_env_val(t_env *head, char *key);
int		ft_strcmp(char *s1, char *s2);

/*
**	export
*/
void	print_export(t_env *env);
void	print_one_export(t_env *head, char *key);
void	update_env(t_env *head, char *key, char *value, int has_equal);
/*
**	export_util
*/

char	*make_env_string(char *key, char *value, int has_equal);
int		check_env_length(t_env *env);
void	sorted_list(char **list, int size);

char	*ft_strjoin2(char *s1, char *s2);
int		get_next_line(int fd, char **line);

/*
**	builtin
*/

int		builtin(t_state *state, t_cmd *cmd);
int		ft_pwd(t_state *s, t_cmd *cmd);
int		ft_pwd(t_state *state, t_cmd *cmd);
int		ft_exit(t_state *state, t_cmd *cmd);
int		ft_cd(t_state *s, t_cmd *cmd);
void	ft_echo(t_state *t, t_cmd *cmd);
void	ft_unset(t_state *s, t_cmd *cmd);
void	ft_export(t_state *state, t_cmd *cmd);

int		check_key(char *key);
int		find_command(t_state *s, t_cmd *cmd);

/*
**	path
*/

void	parse_path(t_state *state);
void	add_path_back(t_path **head, char *path_str);
t_path	*create_path(char *path_str);

/*
**	cmd
*/

void	make_path(t_cmd *cmd, char *str);
int		find_command(t_state *s, t_cmd *cmd);
int		builtin(t_state *s, t_cmd *cmd);
void	parse_cmd(t_state *state);
void	add_cmd_back(t_cmd **head, char **av, int ac, int type);
t_cmd	*create_cmd(char **av, int ac, int type);

#endif
