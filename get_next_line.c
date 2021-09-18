/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:35:40 by glima-de          #+#    #+#             */
/*   Updated: 2021/09/18 10:26:41 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	readFile(char **lastRead, int fd)
{
	char	*r;
	int		sr;
	char	*aux;

	r = calloc(sizeof(char), BUFFER_SIZE + 1);
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

static int	findReturnChar(char *str)
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

static char	*my_split(char *left, char *right, int nPos)
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
	int			nPos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	nPos = findReturnChar(lastRead);
	if (lastRead)
	{
		auxSwap = lastRead;
		if (nPos >= 0)
		{
			auxR = ft_calloc(sizeof(char), nPos + 2);
			lastRead = my_split(auxR, lastRead, nPos);
			free(auxSwap);
			return (auxR);
		}
		if (readFile(&lastRead, fd) <= 0)
		{
			lastRead = NULL;
			return (auxSwap);
		}
		return (get_next_line(fd));
	}
	if (readFile(&lastRead, fd) <= 0)
		return (NULL);
	return (get_next_line(fd));
}
