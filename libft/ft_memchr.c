/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 01:19:11 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/02 01:19:18 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *mass, int ch, size_t cnt)
{
	unsigned char *temp_mass;
	unsigned char temp_ch;

	temp_mass = (unsigned char*)mass;
	temp_ch = ch;
	while ((cnt > 0) && (temp_ch != *temp_mass))
	{
		temp_mass++;
		cnt--;
	}
	if (cnt != 0)
		return (temp_mass);
	return (NULL);
}
