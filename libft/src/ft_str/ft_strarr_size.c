/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:43:50 by bjacobs           #+#    #+#             */
/*   Updated: 2023/04/26 19:18:53 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strarr_size(char **strarr)
{
	size_t	i;

	if (!strarr)
		return (0);
	i = 0;
	while (strarr[i])
		i++;
	return (i);
}
