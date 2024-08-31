#include "../parsing.h"

int	parser(t_tools *tools)
{
	t_simple_cmds	*node;
	t_parser_tools	parser_tool;

	tools->simple_cmds = NULL;
	count_pipes(tools->lexer_list, tools);
	if (tools->lexer_list->token == PIPE)
		return (doubl_token_error(tools, tools->lexer_list,
				tools->lexer_list->token));
	while (tools->lexer_list)
	{
		if (tools->lexer_list && tools->lexer_list->token == PIPE)
			clear_lexer_node(&tools->lexer_list, tools->lexer_list->i);
		if (pipe_error(tools, tools->lexer_list->token))
			return (EXIT_FAILURE);
		parser_tool = init_parser_tools(tools->lexer_list, tools);
		node = init_cmd(&parser_tool);
		if (!node)
			parser_error(0, tools, parser_tool.lexer_list);
		if (!tools->simple_cmds)
			tools->simple_cmds = node;
		else
			add_cmdback(&tools->simple_cmds, node);
		tools->lexer_list = parser_tool.lexer_list;
		// if (tools->lexer_list)
		// {
		// 	if (tools->lexer_list->token == PIPE && tools->lexer_list->next == NULL)
		// 	{
		// 		write(1, "fuck it i'm out of here",23);
		// 		exit(1);
		// 	}
		// }
	}
	return (EXIT_SUCCESS);
}
