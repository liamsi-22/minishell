#include "../parsing.h"
#include "../global_header.h"

t_heredoc g_global = {0, 0, 0, 0}; // Define and initialize the global variable

int	export_error(char *c)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	if (c)
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(c, STDERR_FILENO);
		ft_putstr_fd("\': is ", STDERR_FILENO);
	}
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

char *delete_quotes(char *str) {
    int i = 0;
    int j = 0;
    char *sub;
    char *final_str = ft_strdup("");
    char cc = '\0';  // Initialize cc to avoid undefined behavior

    while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
		{
			j = i;
			while (str[i] && str[i] != '\'' && str[i] != '"')
				i++;
			// Allocate memory for sub and copy the substring
			sub = malloc(i - j + 1);
			if (!sub)
				return NULL;
			ft_strncpy(sub, &str[j], i - j);
			sub[i - j] = '\0';  // Null-terminate the substring

			// Join the current substring with the final result string
			char *temp = final_str;
			final_str = ft_strjoin(final_str, sub);
			free(temp);  // Free the old final_str
			free(sub);  // Free the current substring
		}
		else 
		{
			cc = str[i];  // Store the quote character
			i++;  // Move past the opening quote

			j = i;
			while (str[i] && str[i] != cc)
				i++;
			// Allocate memory for sub and copy the substring
			sub = malloc(i - j + 1);
			if (!sub)
				return NULL;
			ft_strncpy(sub, &str[j], i - j);
			sub[i - j] = '\0';  // Null-terminate the substring

			// Join the current substring with the final result string
			char *temp = final_str;
			final_str = ft_strjoin(final_str, sub);
			free(temp);  // Free the old final_str
			free(sub);  // Free the current substring

			// If we encounter the closing quote, skip it
			if (str[i] == cc && str[i])
				i++;
		}
    }
	free(str);
	str = final_str;
    return (str);  // Return the joined result string
}

int	cmd_not_found(char *str, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		return (126);

	}
	else if (i == 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}

	return (127);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	after_dol_lenght(char *str, int j)
{
	int	i;

	i = j + 1;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' '
		&& str[i] != '\"' && str[i] != '\'' && str[i] != '=' && str[i] != '-'
		&& str[i] != ':')
		i++;
	return (i);
}

size_t	equal_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

