/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:58:12 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/01 16:58:13 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	mini_pwd(t_tools *tools, t_simple_cmds *simple_cmd)
{
	(void)simple_cmd;
	if (tools->pwd)
		ft_putendl_fd(tools->pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
