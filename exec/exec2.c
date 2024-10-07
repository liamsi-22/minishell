/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:57:51 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/06 15:57:23 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../global_header.h"
#include "../parsing.h"

void	dup_cmd(t_simple_cmds *cmd, t_tools *tools, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error(4, tools);
	close(end[0]);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		ft_error(4, tools);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_cmd(cmd, tools);
}

int	pipe_wait(int *pid, int amount)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < amount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		g_global.error_num = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}

int	check_fd_heredoc(t_tools *tools, int end[2], t_simple_cmds *cmd)
{
	int	fd_in;

	(void)tools;
	fd_in = 0;
	if (!cmd->next)
		close(end[0]);
	else
		fd_in = end[0];
	return (fd_in);
}

int	ft_fork(t_tools *tools, int end[2], int fd_in, t_simple_cmds *cmd)
{
	static int	i = 0;

	if (tools->reset == true)
	{
		i = 0;
		tools->reset = false;
	}
	tools->pid[i] = fork();
	if (tools->pid[i] < 0)
		ft_error(5, tools);
	if (tools->pid[i] == 0)
		dup_cmd(cmd, tools, end, fd_in);
	i++;
	return (EXIT_SUCCESS);
}

int	multiple_cmd(t_tools *tools)
{
	int				end[2];
	int				fd_in;
	t_simple_cmds	*tmp;

	tmp = tools->simple_cmds;
	fd_in = STDIN_FILENO;
	while (tools->simple_cmds)
	{
		tools->simple_cmds = call_expander(tools, tools->simple_cmds);
		if (tools->simple_cmds->next)
			pipe(end);
		handle_heredoc(tools, tools->simple_cmds);
		ft_fork(tools, end, fd_in, tools->simple_cmds);
		close(end[1]);
		if (tools->simple_cmds->prev)
			close(fd_in);
		fd_in = end[0];
		if (tools->simple_cmds->next)
			tools->simple_cmds = tools->simple_cmds->next;
		else
			break ;
	}
	pipe_wait(tools->pid, tools->pipes);
	tools->simple_cmds = tmp;
	return (0);
}
