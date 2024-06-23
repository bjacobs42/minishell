/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 13:34:42 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/06/21 21:51:43 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtin.h"

static int	export_parse(char *arg)
{
	size_t	i;

	if (!*arg || *arg == '=' || !ft_strncmp(arg, "+=", 2) || ft_isdigit(*arg))
		return (EXIT_FAILURE);
	i = 0;
	while (arg[i] && arg[i] != '=' && ft_strncmp(&arg[i], "+=", 2))
	{
		if (!ft_isdigit(arg[i]) && !ft_isalpha(arg[i]) && arg[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	export_variable(char **arg, t_list **env)
{
	size_t	i;
	char	*val;
	char	*tmp;

	i = 0;
	while ((*arg)[i] && (*arg)[i] != '+' && (*arg)[i] != '=')
		i++;
	if (**arg == '_' && i == 1)
		return (EXIT_SUCCESS);
	if (!(*arg)[i] || ft_strncmp(&(*arg)[i], "+=", 2))
		return (update_variable(*arg, env));
	(*arg)[i] = '\0';
	val = get_env_var(*arg, *env);
	val = ft_strjoin(val, 0, &(*arg)[i + 2]);
	if (!val)
		return (EXIT_FAILURE);
	tmp = ft_strjoin(*arg, '=', val);
	free(val);
	if (!tmp)
		return (EXIT_FAILURE);
	free(*arg);
	*arg = tmp;
	return (update_variable(*arg, env));
}

static void	*add_quote(void *content)
{
	size_t	i;
	size_t	j;
	char	*new;
	char	*var;

	var = (char *)content;
	j = ft_strlen(var);
	new = (char *)malloc(sizeof(char) * (j + 3));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (var[j] && var[j] != '=')
		new[i++] = var[j++];
	if (var[j])
	{
		new[i++] = var[j++];
		new[i++] = '\"';
		while (var[j])
			new[i++] = var[j++];
		new[i++] = '\"';
	}
	new[i] = '\0';
	return ((void *)new);
}

static int	export_penv(t_list *env)
{
	t_list	*lstdup;

	lstdup = ft_lstmap(env, add_quote, free);
	if (!lstdup)
		return (perror("minishell: export"), EXIT_FAILURE);
	ft_lstsort_alpha(lstdup);
	ms_penv(lstdup, true);
	ft_lstclear(&lstdup, free);
	return (EXIT_SUCCESS);
}

int	ms_export(char **av, t_list **env)
{
	size_t	i;
	int		estatus;

	if (!av[1] && *env)
	{
		if (export_penv(*env) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	i = 1;
	estatus = EXIT_SUCCESS;
	while (av[i])
	{
		if (export_parse(av[i]) == EXIT_FAILURE)
		{
			ft_printf_fd(VAR_INVALID, STDERR_FILENO, av[i]);
			estatus = EXIT_FAILURE;
		}
		else if (export_variable(&av[i], env) != EXIT_SUCCESS)
			return (perror("minishell: export"), EXIT_FAILURE);
		i++;
	}
	return (estatus);
}
