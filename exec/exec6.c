/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:25:20 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 10:03:59 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/global_header.h"
#include "../header_file/execution.h"

size_t	equal_sgn(char *str)
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
		fd = open(redirections->word, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redirections->word, O_CREAT | O_RDWR | O_TRUNC, 0644);
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
	int		i;
	int		x;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	x = 0;
	while (tools->env[i])
	{
		if (ft_strncmp(str + j + 1, tools->env[i], equal_sgn(tools->env[i])
				- 1) == 0 && after_dol(str, j)
			- j == (int)equal_sgn(tools->env[i]))
		{
			tmp2 = ft_strdup(tools->env[i] + equal_sgn(tools->env[i]));
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			x = equal_sgn(tools->env[i]);
		}
		i++;
	}
	if (x == 0)
		x = after_dol(str, j) - j;
	return (x);
}

int	question_mark(char **tmp)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_itoa(g_global.error_num);
	tmp2 = *tmp;
	*tmp = ft_strjoin(*tmp, tmp1);
	free(tmp1);
	free(tmp2);
	return (2);
}
