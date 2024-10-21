/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:57:48 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/21 12:19:12 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../global_header.h"
#include "../parsing.h"
#include <signal.h>

void			sigquit_handler(int sig);

t_heredoc		g_global = {0, 0, 0, 0};

t_simple_cmds	*call_expander(t_tools *tools, t_simple_cmds *cmd)
{
	t_lexer	*start;

	start = NULL;
	cmd->str = expander(tools, cmd->str);
	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token != LESS_LESS)
			cmd->redirections->word = expand_str(tools,
					cmd->redirections->word);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (cmd);
}

void	handle_cmd(t_simple_cmds *cmd, t_tools *tools)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redirections)
		if (check_redirections(cmd) || (!check_redirections(cmd)
				&& !cmd->str[0]))
			exit(0);
	if (cmd->builtin != NULL)
	{
		exit_code = cmd->builtin(tools, cmd);
		exit(exit_code);
	}
	else if (cmd->str[0] && cmd->str[0][0] != '\0')
		exit_code = find_cmd(cmd, tools);
	exit(exit_code);
}

int	handle_heredoc(t_tools *tools, t_simple_cmds *cmd)
{
	t_lexer	*start;
	int		x;

	start = cmd->redirections;
	x = EXIT_SUCCESS;
	while (cmd->redirections)
	{
		if (cmd->redirections->token == LESS_LESS)
		{
			if (cmd->hd_file_name)
				free(cmd->hd_file_name);
			cmd->hd_file_name = generate_heredoc_filename();
			x = ft_heredoc(tools, cmd->redirections, cmd->hd_file_name);
			if (x)
				return (reset_tools(tools));
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
}

void	single_cmd(t_simple_cmds *cmd, t_tools *tools)
{
	int	pid;
	int	status;

	status = 0;
	pid = 0;
	tools->simple_cmds = call_expander(tools, tools->simple_cmds);
	if (cmd->builtin == mini_cd || cmd->builtin == mini_exit
		|| cmd->builtin == mini_export || cmd->builtin == mini_unset
		|| cmd->builtin == mini_env || cmd->builtin == mini_pwd
		|| cmd->builtin == mini_echo)
	{
		g_global.error_num = cmd->builtin(tools, cmd);
		return ;
	}
	handle_heredoc(tools, cmd);
	pid = fork();
	if (pid < 0)
		ft_error(5, tools);
	if (pid == 0)
		handle_cmd(cmd, tools);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_global.error_num = WEXITSTATUS(status);
}

int	executor(t_tools *tools)
{
	signal(SIGQUIT, sigquit_handler);
	g_global.on_going_cmd = 1;
	if (tools->pipes == 0)
		single_cmd(tools->simple_cmds, tools);
	else
	{
		tools->pid = ft_calloc(sizeof(int), tools->pipes + 1);
		if (!tools->pid)
			return (ft_error(1, tools));
		multiple_cmd(tools);
	}
	g_global.on_going_cmd = 0;
	return (EXIT_SUCCESS);
}
