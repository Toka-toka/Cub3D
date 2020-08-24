/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 00:54:14 by jmitchel          #+#    #+#             */
/*   Updated: 2020/05/26 00:54:16 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

void	ft_bzero(void *str, size_t cnt);
void	*ft_memccpy (void *str_out, const void *str_in, int ch, size_t cnt);
void	*ft_memchr(const void *mass, int ch, size_t cnt);
int		ft_memcmp(const void *mass_1, const void *mass_2, size_t cnt);
void	*ft_memcpy (void *str_out, const void *str_in, size_t cnt);
void	*ft_memmove (void *str_out, const void *str_in, size_t cnt);
void	*ft_memset(void *str, int chr, size_t cnt);
size_t	ft_strlcat (char *str_out, char *str_in, size_t len);
size_t	ft_strlcpy (char *str_out, const char *str_in, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int ch);
char	*ft_strrchr(const char *str, int ch);
char	*ft_strnstr(const char *str, const char *find, size_t len);
int		ft_strncmp(const char *str_1, const char *str_2, size_t len);
int		ft_atoi(const char *str);
int		ft_isalpha (int ch);
int		ft_isdigit (int ch);
int		ft_isalnum (int ch);
int		ft_isascii (int ch);
int		ft_isprint (int ch);
int		ft_toupper (int ch);
int		ft_tolower (int ch);
void	*ft_calloc(size_t num, size_t sz);
char	*ft_strdup(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putendl_fd(char *s, int fd);
char	*ft_itoa(int n);
int		get_next_line(int fd, char **line);

#endif
