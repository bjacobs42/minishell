/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 21:51:18 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/06/21 19:58:04 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_builtin.h"

static int	exec_builtin(char **args, t_cmd **head, t_list **env, bool child)
{
	if (!args || !*args)
		return (-1);
	if (!ft_strncmp(args[0], "cd", 3))
		return (ms_cd(args[1], env));
	else if (!ft_strncmp(args[0], "echo", 5))
		return (ms_echo(args));
	else if (!ft_strncmp(args[0], "env", 4))
		return (ms_penv(*env, false), EXIT_SUCCESS);
	else if (!ft_strncmp(args[0], "exit", 5))
		return (ms_exit(args, head, env, child));
	else if (!ft_strncmp(args[0], "export", 7))
		return (ms_export(args, env));
	else if (!ft_strncmp(args[0], "pwd", 4))
		return (ms_pwd());
	else if (!ft_strncmp(args[0], "unset", 6))
		return (ms_unset(args, env));
	return (-1);
}

int	exec_cmd(t_cmd *cmd, t_cmd **head, t_list **env, bool child)
{
	int	estatus;
	int	stdio[2];

	if (cmd->next && cmd->next->fd[IN] != STDIN_FILENO)
		close(cmd->next->fd[IN]);
	if (change_fd(cmd->fd, cmd->files) == EXIT_FAILURE)
		return (close_pipes(cmd->fd), EXIT_FAILURE);
	stdio[IN] = replace_stdio(cmd->fd[IN], STDIN_FILENO, true);
	stdio[OUT] = replace_stdio(cmd->fd[OUT], STDOUT_FILENO, true);
	estatus = exec_builtin(cmd->arguments, head, env, child);
	if (estatus == -1)
		estatus = ms_execvp(cmd->arguments, *env);
	replace_stdio(stdio[IN], STDIN_FILENO, false);
	replace_stdio(stdio[OUT], STDOUT_FILENO, false);
	return (estatus);
}
