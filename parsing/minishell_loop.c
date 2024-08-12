#include "../parsing.h"

int	reset_tools(t_tools *tools)
{
	//ft_simple_cmdsclear(&tools->simple_cmds);
	free(tools->args);
	if (tools->pid)
		free(tools->pid);
	free_arr(tools->paths);
	initiate_tools(tools);
	tools->reset = true;
	minishell_loop(tools);
	return (1);
}

int minishell_loop(t_tools *tools)
{
    char *tmp;

    tools->args = readline("minishell --> ");
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
    if (!count_quotes(tools->args))
		return (ft_error(2, tools));
    if (!token_reader(tools))
		return (ft_error(1, tools));
    //parser(tools);
	//prepare_executor(tools);
	reset_tools(tools);
    return (1);
}