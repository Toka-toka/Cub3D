/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 04:29:58 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/08 04:30:00 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*temp;
	size_t	ind;
	size_t	ind_s;
	size_t	ind_e;

	if (s1 == NULL)
		return (NULL);
	if (set[0] == '\0' || set == NULL)
		return ((char *)s1);
	ind_s = 0;
	ind_e = ft_strlen(s1);
	while (ft_strrchr(set, s1[ind_s]) != 0 && s1[ind_s] != '\0')
		ind_s++;
	while (ft_strrchr(set, s1[ind_e]) != 0 && ind_s < ind_e)
		ind_e--;
	temp = malloc(sizeof(*s1) * (ind_e - ind_s + 2));
	if (temp == NULL)
		return (NULL);
	ind = 0;
	while (ind_s + ind <= ind_e)
	{
		temp[ind] = s1[ind_s + ind];
		ind++;
	}
	temp[ind] = '\0';
	return (temp);
}
