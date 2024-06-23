/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:46:27 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/18 21:04:56 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_type	identify_token(char *token)
{
	if (!(ft_strncmp(token, "||", 2)))
		return (OR);
	if (!(ft_strncmp(token, "|", 1)))
		return (PIPE);
	if (!(ft_strncmp(token, ">>", 2)))
		return (RE_OU_AP);
	if (!(ft_strncmp(token, ">", 1)))
		return (RE_OU_TR);
	if (!(ft_strncmp(token, "<<", 2)))
		return (HERE_DOC);
	if (!(ft_strncmp(token, "<", 1)))
		return (RE_IN);
	if (!(ft_strncmp(token, "&&", 2)))
		return (AND);
	if (!(ft_strncmp(token, "(", 1)))
		return (PAR_OPEN);
	if (!(ft_strncmp(token, ")", 1)))
		return (PAR_CLOSE);
	return (WORD);
}

static int	bufferset(char *cmd_line, char **buffer)
{
	int		size;

	size = other_length(cmd_line);
	if (size < 0)
	{
		write(2, "minishell: unclosed quotes\n", 27);
		return (-1);
	}
	*buffer = malloc((size + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	ft_strlcpy(*buffer, cmd_line, size + 1);
	return (size);
}

int	tokenize(char *cmd_line, t_list **tokens)
{
	int		i;
	char	*buffer;
	t_token	*token;
	t_list	*link;

	i = bufferset(cmd_line, &buffer);
	if (i == -1)
		return (-1);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(buffer);
		return (-1);
	}
	token->type = identify_token(buffer);
	token->value = buffer;
	link = ft_lstnew(token);
	if (link == NULL)
	{
		free(token->value);
		free(token);
		return (-1);
	}
	ft_lstadd_back(tokens, link);
	return (i);
}
