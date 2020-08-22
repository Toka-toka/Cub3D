/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 17:26:30 by jmitchel          #+#    #+#             */
/*   Updated: 2020/05/25 17:26:35 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int chr, size_t cnt)
{
	unsigned char	*nstr;
	unsigned char	nchr;

	nstr = (unsigned char*)str;
	nchr = chr;
	while (cnt > 0)
	{
		*nstr = nchr;
		nstr++;
		cnt--;
	}
	return (str);
}
