/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyeon <dhyeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:26:45 by dhyeon            #+#    #+#             */
/*   Updated: 2021/03/26 21:39:46 by dhyeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	t_state	state;

	(void)argc;
	(void)argv;
	init_state(&state);
	signal(SIGINT, (void *)handle_signal);
	signal(SIGQUIT, (void *)handle_signal);
	parse_env(envp, &state);
	while (1)
	{
		prompt(&state);
		builtin(&state, state.cmd); // 임시파일
		// tokenizer(&state);
		// state.token_head = 0; // 토큰 전체 프리해줘야함.
	}
}

void	init_state(t_state *state)
{
	state->token_head = 0;
	state->env_head = 0;
	state->input = 0;
	state->ret = 0;
}
