/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 03:23:40 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/07 03:23:43 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t sz)
{
	void *temp;

	temp = malloc(sz * num);
	if (temp != NULL)
	{
		ft_bzero(temp, sz * num);
		return (temp);
	}
	return (NULL);
}
