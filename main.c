#include "lexer.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>


int check_token_str(char *str)
{
    if(str_len(str) == 2)
    {
        if(str[0] == '>' && str[1] == '>')
            return 3;
        else if(str[0] == '<' && str[1] == '<')
            return 5;
    }
    else if(str_len(str) == 1)
    {
        if(str[0] == "|")
            return 1;
        if(str[0] == ">")
            return 2;
        if(str[0] == "<")
            return 4;
    }
    return -1;
}

void lexing()
{

}


int main(int ac, char **av, char **env)
{
    (void)env;

    if (ac != 1 || av[1])
    {
        printf("This program does not accept arguments\n");
        exit(0);
    }

    while (1)
    {
        char *input = readline("minishell% ");
        if (!input)
        {
            printf("\nExiting minishell.\n");
            break;
        }
        char **spt = split(input," ");
        lexing(spt);
        add_history(input);
        free(input);
    }
    return 0;
}
