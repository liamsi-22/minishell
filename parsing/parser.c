/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_original.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakhcha <abakhcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:19:37 by abakhcha          #+#    #+#             */
/*   Updated: 2024/10/03 14:19:37 by abakhcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/parsing.h"

void	count_pipes(t_lexer *lexer_list, t_tools *tools)
{
	t_lexer	*tmp;

	tmp = lexer_list;
	tools->pipes = 0;
	while (tmp)
	{
		if (tmp->token == PIPE)
			tools->pipes++;
		tmp = tmp->next;
	}
}

int	check_first_pipe(t_tools *tools)
{
	count_pipes(tools->lexer_list, tools);
	if (tools->lexer_list->token == PIPE)
		return (doubl_token_error(tools, tools->lexer_list,
				tools->lexer_list->token));
	return (EXIT_SUCCESS);
}

int	parser(t_tools *tools)
{
	t_simple_cmds	*node;

	node = NULL;
	check_first_pipe(tools);
	while (tools->lexer_list)
	{
		if (tools->lexer_list && tools->lexer_list->token == PIPE)
			clear_lexer_node(&tools->lexer_list, tools->lexer_list->i);
		if (pipe_error(tools))
			return (EXIT_FAILURE);
		node = init_cmd(tools);
		if (!node)
		{
			clear_cmd(&tools->simple_cmds);
			parser_error(0, tools, tools->lexer_list);
		}
		if (!tools->simple_cmds)
			tools->simple_cmds = node;
		else
			add_cmdback(&tools->simple_cmds, node);
	}
	return (EXIT_SUCCESS);
}
