/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 03:05:49 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/10 03:05:52 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	invert_pr(int index, int zn, int fd)
{
	int	ost;

	if (index != 0)
	{
		ost = index % 10;
		if (ost == 0 && index == 0)
			return ;
		invert_pr(index / 10, zn, fd);
		ft_putchar_fd(ost * zn + '0', fd);
		return ;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		ft_putchar_fd('0', fd);
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		invert_pr(n, -1, fd);
		return ;
	}
	if (n > 0)
	{
		invert_pr(n, 1, fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		invert_pr(n, -1, fd);
		return ;
	}
}
