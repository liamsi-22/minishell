/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:23:02 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/20 15:51:34 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../global_header.h"
#include "../parsing.h"

int	find_cmd(t_simple_cmds *cmd, t_tools *tools)
{
	int		i;
	char	*mycmd;

	if ((tools->pwd && !ft_strcmp(cmd->str[0], tools->pwd))
		|| (!access(cmd->str[0], F_OK) && cmd->str[0][ft_strlen(cmd->str[0])
			- 1] == '/'))
		return (cmd_not_found(cmd->str[0], 1));
	else if (cmd->str[0][0] == '/' && access(cmd->str[0], F_OK))
		return (cmd_not_found(cmd->str[0], 2));
	if (!access(cmd->str[0], F_OK))
		execve(cmd->str[0], cmd->str, tools->env);
	i = 0;
	while (tools->paths[i] && cmd->str[0][0] != '/')
	{
		mycmd = ft_strjoin(tools->paths[i], cmd->str[0]);
		if (!access(mycmd, F_OK))
			execve(mycmd, cmd->str, tools->env);
		free(mycmd);
		i++;
	}
	return (cmd_not_found(cmd->str[0], 0));
}

int	check_redirections(t_simple_cmds *cmd)
{
	t_lexer	*start;

	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token == LESS)
		{
			if (handle_infile(cmd->redirections->word))
				return (EXIT_FAILURE);
		}
		else if (cmd->redirections->token == GREAT
			|| cmd->redirections->token == GREAT_GREAT)
		{
			if (handle_outfile(cmd->redirections))
				return (EXIT_FAILURE);
		}
		else if (cmd->redirections->token == LESS_LESS)
		{
			if (handle_infile(cmd->hd_file_name))
				return (EXIT_FAILURE);
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
}

char	*delete_quotes2(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], strlen(str) - i);
		}
		i++;
	}
	return (str);
}

int	ft_heredoc(t_tools *tools, t_lexer *heredoc, char *file_name)
{
	bool	quotes;
	int		x;

	x = EXIT_SUCCESS;
	if ((heredoc->word[0] == '\"' && heredoc->word[ft_strlen(heredoc->word)
				- 1] == '\"') || (heredoc->word[0] == '\''
			&& heredoc->word[ft_strlen(heredoc->word) - 1] == '\''))
		quotes = true;
	else
		quotes = false;
	delete_quotes2(heredoc->word, '\'');
	delete_quotes2(heredoc->word, '"');
	g_global.stop_heredoc = 0;
	g_global.in_heredoc = 1;
	x = create_heredoc(heredoc, quotes, tools, file_name);
	g_global.in_heredoc = 0;
	return (x);
}

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin(".tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}
