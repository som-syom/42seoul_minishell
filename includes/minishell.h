/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:29:42 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/26 21:55:50 by dhyeon           ###   ########.fr       */
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

# define ERROR 0
# define FALSE 0
# define TRUE 1

typedef struct		s_cmd
{
	char			**av;
	int				ac;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_env
{
	char			*key;
	char			*value;
	int				has_equal;
	struct s_env	*next;
}					t_env;

typedef struct		s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct		s_state
{
	t_token			*token_head;
	t_env			*env_head;
	t_cmd			*cmd;
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
int		is_operator(char c);
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

/*
**	export
*/
void	print_export(t_env *env);
void	print_one_export(t_env *head, char *key);
void	update_env(t_env *head, char *key, char *value, int has_equal);
/*
**	export_util
*/
char 	*make_env_string(char *key, char *value, int has_equal);
int		check_env_length(t_env *env);
void	sorted_list(char **list, int size);

char	*ft_strjoin2(char *s1, char *s2);
int		get_next_line(int fd, char **line);

int		builtin(t_state *state, t_cmd *cmd);
int		ft_pwd(t_state *state, t_cmd *cmd);
int		ft_exit(t_state *state, t_cmd *cmd);
int		ft_cd(t_state *s, t_cmd *cmd);
void	ft_echo(t_state *t, t_cmd *cmd);
void	ft_unset(t_state *s, t_cmd *cmd);
void	ft_export(t_state *state, t_cmd *cmd);

int		check_key(char *key);

#endif
