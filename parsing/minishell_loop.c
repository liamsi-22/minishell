#include "../parsing.h"

void	clear_cmd(t_simple_cmds **lst)
{
	t_simple_cmds	*tmp;
	t_lexer			*redirect_tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		redirect_tmp = (*lst)->redirections;
		lexer_clear(&redirect_tmp);
		if ((*lst)->str)
			free_arr((*lst)->str);
		if ((*lst)->hd_file_name)
			free((*lst)->hd_file_name);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

int	reset_tools(t_tools *tools)
{
	clear_cmd(&tools->simple_cmds);
	free(tools->args);
	if (tools->pid)
		free(tools->pid);
	free_arr(tools->paths);
	init_tools(tools);
	tools->reset = true;
	minishell_loop(tools);
	return (1);
}

int minishell_loop(t_tools *tools)
{
    char *tmp;

    tools->args = readline(READLINE_MSG);
    tmp = ft_strtrim(tools->args, " ");
    free(tools->args);
    tools->args = tmp;
    if (!tools->args)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(0);
	}
    if (tools->args[0] == '\0')
		return (reset_tools(tools));
    add_history(tools->args);
    if (!handle_quotes(tools->args))
		return (ft_error(2, tools));
    if (!init_lexer(tools))
		return (ft_error(1, tools));
    parser(tools);
	prepare_executor(tools);
	reset_tools(tools);
    return (1);
}