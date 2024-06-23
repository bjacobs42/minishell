/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:12:07 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/01 19:10:55 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_fd.h"
#include <stdlib.h>

int	print_p(unsigned long long n, int fd)
{
	int		characters;
	char	*hex;
	char	*s;

	hex = ft_btoa(n, 16);
	if (!hex)
		return (-1);
	s = ft_strjoin("0x", 0, hex);
	free(hex);
	if (!s)
		return (-1);
	characters = print_s(s, fd);
	return (free(s), characters);
}
