/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+        +:+      */
/*   By: abakhcha <abakhcha@student.42.fr>          +#+  +:+      +#+         */
/*                                                +#+#+#+#+#+  +#+            */
/*   Created: 2024/10/03 14:16:17 by abakhcha          #+#    #+#             */
/*   Updated: 2024/10/03 14:16:17 by abakhcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/parsing.h"

int	count_args(t_lexer *lexer_list)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = lexer_list;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->i >= 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	add_newredirection(t_lexer *tmp, t_tools *tools)
{
	t_lexer	*node;
	int		index1;
	int		index2;

	node = lexer_new(ft_strdup(tmp->next->word), tmp->token);
	if (!node)
		parser_error(1, tools, tools->lexer_list);
	lexer_addback(&tools->redirections, node);
	index1 = tmp->i;
	index2 = tmp->next->i;
	clear_lexer_node(&tools->lexer_list, index1);
	clear_lexer_node(&tools->lexer_list, index2);
	return (0);
}

void	handle_redirections(t_tools *tools)
{
	t_lexer	*tmp;

	tmp = tools->lexer_list;
	while (tmp && tmp->token == 0)
		tmp = tmp->next;
	if (!tmp || tmp->token == PIPE)
		return ;
	if (!tmp->next)
		parser_error(0, tools, tools->lexer_list);
	if (tmp->next->token)
		doubl_token_error(tools, tools->lexer_list,
			tmp->next->token);
	if ((tmp->token >= GREAT && tmp->token <= LESS_LESS))
		add_newredirection(tmp, tools);
	handle_redirections(tools);
}

t_simple_cmds	*init_cmd(t_tools	*tools)
{
	char	**str;
	int		i;
	int		num_args;
	t_lexer	*tmp;

	i = 0;
	tools->redirections = NULL;
	handle_redirections(tools);
	num_args = count_args(tools->lexer_list);
	str = malloc((num_args + 1) * sizeof(char *));
	if (!str)
		parser_error(1, tools, tools->lexer_list);
	tmp = tools->lexer_list;
	while (num_args > 0)
	{
		if (tmp->word)
		{
			str[i++] = ft_strdup(tmp->word);
			clear_lexer_node(&tools->lexer_list, tmp->i);
			tmp = tools->lexer_list;
		}
		num_args--;
	}
	str[i] = NULL;
	return (creat_newcmd(str, tools->redirections));
}