int	check_append_outfile(t_lexer *redirections)
{
	int	fd;

	if (redirections->token == GREAT_GREAT)
		fd = open(redirections->word,
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redirections->word,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

char	*char_to_str(char c)
{
	char	*str;

	str = ft_calloc(sizeof(char), 2);
	str[0] = c;
	return (str);
}

int	loop_if_dollar_sign(t_tools *tools, char *str, char **tmp, int j)
{
	int		k;
	int		ret;
	char	*tmp2;
	char	*tmp3;

	k = 0;
	ret = 0;
	while (tools->env[k])
	{
		if (ft_strncmp(str + j + 1, tools->env[k], equal_sign(tools->env[k]) - 1) == 0 && after_dol_lenght(str, j) - j == (int)equal_sign(tools->env[k]))
		{
			tmp2 = ft_strdup(tools->env[k] + equal_sign(tools->env[k]));
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			ret = equal_sign(tools->env[k]);
		}
		k++;
	}
	if (ret == 0)
		ret = after_dol_lenght(str, j) - j;
	return (ret);
}

int	question_mark(char **tmp)
{
	char	*tmp0;
	char	*tmp1;
	tmp1 = ft_itoa(g_global.error_num);
	tmp0 = *tmp;
	*tmp = ft_strjoin(*tmp , tmp1);
	free(tmp0);
	free(tmp1);
	return (2);
}

int	handle_digit_after_dollar(int j, char *str, char **tmp)
{
	int	i;
	char *tmp2;

	i = j;
	if (str[j] == '$')
	{
		if (ft_isdigit(str[j + 1]) == 1)
		{
			if (str[j + 1] == '0' && !ft_isdigit(str[j + 2]))
			{
				tmp2 = ft_strjoin(*tmp , "bash");
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

int	create_heredoc(t_lexer *heredoc, bool quotes, t_tools *tools, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(HEREDOC_MSG);
	while (line && ft_strncmp(heredoc->word, line, ft_strlen(heredoc->word))
		&& !g_global.stop_heredoc)
	{
		if (quotes == false)
			line = expander_str(tools, line);
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
			j += handle_digit_after_dollar(j, str, &tmp);
		else if (str[j] == '$' && str[j + 1] == '?')
			j += question_mark(&tmp);
		else if (str[j] == '$' && (str[j + 1] != ' ' && (str[j + 1] != '"' || str[j + 2] != '\0')) && str[j + 1] != '\0')
			j += loop_if_dollar_sign(tools, str, &tmp, j);
		else
		{	

				tmp2 = char_to_str(str[j]);
				tmp3 = ft_strjoin(tmp, tmp2);
				free(tmp);
				tmp = tmp3;
				free(tmp2);
				j++;
		}
	}
	return (tmp);
}

size_t	dollar_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

int	find_cmd(t_simple_cmds *cmd, t_tools *tools)
{
	int		i;
	char	*mycmd;

	i = 0;
	// cmd->str = resplit_str(cmd->str);

	if (!ft_strcmp(cmd->str[0],tools->pwd))
		return (cmd_not_found(cmd->str[0], 1));
	if (!access(cmd->str[0], F_OK) && cmd->str[0][ft_strlen(cmd->str[0]) - 1] ==  '/')
		return (cmd_not_found(cmd->str[0], 1));
	else if (cmd->str[0][0] == '/' && access(cmd->str[0], F_OK))
		return (cmd_not_found(cmd->str[0], 2));
	if (!access(cmd->str[0], F_OK))
		execve(cmd->str[0], cmd->str, tools->env);
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
	int		sl;

	sl = EXIT_SUCCESS;
	if ((heredoc->word[0] == '\"' && heredoc->word[ft_strlen(heredoc->word) - 1] == '\"')
		|| (heredoc->word[0] == '\'' && heredoc->word[ft_strlen(heredoc->word) - 1] == '\''))
		quotes = true;
	else
		quotes = false;
	delete_quotes2(heredoc->word, '\'');
	delete_quotes2(heredoc->word, '"');
	g_global.stop_heredoc = 0;
	g_global.in_heredoc = 1;
	sl = create_heredoc(heredoc, quotes, tools, file_name);
	g_global.in_heredoc = 0;
	tools->heredoc = true;
	return (sl);
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

int	is_paire(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			x++;
		if (str[i] == '$')
			break;
		i++;
	}
	return (x);
}
char	*expander_str(t_tools *tools, char *str)
{
	char	*tmp;

	tmp = NULL;
	int x = dollar_sign(str) - 2;
	if (dollar_sign(str) != 0 && str[dollar_sign(str)] != '\0')
	{
		if (x < 0 || str[0] == '"' || str[dollar_sign(str) - 2] != '\'' && is_paire(str) % 2 == 0)
		{
			tmp = detect_dollar_sign(tools, str);
			free(str);
			str = tmp;
		}
	}
	str = delete_quotes(str);
	return (str);
}

char	**expander(t_tools *tools, char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] != NULL)
	{
		int x = dollar_sign(str[i]) - 2;
		if (dollar_sign(str[i]) != 0 && str[i][dollar_sign(str[i])] != '\0') // remove && str[i][0] != '\''
		{
			if (x < 0 || (str[i][0] == '"' && is_paire(str[i]) % 2 == 0) || (str[i][dollar_sign(str[i]) - 2] == '\'' && is_paire(str[i]) % 2 == 0) || is_paire(str[i]) % 2 == 0)
			{
				tmp = detect_dollar_sign(tools, str[i]);
				free(str[i]);
				str[i] = tmp;
			}
		}
		if (ft_strncmp(str[0], "export", ft_strlen(str[0]) - 1) != 0)
			str[i] = delete_quotes(str[i]);
		i++;
	}
	return (str);
}

void	handle_cmd(t_simple_cmds *cmd, t_tools *tools)
{
	int	exit_code;
	
	exit_code = 0;
	if (cmd->redirections)
		if (check_redirections(cmd))
			exit(1);
	if (cmd->builtin != NULL)
	{
		exit_code = cmd->builtin(tools, cmd);
		exit(exit_code);
	}
	else if (cmd->str[0] && cmd->str[0][0] != '\0') // added cmd->str[0] &&
		exit_code = find_cmd(cmd, tools);
	exit(exit_code);
}

int	send_heredoc(t_tools *tools, t_simple_cmds *cmd)
{
	t_lexer	*start;
	int		sl;

	start = cmd->redirections;
	sl = EXIT_SUCCESS;
	while (cmd->redirections)
	{	
		if (cmd->redirections->token == LESS_LESS)
		{
			if (cmd->hd_file_name)
				free(cmd->hd_file_name);
			cmd->hd_file_name = generate_heredoc_filename();
			sl = ft_heredoc(tools, cmd->redirections, cmd->hd_file_name);
			if (sl)
			{
				g_global.error_num = 1;
				return (reset_tools(tools));
			}
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
}

t_simple_cmds	*call_expander(t_tools *tools, t_simple_cmds *cmd)
{
	t_lexer	*start;

	cmd->str = expander(tools, cmd->str);
	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token != LESS_LESS)
			cmd->redirections->word = expander_str(tools, cmd->redirections->word);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (cmd);
}

void	single_cmd(t_simple_cmds *cmd, t_tools *tools)
{
	int	pid;
	int	status;


	tools->simple_cmds = call_expander(tools, tools->simple_cmds);
	if (cmd->builtin == mini_cd || cmd->builtin == mini_exit
		|| cmd->builtin == mini_export || cmd->builtin == mini_unset)
	{
		g_global.error_num = cmd->builtin(tools, cmd);
		return ;
	}
	send_heredoc(tools, cmd);
	pid = fork();
	if (pid < 0)
		ft_error(5, tools);
	if (pid == 0)
		handle_cmd(cmd, tools);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_global.error_num = WEXITSTATUS(status);
}

int	prepare_executor(t_tools *tools)
{
	//signal(SIGQUIT, sigquit_handler);
	g_global.in_cmd = 1;
	if (tools->pipes == 0)
		single_cmd(tools->simple_cmds, tools);
	else
	{
		tools->pid = ft_calloc(sizeof(int), tools->pipes + 2);
		if (!tools->pid)
			return (ft_error(1, tools));
		executor(tools);
	}
	g_global.in_cmd = 0;
	return (EXIT_SUCCESS);
}
