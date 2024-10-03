/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:58:15 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/03 15:20:33 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../parsing.h"

char **whileloop_del_var(char **arr, char **rtn, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		if (!(ft_strncmp(arr[i], str, equal_sgn(arr[i]) - 1) == 0 && str[equal_sgn(arr[i]) - 1] == '\0' && arr[i][ft_strlen(str)] == '='))
		{
			rtn[j] = ft_strdup(arr[i]);
			if (rtn[j] == NULL)
			{
				free_arr(rtn);
				return (rtn);
			}
			j++;
		}
		i++;
	}
	rtn[j] = NULL;
	return (rtn);
}

char **del_var(char **arr, char *str)
{
	char **rtn;
	size_t i;

	i = 0;

	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	rtn = whileloop_del_var(arr, rtn, str);
	return (rtn);
}

int unset_error(t_simple_cmds *simple_cmd)
{
	int i;

	i = 0;
	if (!simple_cmd->str[1])
		return (EXIT_SUCCESS);
	while (simple_cmd->str[1][i])
	{
		if (simple_cmd->str[1][i++] == '/')
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(simple_cmd->str[1], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	if (equal_sgn(simple_cmd->str[1]) != 0)
	{
		ft_putendl_fd("minishell: unset: not a valid identifier",
					  STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int mini_unset(t_tools *tools, t_simple_cmds *simple_cmd)
{
	char **tmp;

	tmp = NULL;
	if (unset_error(simple_cmd) == 1)
		return (EXIT_FAILURE);
	else
	{
		if (simple_cmd->str[1])
		{
			tmp = del_var(tools->env, simple_cmd->str[1]);
			free_arr(tools->env);
			tools->env = tmp;
		}
	}
	return (EXIT_SUCCESS);
}
