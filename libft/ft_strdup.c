/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 17:56:50 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/07 17:56:52 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*temp;
	char	*temp_str;

	temp_str = (char*)str;
	temp = malloc(sizeof(*temp) * (ft_strlen(str) + 1));
	if (temp != NULL)
	{
		ft_strlcpy(temp, temp_str, ft_strlen(str) + 1);
		return (temp);
	}
	return (NULL);
}
