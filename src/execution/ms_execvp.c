/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_execvp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 21:37:21 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/06/19 20:14:21 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtin.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

static int	check_perms(char *cmdn, char *cmdp)
{
	struct stat	finfo;

	if (stat(cmdp, &finfo))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(cmdn);
		return (127);
	}
	if (S_ISDIR(finfo.st_mode))
	{
		ft_printf_fd(IS_DIR, STDERR_FILENO, cmdn);
		return (126);
	}
	if (!(finfo.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
		|| !(finfo.st_mode & (S_IRUSR | S_IRGRP | S_IROTH)))
	{
		ft_printf_fd(PRM_DENIED, STDERR_FILENO, cmdn);
		return (126);
	}
	return (0);
}

static char	*search_path(char *cmd_name, char **bins)
{
	struct stat	finfo;
	char		*cmdp;
	size_t		i;

	i = 0;
	while (bins[i])
	{
		cmdp = ft_strjoin(bins[i], '/', cmd_name);
		if (!cmdp)
		{
			perror("minishell: ms_execvep: ft_strjoin");
			ft_clear_strarr(bins);
			exit(EXIT_FAILURE);
		}
		if (!stat(cmdp, &finfo) && !S_ISDIR(finfo.st_mode))
			return (cmdp);
		free(cmdp);
		i++;
	}
	return (NULL);
}

static char	*get_path(char **args, t_list *env)
{
	char	*envp;
	char	*cmdp;
	char	**bins;

	if (!*args)
		return (NULL);
	envp = get_env_var("PATH", env);
	if (!envp || ft_strchr(*args, '/'))
		return (*args);
	bins = ft_split(envp, ':');
	if (!bins)
	{
		perror("minishell: ms_execvep: ft_split");
		exit(EXIT_FAILURE);
	}
	cmdp = search_path(*args, bins);
	ft_clear_strarr(bins);
	return (cmdp);
}

static int	create_env(char ***exec_env, t_list *env)
{
	size_t	i;
	size_t	lstsize;

	if (!env)
	{
		*exec_env = NULL;
		return (EXIT_SUCCESS);
	}
	lstsize = ft_lstsize(env);
	*exec_env = (char **)malloc(sizeof(char *) * (lstsize + 1));
	if (!(*exec_env))
		return (perror("minishell: ms_execvp"), EXIT_FAILURE);
	i = 0;
	(*exec_env)[lstsize] = NULL;
	while (env)
	{
		(*exec_env)[i] = (char *)env->content;
		env = env->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ms_execvp(char **av, t_list *env)
{
	char	*cmdp;
	char	**exec_env;
	int		estatus;

	if (!av || !*av)
		return (EXIT_SUCCESS);
	cmdp = get_path(av, env);
	if (!cmdp)
	{
		ft_printf_fd(CMD_NOT_FOUND, STDERR_FILENO, *av);
		return (127);
	}
	estatus = check_perms(*av, cmdp);
	if (estatus != 0)
		return (free(cmdp), estatus);
	if (create_env(&exec_env, env) == EXIT_FAILURE)
		return (free(cmdp), EXIT_FAILURE);
	execve(cmdp, av, exec_env);
	return (free(exec_env), free(cmdp), EXIT_FAILURE);
}
