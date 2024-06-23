/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:20:06 by bjacobs           #+#    #+#             */
/*   Updated: 2023/06/15 21:07:17 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static void	init_vars(t_file_dt *file, int *o_flags, enum e_fdio *io)
{
	if (file->flag == RE_OU_TR || file->flag == RE_OU_AP)
	{
		*io = OUT;
		if (file->flag == RE_OU_TR)
			*o_flags = O_WRONLY | O_CREAT | O_TRUNC;
		else
			*o_flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	else
	{
		*io = IN;
		*o_flags = O_RDONLY;
	}
}

int	change_fd(int *fd, t_list *file_lst)
{
	int			o_flags;
	t_file_dt	*file;
	enum e_fdio	io;

	while (file_lst)
	{
		file = (t_file_dt *)file_lst->content;
		init_vars(file, &o_flags, &io);
		if ((fd[io] != STDIN_FILENO && io == IN)
			|| (fd[io] != STDOUT_FILENO && io == OUT))
		{
			close(fd[io]);
		}
		fd[io] = open(file->name, o_flags, 0664);
		if (fd[io] == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(file->name);
			return (EXIT_FAILURE);
		}
		file_lst = file_lst->next;
	}
	return (EXIT_SUCCESS);
}

int	replace_stdio(int fd, int oldfd, bool mkdup)
{
	int	dupfd;

	if (fd == oldfd || fd < 0 || oldfd < 0)
		return (-1);
	if (mkdup)
		dupfd = dup(oldfd);
	else
		dupfd = -1;
	dup2(fd, oldfd);
	close(fd);
	return (dupfd);
}
