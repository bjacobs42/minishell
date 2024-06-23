/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   removequotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 18:25:36 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/14 18:25:37 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	removequotes(char *name)
{
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (name[i])
	{
		if (i != j)
			name[j] = name[i];
		if (name[i] == '\'' || name[i] == '\"')
		{
			quote = name[i++];
			while (name[i] && name[i] != quote)
				name[j++] = name[i++];
			name[j] = name[i];
		}
		else
			j++;
		i++;
	}
	name[j] = '\0';
	return (i - j);
}
