/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 22:26:24 by bjacobs           #+#    #+#             */
/*   Updated: 2023/06/20 14:33:51 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTIN_H
# define MS_BUILTIN_H

# include "minishell.h"

# define EXIT_PARSE_MSG "minishell: exit: %s: numeric argument required\n"
# define CMD_NOT_FOUND "minishell: %s: command not found\n"
# define IS_DIR "minishell: %s: is a directory\n"
# define PRM_DENIED "minishell: %s: permission denied\n"
# define VAR_INVALID "minishell: export: `%s': not a valid identifier\n"
# define CD_GETCWD_ERR "minishell: error retrieving current directory:\
 getcwd: %s: "

int		ms_exit(char **av, t_cmd **head, t_list **env, bool child);
int		ms_export(char **av, t_list **env);
int		ms_unset(char **av, t_list **env);
int		ms_echo(char **av);
int		ms_pwd(void);
int		ms_cd(char *arg, t_list **env);
int		update_variable(char *var_name, t_list **env);
int		add_variable(char *variable, t_list **env);
int		parse_str_llong(char *s);

void	ms_penv(t_list *env, bool pexport);

char	*get_env_var(char *var_name, t_list *env);

bool	only_c(char *s, char c, char delimiter);

#endif
