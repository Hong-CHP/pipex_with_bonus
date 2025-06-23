/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:37:44 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/23 16:25:26 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	if_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			return (1);
		i++;
	}
	return (0);
}

int	if_slash(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			count++;
		i++;
	}
	return (count);
}

void	error_exit(char *msg, int infile, int outfile)
{
	perror(msg);
	if (infile > 0)
		close(infile);
	if (outfile > 0)
		close(outfile);
	exit(EXIT_FAILURE);
}

char	**sep_split(char *str, char sep)
{
	char	**res;

	if (sep != 0)
		res = ft_split(str, sep);
	else
	{
		res = malloc(sizeof(char *) * 2);
		if (!res)
			return (NULL);
		res[0] = ft_strdup(str);
		res[1] = NULL;
	}
	return (res);
}

char	**find_sign_then_split(char *str)
{
	int		i;
	char	**res;
	char	sep;

	sep = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		{
			sep = str[i];
			break ;
		}
		else if (str[i] == ':')
		{
			sep = str[i];
			break ;
		}
		i++;
	}
	res = sep_split(str, sep);
	return (res);
}
