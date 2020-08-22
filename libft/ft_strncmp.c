/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 22:35:49 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/06 22:35:55 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str_1, const char *str_2, size_t len)
{
	size_t	ind;

	ind = 0;
	while ((str_1[ind] != '\0' || str_2[ind] != '\0') && ind < len)
	{
		if (str_1[ind] != str_2[ind])
			return ((unsigned char)str_1[ind] - (unsigned char)str_2[ind]);
		ind++;
	}
	return (0);
}
