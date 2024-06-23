/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   skipquotes.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 20:28:47 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/19 20:32:30 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	skipquotes(char *line, int *i)
{
	char	quote;

	if (line[*i] == '\'' || line[*i] == '\"')
	{
		quote = line[*i];
			(*i)++;
		while (line[*i] != quote && line[*i + 1] != '\0')
			(*i)++;
		if (line[*i + 1] != '\0')
			(*i)++;
	}
}
