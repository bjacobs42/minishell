/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cwd_size.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:48:19 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/15 17:36:44 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns the amount of items in current working directory
size_t	get_cwd_size(void)
{
	struct dirent	*data;
	DIR				*dir;
	size_t			i;

	dir = opendir(".");
	if (!dir)
		return (0);
	i = 0;
	data = readdir(dir);
	while (data)
	{
		i++;
		data = readdir(dir);
	}
	closedir(dir);
	return (i);
}
