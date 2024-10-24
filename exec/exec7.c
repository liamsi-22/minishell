/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:26:00 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 10:03:59 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/global_header.h"
#include "../header_file/execution.h"

char	*delete_quotes(char *str)
{
	int		i;
	char	*final_str;

	if (!str)
		return (NULL);
	final_str = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			i = splite_function1(str, &final_str, i);
		else
			i = splite_function2(str, &final_str, i);
	}
	free(str);
	str = final_str;
	return (str);
}

int	cmd_not_found(char *str, int i)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (i == 1)
	{
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		return (126);
	}
	else if (i == 0)
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	else
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (127);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	after_dol(char *str, int j)
{
	int	i;

	i = j + 1;
	while ((str[i] >= '0' && str[i] <= '9')
		|| (str[i] >= 'a' && str[i] <= 'z')
		|| (str[i] >= 'A' && str[i] <= 'Z')
		|| str[i] == '_')
		i++;
	return (i);
}

int	dolar_dolar(char *str, int j)
{
	int	i;

	i = j;
	while (str[i] && str[i] == '$')
		i++;
	return (i - j - 1);
}