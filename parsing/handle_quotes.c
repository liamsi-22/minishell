#include "../parsing.h"

int find_matching_quote(char *line, int i, int *num_del, int del)
{
	int j;

	j = i + 1;
	*num_del += 1;
	while (line[j] && line[j] != del)
		j++;
	if (!line[j])
		return (-1);
	*num_del += 1;
	return (j - i);
}

int avoiding_25line(char *line, int *sgl_quote, int *dbl_quote)
{
	int i;
	int len;

	i = -1;
	while (line[++i])
	{
		if (line[i] == 34)
		{
			len = find_matching_quote(line, i, dbl_quote, 34);
			if (len == -1)
				return (0);
			i += len;
		}
		else if (line[i] == 39)
		{
			len = find_matching_quote(line, i, sgl_quote, 39);
			if (len == -1)
				return (0);
			i += len;
		}
	}
	return (1);
}

int handle_quotes(char *line)
{
	int sgl_quote;
	int dbl_quote;

	sgl_quote = 0;
	dbl_quote = 0;
	if (!avoiding_25line(line, &sgl_quote, &dbl_quote))
		return (0);
	if ((dbl_quote > 0 && dbl_quote % 2 != 0) || (sgl_quote > 0 && sgl_quote % 2 != 0))
		return (0);
	return (1);
}
