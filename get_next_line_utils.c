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
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
