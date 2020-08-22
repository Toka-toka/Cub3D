/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 23:49:12 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/06 23:49:15 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int i;
	int flag;
	int summ;

	summ = 0;
	flag = 1;
	i = 0;
	while (*str == '\b' || *str == '\f' || *str == '\n' || *str == '\r'
			|| *str == '\t' || *str == '\v' || *str == ' ')
		str++;
	if (*str == '-')
		flag = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str <= '9' && *str >= '0')
	{
		summ = summ * 10 + *str - 48;
		str++;
		if (*str > '0' || i > 0)
			i++;
	}
	if (i >= 20)
		return (-0.5 * (flag + 1));
	return (summ = summ * flag);
}
