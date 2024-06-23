/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/02 17:36:00 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/06/21 19:20:11 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtin.h"
#include <limits.h>
#include <sys/param.h>

static int	update_env(t_list **env)
{
	char	*content;
	char	cwd[MAXPATHLEN];

	content = ft_strjoin("OLDPWD=", 0, get_env_var("PWD", *env));
	if (!content)
		return (perror("minishell: cd"), EXIT_FAILURE);
	if (update_variable(content, env) == EXIT_FAILURE)
		return (perror("minishell: cd"), free(content), EXIT_FAILURE);
	free(content);
	if (!getcwd(cwd, MAXPATHLEN))
	{
		ft_printf_fd(CD_GETCWD_ERR, STDERR_FILENO, cwd);
		perror(NULL);
		return (EXIT_FAILURE);
	}
	content = ft_strjoin("PWD=", 0, cwd);
	if (!content)
		return (EXIT_FAILURE);
	if (update_variable(content, env) == EXIT_FAILURE)
		return (free(content), EXIT_FAILURE);
	free(content);
	return (EXIT_SUCCESS);
}

static int	envtopath(char **path, t_list *env, char *var)
{
	char	*varpath;

	varpath = get_env_var(var, env);
	if (!varpath || !varpath[0])
	{
		ft_printf_fd("minishell: cd: %s not set\n", STDERR_FILENO, var);
		return (EXIT_FAILURE);
	}
	*path = varpath;
	return (EXIT_SUCCESS);
}

static int	create_path(char **path, char *arg, t_list *env)
{
	if (!arg || !arg[0] || !ft_strncmp(arg, "--", 3))
	{
		if (envtopath(path, env, "HOME") == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (!ft_strncmp(arg, "-", 2))
	{
		if (envtopath(path, env, "OLDPWD") == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
		*path = arg;
	return (EXIT_SUCCESS);
}

int	ms_cd(char *arg, t_list **env)
{
	char	*path;

	if (create_path(&path, arg, *env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (chdir(path) == -1)
	{
		ft_printf_fd("minishell: cd: %s: ", STDERR_FILENO, path);
		perror(NULL);
		return (EXIT_FAILURE);
	}
	if (update_env(env) == EXIT_SUCCESS
		&& arg && !ft_strncmp(arg, "-", 2))
	{
		path = getcwd(NULL, 0);
		ft_putendl_fd(path, STDOUT_FILENO);
		free(path);
	}
	return (EXIT_SUCCESS);
}
