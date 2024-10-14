/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:24:44 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/07 16:29:07 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../global_header.h"
#include "../parsing.h"
#include <signal.h>

void	sigquit_handler(int sig);

int	handle_digit(int j, char *str, char **tmp)
{
	int		i;
	char	*tmp2;

	i = j;
	if (str[j] == '$')
	{
		if (ft_isdigit(str[j + 1]) == 1)
		{
			if (str[j + 1] == '0' && !ft_isdigit(str[j + 2]))
			{
				tmp2 = ft_strjoin(*tmp, "bash");
				free(*tmp);
				*tmp = tmp2;
			}
			j += 2;
		}
	}
	return (j - i);
}

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
	while (line && ft_strncmp(heredoc->word, line, ft_strlen(heredoc->word))
		&& !g_global.stop_heredoc)
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

char	*detect_dollar_sign(t_tools *tools, char *str)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = 0;
	tmp = ft_strdup("");
	while (str[j])
	{
		if (str[j] == '$' && ft_isdigit(str[j + 1]))
			j += handle_digit(j, str, &tmp);
		else if (str[j] == '$' && str[j + 1] == '?')
			j += question_mark(&tmp);
		else if (str[j] == '$' && str[j + 1] && str[j + 1] != 32 && str[j + 1] != '"')
			j += loop_if_dollar_sign(tools, str, &tmp, j);
		else
		{
			tmp2 = char_to_str(str[j++]);
			tmp3 = ft_strjoin(tmp, tmp2);
			free(tmp);
			tmp = tmp3;
			free(tmp2);
		}
	}
	return (tmp);
}
