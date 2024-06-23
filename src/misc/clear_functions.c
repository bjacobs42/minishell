/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:47:54 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/21 19:36:42 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_tokens(t_list	**token_list)
{
	t_list		*link;
	t_list		*ptr;

	if (*token_list != NULL)
	{
		link = (*token_list);
		while (link != NULL)
		{
			ptr = link->next;
			if (link->content != NULL)
				free(((t_token *)link->content)->value);
			free(link->content);
			free(link);
			link = ptr;
		}
		(*token_list) = NULL;
	}
}

void	charclean(char **ptr)
{
	int		i;
	char	**copy;

	copy = ptr;
	i = 0;
	if (copy == NULL)
		return ;
	while (copy[i] != NULL)
		i++;
	while (i >= 0)
	{
		free(ptr[i]);
		i--;
	}
	free(ptr);
}

static void	clearfd(void *content)
{
	t_file_dt	*file;

	file = (t_file_dt *)content;
	if (file->flag == HERE_DOC)
		unlink(file->name);
	free(file->name);
	free(file);
}

void	clear_t_cmds(t_cmd **content)
{
	t_cmd	*ptr;

	if (content == NULL)
		return ;
	while ((*content) != NULL)
	{
		ptr = (*content)->next;
		if ((*content)->prntss != NULL)
			clear_t_cmds(&((*content)->prntss));
		close_pipes((*content)->fd);
		ft_clear_strarr((*content)->arguments);
		ft_lstclear(&(*content)->files, clearfd);
		free(*content);
		(*content) = ptr;
	}
}
