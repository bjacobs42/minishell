/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:47:11 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/19 08:27:56 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_to_dcharp(t_list **ptr, char *addition, enum e_type tag)
{
	t_file_dt	*new;
	t_list		*newlink;

	new = malloc(sizeof(t_file_dt));
	if (!new)
		return (1);
	new->name = ft_strdup(addition);
	if (!new->name)
	{
		free(new);
		return (1);
	}
	new->flag = tag;
	newlink = ft_lstnew(new);
	if (newlink == NULL)
	{
		free(new->name);
		free(new);
		return (1);
	}
	ft_lstadd_back(ptr, newlink);
	return (0);
}

static int	redirect(t_list *current_token, t_cmd *cmd_list, enum e_type tag)
{
	t_token		*current;

	if (current_token)
	{
		current = current_token->content;
		return (add_to_dcharp(&(cmd_list->files), \
					current->value, tag));
	}
	return (1);
}

int	handle_operator(t_list *current_token, t_cmd *cmd_list, t_list *mini_env)
{
	t_token	*current;

	current = current_token->content;
	if (current->type == HERE_DOC)
		return (heredoc(current_token->next, cmd_list, mini_env));
	return (redirect(current_token->next, cmd_list, current->type));
}
