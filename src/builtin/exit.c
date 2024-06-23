/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 13:35:05 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/06/21 19:34:16 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_builtin.h"

static unsigned char	parse_exit(char **arg, unsigned char *ecode)
{
	if (!arg || !arg[1])
	{
		if (g_estatus > 0)
			*ecode = 1;
		else
			*ecode = 0;
	}
	else if (parse_str_llong(arg[1]) == EXIT_FAILURE)
	{
		ft_printf_fd(EXIT_PARSE_MSG, STDERR_FILENO, arg[1]);
		*ecode = 255;
	}
	else if (ft_strarr_size(arg) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
		*ecode = (unsigned char)ft_atob(arg[1], 10);
	return (EXIT_SUCCESS);
}

int	ms_exit(char **arg, t_cmd **head, t_list **env, bool child)
{
	unsigned char	ecode;

	if (!child)
	{
		if (head || !isatty(STDIN_FILENO))
			ft_putstr_fd("exit\n", STDERR_FILENO);
		else
			ft_putstr_fd("\x1b[A\x1b[12Cexit\n", STDERR_FILENO);
	}
	if (parse_exit(arg, &ecode) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (!child)
		clear_t_cmds(head);
	ft_lstclear(env, free);
	rl_clear_history();
	exit(ecode);
}
