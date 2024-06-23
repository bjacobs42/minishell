/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   emptycheck.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/18 17:18:31 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/19 20:27:00 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_empty(char ***args, size_t *i)
{
	size_t	size;
	char	**temp;
	size_t	idx;

	size = ft_strarr_size(*args);
	idx = 0;
	if (size < 1)
		return (1);
	temp = malloc(size * sizeof(char *));
	if (temp == NULL)
		return (1);
	while (idx < size - 1)
	{
		if (idx >= *i)
			temp[idx] = (*args)[idx + 1];
		else
			temp[idx] = (*args)[idx];
		idx++;
	}
	temp[size - 1] = NULL;
	free((*args)[*i]);
	free(*args);
	*args = temp;
	(*i)--;
	return (0);
}

static int	onlyspacecheck(char *word)
{
	int	i;

	i = 0;
	if (word != NULL)
	{
		if (ft_strlen(word) == 0)
			return (1);
		while (word[i] != '\0')
		{
			if (ft_isspace(word[i]) == 0)
				return (0);
		}
	}
	return (1);
}

int	emptycheck(char ***args, size_t *i)
{
	if (*args == NULL)
		return (0);
	if (onlyspacecheck((*args)[*i]) == 1)
	{
		if (remove_empty(args, i) == 1)
			return (1);
	}
	return (0);
}
