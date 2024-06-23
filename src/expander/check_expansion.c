/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_expansion.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:48:37 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/09 20:48:38 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_expansion(char *string, t_list *current)
{
	if (ft_strncmp((char *)(current->content), string, ft_strlen(string))
	== 0 && ((char *)(current->content))[ft_strlen(string)] == '=')
		return (1);
	return (0);
}
