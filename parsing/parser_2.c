#include "../parsing.h"

int	add_new_redirection(t_lexer *tmp, t_parser_tools *parser_tools)
{
	t_lexer	*node;
	int		index_1;
	int		index_2;

	node = ft_lexernew(ft_strdup(tmp->next->word), tmp->token);
	if (!node)
		parser_error(1, parser_tools->tools, parser_tools->lexer_list);
	ft_lexeradd_back(&parser_tools->redirections, node);
	index_1 = tmp->i;
	index_2 = tmp->next->i;
	ft_lexerdelone(&parser_tools->lexer_list, index_1);
	ft_lexerdelone(&parser_tools->lexer_list, index_2);
	parser_tools->num_redirections++;
	return (0);
}
void	rm_redirections(t_parser_tools *parser_tools)
{
	t_lexer	*tmp;

	tmp = parser_tools->lexer_list;
	while (tmp && tmp->token == 0)
		tmp = tmp->next;
	if (!tmp || tmp->token == PIPE)
		return ;
	if (!tmp->next)
		parser_error(0, parser_tools->tools, parser_tools->lexer_list);
	if (tmp->next->token)
		parser_double_token_error(parser_tools->tools,
			parser_tools->lexer_list, tmp->next->token);
	if ((tmp->token >= GREAT
			&& tmp->token <= LESS_LESS))
		add_new_redirection(tmp, parser_tools);
	rm_redirections(parser_tools);
}

t_simple_cmds	*ft_simple_cmdsnew(char **str,
	int num_redirections, t_lexer *redirections)
{
	t_simple_cmds	*new_element;

	new_element = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
	if (!new_element)
		return (0);
	new_element->str = str;
	//new_element->builtin = builtin_arr(str[0]);
	new_element->hd_file_name = NULL;
	new_element->num_redirections = num_redirections;
	new_element->redirections = redirections;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

t_simple_cmds	*initialize_cmd(t_parser_tools *parser_tools)
{
	char	**str;
	int		i;
	int		arg_size;
	t_lexer	*tmp;

	i = 0;
	rm_redirections(parser_tools);
	arg_size = count_args(parser_tools->lexer_list);
	str = ft_calloc(arg_size + 1, sizeof(char *));
	if (!str)
		parser_error(1, parser_tools->tools, parser_tools->lexer_list);
	tmp = parser_tools->lexer_list;
	while (arg_size > 0)
	{
		if (tmp->word)
		{
			str[i++] = ft_strdup(tmp->word);
			ft_lexerdelone(&parser_tools->lexer_list, tmp->i);
			tmp = parser_tools->lexer_list;
		}
		arg_size--;
	}
	return (ft_simple_cmdsnew(str,
			parser_tools->num_redirections, parser_tools->redirections));
}
t_parser_tools	init_parser_tools(t_lexer *lexer_list, t_tools *tools)
{
	t_parser_tools	parser_tools;

	parser_tools.lexer_list = lexer_list;
	parser_tools.redirections = NULL;
	parser_tools.num_redirections = 0;
	parser_tools.tools = tools;
	return (parser_tools);
}
