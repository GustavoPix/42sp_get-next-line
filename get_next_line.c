/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:35:40 by glima-de          #+#    #+#             */
/*   Updated: 2021/09/16 20:56:11 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*readFile(int *sr, int fd)
{
	char	r[BUFFER_SIZE];
	char	*aux;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	*sr = read(fd, r, BUFFER_SIZE);
	r[*sr] = '\0';
	if (*sr <= 0)
		return (NULL);
	aux = ft_calloc(sizeof(char), *sr + 1);
	if (!aux)
		return (NULL);
	ft_strlcpy(aux, r, *sr + 1);
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

char	*get_next_line(int fd)
{
	static char	*lastRead;
	char		*auxR;
	char		*auxSwap;
	int			nPos;

	nPos = 0;
	if (lastRead)
	{
		nPos = findReturnChar(lastRead);
		if (nPos >= 0)
		{
			auxR = ft_calloc(sizeof(char), nPos + 2);
			//printf("auxR -> |%s|\nlastRead -> |%s|\nnPos -> |%d|",auxR, lastRead, nPos);
			ft_strlcpy(auxR, lastRead, nPos + 2);

			if (ft_strlen(&lastRead[nPos + 1]))
				auxSwap = ft_calloc(sizeof(char), ft_strlen(&lastRead[nPos + 1]) + 1);
			else
			{
				free(lastRead);
				lastRead = NULL;
				return (auxR);
			}
			if (!auxR || !auxSwap)
				return (NULL);
			//printf("|c|");
			ft_strlcpy(auxSwap, &lastRead[nPos + 1], ft_strlen(&lastRead[nPos]));
			free(lastRead);
			lastRead = auxSwap;
			//free(auxSwap);
			auxSwap = NULL;
			return (auxR);
		}
		else
		{
			auxR = readFile(&nPos,fd);
			auxSwap = lastRead;
			if (nPos <= 0)
			{
				//free(auxR);
				lastRead = NULL;
				return(auxSwap);
			}
			//printf("|%s| |%d|\n",auxSwap, nPos);
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
		lastRead = readFile(&nPos,fd);
		if (!lastRead)
			return (NULL);
		return (get_next_line(fd));
	}
}
