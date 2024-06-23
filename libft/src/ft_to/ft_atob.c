/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:31:23 by bjacobs           #+#    #+#             */
/*   Updated: 2023/04/27 16:18:46 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_index(const char *s, size_t *i, int *sign)
{
	*i = 0;
	*sign = 1;
	while (ft_isspace(s[*i]))
		(*i)++;
	if (s[*i] == '-' || s[*i] == '+')
	{
		if (s[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

long long	ft_atob(const char *s, int base)
{
	size_t		i;
	long long	num;
	int			sign;

	if (!s)
		return (0);
	set_index(s, &i, &sign);
	num = 0;
	while (ft_isdigit(s[i]) || ft_isalpha(s[i]))
	{
		if (ft_isdigit(s[i]))
			num = num * base + s[i] - '0';
		else
			num = num * base + ft_tolower(s[i]) - 'a' + 10;
		i++;
	}
	return (num * sign);
}
