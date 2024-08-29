#include "../parsing.h"
#include "../global_header.h"

int	add_newredirection(t_lexer *tmp, t_parser_tools *parser_tools)
{
	t_lexer	*node;
	int		index1;
	int		index2;

	node = lexer_new(ft_strdup(tmp->next->word), tmp->token);
	if (!node)
		parser_error(1, parser_tools->tools, parser_tools->lexer_list);
	lexer_addback(&parser_tools->redirections, node);
	index1 = tmp->i;
	index2 = tmp->next->i;
	clear_lexer_node(&parser_tools->lexer_list, index1);
	clear_lexer_node(&parser_tools->lexer_list, index2);
	parser_tools->num_redirections++;
	return (0);
}

void	handle_redirections(t_parser_tools *parser_tools)
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
		doubl_token_error(parser_tools->tools,
			parser_tools->lexer_list, tmp->next->token);
	if ((tmp->token >= GREAT
			&& tmp->token <= LESS_LESS))
		add_newredirection(tmp, parser_tools);
	handle_redirections(parser_tools);
}

t_simple_cmds	*creat_newcmd(char **str,
	int num_redirections, t_lexer *redirections)
{
	t_simple_cmds	*new_cmd;

	new_cmd = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
	if (!new_cmd)
		return (0);
	new_cmd->str = str;
	new_cmd->builtin = builtin_arr(str[0]);
	new_cmd->hd_file_name = NULL;
	new_cmd->num_redirections = num_redirections;
	new_cmd->redirections = redirections;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

t_simple_cmds	*init_cmd(t_parser_tools *parser_tools)
{
	char	**str;
	int		i;
	int		num_args;
	t_lexer	*tmp;

	i = 0;
	handle_redirections(parser_tools);
	num_args = count_args(parser_tools->lexer_list);
	str = ft_calloc(num_args + 1, sizeof(char *));
	if (!str)
		parser_error(1, parser_tools->tools, parser_tools->lexer_list);
	tmp = parser_tools->lexer_list;
	while (num_args > 0)
	{
		if (tmp->word)
		{
			str[i++] = ft_strdup(tmp->word);
			clear_lexer_node(&parser_tools->lexer_list, tmp->i);
			tmp = parser_tools->lexer_list;
		}
		num_args--;
	}
	return (creat_newcmd(str,
			parser_tools->num_redirections, parser_tools->redirections));
}

t_parser_tools	init_parser_tools(t_lexer *lexer_list, t_tools *tools)
{
	t_parser_tools	parser_tool;

	parser_tool.lexer_list = lexer_list;
	parser_tool.redirections = NULL;
	parser_tool.num_redirections = 0;
	parser_tool.tools = tools;
	return (parser_tool);
}
