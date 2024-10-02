#ifndef PARSING_H
#define PARSING_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

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

char	*find_path(char **envp);
char	**ft_arrdup(char **arr);
void	free_arr(char **arr);
void	*ft_bzero(void *str, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char    **ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strtrim(const char *s);
char *ft_strncpy(char *dest, char *src, int n);
int	ft_strcmp(const char *s1, const char *s2);


void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

char	*delete_quotes2(char *str, char c);
int	init_path(t_tools *tools);
int	find_pwd(t_tools *tools);
int	init_tools(t_tools *tools);
int	handle_quotes(char *line);
int	ft_error(int error, t_tools *tools);
int minishell_loop(t_tools *tools);
int	reset_tools(t_tools *tools);
int	init_lexer(t_tools *tools);
int	read_token(char *str, int i, t_lexer **lexer_list);
t_tokens	check_token(int c);
int	skip_spaces(char *str, int i);
int	is_whitespace(char c);
int	read_word(int i, char *str, t_lexer **lexer_list);
int	add_lexer_node(char *str, t_tokens token, t_lexer **lexer_list);
void	lexer_addback(t_lexer **lst, t_lexer *new);
t_lexer	*lexer_new(char *str, int token);
int	handle_quotes(char *line);
int	find_matching_quote(char *line, int i, int *num_del, int del);
int	skip_quotes(int i, char *str, char del);
int	parser(t_tools *tools);
void	count_pipes(t_lexer *lexer_list, t_tools *tools);
int	doubl_token_error(t_tools *tools, t_lexer *lexer_list, t_tokens token);
void	lexer_clear(t_lexer **lst);
void	clear_cmd(t_simple_cmds **lst);
void	clear_lexer_node(t_lexer **lst, int key);
void	clear_first_node(t_lexer **lst);
t_lexer	*cleare_node(t_lexer **lst);
int	pipe_error(t_tools *tools);
void	parser_error(int error, t_tools *tools, t_lexer *lexer_list);
t_parser_tools	init_parser_tools(t_lexer *lexer_list, t_tools *tools);
void	add_cmdback(t_simple_cmds **lst, t_simple_cmds *new);
t_simple_cmds	*init_cmd(t_parser_tools *parser_tools);
void	handle_redirections(t_parser_tools *parser_tools);
int	count_args(t_lexer *lexer_list);
void	*ft_calloc(size_t count, size_t size);
t_simple_cmds	*creat_newcmd(char **str, int num_redirections, t_lexer *redirections);
int	add_newredirection(t_lexer *tmp, t_parser_tools *parser_tools);

//executor functions

// int	export_error(char *c);
// char	*delete_quotes(char *str);
// int	ft_isdigit(int c);
// void	ft_simple_cmdsclear(t_simple_cmds **lst);
// int	executor(t_tools *tools);
// int	mini_cd(t_tools *tools, t_simple_cmds *simple_cmd);
// int	mini_echo(t_tools *tools, t_simple_cmds *simple_cmd);
// int	mini_env(t_tools *tools, t_simple_cmds *simple_cmd);
// int	mini_exit(t_tools *tools, t_simple_cmds *simple_cmd);
// int	mini_export(t_tools *tools, t_simple_cmds *simple_cmd);
// int	mini_pwd(t_tools *tools, t_simple_cmds *simple_cmd);
// int	mini_unset(t_tools *tools, t_simple_cmds *simple_cmd);
// int	check_valid_identifier(char c);
// char	*delete_quotes_value(char *str);
// size_t	equal_sign(char *str);
// void	change_path(t_tools *tools);
// char	*expand_str(t_tools *tools, char *str);
// char	*ft_itoa(int n);
// int	cmd_not_found(char *str, int i);
// int	after_dol_lenght(char *str, int j);
// int	check_append_outfile(t_lexer *redirections);
// char	*char_to_str(char c);
// int	loop_if_dollar_sign(t_tools *tools, char *str, char **tmp, int j);
// int	question_mark(char **tmp);
// int	handle_digit(int j, char *str, char **tmp);
// int	handle_infile(char *file);
// int	handle_outfile(t_lexer *redirection);
// int	create_heredoc(t_lexer *heredoc, bool quotes, t_tools *tools, char *file_name);
// char	*detect_dollar_sign(t_tools *tools, char *str);
// size_t	dollar_sign(char *str);
// int	find_cmd(t_simple_cmds *cmd, t_tools *tools);
// int	check_redirections(t_simple_cmds *cmd);
// int	ft_heredoc(t_tools *tools, t_lexer *heredoc, char *file_name);
// char	*generate_heredoc_filename(void);
// char	**expander(t_tools *tools, char **str);
// void	handle_cmd(t_simple_cmds *cmd, t_tools *tools);
// int	handle_heredoc(t_tools *tools, t_simple_cmds *cmd);
// t_simple_cmds	*call_expander(t_tools *tools, t_simple_cmds *cmd);
// void	single_cmd(t_simple_cmds *cmd, t_tools *tools);
// int multiple_cmd(t_tools *tools);
// int	ft_fork(t_tools *tools, int end[2], int fd_in, t_simple_cmds *cmd);
// int	check_fd_heredoc(t_tools *tools, int end[2], t_simple_cmds *cmd);
// int	pipe_wait(int *pid, int amount);
// void	dup_cmd(t_simple_cmds *cmd, t_tools *tools, int end[2], int fd_in);

int export_error(char *c);
char *delete_quotes(char *str);
int cmd_not_found(char *str, int i);
int ft_isdigit(int c);
int after_dol_lenght(char *str, int j);
size_t equal_sign(char *str);
int check_append_outfile(t_lexer *redirections);
char *char_to_str(char c);
int loop_if_dollar_sign(t_tools *tools, char *str, char **tmp, int j);
int question_mark(char **tmp);
int handle_digit(int j, char *str, char **tmp);
int handle_infile(char *file);
int handle_outfile(t_lexer *redirection);
int create_heredoc(t_lexer *heredoc, bool quotes, t_tools *tools, char *file_name);
char *detect_dollar_sign(t_tools *tools, char *str);
size_t dollar_sign(char *str);
int find_cmd(t_simple_cmds *cmd, t_tools *tools);
int check_redirections(t_simple_cmds *cmd);
char *delete_quotes2(char *str, char c);
int ft_heredoc(t_tools *tools, t_lexer *heredoc, char *file_name);
char *generate_heredoc_filename(void);
int is_paire(char *str);
char *expand_str(t_tools *tools, char *str);
int	check_void(char **str, char *tmp, int i);
char **expander(t_tools *tools, char **str);
void handle_cmd(t_simple_cmds *cmd, t_tools *tools);
int handle_heredoc(t_tools *tools, t_simple_cmds *cmd);
t_simple_cmds *call_expander(t_tools *tools, t_simple_cmds *cmd);
void single_cmd(t_simple_cmds *cmd, t_tools *tools);
int executor(t_tools *tools);
void dup_cmd(t_simple_cmds *cmd, t_tools *tools, int end[2], int fd_in);
int pipe_wait(int *pid, int amount);
int check_fd_heredoc(t_tools *tools, int end[2], t_simple_cmds *cmd);
int ft_fork(t_tools *tools, int end[2], int fd_in, t_simple_cmds *cmd);
int multiple_cmd(t_tools *tools);
int	mini_cd(t_tools *tools, t_simple_cmds *simple_cmd);
void	add_path_to_env(t_tools *tools);
int	specific_path(t_tools *tools, char *str);
char	*find_path_ret(char *str, t_tools *tools);
void print_lines(int i, char **str, int out);
int mini_echo(t_tools *tools, t_simple_cmds *simple_cmd);
int mini_env(t_tools *tools, t_simple_cmds *simple_cmd);
void	ft_lexerclear(t_lexer **lst);
// void	ft_simple_cmdsclear(t_simple_cmds **lst);
void	free_tools(t_tools *tools);
int	is_str_digit(char *str);
void	determine_exit_code(char **str);
int	mini_exit(t_tools *tools, t_simple_cmds *simple_cmd);
int	variable_exist(t_tools *tools, char *str);
int	check_parameter(char *str);
char	**whileloop_add_var(char **env, char **new_env, char *str);
char	**add_var(char **env, char *str);
int	mini_export(t_tools *tools, t_simple_cmds *simple_cmd);
int mini_pwd(t_tools *tools, t_simple_cmds *simple_cmd);
char **whileloop_del_var(char **arr, char **rtn, char *str);
char **del_var(char **arr, char *str);
int unset_error(t_simple_cmds *simple_cmd);
int mini_unset(t_tools *tools, t_simple_cmds *simple_cmd);
void change_path(t_tools *tools);
char *delete_quotes_value(char *str);
int check_valid_identifier(char c);
char	*ft_itoa(int n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int	ft_atoi(const char *str);

#endif
