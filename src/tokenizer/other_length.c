/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   other_length.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:47:02 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/19 20:40:44 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quote_length(char *cmd_line, int i)
{
	char	quote;

	while (!(cmd_line[i] == ' ') && !(cmd_line[i] == '\t') \
		&& !(cmd_line[i] == '\0') && !(cmd_line[i] == '|') \
		&& !(cmd_line[i] == '<') && !(cmd_line[i] == '>') \
		&& !(cmd_line[i] == '(') && !(cmd_line[i] == ')') \
		&& !(cmd_line[i] == '&' && cmd_line[i + 1] == '&'))
	{
		if (cmd_line[i] == '\'' || cmd_line[i] == '\"')
		{
			quote = cmd_line[i];
			i++;
			while (cmd_line[i] != '\0' && cmd_line[i] != quote)
				i++;
		}
		if (cmd_line[i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}

int	other_length(char *cmd_line)
{
	int	i;

	i = 0;
	if (cmd_line[i] == '<' && cmd_line[i + 1] == '<')
		return (2);
	else if (cmd_line[i] == '>' && cmd_line[i + 1] == '>')
		return (2);
	else if (cmd_line[i] == '|' && cmd_line[i + 1] == '|')
		return (2);
	else if (cmd_line[i] == '&' && cmd_line[i + 1] == '&')
		return (2);
	else if (cmd_line[i] == '|' || cmd_line[i] == '<' || cmd_line[i] == '>' \
		|| cmd_line[i] == '(' || cmd_line[i] == ')')
		return (1);
	i = quote_length(cmd_line, i);
	return (i);
}
