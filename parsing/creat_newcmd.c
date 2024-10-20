/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:11:08 by abakhcha          #+#    #+#             */
/*   Updated: 2024/10/16 00:55:46 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../global_header.h"
#include "../parsing.h"

t_lexer	*lexer_new(char *str, int token)
{
	t_lexer		*new_lexer_node;
	static int	i = 0;

	new_lexer_node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_lexer_node)
		return (0);
	new_lexer_node->word = str;
	new_lexer_node->token = token;
	new_lexer_node->i = i++;
	new_lexer_node->next = NULL;
	new_lexer_node->prv = NULL;
	return (new_lexer_node);
}

void	lexer_addback(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prv = tmp;
}

int	add_lexer_node(char *str, t_tokens token, t_lexer **lexer_list)
{
	t_lexer	*node;

	node = lexer_new(str, token);
	if (!node)
		return (0);
	lexer_addback(lexer_list, node);
	return (1);
}

t_simple_cmds	*creat_newcmd(char **str, t_lexer	*redirections)
{
	t_simple_cmds	*new_cmd;

	new_cmd = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
	if (!new_cmd)
		return (0);
	if (str)
		new_cmd->str = str;
	new_cmd->builtin = NULL;
	if (*str)
		new_cmd->builtin = builtin_arr(str[0]);
	new_cmd->hd_file_name = NULL;
	if (redirections)
		new_cmd->redirections = redirections;
	else
		new_cmd->redirections = NULL;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

void	add_cmdback(t_simple_cmds **lst, t_simple_cmds *new)
{
	t_simple_cmds	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
