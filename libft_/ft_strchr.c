/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:52:20 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/05 01:52:25 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	char	*str_temp;
	size_t	ind;

	str_temp = (char*)str;
	ind = 0;
	while (str_temp[ind] != '\0')
	{
		if (str_temp[ind] == ch)
			return (str_temp + ind);
		ind++;
	}
	if (ch == '\0')
		return (str_temp + ind);
	return (NULL);
}
