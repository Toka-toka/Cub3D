/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 00:47:31 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/01 00:47:35 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str_out, const void *str_in, size_t cnt)
{
	unsigned char	*temp_out;
	unsigned char	*temp_in;

	temp_out = (unsigned char*)str_out;
	temp_in = (unsigned char*)str_in;
	if (temp_out == NULL && temp_in == NULL)
		return (NULL);
	if (str_in > str_out)
		while (cnt > 0)
		{
			*temp_out = *temp_in;
			temp_out++;
			temp_in++;
			cnt--;
		}
	else
		while (cnt > 0)
		{
			temp_out[cnt - 1] = temp_in[cnt - 1];
			cnt--;
		}
	return (str_out);
}
