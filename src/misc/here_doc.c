/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 19:01:56 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/06/21 19:19:35 by kvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>

static char	*mktmp(void)
{
	char			*num;
	char			*here_doc;
	unsigned long	i;

	i = 1;
	while (i < ULONG_MAX)
	{
		num = ft_btoa((ft_random() * i) % RAND_MAX, 16);
		if (!num)
			return (perror("minishell: heredoc"), NULL);
		here_doc = ft_strjoin("/tmp/here_doc-ms", 0, num);
		free(num);
		if (!here_doc)
			return (perror("minishell: heredoc"), NULL);
		if (access(here_doc, F_OK))
			return (here_doc);
		free(here_doc);
		i++;
	}
	ft_putendl_fd(HD_MAX_TMPFILE, STDERR_FILENO);
	return (NULL);
}

static int	ms_getline(int fd, char *delim, t_list *env)
{
	char	*line;
	int		quotes;
	size_t	linelen;

	quotes = removequotes(delim);
	line = readline("> ");
	while (line)
	{
		linelen = ft_strlen(line);
		if (!ft_strncmp(line, delim, linelen + 1))
			return (free(line), EXIT_SUCCESS);
		if (!quotes)
		{
			line[linelen] = '\0';
			argloop(&line, 0, env);
			linelen = ft_strlen(line);
		}
		line[linelen] = '\n';
		if (write(fd, line, linelen + 1) == -1)
			return (perror("minishell: heredoc: write"), EXIT_FAILURE);
		free(line);
		line = readline("> ");
	}
	return (EXIT_SUCCESS);
}

static int	sub_heredoc(int fd, char *delim, t_list *env)
{
	int	wstatus;
	int	pid;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		rl_catch_signals = 1;
		signal(SIGINT, SIG_DFL);
		wstatus = ms_getline(fd, delim, env);
		close(fd);
		exit(wstatus);
	}
	close(fd);
	waitpid(pid, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
		return (EXIT_FAILURE);
	return (WEXITSTATUS(wstatus));
}

static char	*create_heredoc(char *delim, t_list *env)
{
	char	*doc_name;
	int		fd;

	doc_name = mktmp();
	if (!doc_name)
		return (NULL);
	fd = open(doc_name, O_WRONLY | O_CREAT, 0655);
	if (fd == -1)
		return (free(doc_name), perror("minishell: heredoc: open"), NULL);
	signal(SIGINT, &inthandler2);
	if (sub_heredoc(fd, delim, env) != EXIT_SUCCESS)
		return (unlink(doc_name), free(doc_name), NULL);
	return (doc_name);
}

int	heredoc(t_list *current_token, t_cmd *cmd_list, t_list *env)
{
	t_token		*current;
	char		*filename;

	if (!current_token)
		return (EXIT_FAILURE);
	current = current_token->content;
	filename = create_heredoc(current->value, env);
	if (filename == NULL)
		return (EXIT_FAILURE);
	add_to_dcharp(&(cmd_list->files), filename, HERE_DOC);
	free(filename);
	return (EXIT_SUCCESS);
}
