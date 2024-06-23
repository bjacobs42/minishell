/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:43:47 by bjacobs           #+#    #+#             */
/*   Updated: 2023/01/18 17:10:44 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_clear_arr(void **array, int i)
{
	while (i--)
	{
		free(array[i]);
		array[i] = NULL;
	}			
	free(array);
	array = NULL;
}
