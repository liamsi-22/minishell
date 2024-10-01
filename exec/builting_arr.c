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
#include "../global_header.h"

extern int (*builtin_arr(char *str))(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int i;

	static void *builtins[7][2] = {
		{"echo", mini_echo},
		{"cd", mini_cd},
		{"pwd", mini_pwd},
		{"export", mini_export},
		{"unset", mini_unset},
		{"env", mini_env},
		{"exit", mini_exit}};

	i = 0;
	while (i < 7)
	{
		if (str)
		{
			if (!ft_strcmp(str, builtins[i][0]))
				return (builtins[i][1]);
		}
		i++;
	}
	return (NULL);
}
