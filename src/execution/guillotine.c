/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   guillotine.c                                       :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 08:40:40 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/06/20 15:06:47 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ms_isbuiltin(char **args)
{
	char	*cmd_name;

	if (!args)
		return (false);
	cmd_name = args[0];
	if (!ft_strncmp(cmd_name, "cd", 3)
		|| !ft_strncmp(cmd_name, "echo", 5)
		|| !ft_strncmp(cmd_name, "env", 4)
		|| !ft_strncmp(cmd_name, "exit", 5)
		|| !ft_strncmp(cmd_name, "export", 7)
		|| !ft_strncmp(cmd_name, "pwd", 4)
		|| !ft_strncmp(cmd_name, "unset", 6))
	{
		return (true);
	}
	return (false);
}

static void	skip_group(t_cmd **cmd)
{
	(*cmd) = (*cmd)->next;
	while (*cmd && (*cmd)->type == PIPE)
		*cmd = (*cmd)->next;
}

int	guillotine(t_cmd **head, t_list **env, bool child)
{
	t_cmd	*cmd;

	cmd = *head;
	while (cmd && (cmd->type != AND || g_estatus == EXIT_SUCCESS)
		&& cmd->type != PIPE && g_estatus != CRIT_FAILURE)
	{
		if ((!cmd->next || cmd->next->type != PIPE) \
				&& ms_isbuiltin(cmd->arguments))
		{
			g_estatus = expander(cmd, *env);
			if (g_estatus == 0)
				g_estatus = exec_cmd(cmd, head, env, child);
			cmd = cmd->next;
		}
		else
			g_estatus = executer(&cmd, env);
		if (cmd && cmd->type == OR && g_estatus == EXIT_SUCCESS)
			skip_group(&cmd);
	}
	if (g_estatus == CRIT_FAILURE)
		g_estatus = EXIT_FAILURE;
	return (g_estatus);
}
