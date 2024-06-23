/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 21:31:38 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/06/01 22:09:03 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdbool.h"
#include "stdlib.h"

static int	llong_min_max(char *s, bool sign)
{
	size_t	i;

	i = 0;
	while (s[i] == '0')
		i++;
	if (ft_strlen(&s[i]) < 19)
		return (0);
	if (sign)
		return (ft_strncmp(&s[i], "9223372036854775808", 20));
	return (ft_strncmp(&s[i], "9223372036854775807", 20));
}

int	parse_str_llong(char *s)
{
	size_t	i;

	i = 0;
	if (s[i] == '-' && s[i + 1])
	{
		i++;
		if (llong_min_max(&s[i], true) > 0)
			return (EXIT_FAILURE);
	}
	else
	{
		if (s[i] == '+' && s[i + 1])
			i++;
		if (llong_min_max(&s[i], false) > 0)
			return (EXIT_FAILURE);
	}
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
