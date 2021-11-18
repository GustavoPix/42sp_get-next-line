/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:35:40 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/18 20:39:22 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_file(char **lastRead, int fd)
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

static int	find_return_char(char *str)
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
	char		*aux_swap;

	ft_strlcpy(left, right, nPos + 2);
	if (ft_strlen(&right[nPos + 1]))
		aux_swap = ft_calloc(sizeof(char), ft_strlen(&right[nPos + 1]) + 1);
	else
		return (NULL);
	if (!left || !aux_swap)
		return (NULL);
	ft_strlcpy(aux_swap, &right[nPos + 1], ft_strlen(&right[nPos]));
	return (aux_swap);
}

char	*get_next_line(int fd)
{
	static char	*lread;
	char		*aux_read;
	char		*aux_swap;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (lread)
	{
		aux_swap = lread;
		if (find_return_char(lread) >= 0)
		{
			aux_read = ft_calloc(sizeof(char), find_return_char(lread) + 2);
			lread = gnl_split(aux_read, lread, find_return_char(lread));
			free(aux_swap);
			return (aux_read);
		}
		if (read_file(&lread, fd) <= 0)
		{
			lread = NULL;
			return (aux_swap);
		}
	}
	else if (read_file(&lread, fd) <= 0)
		return (NULL);
	return (get_next_line(fd));
}
