/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 20:11:15 by glima-de          #+#    #+#             */
/*   Updated: 2021/09/06 20:11:15 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*aux;
	size_t	i;

	i = 0;
	aux = malloc(nmemb * size);
	if (aux)
	{
		while (i < nmemb * size)
		{
			aux[i] = '\0';
			i++;
		}
	}
	return ((void *)aux);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

unsigned int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*aux;
	size_t	i;
	size_t	ia;

	i = 0;
	ia = 0;
	aux = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	while (s1[i])
	{
		aux[ia] = s1[i];
		i++;
		ia++;
	}
	i = 0;
	while (s2[i])
	{
		aux[ia] = s2[i];
		i++;
		ia++;
	}
	aux[ia] = '\0';
	return (aux);
}
