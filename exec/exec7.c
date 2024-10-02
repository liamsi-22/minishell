/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:26:00 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/02 22:26:23 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"
#include "../global_header.h"

int export_error(char *c)
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

char *delete_quotes(char *str)
{
	int i;
	int j;
	char *sub;
	char *final_str;
	char sep;

	if (!str)
		return (NULL);
	sep = '\0';
	final_str = ft_strdup("");
	i = 0;
	j = 0;
	while (str[i])
	{

		if (str[i] != '\'' && str[i] != '"')
		{
			j = i;
			while (str[i] && str[i] != '\'' && str[i] != '"')
				i++;
			sub = malloc(i - j + 1);
			if (!sub)
				return NULL;
			ft_strncpy(sub, &str[j], i - j);
			sub[i - j] = '\0';
			char *temp = final_str;
			final_str = ft_strjoin(final_str, sub);
			free(temp);
			free(sub);
		}
		else
		{
			sep = str[i];
			i++;
			j = i;
			while (str[i] && str[i] != sep)
				i++;
			sub = malloc(i - j + 1);
			if (!sub)
				return NULL;
			ft_strncpy(sub, &str[j], i - j);
			sub[i - j] = '\0';
			char *temp = final_str;
			final_str = ft_strjoin(final_str, sub);
			free(temp);
			free(sub);
			if (str[i] == sep && str[i])
				i++;
		}
	}
	free(str);
	str = final_str;
	return (str);
}

int cmd_not_found(char *str, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		return (126);
	}
	else if (i == 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}

	return (127);
}

int ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int after_dol_lenght(char *str, int j)
{
	int i;

	i = j + 1;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' ' && str[i] != '\"' && str[i] != '\'' && str[i] != '=' && str[i] != '-' && str[i] != ':')
		i++;
	return (i);
}
