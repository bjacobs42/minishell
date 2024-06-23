/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:36:31 by bjacobs           #+#    #+#             */
/*   Updated: 2023/06/21 21:54:37 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

static void	delvar(char *value, t_list **env)
{
	t_list	*prev;
	t_list	*tmp;
	size_t	valsize;
	char	*content;

	prev = NULL;
	tmp = *env;
	valsize = ft_strlen(value);
	while (tmp)
	{
		content = (char *)tmp->content;
		if (!ft_strncmp(value, content, ft_strlen(value))
			&& (!content[valsize] || content[valsize] == '='))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			ft_lstdelone(tmp, free);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ms_unset(char **av, t_list **env)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_strncmp(av[i], "_", 2))
			delvar(av[i], env);
		i++;
	}
	return (EXIT_SUCCESS);
}
