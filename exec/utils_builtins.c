/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:58:18 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/03 20:58:09 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../parsing.h"

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