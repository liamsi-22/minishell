/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:57:40 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 10:01:07 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/parsing.h"

int	is_space(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

char	*ft_strtrim(char const *s1)
{
	size_t	start;
	size_t	end;
	char	*dup;

	if (!s1)
		return (NULL);
	start = 0;
	if (!s1[start])
	{
		dup = ft_strdup("");
		return (dup);
	}
	while (s1[start] && is_space(s1[start]) != 0)
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && is_space(s1[end]) != 0)
		end--;
	dup = (char *)malloc(end - start + 2);
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s1 + start, end - start + 2);
	return (dup);
}

char	*ft_strtrim2(char const *s1)
{
	size_t	start;
	size_t	end;
	char	*dup;

	if (!s1)
		return (NULL);
	start = 0;
	if (!s1[start])
	{
		dup = ft_strdup("");
		return (dup);
	}
	while (s1[start] && is_space(s1[start]) != 0)
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && is_space(s1[end]) != 0)
		end--;
	dup = (char *)malloc(end - start + 2);
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s1 + start, end - start + 2);
	free((char *)s1);
	return (dup);
}