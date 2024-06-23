/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:48:27 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/22 15:39:46 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argloop(char **name, int i, t_list *env)
{
	int		dollarsign;
	bool	dq;

	dq = false;
	dollarsign = 0;
	while (i != -1 && (*name)[i] != '\0')
	{
		if ((*name)[i] == '\"')
			dq = !dq;
		if ((*name)[i] == '$')
			i = varreplace(name, i, env, &dollarsign);
		else if ((*name)[i] == '\'' && !dq)
		{
			i++;
			while ((*name)[i] != '\'' && ((*name)[i + 1] != '\0'))
				i++;
			i++;
		}
		else if ((*name)[i] != '\0')
			i++;
	}
	if (i == -1)
		return (i);
	return (dollarsign);
}

int	expandfiles(t_list *files, t_list *env)
{
	while (files != NULL)
	{
		if (((t_file_dt *)(files->content))->name == NULL)
			return (1);
		argloop(&(((t_file_dt *)(files->content))->name), 0, env);
		if (wildcardfile(&(((t_file_dt *)(files->content))->name)) != 0)
			return (1);
		removequotes((((t_file_dt *)(files->content))->name));
		files = files->next;
	}
	return (0);
}

int	expandargs(char	***args, t_list *env)
{
	size_t	i;
	int		expand;

	i = 0;
	if (args == NULL)
		return (0);
	while ((*args)[i] != NULL)
	{
		expand = argloop(&((*args)[i]), 0, env);
		if (expand < 0)
			return (1);
		if (wildcardloop(args, &i) == 1)
		{
			removequotes(((*args)[i]));
			if (expand)
			{
				expand = 0;
				if (splitargs(args, i) != 0 || emptycheck(args, &i))
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	expander(t_cmd *command, t_list *mini_env)
{
	if (expandfiles((command)->files, mini_env) != 0)
		return (1);
	if ((command)->arguments != NULL)
	{
		if (expandargs(&(command)->arguments, mini_env) != 0)
			return (1);
	}
	return (0);
}
