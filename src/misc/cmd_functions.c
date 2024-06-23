/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:47:49 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/14 21:25:45 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_t_cmd(void)
{
	t_cmd	*newcommand;

	newcommand = malloc(sizeof(t_cmd));
	if (newcommand == NULL)
		return (NULL);
	newcommand->next = NULL;
	newcommand->prntss = NULL;
	newcommand->arguments = NULL;
	newcommand->files = NULL;
	newcommand->type = -1;
	newcommand->fd[IN] = STDIN_FILENO;
	newcommand->fd[OUT] = STDOUT_FILENO;
	return (newcommand);
}

t_cmd	*t_cmdlast(t_cmd *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		else
			lst = lst->next;
	}
	return (lst);
}

void	t_cmd_addback(t_cmd **command, t_cmd *link)
{
	t_cmd		*last;

	last = t_cmdlast(*command);
	if (last != NULL)
		last->next = link;
	else
		*command = link;
}
