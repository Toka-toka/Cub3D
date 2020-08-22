/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 01:30:08 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/08 01:30:12 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *str_out, const char *str_in, size_t len)
{
	size_t cnt;
	size_t len_in;

	cnt = 0;
	if (str_in == NULL || str_out == NULL)
		return (0);
	len_in = ft_strlen(str_in);
	if (len <= 0)
		return (len_in);
	while ((cnt < (len - 1)) && str_in[cnt] != '\0')
	{
		str_out[cnt] = str_in[cnt];
		cnt++;
	}
	str_out[cnt] = '\0';
	return (len_in);
}
