/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:58:15 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 10:03:14 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/execution.h"

char	**whileloop_del_var(char **arr, char **store, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		if (!(ft_strncmp(arr[i], str, equal_sgn(arr[i]) - 1) == 0
				&& str[equal_sgn(arr[i]) - 1] == '\0'
				&& arr[i][ft_strlen(str)] == '='))
		{
			store[j] = ft_strdup(arr[i]);
			if (store[j] == NULL)
			{
				free_arr(store);
				return (store);
			}
			j++;
		}
		i++;
	}
	store[j] = NULL;
	return (store);
}

char	**del_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	rtn = whileloop_del_var(arr, rtn, str);
	return (rtn);
}

int	mini_unset(t_tools *tools, t_simple_cmds *simple_cmd)
{
	char	**tmp;
	int		i;

	tmp = NULL;
	if (simple_cmd->str[1])
	{
		i = 1;
		while (simple_cmd->str[i])
		{
			tmp = del_var(tools->env, simple_cmd->str[i]);
			free_arr(tools->env);
			tools->env = tmp;
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
