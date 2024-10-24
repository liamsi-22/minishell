/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:58:05 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 10:03:14 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/execution.h"

int	mini_env(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int	i;

	(void)simple_cmd;
	i = 0;
	while (tools->env[i] && equal_sgn(tools->env[i]))
	{
		ft_putendl_fd(tools->env[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	mini_export_env(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int	i;

	(void)simple_cmd;
	i = 0;
	while (tools->env[i])
	{
		ft_putendl_fd(tools->env[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
