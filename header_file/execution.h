/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:38:14 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 10:06:42 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

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
# include <signal.h>
# include "parsing.h"

// executor functions

int							splite_function1(char *str, char **final_str,
								int i);
int							splite_function2(char *str, char **final_str,
								int i);
int							export_error(char *c);
char						*delete_quotes(char *str);
int							cmd_not_found(char *str, int i);
int							after_dol(char *str, int j);
size_t						equal_sgn(char *str);
int							check_append_outfile(t_lexer *redirections);
char						*char_to_str(char c);
int							loop_if_dollar_sign(t_tools *tools, char *str,
								char **tmp, int j);
int							question_mark(char **tmp);
int							handle_digit(int j, char *str, char **tmp);
int							handle_infile(char *file);
int							handle_outfile(t_lexer *redirection);
int							create_heredoc(t_lexer *heredoc, bool quotes,
								t_tools *tools, char *file_name);
char						*detect_dollar_sign(t_tools *tools, char *str);
size_t						dollar_sign(char *str);
int							find_cmd(t_simple_cmds *cmd, t_tools *tools);
int							check_redirections(t_simple_cmds *cmd);
char						*delete_quotes2(char *str, char c);
int							ft_heredoc(t_tools *tools, t_lexer *heredoc,
								char *file_name);
char						*generate_heredoc_filename(void);
int							is_paire(char *str);
char						*expand_str(t_tools *tools, char *str);
int							check_void(char **str, char *tmp, int i);
char						**expander(t_tools *tools, char **str);
void						handle_cmd(t_simple_cmds *cmd, t_tools *tools);
int							handle_heredoc(t_tools *tools, t_simple_cmds *cmd);
t_simple_cmds				*call_expander(t_tools *tools, t_simple_cmds *cmd);
void						single_cmd(t_simple_cmds *cmd, t_tools *tools);
int							executor(t_tools *tools);
void						dup_cmd(t_simple_cmds *cmd, t_tools *tools,
								int end[2], int fd_in);
int							pipe_wait(int *pid, int amount);
int							check_fd_heredoc(t_tools *tools, int end[2],
								t_simple_cmds *cmd);
int							ft_fork(t_tools *tools, int end[2], int fd_in,
								t_simple_cmds *cmd);
int							multiple_cmd(t_tools *tools);
int							mini_cd(t_tools *tools, t_simple_cmds *simple_cmd);
void						add_path_to_env(t_tools *tools);
int							specific_path(t_tools *tools, char *str);
void						print_lines(int i, char **str, int out);
int							mini_echo(t_tools *tools,
								t_simple_cmds *simple_cmd);
int							mini_env(t_tools *tools, t_simple_cmds *simple_cmd);
void						free_tools(t_tools *tools);
int							is_str_digit(char *str);
void						determine_exit_code(char **str);
int							mini_exit(t_tools *tools,
								t_simple_cmds *simple_cmd);
int							variable_exist(t_tools *tools, char *str);
int							check_parameter(char *str);
char						**whileloop_add_var(char **env, char **new_env,
								char *str);
char						**add_var(char **env, char *str);
int							mini_export(t_tools *tools,
								t_simple_cmds *simple_cmd);
int							mini_pwd(t_tools *tools, t_simple_cmds *simple_cmd);
char						**whileloop_del_var(char **arr, char **rtn,
								char *str);
char						**del_var(char **arr, char *str);
int							unset_error(t_simple_cmds *simple_cmd);
int							mini_unset(t_tools *tools,
								t_simple_cmds *simple_cmd);
void						change_path(t_tools *tools);
char						*delete_quotes_value(char *str);
int							check_valid_identifier(char c);
void						init_signals(void);
char						*ft_strtrim2(char const *s1);
int							mini_export_env(t_tools *tools, t_simple_cmds *simple_cmd);
bool 						handle_double_quotes(char *str, int *i);

#endif