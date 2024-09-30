#include "../parsing.h"

int mini_env(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int	i;

	(void)simple_cmd;
	i = 0;
	while (tools->env[i])
	{
		ft_putendl_fd(tools->env[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
