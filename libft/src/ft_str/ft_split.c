/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:38:14 by bjacobs           #+#    #+#             */
/*   Updated: 2023/04/22 16:42:57 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	strarr_size(char const *s, char c)
{
	size_t	i;
	size_t	strarr_size;

	i = 0;
	strarr_size = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			strarr_size++;
		}
		else
			i++;
	}
	return (strarr_size);
}

static char	**create_strarr(char const *s, char c, char **strarr)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	start = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			strarr[j] = ft_substr(s, start, i - start);
			if (!strarr[j])
				return (ft_clear_strarr(strarr), NULL);
			j++;
		}
		else
			i++;
	}
	return (strarr);
}

char	**ft_split(char const *s, char c)
{
	size_t	strarr_s;
	char	**strarr;

	strarr_s = strarr_size(s, c);
	strarr = (char **)malloc(sizeof(char *) * (strarr_s + 1));
	if (!strarr)
		return (NULL);
	strarr[strarr_s] = NULL;
	if (!create_strarr(s, c, strarr))
		return (NULL);
	return (strarr);
}
