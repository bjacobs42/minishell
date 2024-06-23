/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:30:14 by bjacobs           #+#    #+#             */
/*   Updated: 2023/06/19 21:49:33 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

bool	only_c(char *s, char c, char delimiter)
{
	int	i;

	if (s[0] == delimiter || !s[0])
		return (false);
	i = 0;
	while (s[i] == c)
		i++;
	if (s[i] == delimiter || !s[i])
		return (true);
	return (false);
}

int	add_variable(char *arg, t_list **env)
{
	t_list	*new_var;
	char	*content;

	content = ft_strdup(arg);
	if (!content)
		return (EXIT_FAILURE);
	new_var = ft_lstnew(content);
	if (!new_var)
		return (free(content), EXIT_FAILURE);
	ft_lstadd_back(env, new_var);
	return (EXIT_SUCCESS);
}

int	update_variable(char *arg, t_list **env)
{
	char	*content;
	size_t	varlen;
	t_list	*tmp;

	varlen = 0;
	while (arg[varlen] && arg[varlen] != '=')
		varlen++;
	tmp = *env;
	while (tmp)
	{
		content = (char *)tmp->content;
		if (!ft_strncmp(arg, content, varlen) && \
			(content[varlen] == '=' || !content[varlen]))
		{
			if (arg[varlen] != '=')
				return (EXIT_SUCCESS);
			free(tmp->content);
			tmp->content = (void *)ft_strdup(arg);
			if (!tmp->content)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (add_variable(arg, env));
}

char	*get_env_var(char *var, t_list *env)
{
	size_t	varlen;
	char	*content;

	varlen = 0;
	while (var[varlen] && var[varlen] != '=')
		varlen++;
	while (env)
	{
		content = (char *)env->content;
		if (!ft_strncmp(var, content, varlen) && content[varlen] == '=')
			return (&content[varlen + 1]);
		env = env->next;
	}
	return (NULL);
}
