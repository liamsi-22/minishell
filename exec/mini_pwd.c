
#include "../parsing.h"

int mini_pwd(t_tools *tools, t_simple_cmds *simple_cmd)
{
	(void)simple_cmd;
	if (tools->pwd)
		ft_putendl_fd(tools->pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
