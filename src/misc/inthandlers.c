/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inthandlers.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 21:28:20 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/14 21:29:13 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inthandler(int status)
{
	g_estatus = status + 128;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	inthandler2(int status)
{
	g_estatus = status + 128;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}
