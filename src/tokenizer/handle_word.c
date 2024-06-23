/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:47:06 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/19 08:31:47 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(t_list *current_token)
{
	int		count;
	t_token	*current;

	count = 0;
	while (current_token && !is_operator(((t_token *) \
		(current_token->content))->type))
	{
		current = current_token->content;
		if (current->type == WORD)
			count++;
		current_token = current_token->next;
	}
	return (count);
}

int	count_arguments(char **arguments)
{
	int		i;

	i = 0;
	if (arguments != NULL)
	{
		while (arguments[i] != NULL)
			i++;
	}
	return (i);
}

int	add_arguments(t_cmd *cmd_list, int count, \
	char **temp, t_list **current_token)
{
	int	i;
	int	size;

	i = 0;
	size = count_arguments(cmd_list->arguments);
	while (i < size)
	{
		temp[i] = cmd_list->arguments[i];
		i++;
	}
	while (i < (size + count))
	{
		temp[i] = ft_strdup(((t_token *)(*current_token)->content)->value);
		if (temp[i] == NULL)
			return (ft_clear_strarr(temp), 1);
		*current_token = (*current_token)->next;
		i++;
	}
	temp[i] = NULL;
	return (0);
}

int	handle_word(t_list **current_token, t_cmd *cmd_list)
{
	int			count;
	char		**temp;
	int			size;

	count = count_tokens(*current_token);
	size = count_arguments(cmd_list->arguments);
	temp = malloc(sizeof(char *) * (size + count + 1));
	if (temp == NULL)
		return (1);
	if (add_arguments(cmd_list, count, temp, current_token))
	{
		cmd_list->arguments = NULL;
		return (1);
	}
	cmd_list->arguments = temp;
	return (0);
}
