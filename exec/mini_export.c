
#include "../parsing.h"

int	variable_exist(t_tools *tools, char *str)
{
	int	i;
	char *tmp;

	i = 0;
	while (tools->env[i])
	{
		if (ft_strncmp(tools->env[i],
				str, equal_sign(tools->env[i])) == 0)
		{
			free(tools->env[i]);
			tools->env[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}
int	check_parameter(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (export_error(str));
	while (str[i] && str[i] != '=')
	{
		if (check_valid_identifier(str[i]))
			return (export_error(str));
		i++;
	}
	if (str[0] == '=')
		return (export_error(str));
	return (EXIT_SUCCESS);
}

char	**whileloop_add_var(char **env, char **new_env, char *str)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (env[i + 1] == NULL)
		{
			new_env[i] = ft_strdup(str);
			new_env[i + 1] = ft_strdup(env[i]);
		}
		else
			new_env[i] = ft_strdup(env[i]);
		if (new_env[i] == NULL)
			return (new_env);
		i++;
	}
	return (new_env);
}

char	**add_var(char **env, char *str)
{
	char	**new_env;
	size_t	i;
	char	*tmp;

	i = 0;
	while (env[i] != NULL)
		i++;
	new_env = ft_calloc(sizeof(char *), i + 2);
	if (!new_env)
		return (NULL);
	// i = 0;
	new_env = whileloop_add_var(env, new_env, str);
	return (new_env);
}

int	mini_export(t_tools *tools, t_simple_cmds *simple_cmd)
{
	char	**tmp;
	int		i;

	i = 1;
	if (!simple_cmd->str[1] || simple_cmd->str[1][0] == '\0')
		mini_env(tools, simple_cmd);
	else
	{
		while (simple_cmd->str[i])
		{
			if (check_parameter(simple_cmd->str[i]) == 0
				&& variable_exist(tools, simple_cmd->str[i]) == 0)
			{
				if (simple_cmd->str[i])
				{
					tmp = add_var(tools->env, simple_cmd->str[i]);
					free_arr(tools->env);
					tools->env = tmp;
				}
			}
			else if (check_parameter(simple_cmd->str[i]) != 0)
				return (EXIT_FAILURE);
			i++;
		}

	}
	return (EXIT_SUCCESS);
}
