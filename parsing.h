#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

# define READLINE_MSG	"\033[1;36mminishell\033[34m$ \033[0m"
# define HEREDOC_MSG	"\033[1;34m> \033[0m"

typedef	enum	s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}		t_tokens;

typedef struct s_lexer
{
    char	*word;
    t_tokens	token;
    int i;

    struct	s_lexer	*next;
	struct	s_lexer	*prv;
}	t_lexer;

typedef	struct	s_tools
{
	char	*args;
	char **env;
	t_lexer	*lexer_list;
	char *pwd;
	char *old_pwd;
	char **paths;
	int		*pid;
	bool	heredoc;
	bool	reset;
	int		pipes;
}	t_tools;

typedef struct s_heredoc
{
	int	error_num;
	int	stop_heredoc;
	int	in_cmd;
	int	in_heredoc;
}	t_heredoc;

char	**ft_arrdup(char **arr);
void	free_arr(char **arr);
void	*ft_bzero(void *str, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char    **ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);


int	find_pwd(t_tools *tools);
int	initiate_tools(t_tools *tools);

#endif