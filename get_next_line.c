/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:35:40 by glima-de          #+#    #+#             */
/*   Updated: 2021/09/17 19:12:21 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*readFile(int *sr, int fd)
{
	char	*r;
	char	*aux;

	r = calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!r)
	{
		*sr = -1;
		return (NULL);
	}
	*sr = read(fd, (void *)r, BUFFER_SIZE);
	if (*sr <= 0)
	{
		free(r);
		return (NULL);
	}
	aux = ft_calloc(sizeof(char), *sr + 1);
	if (!aux)
		return (NULL);
	ft_strlcpy(aux, r, *sr + 1);
	free(r);
	return (aux);
}

static int	findReturnChar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*split(char *left, char *right, int nPos)
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
	nPos = 0;
	if (lastRead)
	{
		nPos = findReturnChar(lastRead);
		if (nPos >= 0)
		{
			auxR = ft_calloc(sizeof(char), nPos + 2);
			auxSwap = lastRead;
			lastRead = split(auxR, auxSwap, nPos);
			free(auxSwap);
			return (auxR);
		}
		else
		{
			auxR = readFile(&nPos, fd);
			auxSwap = lastRead;
			if (nPos <= 0)
			{
				lastRead = NULL;
				return (auxSwap);
			}
			lastRead = ft_strjoin(lastRead, auxR);
			free(auxSwap);
			free(auxR);
			if (!lastRead)
				return (NULL);
			return (get_next_line(fd));
		}
	}
	else
	{
		lastRead = readFile(&nPos, fd);
		if (!lastRead)
			return (NULL);
		return (get_next_line(fd));
	}
}
