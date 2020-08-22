/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 00:47:44 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/06 00:48:15 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	len_find;
	size_t	ind;

	ind = 0;
	len_find = ft_strlen(find);
	if (ft_strlen(str) == 0)
		return (NULL);
	if (len_find == 0)
		return ((char*)str);
	while ((len_find + ind) <= len)
	{
		if (ft_memcmp(str + ind, find, len_find) == 0)
			return ((char*)str + ind);
		ind++;
	}
	return (NULL);
}
