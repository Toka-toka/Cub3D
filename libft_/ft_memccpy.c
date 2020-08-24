/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 23:50:03 by jmitchel          #+#    #+#             */
/*   Updated: 2020/05/31 23:50:07 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *str_out, const void *str_in, int ch, size_t cnt)
{
	unsigned char	*temp_out;
	unsigned char	*temp_in;
	unsigned char	temp_ch;
	size_t			ind;

	ind = 0;
	temp_out = (unsigned char*)str_out;
	temp_in = (unsigned char*)str_in;
	temp_ch = (unsigned char)ch;
	if (temp_out == NULL && temp_in == NULL)
		return (str_out);
	while (ind < cnt)
	{
		temp_out[ind] = temp_in[ind];
		if (temp_in[ind] == temp_ch)
			return (temp_out + ind + 1);
		ind++;
	}
	return (NULL);
}
