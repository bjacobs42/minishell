/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:48:30 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/21 17:52:45 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_newstr(char *replacement, char *name, int start)
{
	char	*newstring;
	char	*tempstring;

	tempstring = NULL;
	newstring = NULL;
	if (replacement == NULL)
	{
		newstring = ft_substr(name, 0, start);
		if (newstring == NULL)
			return (NULL);
	}
	else
	{
		tempstring = ft_substr(name, 0, start);
		if (tempstring == NULL)
			return (NULL);
		newstring = ft_strjoin(tempstring, 0, replacement);
		if (newstring == NULL)
			return (NULL);
		free(tempstring);
	}
	return (newstring);
}

char	*replacestring(char *replacement, char *name, int start, int i)
{
	char	*newstring;
	char	*newstring2;
	char	*tempstring;

	newstring = make_newstr(replacement, name, start);
	newstring2 = NULL;
	tempstring = ft_substr(name, start + i, ft_strlen(name));
	if (tempstring != NULL)
	{
		newstring2 = ft_strjoin(newstring, 0, tempstring);
		free(tempstring);
	}
	free(newstring);
	return (newstring2);
}

char	*makereplacement(t_list *env, char *name, int start, int i)
{
	char	*var;
	t_list	*current;
	char	*replacement;

	current = env;
	var = NULL;
	replacement = NULL;
	var = ft_substr(name, start + 1, i - 1);
	if (var == NULL)
		return (NULL);
	while (current)
	{
		if (check_expansion(var, current))
		{
			replacement = ft_strdup(ft_strchr(current->content, '=') + 1);
			break ;
		}
		current = current->next;
	}
	free(var);
	return (replacement);
}

static int	countds(char **name, int start, int i)
{
	return ((*name)[start + i] != ' ' && (*name)[start + i] \
	!= '\0' && (*name)[start + i] != '\"' && \
	(*name)[start + i] != '\'' && (*name)[start + i] != '$' && \
	(*name)[start + i] != '=' && (*name)[start + i] != '?');
}

int	varreplace(char **name, int start, t_list *env, int *dollarsign)
{
	int		i;
	char	*replacement;
	char	*temp;
	int		added;

	i = 1;
	while (countds(name, start, i))
		i++;
	if (ft_strncmp(&(*name)[start + 1], "?", 1) == 0)
	{
		i = 2;
		replacement = ft_itoa(g_estatus);
	}
	else if (i == 1)
		return (start + i);
	else
		replacement = makereplacement(env, *name, start, i);
	temp = *name;
	*name = replacestring(replacement, *name, start, i);
	free(temp);
	if (*name == NULL)
		return (free(replacement), -1);
	*dollarsign = 1;
	added = ft_strlen(replacement);
	return (free(replacement), start + added);
}
