/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:04:08 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/20 15:16:24 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

pid_t	make_pipe_child1(int files[], char *cmd1, char **ev, int pipefd[])
{
	pid_t	pid;
	char	**args;

	pid = fork();
	if (pid < 0)
	{
		error_exit("Fork error", files[0], files[1]);
		unlink("here.txt");
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(files[0], 0);
		close(files[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		args = find_sign_then_split(cmd1);
		exe_cmd(cmd1, args, ev);
	}
	return (pid);
}

pid_t	make_pipe_child2(int files[], char *cmd2, char **ev, int pipefd[])
{
	pid_t	pid;
	char	**args;

	pid = fork();
	if (pid < 0)
	{
		error_exit("Fork error", files[0], files[1]);
		unlink("here.txt");
	}
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		dup2(files[1], 1);
		close(files[1]);
		args = find_sign_then_split(cmd2);
		exe_cmd(cmd2, args, ev);
	}
	return (pid);
}

void	creat_pipe_for_here_doc(int files[], char **av, char **ev)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
	{
		error_exit("Fork error", files[0], files[1]);
		unlink("here.txt");
	}
	pid1 = make_pipe_child1(files, av[3], ev, pipefd);
	pid2 = make_pipe_child2(files, av[4], ev, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	creat_write_in_tmp_file(char **av)
{
	char	*limiter;
	int		tmpfile;
	char	*line;

	limiter = av[2];
	tmpfile = open("here.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmpfile < 0)
		return (tmpfile);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(limiter, line, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(tmpfile, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	return (tmpfile);
}
