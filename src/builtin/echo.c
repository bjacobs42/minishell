/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 11:43:56 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/06/20 14:38:02 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtin.h"

static bool	get_option(char **av, int *i)
{
	bool	nl;

	nl = true;
	while (av[*i])
	{
		if (av[*i][0] != '-')
			break ;
		if (!only_c(&av[*i][1], 'n', '\0'))
			break ;
		else
			nl = false;
		(*i)++;
	}
	return (nl);
}

static char	*join_av(char **av)
{
	char	*tmp;
	char	*s;
	int		i;

	if (!*av)
		return (ft_strdup(""));
	i = 0;
	s = NULL;
	while (av[i])
	{
		tmp = ft_strjoin(s, ' ', av[i]);
		free(s);
		if (!tmp)
			return (perror("minishell: echo"), NULL);
		s = tmp;
		i++;
	}
	return (s);
}

int	ms_echo(char **av)
{
	bool	nl;
	char	*output;
	int		size;
	int		i;

	i = 1;
	nl = get_option(av, &i);
	output = join_av(&av[i]);
	if (!output)
		return (EXIT_FAILURE);
	size = ft_strlen(output);
	if (nl)
		output[size++] = '\n';
	if (write(STDOUT_FILENO, output, size) == -1)
		return (perror("minishell: echo: write"), free(output), EXIT_FAILURE);
	free(output);
	return (EXIT_SUCCESS);
}
