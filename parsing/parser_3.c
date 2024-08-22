#include "../parsing.h"

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

void	parser_error(int error, t_tools *tools, t_lexer *lexer_list)
{
	lexer_clear(&lexer_list);
	ft_error(error, tools);
}

int	pipe_error(t_tools *tools, t_tokens token)
{
	if (token == PIPE)
	{
		doubl_token_error(tools, tools->lexer_list,
			tools->lexer_list->token);
		return (EXIT_FAILURE);
	}
	if (!tools->lexer_list)
	{
		parser_error(0, tools, tools->lexer_list);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	doubl_token_error(t_tools *tools, t_lexer *lexer_list,
	t_tokens token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (token == GREAT)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token == GREAT_GREAT)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (token == LESS)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token == LESS_LESS)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (token == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	lexer_clear(&lexer_list);
	reset_tools(tools);
	return (EXIT_FAILURE);
}

void	count_pipes(t_lexer *lexer_list, t_tools *tools)
{
	t_lexer	*tmp;

	tmp = lexer_list;
	tools->pipes = 0;
	while (tmp)
	{
		if (tmp->token == PIPE)
			tools->pipes++;
		tmp = tmp->next;
	}
}
