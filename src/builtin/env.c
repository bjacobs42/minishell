/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:52:11 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/12 12:16:04 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

void	ms_penv(t_list *env, bool pexport)
{
	char	*content;

	while (env)
	{
		content = (char *)env->content;
		if (pexport)
			ft_printf_fd("%s %s\n", STDOUT_FILENO, "declare -x", content);
		else if (ft_strchr(content, '='))
			ft_putendl_fd(content, STDOUT_FILENO);
		env = env->next;
	}
}
