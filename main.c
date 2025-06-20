/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:22:13 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/20 15:18:05 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

void	here_doc(int ac, char **av, char **ev)
{
	int	outfile;
	int	tmpfile;
	int	files[2];

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

void	pipex(int ac, char **av, char **ev)
{
	int	infile;
	int	outfile;
	int	files[2];

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

int	main(int argc, char **argv, char **envp)
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
