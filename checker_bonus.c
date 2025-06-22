/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 09:49:02 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/22 11:30:01 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_limiter(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 'A' || str[i] > 'Z')
			return (-1);
		i++;
	}
	return (0);
}

int	check_access(char *infile, char *outfile)
{
	if (access(infile, F_OK) == -1)
	{
		perror("Infile does not exist");
		return (-1);
	}
	if (access(infile, R_OK) == -1)
	{
		perror("Infile has not read permission");
		return (-1);
	}
	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		perror("Outfile permission denied");
		return (-1);
	}
	return (0);
}

int	ck_here_donc(int ac, char **av)
{
	if (ac != 6)
	{
		perror("Total numbers of parameters are incorrect");
		return (-1);
	}
	if (!av[ac - 1] || !av[ac - 1][0])
	{
		perror("Enter vailable file");
		return (-1);
	}
	if (access(av[ac - 1], F_OK) == 0 && access(av[ac - 1], W_OK) == -1)
	{
		perror("Outfile permission denied");
		return (-1);
	}
	if (check_limiter(av[2]) == -1)
	{
		perror("LIMITER must be written in major");
		return (-1);
	}
	return (0);
}

int	ck_pipex(int ac, char **av)
{
	if (ac < 5)
	{
		perror("Not enough parameters");
		exit (EXIT_FAILURE);
	}
	if (!av[1] || !av[ac - 1])
	{
		perror("Enter vailable file");
		exit (EXIT_FAILURE);
	}
	if (check_access(av[1], av[ac - 1]) == -1)
		return (-1);
	return (0);
}

char	**check_args(char **args)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (args[i])
	{
		j = 0;
		len = ft_strlen(args[i]);
		while (j + 2 < len)
		{
			if (args[i][j] == '\'' && args[i][j + 2] == '\'' )
			{
				args[i][j] = args[i][j + 1];
				args[i][j + 1] = '\0';
			}
			j++;
		}
		i++;
	}
	return (args);
}
