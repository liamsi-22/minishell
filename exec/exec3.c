/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:18:50 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 10:03:59 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/global_header.h"
#include "../header_file/execution.h"

bool handle_double_quotes(char *str, int *i)
{
    (*i)++;
    while (str[*i] && str[*i] != '"') {
        (*i)++;
    }
    if (!str[*i]) return false;
    (*i)++;
    return true;
}

int is_paire(char *str) {
    int i = 0;
    int x = 0;

    if (!str) return 0;

    while (str[i]) {
        if (str[i] == '"') {
            if (!handle_double_quotes(str, &i)) {
                break;
            }
        } else if (str[i] == '\'') {
            x++;
            i++;
        } else if (str[i] == '$') {
            break;
        } else {
            i++;
        }
    }
    return x;
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
		str[i] = ft_strtrim2(tmp);
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
					% 2 == 0))
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
