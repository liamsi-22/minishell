/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:08:21 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 13:14:11 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define READLINE_MSG "\033[1;36mminishell\033[34m$ \033[0m"
# define HEREDOC_MSG "\033[1;34m> \033[0m"

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}							t_tokens;

typedef struct s_lexer
{
	char					*word;
	t_tokens				token;
	int						i;

	struct s_lexer			*next;
}							t_lexer;

typedef struct s_tools
{
	char					*args;
	char					**env;
	t_lexer					*lexer_list;
	struct s_simple_cmds	*simple_cmds;
	char					*pwd;
	char					*old_pwd;
	char					**paths;
	int						*pid;
	bool					reset;
	int						pipes;
	t_lexer					*redirections;
}							t_tools;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_tools *, struct s_simple_cmds *);
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}							t_simple_cmds;

int	(*builtin_arr(char *str))(t_tools *tools, t_simple_cmds *simple_cmd);

char						*find_path(char **envp);
char						**ft_arrdup(char **arr);
void						free_arr(char **arr);
void						*ft_bzero(void *str, size_t n);
char						*ft_strdup(const char *s1);
size_t						ft_strlen(const char *str);
char						*ft_strjoin(char const *s1, char const *s2);
char						**ft_split(char const *s, char c);
char						*ft_substr(char const *s, unsigned int start,
		size_t len);
int							ft_strncmp(const char *s1, const char *s2,
		size_t n);
int							ft_atoi(const char *str);
char						*ft_strtrim(const char *s);
char						*ft_strncpy(char *dest, char *src, int n);
int							ft_strcmp(const char *s1, const char *s2);
void						ft_putendl_fd(char *s, int fd);
void						ft_putstr_fd(char *s, int fd);
void						ft_putchar_fd(char c, int fd);
char						*ft_itoa(int n);
void						ft_putnbr_fd(int n, int fd);
size_t						ft_strlcpy(char *dst, const char *src,
		size_t dstsize);

// parser functions

char						*delete_quotes2(char *str, char c);
int							init_path(t_tools *tools);
int							ft_pwd(t_tools *tools);
int							init_tools(t_tools *tools);
int							handle_quotes(char *line);
int							ft_error(int error, t_tools *tools);
int							minishell_loop(t_tools *tools);
int							reset_tools(t_tools *tools);
int							init_lexer(t_tools *tools);
int							read_token(char *str, int i, t_lexer **lexer_list);
t_tokens					check_token(int c);
int							skip_spaces(char *str, int i);
int							is_space(char c);
int							read_word(int i, char *str, t_lexer **lexer_list);
int							add_lexer_node(char *str, t_tokens token,
		t_lexer **lexer_list);
void						lexer_addback(t_lexer **lst, t_lexer *new);
t_lexer						*lexer_new(char *str, int token);
int							handle_quotes(char *line);
int							find_matching_quote(char *line, int i, int *num_del,
		int del);
int							skip_quotes(int i, char *str, char del);
int							parser(t_tools *tools);
void						count_pipes(t_lexer *lexer_list, t_tools *tools);
int							doubl_token_error(t_tools *tools,
		t_lexer *lexer_list, t_tokens token);
void						lexer_clear(t_lexer **lst);
void						clear_cmd(t_simple_cmds **lst);
void						clear_lexer_node(t_lexer **lst, int key);
void						clear_first_node(t_lexer **lst);
t_lexer						*clear_node(t_lexer **lst);
int							pipe_error(t_tools *tools);
int							add_newredirection(t_lexer *tmp, t_tools *tools);
void						parser_error(int error, t_tools *tools,
		t_lexer *lexer_list);
void						add_cmdback(t_simple_cmds **lst,
		t_simple_cmds *new);
t_simple_cmds				*init_cmd(t_tools	*tools);
void						handle_redirections(t_tools *tools);
int							count_args(t_lexer *lexer_list);
void						*ft_calloc(size_t count, size_t size);
int							ft_isdigit(int c);
t_simple_cmds				*creat_newcmd(char **str, t_lexer *redirections);


#endif
