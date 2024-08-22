#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>


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

typedef struct s_parser_tools
{
	t_lexer			*lexer_list;
	t_lexer			*redirections;
	int				num_redirections;
	struct s_tools	*tools;
}	t_parser_tools;

typedef	struct	s_tools
{
	char	*args;
	char **env;
	t_lexer	*lexer_list;
	struct s_simple_cmds	*simple_cmds;
	char *pwd;
	char *old_pwd;
	char **paths;
	int		*pid;
	bool	heredoc;
	bool	reset;
	int		pipes;
}	t_tools;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_tools *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

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
char	*ft_strtrim(char const *s1, char const *set);

void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

int	parse_envp(t_tools *tools);
int	find_pwd(t_tools *tools);
int	initiate_tools(t_tools *tools);
int	count_quotes(char *line);
int	ft_error(int error, t_tools *tools);
int minishell_loop(t_tools *tools);
int	reset_tools(t_tools *tools);
int	token_reader(t_tools *tools);
int	handle_token(char *str, int i, t_lexer **lexer_list);
t_tokens	check_token(int c);
int	skip_spaces(char *str, int i);
int	is_whitespace(char c);
int	read_words(int i, char *str, t_lexer **lexer_list);
int	add_node(char *str, t_tokens token, t_lexer **lexer_list);
void	ft_lexeradd_back(t_lexer **lst, t_lexer *new);
t_lexer	*ft_lexernew(char *str, int token);
int	count_quotes(char *line);
int	find_matching_quote(char *line, int i, int *num_del, int del);
int	handle_quotes(int i, char *str, char del);

//hado homa li tzado tkhadmo nhar 21/08
int	parser(t_tools *tools);
void	count_pipes(t_lexer *lexer_list, t_tools *tools);
int	parser_double_token_error(t_tools *tools, t_lexer *lexer_list, t_tokens token);
void	ft_lexerclear(t_lexer **lst);
void	ft_lexerdelone(t_lexer **lst, int key);
void	ft_lexerdel_first(t_lexer **lst);
t_lexer	*ft_lexerclear_one(t_lexer **lst);
int	handle_pipe_errors(t_tools *tools, t_tokens token);
void	parser_error(int error, t_tools *tools, t_lexer *lexer_list);
t_parser_tools	init_parser_tools(t_lexer *lexer_list, t_tools *tools);
void	ft_simple_cmdsadd_back(t_simple_cmds **lst, t_simple_cmds *new);
t_simple_cmds	*initialize_cmd(t_parser_tools *parser_tools);
void	rm_redirections(t_parser_tools *parser_tools);
int	count_args(t_lexer *lexer_list);
void	*ft_calloc(size_t count, size_t size);
t_simple_cmds	*ft_simple_cmdsnew(char **str, int num_redirections, t_lexer *redirections);
int	add_new_redirection(t_lexer *tmp, t_parser_tools *parser_tools);

#endif
