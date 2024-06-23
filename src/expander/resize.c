/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resize.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:48:10 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/09 20:48:11 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* resizes the string array to match the amount of wildcard matches
 * returns a resized p */
char	**resize(char **p, size_t oldsize, size_t newsize)
{
	char	**cp;
	size_t	i;

	cp = (char **)malloc(sizeof(char *) * (newsize + 1));
	if (!cp)
		return (free(p), NULL);
	i = 0;
	cp[newsize] = NULL;
	while (i < newsize && i < oldsize)
	{
		cp[i] = p[i];
		i++;
	}
	free(p);
	return (cp);
}
