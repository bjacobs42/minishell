/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_needles.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:48:23 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/19 20:26:49 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* checks if hay(file/dir name) matches the wildcard
 * return true if it matches false if it doesn't */
static bool	search_hay(char *hay, char **pieces, char *wildcard)
{
	size_t	i;
	size_t	haylen;

	i = 0;
	if (wildcard[i] != '*')
	{
		if (ft_strncmp(hay, pieces[i], ft_strlen(pieces[i])))
			return (false);
		i++;
	}
	haylen = ft_strlen(hay);
	while (pieces[i])
	{
		hay = ft_strnstr(hay, pieces[i], haylen);
		if (!hay)
			return (false);
		i++;
	}
	if (wildcard[ft_strlen(wildcard) - 1] != '*' && i > 0)
	{
		if (ft_strncmp(&hay[ft_strlen(hay) - ft_strlen(pieces[i - 1])],
				pieces[i - 1], ft_strlen(pieces[i - 1]) + 1))
			return (false);
	}
	return (true);
}

static void	sort_needle(char **needles, int i)
{
	int	j;
	int	needlelen;

	j = i - 1;
	needlelen = ft_strlen(needles[i]) + 1;
	while (j >= 0)
	{
		if (ft_strncmp(needles[j], needles[i], needlelen) > 0)
		{
			ft_memswap((void **)&needles[j], (void **)&needles[i]);
			i--;
		}
		else
			break ;
		j--;
	}
}

static int	remove_prefix(char ***pieces, char *asterisk)
{
	if (!*pieces || !**pieces || ft_strncmp(**pieces, "./", 2))
		return (EXIT_FAILURE);
	if (!ft_strncmp(**pieces, "./", 3))
	{
		(*pieces)++;
		if (*asterisk == '\'' || *asterisk == '\"')
			ft_strlcpy(asterisk, &asterisk[4], ft_strlen(asterisk));
		else
			ft_strlcpy(asterisk, &asterisk[2], ft_strlen(asterisk));
		return (EXIT_SUCCESS);
	}
	ft_strlcpy(**pieces, &(**pieces)[2], ft_strlen(**pieces));
	if (*asterisk == '\'' || *asterisk == '\"')
		ft_strlcpy(&asterisk[1], &asterisk[3], ft_strlen(asterisk));
	else
		ft_strlcpy(asterisk, &asterisk[2], ft_strlen(asterisk));
	return (EXIT_SUCCESS);
}

static int	start_search(DIR *haystack, char **pieces, \
			char **needles, char *asterisk)
{
	size_t			i;
	struct dirent	*hay;
	char			*prefix;

	i = 0;
	prefix = NULL;
	if (remove_prefix(&pieces, asterisk) == EXIT_SUCCESS)
		prefix = "./";
	hay = readdir(haystack);
	while (hay)
	{
		if ((hay->d_name[0] != '.' || asterisk[0] == '.' || \
			!ft_strncmp("\'.", asterisk, 2) || !ft_strncmp("\".", asterisk, 2))
			&& search_hay(hay->d_name, pieces, asterisk))
		{
			needles[i] = ft_strjoin(prefix, 0, hay->d_name);
			if (!needles[i])
				return (EXIT_FAILURE);
			sort_needle(needles, i);
			i++;
		}
		hay = readdir(haystack);
	}
	return (EXIT_SUCCESS);
}

/* Uses search_hay() on every single thing in the current dir
 * returns EXIT_FAILURE on error or EXIT_SUCCESS on success */
int	find_needles(DIR *haystack, char **needles, char *asterisk)
{
	char			**pieces;
	char			*astercopy;
	size_t			i;

	i = 0;
	astercopy = ft_strdup(asterisk);
	if (!astercopy)
		return (EXIT_FAILURE);
	pieces = wildcardsplit(asterisk, '*');
	if (!pieces)
		return (free(astercopy), EXIT_FAILURE);
	while (pieces[i] != NULL)
	{
		removequotes(pieces[i]);
		i++;
	}
	if (start_search(haystack, pieces, needles, astercopy) != EXIT_SUCCESS)
		return (free(astercopy), charclean(pieces), EXIT_FAILURE);
	free(astercopy);
	charclean(pieces);
	return (EXIT_SUCCESS);
}
