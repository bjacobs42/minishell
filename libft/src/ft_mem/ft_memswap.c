/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:39:23 by bjacobs           #+#    #+#             */
/*   Updated: 2023/04/25 16:39:30 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_memswap(void **p1, void **p2)
{
	void	*storage;

	storage = *p1;
	*p1 = *p2;
	*p2 = storage;
}
