/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 22:01:35 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/06/21 16:44:16 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_builtin.h"
#include <sys/wait.h>
#include <fcntl.h>

static int	get_estatus(int *pids, int amount)
{
	int	wstatus;
	int	i;

	i = 0;
	while (i < amount)
	{
		waitpid(pids[i], &wstatus, 0);
		i++;
	}
	free(pids);
	if (WIFSIGNALED(wstatus))
	{
		wstatus = WTERMSIG(wstatus);
		if (wstatus == SIGQUIT)
			ft_putstr_fd("Quit 3\n", STDERR_FILENO);
		return (wstatus + 128);
	}
	return (WEXITSTATUS(wstatus));
}

static int	sub_guillotine(t_cmd *cmd, t_list **env)
{
	int	fd;
	int	ecode;

	if (cmd->next && cmd->next->fd[IN] != STDIN_FILENO)
		close(cmd->next->fd[IN]);
	change_fd(cmd->fd, cmd->files);
	fd = replace_stdio(cmd->fd[OUT], STDOUT_FILENO, true);
	ecode = guillotine(&cmd->prntss, env, true);
	replace_stdio(fd, STDOUT_FILENO, false);
	return (ecode);
}

static int	sub_executer(t_cmd **cmd, int *pid, t_list **env)
{
	int	ecode;

	*pid = fork();
	if (*pid == -1)
		return (perror("minishell: executer: fork"), EXIT_FAILURE);
	if (*pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (expander(*cmd, *env) != EXIT_SUCCESS)
			ecode = EXIT_FAILURE;
		if ((*cmd)->prntss)
			ecode = sub_guillotine(*cmd, env);
		else
			ecode = exec_cmd(*cmd, NULL, env, true);
		exit(ecode);
	}
	return (EXIT_SUCCESS);
}

int	executer(t_cmd **cmd, t_list **env)
{
	int		*pids;
	size_t	i;

	if (init_pids(*cmd, &pids) != EXIT_SUCCESS)
		return (CRIT_FAILURE);
	i = 0;
	while (*cmd && (i == 0 || ((*cmd)->type != AND && (*cmd)->type != OR)))
	{
		if ((*cmd)->next && (*cmd)->next->type == PIPE)
		{
			if (init_pipe(*cmd) == EXIT_FAILURE)
				return (clean_executer(*cmd, pids), CRIT_FAILURE);
		}
		if (sub_executer(cmd, &pids[i], env) != EXIT_SUCCESS)
			return (clean_executer(*cmd, pids), CRIT_FAILURE);
		close_pipes((*cmd)->fd);
		*cmd = (*cmd)->next;
		i++;
	}
	return (get_estatus(pids, i));
}
