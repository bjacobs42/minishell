/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:47:15 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/20 19:41:04 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parenthesischeck(char *cmd_line)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (cmd_line[i] != '\0')
	{
		if (cmd_line[i] == '(')
			ret++;
		else if (cmd_line[i] == ')')
			ret--;
		if (ret < 0)
			return (-1);
		skipquotes(cmd_line, &i);
		i++;
	}
	if (ret != 0)
		return (-1);
	return (0);
}

static int	lextotoken(t_list **tokenlist, char *input)
{
	int		i;
	int		ret;
	int		cmdlength;

	i = 0;
	ret = 0;
	cmdlength = ft_strlen(input);
	while (i < cmdlength)
	{
		while (ft_isspace(input[i]) == 1)
			i++;
		if (!input[i])
			break ;
		ret = tokenize(&input[i], tokenlist);
		if (ret == -1)
			return (-1);
		else
			i += ret;
	}
	return (ret);
}

int	lexer(t_list **tokenlist, char *input)
{
	int		ret;

	ret = 0;
	if (input == NULL)
		return (1);
	if (parenthesischeck(input) != 0)
	{
		write(2, "minishell: unclosed parentheses\n", 33);
		return (-1);
	}
	ret = lextotoken(tokenlist, input);
	return (ret);
}
