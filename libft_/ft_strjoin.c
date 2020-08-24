/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 23:40:18 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/07 23:40:20 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_1;
	size_t	len_2;
	char	*temp;

	if (!s1 || !s2)
		return (NULL);
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	temp = malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (temp != NULL)
	{
		ft_strlcpy(temp, (char*)s1, len_1 + 1);
		ft_strlcat(temp, (char*)s2, len_1 + len_2 + 1);
		return (temp);
	}
	return (NULL);
}
