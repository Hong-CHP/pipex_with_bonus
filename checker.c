/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:47:59 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/22 10:59:20 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
