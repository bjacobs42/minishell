/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:35:13 by bjacobs           #+#    #+#             */
/*   Updated: 2023/06/20 14:36:41 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

int	ms_pwd(void)
{
	char	path[MAXPATHLEN];
	size_t	pathlen;

	getcwd(path, MAXPATHLEN);
	pathlen = ft_strlen(path);
	path[pathlen] = '\n';
	if (write(STDOUT_FILENO, path, pathlen + 1) == -1)
		perror("minishell: pwd: write");
	return (EXIT_SUCCESS);
}
