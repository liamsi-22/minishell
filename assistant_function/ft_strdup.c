/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:57:22 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/01 16:57:23 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	size;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	size = ft_strlen(s1);
	s2 = (char *)malloc((size + 1) * sizeof(char));
	if (!s2)
		return (0);
	while (i < size)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
