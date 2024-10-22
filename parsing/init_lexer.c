/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:21:16 by abakhcha          #+#    #+#             */
/*   Updated: 2024/10/22 10:01:07 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/parsing.h"

t_tokens	check_token(int c)
{
	int			i;
	static int	token_arr[3][2];

	i = 0;
	token_arr[0][0] = '|';
	token_arr[0][1] = PIPE;
	token_arr[1][0] = '>';
	token_arr[1][1] = GREAT;
	token_arr[2][0] = '<';
	token_arr[2][1] = LESS;
	while (i < 3)
	{
		if (token_arr[i][0] == c)
			return (token_arr[i][1]);
		i++;
	}
	return (0);
}

int	read_token(char *str, int i, t_lexer **lexer_list)
{
	t_tokens	token;

	token = check_token(str[i]);
	if (token == GREAT && check_token(str[i + 1]) == GREAT)
	{
		if (!add_lexer_node(NULL, GREAT_GREAT, lexer_list))
			return (-1);
		return (2);
	}
	else if (token == LESS && check_token(str[i + 1]) == LESS)
	{
		if (!add_lexer_node(NULL, LESS_LESS, lexer_list))
			return (-1);
		return (2);
	}
	else if (token)
	{
		if (!add_lexer_node(NULL, token, lexer_list))
			return (-1);
		return (1);
	}
	return (0);
}

int	read_word(int i, char *str, t_lexer **lexer_list)
{
	int	j;

	j = 0;
	while (str[i + j] && !(check_token(str[i + j])))
	{
		if (str[i + j] == 34 || str[i + j] == 39)
			j += skip_quotes(i + j, str, str[i + j]);
		else if (is_space(str[i + j]))
			break ;
		else
			j++;
	}
	if (!add_lexer_node(ft_substr(str, i, j), 0, lexer_list))
		return (-1);
	return (j);
	return (0);
}

int	init_lexer(t_tools *tools)
{
	int	i;
	int	j;

	i = 0;
	while (tools->args[i])
	{
		j = 0;
		i += skip_spaces(tools->args, i);
		if (check_token(tools->args[i]))
			j = read_token(tools->args, i, &tools->lexer_list);
		else
			j = read_word(i, tools->args, &tools->lexer_list);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
