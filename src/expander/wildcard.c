/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/30 18:16:03 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/06/19 20:32:11 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MS_AMBIGU_ERR "minishell: %s: ambiguous redirect\n"

/* returns a char** with all wildcard matches or NULL if none/error */
char	**stars(char *asterisk)
{
	char	**needles;
	DIR		*haystack;
	size_t	dirsize;
	size_t	newsize;

	dirsize = get_cwd_size();
	if (!dirsize)
		return (NULL);
	haystack = opendir(".");
	if (!haystack)
		return (NULL);
	needles = (char **)ft_calloc(sizeof(char *), (dirsize + 1));
	if (!needles)
		return (closedir(haystack), NULL);
	if (find_needles(haystack, needles, asterisk) != EXIT_SUCCESS)
		return (closedir(haystack), free(needles), NULL);
	closedir(haystack);
	newsize = ft_strarr_size(needles);
	if (!newsize)
		return (charclean(needles), NULL);
	if (dirsize > newsize)
		needles = resize(needles, dirsize, newsize);
	return (needles);
}

static char	**make_temp(char **name, char **needles, size_t *j, size_t arrsize)
{
	size_t		i;
	size_t		oldsize;
	char		**temp;

	i = 0;
	oldsize = ft_strarr_size(name);
	temp = malloc((arrsize + oldsize) * sizeof(char *));
	if (!temp)
		return (NULL);
	free(name[*j]);
	while (i + 1 < (arrsize + oldsize))
	{
		if (i < *j)
			temp[i] = (name)[i];
		else if ((i - *j) < arrsize)
			temp[i] = needles[i - *j];
		else if ((i + 1) < (arrsize + oldsize))
			temp[i] = (name)[i - arrsize + 1];
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

int	wildcard(char ***name, size_t *j)
{
	size_t		arrsize;
	char		**needles;
	char		**temp;

	needles = stars((*name)[*j]);
	if (!needles)
		return (1);
	arrsize = ft_strarr_size(needles);
	temp = make_temp(*name, needles, j, arrsize);
	if (temp == NULL)
		return (ft_clear_strarr(needles), 1);
	free(needles);
	free(*name);
	*name = temp;
	(*j) += arrsize - 1;
	return (0);
}

int	wildcardloop(char ***name, size_t *j)
{
	int		i;
	char	*word;

	i = 0;
	word = (*name)[*j];
	while (word[i] != '\0')
	{
		if (word[i] == '*')
			return (wildcard(name, j));
		skipquotes(word, &i);
		i++;
	}
	return (1);
}

int	wildcardfile(char **name)
{
	char	**needles;
	size_t	arrsize;

	if (ft_strchr(*name, '*'))
	{
		needles = stars(*name);
		if (!needles)
			return (0);
		arrsize = ft_strarr_size(needles);
		if (arrsize == 1)
		{
			free(*name);
			*name = *needles;
			free(needles);
		}
		else if (arrsize > 1)
		{
			ft_clear_strarr(needles);
			return (ft_printf_fd(MS_AMBIGU_ERR, 2, *name), -1);
		}
	}
	return (0);
}
