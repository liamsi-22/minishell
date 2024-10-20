/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakhcha <abakhcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:15:07 by abakhcha          #+#    #+#             */
/*   Updated: 2024/10/03 14:15:07 by abakhcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_lexer	*clear_node(t_lexer **lst)
{
	if ((*lst)->word)
	{
		free((*lst)->word);
		(*lst)->word = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

void	clear_first_node(t_lexer **lst)
{
	t_lexer	*tmp;

	tmp = *lst;
	*lst = tmp->next;
	clear_node(&tmp);
	if (*lst)
		(*lst)->prv = NULL;
}

void	clear_lexer_node(t_lexer **lst, int key)
{
	t_lexer	*node;
	t_lexer	*prv;
	t_lexer	*start;

	start = *lst;
	node = start;
	if ((*lst)->i == key)
	{
		clear_first_node(lst);
		return ;
	}
	while (node && node->i != key)
	{
		prv = node;
		node = node->next;
	}
	if (node)
		prv->next = node->next;
	else
		prv->next = NULL;
	if (prv->next)
		prv->next->prv = prv;
	clear_node(&node);
	*lst = start;
}

void	lexer_clear(t_lexer **lst)
{
	t_lexer	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->word)
			free((*lst)->word);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
