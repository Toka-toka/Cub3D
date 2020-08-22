/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 23:23:12 by jmitchel          #+#    #+#             */
/*   Updated: 2020/05/25 23:23:15 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t cnt)
{
	unsigned char	*nstr;

	nstr = (unsigned char*)str;
	while (cnt > 0)
	{
		*nstr = '\0';
		nstr++;
		cnt--;
	}
}
