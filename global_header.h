/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_header.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakhcha <abakhcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:29:14 by abakhcha          #+#    #+#             */
/*   Updated: 2024/10/03 14:29:14 by abakhcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_HEADER_H
# define GLOBAL_HEADER_H

typedef struct s_heredoc
{
	int	error_num;
	int	stop_heredoc;
	int	in_cmd;
	int	in_heredoc;
}	t_heredoc;

extern t_heredoc	g_global;

extern int	(*builtin_arr(char *str))(t_tools *tools,
				t_simple_cmds *simple_cmd);

#endif