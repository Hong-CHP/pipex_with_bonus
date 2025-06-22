/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:22:13 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/22 11:08:42 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	make_pipe_child1(int files[], char *cmd1, char **ev, int pipefd[])
{
	pid_t	pid;
	char	**args;
	
	pid = fork();
	if (pid < 0)
		error_exit("Display file error",files[0], files[1]);
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
		error_exit("Display file error",files[0], files[1]);
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

void	creat_pipe(int files[], char **av, char **ev)
{
	int	pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
		error_exit("Display file error",files[0], files[1]);
	pid1 = make_pipe_child1(files, av[2], ev, pipefd);
	pid2 = make_pipe_child2(files, av[3], ev, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	pipex(char **av, char **ev)
{
	int	infile;
	int	outfile;
	int	files[2];

	infile = open(av[1], O_RDONLY);
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
		error_exit("Display file error",infile, outfile);
	files[0] = infile;
	files[1] = outfile;
	creat_pipe(files, av, ev);
	close(files[0]);
	close(files[1]);
}

int	main(int argc, char *argv[], char **envp)
{
	if (argc != 5)
	{
		perror("Not enough arguments");
		return (1);
	}
	if (!argv[1] || !argv[4])
	{
		perror("Invalid files arguments");
		return (1);
	}
	if (check_access(argv[1], argv[4]) == -1)
		return (1);
	pipex(argv, envp);
	return (0);
}
