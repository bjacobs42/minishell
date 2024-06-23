/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:37:49 by bjacobs           #+#    #+#             */
/*   Updated: 2023/06/15 17:16:05 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

long	ft_random(void)
{
	int		fd;
	long	rnum;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (984752);
	read(fd, &rnum, sizeof(long));
	close(fd);
	return (rnum);
}
