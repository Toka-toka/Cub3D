/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 19:18:45 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/03 19:18:57 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *str_out, char *str_in, size_t len)
{
	size_t cnt;
	size_t len_o;

	cnt = 0;
	len_o = ft_strlen(str_out);
	if (len == 0)
		return (ft_strlen(str_in));
	if (len < len_o)
		return (ft_strlen(str_in) + len);
	if (len > len_o)
		while ((len_o + cnt) < len - 1 && str_in[cnt] != '\0')
		{
			str_out[len_o + cnt] = str_in[cnt];
			cnt++;
		}
	str_out[len_o + cnt] = '\0';
	return (len_o + ft_strlen(str_in));
}
