/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiat_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:28:12 by abakhcha          #+#    #+#             */
/*   Updated: 2024/10/22 16:35:38 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/global_header.h"
#include "../header_file/execution.h"

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup(""));
}

int	init_path(t_tools *tools)
{
	char	*env_path;
	int		i;
	char	*tmp;

	i = 0;
	env_path = find_path(tools->env);
	tools->paths = ft_split(env_path, ':');
	free(env_path);
	while (tools->paths[i])
	{
		if (tools->paths[i][ft_strlen(tools->paths[i]) - 1] != '/')
		{
			tmp = ft_strjoin(tools->paths[i], "/");
			free(tools->paths[i]);
			tools->paths[i] = tmp;
		}
		i++;
	}
	return (0);
}

int	init_tools(t_tools *tools)
{
	tools->simple_cmds = NULL;
	tools->lexer_list = NULL;
	// tools->reset = false;
	tools->pid = NULL;
	g_global.stop_heredoc = 0;
	g_global.on_going_cmd = 0;
	g_global.in_heredoc = 0;
	init_path(tools);
	init_signals();
	return (1);
}
