#include "../parsing.h"
#include "../global_header.h"

char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup("\0"));
}

int	init_path(t_tools *tools)
{
	char	*env_path;
	int		i;
	char	*tmp;

	env_path = find_path(tools->env);
	tools->paths = ft_split(env_path, ':');
	free(env_path);
	i = 0;
	while (tools->paths[i])
	{
		if (ft_strncmp(&tools->paths[i][ft_strlen(tools->paths[i]) - 1],
			"/", 1) != 0)
		{
			tmp = ft_strjoin(tools->paths[i], "/");
			free(tools->paths[i]);
			tools->paths[i] = tmp;
		}
		i++;
	}
	return (0);
}

int	init_tools(t_tools *tools)
{
	t_heredoc	g_heredoc;

	tools->simple_cmds = NULL;
	tools->lexer_list = NULL;
	tools->reset = false;
	tools->pid = NULL;
	tools->heredoc = false;
	g_heredoc.stop_heredoc = 0;
	g_heredoc.in_cmd = 0;
	g_heredoc.in_heredoc = 0;
	init_path(tools);
    // init_signals();
	return (1);
}