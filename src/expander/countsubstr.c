/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   countsubstr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:48:34 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/09 20:48:35 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	substiter(const char *s, size_t *j, size_t *k)
{
	int	quote;

	quote = s[*j];
	(*j)++;
	(*k)++;
	while ((s)[*j] != quote && s[*j] != '\0')
	{
		(*k)++;
		(*j)++;
	}
	if (s[*j] != '\0')
	{
		(*k)++;
		(*j)++;
	}
}

void	countsubstr(char const *s, size_t *n, char c)
{
	size_t		j;
	size_t		k;

	j = 0;
	k = 0;
	while (s[j] != '\0')
	{
		if (s[j] == '\'' || s[j] == '\"')
			substiter(s, &j, &k);
		else if (s[j] != c && s[j] != '\0')
		{
			j++;
			k++;
		}
		else if ((s[j] == c) && (k != 0))
		{
			*n = *n + 1;
			k = 0;
		}
		else
			j++;
	}
	if (k > 0)
		*n = *n + 1;
}
