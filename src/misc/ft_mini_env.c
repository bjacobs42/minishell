/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:47:44 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/21 17:04:22 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_builtin.h"

static void	put_lvl_warning(long long lvl)
{
	char	*s;

	s = ft_btoa(lvl, 10);
	if (!s)
	{
		perror("minishell: setlevel");
		return ;
	}
	ft_printf_fd(MS_WARNING_SHLVL, STDERR_FILENO, s);
	free(s);
}

static int	setlevel(t_list **env)
{
	long long	lvl;
	char		*shlvl;
	char		*tmp;

	shlvl = get_env_var("SHLVL", *env);
	if (!shlvl || parse_str_llong(shlvl) != EXIT_SUCCESS)
		shlvl = "0";
	lvl = ft_atob(shlvl, 10) + 1;
	if (lvl > 1000)
	{
		put_lvl_warning(lvl);
		lvl = 1;
	}
	else if (lvl < 0)
		lvl = 0;
	tmp = ft_itoa(lvl);
	if (!tmp)
		return (EXIT_FAILURE);
	shlvl = ft_strjoin("SHLVL=", 0, tmp);
	free(tmp);
	if (!shlvl)
		return (EXIT_FAILURE);
	if (update_variable(shlvl, env) != EXIT_SUCCESS)
		return (free(shlvl), EXIT_FAILURE);
	return (free(shlvl), EXIT_SUCCESS);
}

int	ft_make_env(t_list **mini_env, char **environ)
{
	int			i;
	t_list		*link;
	char		*element;

	i = 0;
	while (environ[i] != NULL)
	{
		element = ft_strdup(environ[i]);
		if (element == NULL)
			return (1);
		link = ft_lstnew(element);
		if (link == NULL)
		{
			ft_lstclear(mini_env, free);
			ft_putstr_fd(MS_MINIENV_FAILED, STDERR_FILENO);
			return (1);
		}
		ft_lstadd_back(mini_env, link);
		i++;
	}
	if (setlevel(mini_env) != EXIT_SUCCESS)
		return (ft_putstr_fd(MS_MINIENV_FAILED, STDERR_FILENO), \
				ft_lstclear(mini_env, free), 1);
	return (0);
}
