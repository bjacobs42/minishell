/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:55:07 by bjacobs           #+#    #+#             */
/*   Updated: 2023/04/13 20:00:36 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	print_c(char c, int fd)
{
	int	size;

	size = sizeof(char);
	if (write(fd, &c, size) < 0)
		return (-1);
	return (size);
}

int	print_s(char *s, int fd)
{
	int	size;

	if (!s)
	{
		s = ft_strdup("(null)");
		if (!s)
			return (-1);
		size = print_s(s, fd);
		return (free(s), size);
	}
	size = ft_strlen(s);
	if (write(fd, s, size) < 0)
		return (-1);
	return (size);
}

int	print_u(unsigned int n, int fd)
{
	char	*s;
	int		characters;

	s = ft_btoa(n, 10);
	if (!s)
		return (-1);
	characters = print_s(s, fd);
	return (free(s), characters);
}

int	print_d(int n, int fd)
{
	char	*s;
	int		characters;

	s = ft_itoa(n);
	if (!s)
		return (-1);
	characters = print_s(s, fd);
	return (free(s), characters);
}

int	print_x(unsigned int n, char c, int fd)
{
	int		characters;
	char	*s;

	s = ft_btoa(n, 16);
	if (!s)
		return (-1);
	if (c == 'X')
		ft_ltou(s);
	characters = print_s(s, fd);
	return (free(s), characters);
}
