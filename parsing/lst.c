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

#include "../header_file/parsing.h"

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
}

void	clear_lexer_node(t_lexer **lst, int key)
{
	t_lexer	*tmp;
	t_lexer	*tmp1;
	t_lexer	*start;

	start = *lst;
	tmp1 = start;
	if ((*lst)->i == key)
	{
		clear_first_node(lst);
		return ;
	}
	while (tmp1 && tmp1->i != key)
	{
		tmp = tmp1;
		tmp1 = tmp1->next;
	}
	if (tmp1)
		tmp->next = tmp1->next;
	else
		tmp->next = NULL;
	clear_node(&tmp1);
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
