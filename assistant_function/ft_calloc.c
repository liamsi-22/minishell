/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:40:06 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/22 10:40:30 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../header_file/parsing.h"

void	*ft_calloc(size_t count, size_t size)
{
	int	*ret;

	ret = malloc(count * size);
	if (!ret)
		return (0);
	ft_bzero(ret, count * size);
	return (ret);
}
