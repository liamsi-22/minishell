/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:56:54 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/01 16:56:55 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;

    if (!arr)
        return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
