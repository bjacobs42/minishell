/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   precheck.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:47:23 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/18 17:21:08 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MS_SYNTAX_ERR "minishell: syntax error near unexpected token `%s'\n"

static int	errmessage(char *value)
{
	ft_printf_fd(MS_SYNTAX_ERR, 2, value);
	g_estatus = 2;
	return (1);
}

static int	contincheck(t_token *current, t_token *next)
{
	if ((current->type == WORD) && (next->type == PAR_OPEN))
		return (errmessage(next->value));
	else if (current->type == PIPE && (next->type == PIPE || \
		next->type == AND || next->type == OR || next->type == PAR_CLOSE))
		return (errmessage(next->value));
	else if ((current->type == RE_IN || current->type == HERE_DOC \
	|| current->type == RE_OU_TR || current->type == RE_OU_AP) && \
	(next->type != WORD && next->type != WILDCARD))
		return (errmessage(next->value));
	else if ((current->type == PAR_OPEN) && (next->type != WORD \
		&& next->type != WILDCARD))
		return (errmessage(next->value));
	return (0);
}

int	precheck(t_list *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens->content;
	if (current->type == AND || current->type == OR || \
		current->type == PIPE || current->type == PAR_CLOSE)
		return (errmessage(current->value));
	while (tokens->next != NULL)
	{
		next = (tokens->next)->content;
		if (contincheck(current, next))
			return (1);
		tokens = tokens->next;
		current = tokens->content;
	}
	if ((current->type > 0 && current->type != WILDCARD && \
		current->type != PAR_CLOSE) && (tokens->next == NULL))
		return (errmessage("newline"));
	return (0);
}
