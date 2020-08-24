/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 23:58:29 by jmitchel          #+#    #+#             */
/*   Updated: 2020/05/25 23:58:39 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *str_out, const void *str_in, size_t cnt)
{
	unsigned char	*temp_out;
	unsigned char	*temp_in;

	temp_out = (unsigned char*)str_out;
	temp_in = (unsigned char*)str_in;
	if (temp_out == NULL && temp_in == NULL)
		return (str_out);
	while (cnt > 0)
	{
		*temp_out = *temp_in;
		temp_out++;
		temp_in++;
		cnt--;
	}
	return (str_out);
}
