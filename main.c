#include "parsing.h"

int main(int ac,char **av,char **env)
{
    t_tools tools;

    if(ac != 1)
    {
        printf("This program does not accept arguments\n");
        exit(0);
    }
    int i;

    i = 0;
    tools.env = ft_arrdup(env);
    find_pwd(&tools);
    initiate_tools(&tools);
    // init_signals();
    minishell_loop(&tools);
}