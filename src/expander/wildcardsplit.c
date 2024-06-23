/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcardsplit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 17:52:15 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/19 20:26:13 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean(size_t i, char **ptr)
{
	size_t		j;

	j = i;
	while (i <= j)
	{
		free(ptr[i]);
		i--;
	}
	free(ptr);
}

static void	writeiter(char const *s, size_t j, size_t *k, char c)
{
	char	quote;

	while ((s[j + *k] != c) && (s[j + *k] != '\0'))
	{
		if (s[j + *k] == '\'' || s[j + *k] == '\"')
		{
			quote = s[j + *k];
			(*k)++;
			while ((s)[j + *k] != quote && (s[j + *k] != '\0'))
				(*k)++;
			(*k)++;
		}	
		else
			(*k)++;
	}
}

static void	writearr(char const *s, char **ptr, char c, int i)
{
	size_t		j;
	size_t		k;

	j = 0;
	while (s[j] != '\0')
	{
		k = 0;
		if (s[j] != c)
		{
			writeiter(s, j, &k, c);
			ptr[i] = ft_substr(s, j, k);
			if (ptr[i] == NULL)
			{
				clean(i, ptr);
				return ;
			}
			i++;
			j += k;
		}
		if (s[j] != '\0')
			j++;
	}
	ptr[i] = NULL;
}

char	**wildcardsplit(char const *s, char c)
{
	char	**ptr;
	size_t	n;
	int		i;

	n = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	countsubstr(s, &n, c);
	ptr = (char **)malloc((n + 1) * sizeof(char *));
	if (ptr != NULL)
		writearr(s, ptr, c, i);
	return (ptr);
}
