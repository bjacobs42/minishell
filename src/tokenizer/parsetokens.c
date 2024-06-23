/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsetokens.c                                      :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:46:53 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/20 15:06:10 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(enum e_type type)
{
	if ((type != WORD))
		return (1);
	return (0);
}

int	addlink(t_cmd **command, t_token *part)
{
	t_cmd	*link;

	link = init_t_cmd();
	if (link == NULL)
		return (1);
	if (part != NULL)
		link->type = part->type;
	t_cmd_addback(command, link);
	return (0);
}

static int	createbranch(t_cmd **command, t_token *part, \
	t_list **tokens, t_list *mini_env)
{
	t_cmd	*last;
	t_cmd	*link;

	last = t_cmdlast(*command);
	if (last->arguments != NULL || last->files != \
		NULL || last->prntss != NULL)
		addlink(command, part);
	link = init_t_cmd();
	return (t_cmd_addprntss(tokens, command, link, mini_env));
}

int	ophandling(t_list **tokens, t_cmd **command, t_list *mini_env)
{
	t_cmd	*last;

	last = t_cmdlast(*command);
	if (handle_operator(*tokens, last, mini_env) == EXIT_FAILURE)
		return (1);
	*tokens = (*tokens)->next;
	if (*tokens != NULL)
		*tokens = (*tokens)->next;
	return (0);
}

int	parsetokens(t_list *tokens, t_cmd **command, t_list *mini_env)
{
	t_token	*part;
	int		res;

	addlink(command, NULL);
	while (tokens != NULL)
	{
		part = tokens->content;
		if (part->type == PAR_OPEN)
			res = createbranch(command, part, &tokens, mini_env);
		else if (part->type == PIPE || part->type == AND || part->type == OR)
		{
			res = addlink(command, part);
			tokens = tokens->next;
		}
		else if (is_operator(part->type))
			res = ophandling(&tokens, command, mini_env);
		else
			res = handle_word(&tokens, t_cmdlast(*command));
		if (res > 0)
			return (1);
	}
	return (0);
}
