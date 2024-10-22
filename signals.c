/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:24:28 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 10:06:09 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_file/execution.h"
#include "header_file/global_header.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	sigint_handler(int sig)
{
	g_global.error_num = 128 + sig;
	if (!g_global.in_heredoc)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (g_global.on_going_cmd)
	{
		g_global.stop_heredoc = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	g_global.error_num = 128 + sig;
	ft_putstr_fd("Quit: (core dumped)", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	init_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
