/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:46:57 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/19 08:29:32 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(char *input, t_cmd **command, t_list *mini_env)
{
	t_list	*tokens;
	int		ret;

	ret = 0;
	tokens = NULL;
	if (lexer(&tokens, input) <= 0 || precheck(tokens))
		ret = 1;
	else
		ret = parsetokens(tokens, command, mini_env);
	clear_tokens(&tokens);
	return (ret);
}
