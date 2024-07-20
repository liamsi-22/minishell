#include "lexer.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>



t_lexer	*ft_lstlast(t_lexer *lst)
{
	while (lst != NULL && lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
    {
		ft_lstlast(*lst)->next = new;
        new->prev = ft_lstlast(*lst);
    }
	else
    {
		*lst = new;
        new->prev = NULL;
    }
}

t_lexer	*ft_lstnew(char *str, int token, int i)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = str;
    new->i = i;
    new->token = token;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
/**************************************************************/
t_lexer *init_string(char *ptr,int i)
{
    t_lexer *lst;

    lst = NULL;
    if (i == 1)
        lst = ft_lstnew(ptr,0,i);
    else
        ft_lstadd_back(lst,ft_lstnew(ptr,0,i));
    return lst;
}

t_lexer *init_token(int var,int i)
{
    t_lexer *lst;

    lst = NULL;
    if (i == 1)
        lst = ft_lstnew(0,var,i);
    else
        ft_lstadd_back(lst,ft_lstnew(0,var,i));
    return lst;
}

int check_token_str(char *str)
{
    if(strlen(str) == 2)
    {
        if(str[0] == '>' && str[1] == '>')
            return GREAT_GREAT;
        else if(str[0] == '<' && str[1] == '<')
            return LESS_LESS;
    }
    else if(strlen(str) == 1)
    {
        if(str[0] == '|')
            return PIPE;
        if(str[0] == '>')
            return GREAT;
        if(str[0] == '<')
            return LESS;
    }
    return -1;
}

void lexing(char **str)
{
    int i = 0;
    int var = 0;
    t_lexer *tmp;

    tmp = NULL;
    while(str[i])
    {
        if((var = check_token_str(str[i])) == -1)
           tmp = init_string(str[i],i);
        else
           tmp = init_token(var,i);
        i++;
    }
    while (tmp)
    {
        printf("%d\n",i);
        tmp = tmp->next;
    }
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
        char **spt = ft_split(input," ");
        lexing(spt);
        add_history(input);
        free(input);
    }
    return 0;
}
