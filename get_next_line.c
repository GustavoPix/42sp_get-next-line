/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:35:40 by glima-de          #+#    #+#             */
/*   Updated: 2021/09/18 11:07:40 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	gnl_readFile(char **lastRead, int fd)
{
	char	*r;
	int		sr;
	char	*aux;

	r = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!r)
		return (-1);
	sr = read(fd, (void *)r, BUFFER_SIZE);
	if (sr <= 0)
	{
		free(r);
		return (sr);
	}
	if (!*lastRead)
	{
		*lastRead = ft_calloc(sizeof(char), sr + 1);
		if (!*lastRead)
			return (-1);
	}
	aux = *lastRead;
	*lastRead = ft_strjoin(*lastRead, r);
	free(aux);
	free(r);
	return (sr);
}

static int	gnl_findReturnChar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*gnl_split(char *left, char *right, int nPos)
{
	char		*auxSwap;

	ft_strlcpy(left, right, nPos + 2);
	if (ft_strlen(&right[nPos + 1]))
		auxSwap = ft_calloc(sizeof(char), ft_strlen(&right[nPos + 1]) + 1);
	else
		return (NULL);
	if (!left || !auxSwap)
		return (NULL);
	ft_strlcpy(auxSwap, &right[nPos + 1], ft_strlen(&right[nPos]));
	return (auxSwap);
}

char	*get_next_line(int fd)
{
	static char	*lastRead;
	char		*auxR;
	char		*auxSwap;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (lastRead)
	{
		auxSwap = lastRead;
		if (gnl_findReturnChar(lastRead) >= 0)
		{
			auxR = ft_calloc(sizeof(char), gnl_findReturnChar(lastRead) + 2);
			lastRead = gnl_split(auxR, lastRead, gnl_findReturnChar(lastRead));
			free(auxSwap);
			return (auxR);
		}
		if (gnl_readFile(&lastRead, fd) <= 0)
		{
			lastRead = NULL;
			return (auxSwap);
		}
	}
	else if (gnl_readFile(&lastRead, fd) <= 0)
		return (NULL);
	return (get_next_line(fd));
}
