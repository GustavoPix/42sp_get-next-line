/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:26:37 by glima-de          #+#    #+#             */
/*   Updated: 2021/09/18 11:08:05 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

char			*get_next_line(int fd);
unsigned int	ft_strlen(const char *str);
void			*ft_calloc(size_t nmemb, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
char			*ft_strjoin(char const *s1, char const *s2);

#endif
