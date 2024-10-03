/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:57:12 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/01 16:57:12 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	dup_fill(char *str, int index, long int x)
{
	str[index] = '\0';
	if (x == 0)
		str[0] = '0';
	else
	{
		if (x < 0)
		{
			x *= -1;
			str[0] = '-';
		}
		while (x != 0)
		{
			str[--index] = (x % 10) + '0';
			x /= 10;
		}
	}
}

static int	n_len(long int x)
{
	int	index;

	index = 0;
	if (x == 0)
	{
		index++;
		return (index);
	}
	else
	{
		if (x < 0)
			index++;
		while (x != 0)
		{
			x /= 10;
			index++;
		}
	}
	return (index);
}

char	*ft_itoa(int n)
{
	long int	x;
	char		*dup;

	x = n;
	dup = (char *)malloc(n_len(x) + 1);
	if (dup == NULL)
		return (NULL);
	dup_fill(dup, n_len(x), x);
	return (dup);
}
