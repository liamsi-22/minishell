#include "../parsing.h"

int	find_matching_quote(char *line, int i, int *num_del, int del)
{
	int	j;

	j = i + 1;
	*num_del += 1;
	while (line[j] && line[j] != del)
		j++;
	if (line[j] == del)
		*num_del += 1;
	return (j - i);
}

int	handle_quotes(char *line)
{
	int	i;
	int	num_sgl_quote;
	int	num_dbl_quote;

	num_sgl_quote = 0;
	num_dbl_quote = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == 34)
			i += find_matching_quote(line, i, &num_dbl_quote, 34);
		if (line[i] == 39)
			i += find_matching_quote(line, i, &num_sgl_quote, 39);
	}
	if ((num_dbl_quote > 0 && num_dbl_quote % 2 != 0) || (num_sgl_quote > 0 && num_sgl_quote % 2 != 0))
		return (0);
	return (1);
}
