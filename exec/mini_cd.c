/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:57:54 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 10:03:14 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/execution.h"

void	change_path(t_tools *tools)
{
	char	*tmp;

	tmp = ft_strdup(tools->pwd);
	if (tools->old_pwd)
		free(tools->old_pwd);
	tools->old_pwd = tmp;
	if (tools->pwd)
		free(tools->pwd);
	tools->pwd = getcwd(NULL, 0);
	if (!tools->pwd)
		tools->pwd = ft_strdup(tools->old_pwd);
}

int	specific_path(t_tools *tools, char *str)
{
	char	*tmp;
	int		ret;
	int i;

	i = 0;
	tmp = NULL;
	while (tools->env[i])
	{
		if (!ft_strncmp(tools->env[i], str, ft_strlen(str)))
			tmp = ft_substr(tools->env[i], ft_strlen(str), ft_strlen(tools->env[i]) - ft_strlen(str));
		i++;
	}
	if (!tmp)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
	return (ret);
}

void	add_path_to_env(t_tools *tools)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tools->env && tools->env[i])
	{
		if (!ft_strncmp(tools->env[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", tools->pwd);
			free(tools->env[i]);
			tools->env[i] = tmp;
		}
		else if (!ft_strncmp(tools->env[i], "OLDPWD=", 7) && tools->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", tools->old_pwd);
			free(tools->env[i]);
			tools->env[i] = tmp;
		}
		i++;
	}
}

int	mini_cd(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int	ret;

	if (simple_cmd->str[1] && simple_cmd->str[2])
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("cd: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!simple_cmd->str[1])
		ret = specific_path(tools, "HOME=");
	else
	{
		ret = chdir(simple_cmd->str[1]);
		if (ret != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(simple_cmd->str[1], STDERR_FILENO);
			perror(" ");
		}
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	change_path(tools);
	add_path_to_env(tools);
	return (EXIT_SUCCESS);
}
