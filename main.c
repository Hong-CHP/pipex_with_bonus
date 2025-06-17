/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:22:13 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/17 14:16:14 by hporta-c         ###   ########.fr       */
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
		error_exit("Fork error", files[0], files[1]);
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
		error_exit("Fork error", files[0], files[1]);
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
	int	pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
		error_exit("Pipe error", files[0], files[1]);
	pid1 = make_pipe_child1(files, av[3], ev, pipefd);
	pid2 = make_pipe_child2(files, av[4], ev, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int creat_write_in_tmp_file(char **av)
{
    char    *limiter;
    int     tmpfile;
    char    *line;
    
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

void    here_doc(int ac, char **av, char **ev)
{
    int     outfile;
    int     tmpfile;
    int files[2];
    
    outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    tmpfile = creat_write_in_tmp_file(av);
    if (outfile < 0 || tmpfile < 0)
        return ;
    close(tmpfile);
    tmpfile = open("here.txt", O_RDONLY);
    if (tmpfile < 0)
        error_exit("Temporary file ropenning failed", tmpfile, outfile);
    files[0] = tmpfile;
    files[1] = outfile;
    creat_pipe_for_here_doc(files, av, ev);
    close(files[0]);
    close(files[1]);
    unlink("here.txt");
}

void    pipex(int ac, char **av, char **ev)
{
    int infile;
    int outfile;
    int files[2];

    infile = open(av[1], O_RDONLY);
    outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (infile < 0 || outfile < 0)
        error_exit("File openning failed", infile, outfile);
    files[0] = infile;
    files[1] = outfile;
    creat_pipe_fork_childs(files, ac, av, ev);
    while (wait(NULL) > 0)
        ;
    close(files[0]);
    close(files[1]);
    close(infile);
    close(outfile);
}

int main(int argc, char **argv, char **envp)
{
    if (ft_strncmp("here_doc", argv[1], ft_strlen(argv[1])) == 0)
    {
        if (ck_here_donc(argc, argv) != -1)
            here_doc(argc, argv, envp);
        else
            return (1);
    }
    else
    {
        if (ck_pipex(argc, argv) == -1)
            return (1);
        pipex(argc, argv, envp);
    }
    return (0);
}
