/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   branch_functions.c                                 :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 21:25:22 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/20 19:44:58 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	addbranch(t_cmd *cmd, t_token *part, \
	t_list **tokens, t_list *mini_env)
{
	t_cmd		*link;

	addlink(&cmd, part);
	link = init_t_cmd();
	return (t_cmd_addprntss(tokens, &cmd, link, mini_env));
}

static int	prntssloop(t_token *part, t_cmd *cmd, \
	t_list **tokens, t_list *mini_env)
{
	if (part->type == PAR_OPEN)
		addbranch(cmd, part, tokens, mini_env);
	else if (part->type == PAR_CLOSE)
	{
		*tokens = (*tokens)->next;
		return (-1);
	}
	else if (part->type == PIPE || part->type == AND || part->type == OR)
	{
		addlink(&cmd, part);
		*tokens = (*tokens)->next;
	}
	else if (is_operator(part->type))
	{
		if (ophandling(tokens, &cmd, mini_env))
			return (1);
	}
	else
		if (handle_word(tokens, t_cmdlast(cmd)))
			return (1);
	return (0);
}

int	t_cmd_addprntss(t_list **tokens, t_cmd **command, \
	t_cmd *link, t_list *mini_env)
{
	t_cmd		*last;
	t_token		*part;
	t_cmd		*cmd;
	int			res;

	res = 0;
	*tokens = (*tokens)->next;
	last = t_cmdlast(*command);
	last->prntss = link;
	cmd = link;
	while (*tokens != NULL)
	{
		part = (*tokens)->content;
		res = prntssloop(part, cmd, tokens, mini_env);
		if (res != 0)
			return (res);
	}
	return (0);
}
