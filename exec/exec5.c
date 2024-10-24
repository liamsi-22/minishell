/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:24:44 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 10:03:59 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/execution.h"
#include "../header_file/global_header.h"
#include <signal.h>

void	sigquit_handler(int sig);

int	handle_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		if (!(access(file, F_OK)) && (access(file, W_OK | R_OK)))
			ft_putstr_fd("minishell:  Permission denied\n", STDERR_FILENO);
		else
			ft_putstr_fd("minishell: infile: No such file or directory\n",
				STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	handle_outfile(t_lexer *redirection)
{
	int	fd;

	fd = check_append_outfile(redirection);
	if (fd < 0)
	{
		if ((access(redirection->word, W_OK | R_OK)))
			ft_putstr_fd("minishell:  Permission denied\n", STDERR_FILENO);
		else
			ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	create_heredoc(t_lexer *heredoc, bool quotes, t_tools *tools,
		char *file_name)
{
	int		fd;
	char	*line;

	signal(SIGQUIT, SIG_IGN);
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(HEREDOC_MSG);
	while (line && ft_strcmp(heredoc->word, line) && !g_global.stop_heredoc)
	{
		if (quotes == false)
			line = expand_str(tools, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_MSG);
	}
	free(line);
	if (g_global.stop_heredoc || !line)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

char	*append_char_to_str(char *tmp, char c)
{
	char	*tmp2;
	char	*tmp3;

	tmp2 = char_to_str(c);
	tmp3 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	return (tmp3);
}


char	*detect_dollar_sign(t_tools *tools, char *s)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = ft_strdup("");
	while (s[j])
	{
		if (s[j] == '$' && ft_isdigit(s[j + 1]))
			j += handle_digit(j, s, &tmp);
		else if (s[j] == '$' && s[j + 1] == '$')
			j += dolar_dolar(s, j);
		else if (s[j] == '$' && s[j + 1] == '?')
			j += question_mark(&tmp);
		else if (s[j] == '$' && s[j + 1] && s[j + 1] != 32 && (s[j + 1] != '"'
				|| s[j + 2]))
			j += loop_if_dollar_sign(tools, s, &tmp, j);
		else
			tmp = append_char_to_str(tmp, s[j++]);
	}
	return (tmp);
}
