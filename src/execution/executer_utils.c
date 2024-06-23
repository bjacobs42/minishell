/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 21:51:18 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/06/21 19:37:54 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_executer(t_cmd *cmd, int *pids)
{
	if (cmd->fd[IN] != STDIN_FILENO)
		close(cmd->fd[IN]);
	if (cmd->next->fd[IN] != STDIN_FILENO)
		close(cmd->next->fd[IN]);
	if (cmd->fd[OUT] != STDOUT_FILENO)
		close(cmd->fd[OUT]);
	free(pids);
}

void	close_pipes(int *fd)
{
	if (fd[OUT] != STDOUT_FILENO && fd[OUT] > 0)
	{
		close(fd[OUT]);
		fd[OUT] = -1;
	}
	if (fd[IN] != STDIN_FILENO && fd[IN] > 0)
	{
		close(fd[IN]);
		fd[IN] = -1;
	}
}

int	init_pipe(t_cmd *cmd)
{
	int	pfd[2];

	if (pipe(pfd) == -1)
		return (perror("minishell: executer: pipe"), EXIT_FAILURE);
	cmd->fd[OUT] = pfd[OUT];
	cmd->next->fd[IN] = pfd[IN];
	if (cmd->next->prntss)
		cmd->next->prntss->fd[IN] = pfd[IN];
	return (EXIT_SUCCESS);
}

int	init_pids(t_cmd *cmd, int **pids)
{
	size_t	i;

	i = 0;
	while (true)
	{
		i++;
		cmd = cmd->next;
		if (!cmd || cmd->type == AND || cmd->type == OR)
			break ;
	}
	*pids = (int *)malloc(sizeof(int) * i);
	if (!pids)
		return (perror("minishell: executer"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
