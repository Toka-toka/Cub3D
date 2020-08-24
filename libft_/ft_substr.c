/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 21:29:29 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/07 21:29:34 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *temp;
	
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s) < start ? 0 : len;
	if (len != 0)
		len = len > ft_strlen(s + start) ? ft_strlen(s + start) : len;
	temp = (char*) malloc (sizeof(char) * (len + 1));
	if (!temp)
		return (NULL);
			ft_memcpy(temp, s + start, len);
	temp[len] = '\0';
	return (temp);
}
