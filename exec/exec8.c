/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:29:02 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 10:03:59 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/global_header.h"
#include "../header_file/execution.h"

int	handle_digit(int j, char *str, char **tmp)
{
	int		i;
	char	*tmp2;

	i = j;
	if (str[j] == '$')
	{
		if (ft_isdigit(str[j + 1]) == 1)
		{
			if (str[j + 1] == '0' && !ft_isdigit(str[j + 2]))
			{
				tmp2 = ft_strjoin(*tmp, "minishell");
				free(*tmp);
				*tmp = tmp2;
			}
			j += 2;
		}
	}
	return (j - i);
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

int	export_error(char *c)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	if (c)
	{
		ft_putchar_fd('`', STDERR_FILENO);
		ft_putstr_fd(c, STDERR_FILENO);
	}
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	splite_function1(char *str, char **final_str, int i)
{
	int		j;
	char	*tmp;
	char	*sub;

	j = i;
	while (str[i] && str[i] != '\'' && str[i] != '"')
		i++;
	sub = malloc(i - j + 1);
	if (!sub)
		return (0);
	ft_strncpy(sub, &str[j], i - j);
	sub[i - j] = '\0';
	tmp = *final_str;
	*final_str = ft_strjoin(*final_str, sub);
	free(tmp);
	free(sub);
	return (i);
}

int	splite_function2(char *str, char **final_str, int i)
{
	int		j;
	char	sep;
	char	*sub;
	char	*tmp;

	sep = str[i];
	i++;
	j = i;
	while (str[i] && str[i] != sep)
		i++;
	sub = malloc(i - j + 1);
	if (!sub)
		return (0);
	ft_strncpy(sub, &str[j], i - j);
	sub[i - j] = '\0';
	tmp = *final_str;
	*final_str = ft_strjoin(*final_str, sub);
	free(tmp);
	free(sub);
	if (str[i] == sep && str[i])
		i++;
	return (i);
}
