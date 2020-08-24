/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 00:42:26 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/03 00:42:32 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *mass_1, const void *mass_2, size_t cnt)
{
	unsigned char *temp_mass_1;
	unsigned char *temp_mass_2;

	temp_mass_1 = (unsigned char*)mass_1;
	temp_mass_2 = (unsigned char*)mass_2;
	while ((cnt > 0) && (*temp_mass_1 == *temp_mass_2))
	{
		temp_mass_1++;
		temp_mass_2++;
		cnt--;
	}
	if (cnt != 0)
		return (*temp_mass_1 - *temp_mass_2);
	return (0);
}
