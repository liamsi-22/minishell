/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:57:46 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/01 16:57:46 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	(*builtin_arr(char *str))(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int			i;
	static void	*builtins[7][2];

	builtins[0][0] = "echo";
	builtins[0][1] = mini_echo;
	builtins[1][0] = "cd";
	builtins[1][1] = mini_cd;
	builtins[2][0] = "pwd";
	builtins[2][1] = mini_pwd;
	builtins[3][0] = "export";
	builtins[3][1] = mini_export;
	builtins[4][0] = "unset";
	builtins[4][1] = mini_unset;
	builtins[5][0] = "env";
	builtins[5][1] = mini_env;
	builtins[6][0] = "exit";
	builtins[6][1] = mini_exit;
	i = 0;
	while (i < 7)
	{
		if (str && !ft_strcmp(str, builtins[i][0]))
			return (builtins[i][1]);
		i++;
	}
	// while (i < 7)
	// {
	// 	if (str)
	// 	{
	// 		if (!ft_strcmp(str, builtins[i][0]))
	// 			return (builtins[i][1]);
	// 	}
	// 	i++;
	// }
	return (0);
}
