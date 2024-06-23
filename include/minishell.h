/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 22:08:18 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/06/21 18:04:29 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <dirent.h>
# include <stdbool.h>

# define MS_WARNING_SHLVL "minishell: warning: shell level\
 (%s) too high, resetting to 1\n"
# define MS_MINIENV_FAILED "minishell: warning: Unable to create environment\n"

# define HD_MAX_TMPFILE "here_doc: Unable to make temporary file\n"

# define CRIT_FAILURE -1

enum e_fdio
{
	IN,
	OUT
};

enum e_type
{
	WORD,
	PIPE,
	RE_IN,
	HERE_DOC,
	RE_OU_TR,
	RE_OU_AP,
	AND,
	OR,
	WILDCARD,
	PAR_OPEN,
	PAR_CLOSE
};

typedef struct s_token
{
	char		*value;
	enum e_type	type;
}	t_token;

typedef struct s_file_data
{
	char		*name;
	enum e_type	flag;
}				t_file_dt;

typedef struct s_command
{
	struct s_command	*next;
	struct s_command	*prntss;
	t_list				*files;
	char				**arguments;
	int					fd[2];
	enum e_type			type;
}				t_cmd;

extern int	g_estatus;

		/* Executer functions */
int		exec_cmd(t_cmd *cmd, t_cmd **head, t_list **env, bool child);
int		guillotine(t_cmd **head, t_list **env, bool child);
int		ms_execvp(char **arguments, t_list *env);
int		executer(t_cmd **cmd, t_list **env);
int		init_pipe(t_cmd *cmd);
int		init_pids(t_cmd *cmd, int **pids);
int		change_fd(int *fd, t_list *file_lst);
int		replace_stdio(int fd, int oldfd, bool mkdup);
void	clean_executer(t_cmd *cmd, int *pids);
void	close_pipes(int *pfd);

		/* tokenizer functions */
int		lexer(t_list **tokenlist, char *input);
int		tokenize(char *cmd_line, t_list **tokens);
int		tokenize_quote(char *cmd_line, t_list **tokens, char quotation);
int		other_length(char *cmd_line);
int		parsetokens(t_list *tokens, t_cmd **command, t_list *mini_env);
int		parse(char *input, t_cmd **command, t_list *mini_env);
int		add_to_dcharp(t_list **ptr, char *addition, enum e_type tag);
int		handle_operator(t_list *current_token, \
			t_cmd *cmd_list, t_list *mini_env);
int		addlink(t_cmd **command, t_token *part);
int		is_operator(enum e_type type);
int		handle_word(t_list **current_token, t_cmd *cmd_list);
int		precheck(t_list *tokens);
int		ophandling(t_list **tokens, t_cmd **command, t_list *mini_env);

		/* clean up functions */
void	clear_tokens(t_list **token_list);
void	clear_t_cmds(t_cmd **content);
void	charclean(char **ptr);

		/* expander functions */
int		expander(t_cmd *command, t_list *mini_env);
int		check_expansion(char *string, t_list *current);
void	countsubstr(char const *s, size_t *n, char c);
char	*replacestring(char *replacement, char *name, int start, int i);
char	*makereplacement(t_list *env, char *name, int start, int i);
int		argloop(char **name, int i, t_list *env);
int		find_needles(DIR *haystack, char **needles, char *asterisk);
size_t	get_cwd_size(void);
int		removequotes(char *name);
char	**resize(char **p, size_t oldsize, size_t newsize);
int		wildcardloop(char ***name, size_t *j);
int		wildcardfile(char **name);
int		wildcard(char ***name, size_t *j);
char	**stars(char *asterisk);
char	**wildcardsplit(char const *s, char c);
int		splitargs(char ***args, int i);
int		emptycheck(char ***args, size_t *i);
int		varreplace(char **name, int start, t_list *env, int *dollarsign);

		/* misc functions */
int		ft_make_env(t_list **mini_env, char **environ);
int		heredoc(t_list *current_token, t_cmd *cmd_list, t_list *env);
void	t_cmd_addback(t_cmd **command, t_cmd *link);
t_cmd	*t_cmdlast(t_cmd *lst);
t_cmd	*init_t_cmd(void);
int		t_cmd_addprntss(t_list **tokens, t_cmd **command, \
			t_cmd *link, t_list *mini_env);
void	inthandler(int status);
void	inthandler2(int status);
void	skipquotes(char *line, int *i);

#endif
