/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bjacobs <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 15:35:31 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/06/22 16:34:13 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

size_t	get_size(char *arg)
{
	size_t	i;
	size_t	size;
	bool	dq;

	i = 0;
	size = 0;
	dq = false;
	while (arg[i])
	{
		if (arg[i] == '\"')
			dq = !dq;
		else if (arg[i] == '$' && !ft_isspace(arg[i + 1]))
			size++;
		else if (arg[i] == '\'' && !dq)
		{
			i++;
			while (arg[i + 1] && arg[i] != '\'')
				i++;
		}
		i++;
	}
	return (size + 1);
}

char	*envtoarg(char *arg, int *i, t_list *env)
{
	int		start;
	char	*val;

	(*i)++;
	start = *i;
	while (arg[*i] && isvalidvar())
		(*i)++;
	if (arg[*i])
		arg[(*i)++] = '\0';
	val = get_env_val(&arg[start], env);
	if (!val)
		return (ft_strdup(""));
	val = ft_strdup(val);
	if (!val)
		return (NULL);
	return (val);
}

int	fill_bin(char *arg, char **bin, t_list *env)
{
	size_t	start;
	size_t	j;
	int		i;
	bool	dq;

	i = 0;
	j = 0;
	start = 0;
	dq = false;
	while (arg[i])
	{
		if (arg[i] == '\"')
			dq = !dq;
		else if (arg[i] == '$' && !ft_isspace(arg[i + 1]))
		{
			bin[j++] = ft_substr(arg, start, i - 1);
			bin[j++] = envtoarg(arg, &i);
			if (!bin[j - 1] || !bin[j - 2])
				return (free(bin[j - 1]), EXIT_FAILURE);
		}
		else if (arg[i] == '\'' && !dq)
		{
			i++;
			while (arg[i + 1] && arg[i] != '\'')
				i++;
			i++;
		}
		if (arg[i])
			i++;
	}
	return (EXIT_SUCCESS);
}

int	expande(char *arg, char **bin, t_list *env)
{
	size_t	arrsize;

	arrsize = get_size(arg);
	if (arrsize < 1)
		return (EXIT_SUCCESS);
	bin = (char **)malloc(sizeof(char *) * (arrsize + 1));
	if (!bin)
		return (EXIT_FAILURE);
	bin[arrsize] = NULL;
	fill_bin(arg, bin);
	if (!bin)
		return (ft_clear_strarr(bin), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	bintoarg(char ***args, size_t pos, char **bin)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (bin[i])
	{
		if (!end_quotes(bin[0]))
		{
			tmp = ft_strjoin(bin[i++], 0, bin[i++]);
			if (!tmp)
				return (EXIT_FAILURE);
			free(bin[0]);
			bin[0] = tmp;
			tmp = ft_strjoin(tmp, 0, bin[i]);
			if (!tmp)
				return (EXIT_FAILURE);
		}
		else
		{
			removequotes(
		}
		i++;
	}
}

int	argloop(char ***arguments, t_list *env)
{
	size_t	i;
	char	**bin;

	i = 0;
	while (arguments[i])
	{
		if (expande((*arguments)[i], &bin, env) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (wildcard(bin) != EXIT_SUCCESS)
		{
			if (bintoarg(arguments, i, bin) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
