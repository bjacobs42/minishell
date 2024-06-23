/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitargs.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 17:10:45 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/19 19:54:32 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**make_temp(char **args, int arrsize, int idx, int *i)
{
	char	**temp;
	char	**split;
	int		splitsize;

	split = ft_split(args[idx], ' ');
	if (split == NULL)
		return (NULL);
	splitsize = ft_strarr_size(split);
	temp = malloc((arrsize + splitsize + 1) * sizeof(char *));
	if (temp == NULL)
		return (charclean(split), NULL);
	while (*i < (arrsize + splitsize))
	{
		if (*i < idx)
			temp[*i] = args[*i];
		else if ((*i - idx) < splitsize)
			temp[*i] = split[*i - idx];
		else if ((*i) < (arrsize + splitsize))
			temp[*i] = args[*i - splitsize + 1];
		(*i)++;
	}
	temp[*i] = NULL;
	return (free(split), temp);
}

static char	**split_add(char **args, int idx)
{
	int		arrsize;
	char	**temp;
	int		i;

	i = 0;
	arrsize = ft_strarr_size(args);
	temp = make_temp(args, arrsize, idx, &i);
	return (temp);
}

int	splitargs(char ***args, int i)
{
	char	**temp;

	if (*args == NULL)
		return (1);
	if (ft_strchr((*args)[i], ' ') != NULL)
	{
		temp = split_add(*args, i);
		if (temp == NULL)
			return (1);
		free((*args)[i]);
		free(*args);
		*args = temp;
	}
	return (0);
}
