/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llim <llim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:55:03 by llim              #+#    #+#             */
/*   Updated: 2021/04/07 23:43:55 by llim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(t_state *state)
{
	int		type;
	int		count;
	int		i;

	i = 0;
	while (state->input[i])
	{
		if (!(type = is_operator(state->input, i)))
			count = get_len(state->input, i);
		else if (type == DOUBLERIGHT || type == BACKSLASH)
			count = 2;
		else if (type == SINGLE || type == DOUBLE)
		{
			if (!(count = find_end(state->input, type, ++i)))
			{
				printf("따옴표 에러\n");
				return ;
			}
		}
		else
			count = 1;
		i = make_token(state, count, i, type);
	}
	parse_cmd(state);
}

int		make_token(t_state *state, int count, int i, int type)
{
	char	*token_str;
	int		j;

	if (!ft_calloc(count + 1, sizeof(char), (void *)& token_str))
		return (0);
	j = 0;
	while (j < count)
		token_str[j++] = state->input[i++];
	token_str[j] = '\0';
	add_token_back(&state->token_head, token_str, type);
	free(token_str);
	return (i);
}

void	add_token_back(t_token **head, char *str, int type)
{
	t_token *token;
	int		i;

	if (type == SINGLE || type == DOUBLE)
		str[ft_strlen(str) - 1] = '\0';
	else if (type == BACKSLASH)
	{
		i = 0;
		str[i] = str[i + 1];
		str[i + 1] = '\0';
	}
	if (*head == NULL)
		*head = create_token(str, type);
	else
	{
		token = *head;
		while (token->next)
			token = token->next;
		token->next = create_token(str, type);
	}
}

t_token	*create_token(char *str, int type)
{
	t_token *token;

	if (!ft_calloc(1, sizeof(t_token), (void *)& token))
		return (0);
	if (token == NULL)
		return (0);
	token->str = ft_strdup(str);
	token->type = type;
	token->next = 0;
	return (token);
}