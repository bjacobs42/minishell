/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvan-der <kvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 20:47:31 by kvan-der      #+#    #+#                 */
/*   Updated: 2023/06/21 16:46:29 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_builtin.h"

int	g_estatus;

void	main_loop(t_list **mini_env)
{
	char		*input;
	t_cmd		*command;

	command = NULL;
	input = readline("minishell-$ ");
	if (input == NULL)
		ms_exit(NULL, NULL, mini_env, false);
	if (input[0] != '\0')
	{
		add_history(input);
		signal(SIGINT, SIG_IGN);
		if (parse(input, &command, *mini_env) == 0)
			guillotine(&command, mini_env, false);
		clear_t_cmds(&command);
	}
	free(input);
}

int	set_echo(void)
{
	int				fd;
	struct termios	settings;

	fd = ttyslot();
	if (!isatty(fd))
		return (0);
	if (tcgetattr(fd, &settings) < 0)
		return (0);
	settings.c_lflag |= ICANON;
	settings.c_lflag |= ECHO;
	settings.c_lflag |= PENDIN;
	if (tcsetattr(fd, TCSADRAIN, &settings) < 0)
		return (1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_list		*mini_env;

	if (ac < 1 || !av[0])
		return (EXIT_FAILURE);
	g_estatus = 0;
	mini_env = NULL;
	if (ft_make_env(&mini_env, envp) == 1)
		mini_env = NULL;
	while (1)
	{
		rl_catch_signals = 0;
		signal(SIGINT, &inthandler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
		set_echo();
		main_loop(&mini_env);
	}
	rl_clear_history();
	ft_lstclear(&mini_env, free);
}
