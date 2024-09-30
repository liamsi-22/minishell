
#include "../parsing.h"

void change_path(t_tools *tools)
{
	char *tmp;

	tmp = ft_strdup(tools->pwd);
	if (tools->old_pwd)
		free(tools->old_pwd);
	tools->old_pwd = tmp;
	if (tools->pwd)
		free(tools->pwd);
	tools->pwd = getcwd(NULL, 0);
	if (!tools->pwd)
		tools->pwd = ft_strdup(tools->old_pwd);
}

char *delete_quotes_value(char *str)
{
	char **split_quotes;

	split_quotes = ft_split(str, '"');
	if (!split_quotes[1])
	{
		free_arr(split_quotes);
		split_quotes = ft_split(str, '\'');
	}
	free(str);
	str = ft_strjoin(split_quotes[0], split_quotes[1]);
	free_arr(split_quotes);
	return (str);
}

int check_valid_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']' || c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.' || c == ':' || c == '/' || c == '{' || c == '}' || c == '+' || c == '^' || c == '%' || c == '#' || c == '@' || c == '!' || c == '~' || c == '=' || c == '-' || c == '?' || c == '&' || c == '*');
}