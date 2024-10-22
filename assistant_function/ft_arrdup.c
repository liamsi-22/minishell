/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:56:59 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 10:40:16 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/parsing.h"

char	**ft_arrdup(char **arr)
{
	char	**array2;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	array2 = malloc(sizeof(char *) * (i + 1));
	if (!array2)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		array2[i] = ft_strdup(arr[i]);
		if (array2[i] == NULL)
		{
			free_arr(array2);
			return (NULL);
		}
		i++;
	}
	array2[i] = NULL;
	return (array2);
}
