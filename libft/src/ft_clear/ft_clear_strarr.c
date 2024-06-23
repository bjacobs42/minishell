/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_strarr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:10:28 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/01 19:10:30 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_clear_strarr(char **strarr)
{
	int	i;

	if (!strarr)
		return ;
	i = 0;
	while (strarr[i])
	{
		free(strarr[i]);
		strarr[i] = NULL;
		i++;
	}
	free(strarr);
}
