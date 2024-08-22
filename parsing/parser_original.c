#include "../parsing.h"

int	parser(t_tools *tools)
{
	t_simple_cmds	*node;
	t_parser_tools	parser_tools;

	tools->simple_cmds = NULL;
	count_pipes(tools->lexer_list, tools);
	if (tools->lexer_list->token == PIPE)
		return (parser_double_token_error(tools, tools->lexer_list,
				tools->lexer_list->token));
	while (tools->lexer_list)
	{
		if (tools->lexer_list && tools->lexer_list->token == PIPE)
			ft_lexerdelone(&tools->lexer_list, tools->lexer_list->i);
		if (handle_pipe_errors(tools, tools->lexer_list->token))
			return (EXIT_FAILURE);
		parser_tools = init_parser_tools(tools->lexer_list, tools);
		node = initialize_cmd(&parser_tools);
		if (!node)
			parser_error(0, tools, parser_tools.lexer_list);
		if (!tools->simple_cmds)
			tools->simple_cmds = node;
		else
			ft_simple_cmdsadd_back(&tools->simple_cmds, node);
		tools->lexer_list = parser_tools.lexer_list;
	}
	return (EXIT_SUCCESS);
}
