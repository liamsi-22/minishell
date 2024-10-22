/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:10:01 by abakhcha          #+#    #+#             */
/*   Updated: 2024/10/22 10:04:25 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_file/parsing.h"

int	ft_pwd(t_tools *tools)
{
	int	i;

	i = 0;
	tools->pwd = NULL;
	tools->old_pwd = NULL;
	while (tools->env[i])
	{
		if (!ft_strncmp(tools->env[i], "PWD=", 4))
			tools->pwd = ft_substr(tools->env[i], 4, ft_strlen(tools->env[i])
					- 4);
		if (!ft_strncmp(tools->env[i], "OLDPWD=", 7))
			tools->old_pwd = ft_substr(tools->env[i], 7,
					ft_strlen(tools->env[i]) - 7);
		i++;
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_tools	tools;

	(void)av;
	if (ac != 1)
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	tools.env = ft_arrdup(env);
	ft_pwd(&tools);
	init_tools(&tools);
	minishell_loop(&tools);
}
