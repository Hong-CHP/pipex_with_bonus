/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipe_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 09:25:09 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/23 15:28:38 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_childs(int pipefd[], int i, int nb_cmd, int *prev_pipe)
{
	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (i != nb_cmd - 1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	close_parent(int pipefd[], int i, int nb_cmd, int *prev_pipe)
{
	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (i < nb_cmd - 1)
	{
		close(pipefd[1]);
		*prev_pipe = pipefd[0];
	}
}

void	pipe_in_childs(int files[], int *prev_pipe, int i)
{
	if (i == 0)
	{
		dup2(files[0], 0);
		close(files[0]);
	}
	else
		dup2(*prev_pipe, 0);
}

void	pipe_out_childs(int files[], int pipefd[], int i, int nb_cmd)
{
	if (i != nb_cmd - 1)
		dup2(pipefd[1], 1);
	else
	{
		dup2(files[1], 1);
		close(files[1]);
	}
}

void	creat_pipe_fork_childs(int files[], int ac, char **av, char **ev)
{
	int		prev_pipe;
	int		pipefd[2];
	int		i;
	pid_t	pid;

	prev_pipe = -1;
	i = 0;
	while (i < ac - 3)
	{
		if (i != ac - 3 - 1 && pipe(pipefd) == -1)
			error_exit("Pipe error", files[0], files[1]);
		pid = fork();
		if (pid < 0)
			error_exit("Fork error", files[0], files[1]);
		if (pid == 0)
		{
			pipe_in_childs(files, &prev_pipe, i);
			pipe_out_childs(files, pipefd, i, ac - 3);
			close_childs(pipefd, i, ac - 3, &prev_pipe);
			exe_cmd(av[i + 2], find_sign_then_split(av[i + 2]), ev);
		}
		close_parent(pipefd, i, ac - 3, &prev_pipe);
		i++;
	}
	close_childs(pipefd, i, ac - 3, &prev_pipe);
}
