#include "../parsing.h"

t_lexer	*cleare_node(t_lexer **lst)
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
	cleare_node(&tmp);
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
	cleare_node(&node);
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
