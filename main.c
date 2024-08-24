#include "./parsing.h"

int	find_pwd(t_tools *tools)
{
	int	i;

	i = 0;
	while (tools->env[i])
	{
		if (!ft_strncmp(tools->env[i], "PWD=", 4))
			tools->pwd = ft_substr(tools->env[i],
					4, ft_strlen(tools->env[i]) - 4);
		if (!ft_strncmp(tools->env[i], "OLDPWD=", 7))
			tools->old_pwd = ft_substr(tools->env[i],
					7, ft_strlen(tools->env[i]) - 7);
		i++;
	}
	return (1);
}

int main(int ac,char **av,char **env)
{
    t_tools tools;

	(void)av;
    if(ac != 1)
    {
        printf("This program does not accept arguments\n");
        exit(0);
    }
    tools.env = ft_arrdup(env);
    find_pwd(&tools);
    init_tools(&tools);
    minishell_loop(&tools);
}