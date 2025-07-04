/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 09:20:48 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/23 18:55:49 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
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
	if (argc < 5)
	{
		ft_putstr("Error: Not enough parameters");
		return (1);
	}
	else if (argc == 6
		&& ft_strncmp("here_doc", argv[1], ft_strlen(argv[1])) == 0)
	{
		if (!argv[3][0] || !argv[4][0])
		{
			ft_putstr("Error: Enter vailable path");
			return (-1);
		}
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
