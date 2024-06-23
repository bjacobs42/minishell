/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:50:44 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/01 17:10:54 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void *p, size_t old_size, size_t new_size)
{
	void	*cp;
	size_t	smallest;

	cp = malloc(new_size);
	if (!cp)
		return (NULL);
	if (old_size > new_size)
		smallest = new_size;
	else
		smallest = old_size;
	ft_memcpy(cp, p, smallest);
	free(p);
	return (cp);
}
