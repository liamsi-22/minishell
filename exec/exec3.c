/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:18:50 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/02 22:26:55 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../global_header.h"
#include "../parsing.h"

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
			break ;
		i++;
	}
	return (x);
}

char	*expand_str(t_tools *tools, char *str)
{
	char	*tmp;
	int		x;

	tmp = NULL;
	x = dollar_sign(str) - 2;
	if (dollar_sign(str) != 0 && str[dollar_sign(str)] != '\0')
	{
		if (x < 0 || str[0] == '"' || (str[dollar_sign(str) - 2] != '\''
				&& is_paire(str) % 2 == 0))
		{
			tmp = detect_dollar_sign(tools, str);
			free(str);
			str = tmp;
		}
	}
	str = delete_quotes(str);
	return (str);
}

int	check_void(char **str, char *tmp, int i)
{
	int		j;
	char	*p;

	j = 0;
	p = NULL;
	if (tmp[0] == '\0')
	{
		p = str[i];
		j = i;
		while (str[j + 1])
		{
			str[j] = str[j + 1];
			j++;
		}
		str[j] = NULL;
		free(tmp);
		free(p);
		return (1);
	}
	else
	{
		free(str[i]);
		str[i] = tmp;
	}
	return (0);
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

char	**expander(t_tools *tools, char **str)
{
	int		i;
	int		j;
	int		check;
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		j = 0;
		check = dollar_sign(str[i]) - 2;
		if (dollar_sign(str[i]) != 0 && str[i][dollar_sign(str[i])] != '\0')
		{
			if (check < 0 || (str[i][0] == '"' && is_paire(str[i]) % 2 == 0)
				|| (str[i][dollar_sign(str[i]) - 2] == '\'' && is_paire(str[i])
					% 2 == 0) || is_paire(str[i]) % 2 == 0)
			{
				tmp = detect_dollar_sign(tools, str[i]);
				j = check_void(str, tmp, i);
			}
		}
		str[i] = delete_quotes(str[i]);
		if (j != 0)
			i--;
	}
	return (str);
}
