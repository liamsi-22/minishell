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
