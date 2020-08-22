/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 01:46:27 by jmitchel          #+#    #+#             */
/*   Updated: 2020/06/09 01:46:32 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sz(char *s, char c)
{
	int i;
	int sz;

	i = 0;
	sz = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			sz++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (sz);
}

char	**ft_sv_str(char *s, char **temp, char c)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (ft_sz(s, c) > n)
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i + j] != c && s[i + j])
		{
			temp[n][j] = s[i + j];
			j++;
		}
		temp[n][j] = 0;
		i = i + j;
		n++;
	}
	temp[n] = 0;
	return (temp);
}

char	**init_str(char *s, char **temp, char c)
{
	int i;
	int j;
	int n;

	i = 0;
	n = 0;
	while (ft_sz(s, c) > n)
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i + j] != c && s[i + j])
			j++;
		if (!(temp[n] = (char*)malloc(sizeof(char) * (j + 1))))
			return (NULL);
		n++;
		i = i + j;
	}
	return (temp);
}

char	**ft_split(char const *s, char c)
{
	char	**temp;

	if (s == NULL || !c)
		return (NULL);
	if (!(temp = (char**)malloc(sizeof(char*) * (ft_sz((char*)s, c) + 1))))
		return (NULL);
	if (!(temp = init_str((char*)s, temp, c)))
	{
		free(temp);
		return (NULL);
	}
	return (ft_sv_str((char*)s, temp, c));
}
