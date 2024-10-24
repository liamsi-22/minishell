/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:58:10 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 10:03:14 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/execution.h"

int	variable_exist(t_tools *tools, char *str)
{
	int	i;

	i = 0;
	while (tools->env[i])
	{
		if (ft_strncmp(tools->env[i], str, equal_sgn(tools->env[i])) == 0)
		{
			free(tools->env[i]);
			tools->env[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_parameter(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (export_error(str));
	while (str[i] && str[i] != '=')
	{
		if (check_valid_identifier(str[i]))
			return (export_error(str));
		i++;
	}
	if (str[0] == '=')
		return (export_error(str));
	return (EXIT_SUCCESS);
}

char	**whileloop_add_var(char **env, char **new_env, char *str)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	free_arr(env);
	return (new_env);
}

char	**add_var(char **env, char *str)
{
	char	**new_env;
	size_t	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	new_env = ft_calloc(sizeof(char *), i + 2);
	if (!new_env)
		return (NULL);
	new_env = whileloop_add_var(env, new_env, str);
	return (new_env);
}

int	mini_export(t_tools *tools, t_simple_cmds *simple_cmd)
{
	char	**tmp;
	int		i;

	i = 1;
	if (!simple_cmd->str[1] || simple_cmd->str[1][0] == '\0')
		mini_export_env(tools, simple_cmd);
	else
	{
		while (simple_cmd->str[i])
		{
			if (check_parameter(simple_cmd->str[i]) != 0)
				return (EXIT_FAILURE);
			else if (!check_parameter(simple_cmd->str[i])
				&& !variable_exist(tools, simple_cmd->str[i]))
			{
				if (simple_cmd->str[i])
				{
					tmp = add_var(tools->env, simple_cmd->str[i]);
					tools->env = tmp;
				}
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
