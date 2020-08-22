/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 23:47:05 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/05 23:47:09 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	char	*str_temp;
	size_t	ind;

	str_temp = (char*)str;
	ind = ft_strlen(str) + 1;
	while (ind > 0)
	{
		ind--;
		if (str_temp[ind] == ch)
			return (str_temp + ind);
	}
		return (NULL);
}
