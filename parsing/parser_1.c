#include "../parsing.h"

t_lexer	*ft_lexerclear_one(t_lexer **lst)
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

void	ft_lexerdel_first(t_lexer **lst)
{
	t_lexer	*node;

	node = *lst;
	*lst = node->next;
	ft_lexerclear_one(&node);
	if (*lst)
		(*lst)->prv = NULL;
}

void	ft_lexerdelone(t_lexer **lst, int key)
{
	t_lexer	*node;
	t_lexer	*prv;
	t_lexer	*start;

	start = *lst;
	node = start;
	if ((*lst)->i == key)
	{
		ft_lexerdel_first(lst);
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
	ft_lexerclear_one(&node);
	*lst = start;
}

void	ft_lexerclear(t_lexer **lst)
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
void	ft_simple_cmdsadd_back(t_simple_cmds **lst, t_simple_cmds *new)
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
