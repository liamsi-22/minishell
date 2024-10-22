/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:57:04 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/01 16:57:04 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/parsing.h"

int	ft_atoi(const char *str)
{
	int	ret;
	int	sign;
	int	i;

	i = 0;
	ret = 0;
	sign = 1;
	while (*str == ' ' || (*str > 8 && *str < 14))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		ret = (ret * 10) + (str[i] - '0');
		i++;
		if (i == 10 && str[i] && sign == -1)
			return (0);
		else if (i == 10 && str[i])
			return (-1);
	}
	return (ret * sign);
}
