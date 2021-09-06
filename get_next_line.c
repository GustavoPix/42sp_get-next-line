/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:35:40 by glima-de          #+#    #+#             */
/*   Updated: 2021/09/06 20:16:44 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*read_next_char(size_t sbuf, int fd)
{
	char	r[1];
	char	*buf;
	int		sr;

	sr = read(fd, r, 1);
	if (sr < 0)
		return (NULL);
	if (sr == 0 || r[0] == '\n')
	{
		if (sr == 0)
			sbuf--;
		if (sbuf == 0)
			return (NULL);
		buf = ft_calloc((sbuf + 1), sizeof(char));
	}
	else
		buf = read_next_char(sbuf + 1, fd);
	if (!buf)
		return (NULL);
	if (sr > 0)
		buf[sbuf - 1] = r[0];
	return (buf);
}

char	*get_next_line(int fd)
{
	static int	lastfd = 0;
	static int	end = 0;
	char		*aux;

	if (lastfd == fd)
	{
		if (end)
			return (NULL);
	}
	else
	{
		lastfd = fd;
		end = 0;
	}
	aux = read_next_char(1, fd);
	if (aux)
		return (aux);
	else
	{
		end = 1;
		return (NULL);
	}
}
