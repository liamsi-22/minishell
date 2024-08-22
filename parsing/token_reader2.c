#include "../parsing.h"

int	skip_quotes(int i, char *str, char del)
{
	int	j;

	j = 0;
	if (str[i + j] == del)
	{
		j++;
		while (str[i + j] != del && str[i + j])
			j++;
		j++;
	}
	return (j);
}

int	add_lexer_node(char *str, t_tokens token, t_lexer **lexer_list)
{
	t_lexer	*node;

	node = lexer_new(str, token);
	if (!node)
		return (0);
	lexer_addback(lexer_list, node);
	return (1);
}

int	read_word(int i, char *str, t_lexer **lexer_list)
{
	int	j;

	j = 0;
	while (str[i + j] && !(check_token(str[i + j])))
	{
		j += skip_quotes(i + j, str, 34);
		j += skip_quotes(i + j, str, 39);
		if (is_whitespace(str[i + j]))
			break ;
		else
			j++;
	}
	if (!add_lexer_node(ft_substr(str, i, j), 0, lexer_list))
		return (-1);
	return (j);
}

