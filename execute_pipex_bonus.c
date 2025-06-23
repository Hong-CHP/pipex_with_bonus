/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipex_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 09:50:35 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/23 16:23:12 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**extract_path(char **ev)
{
	int		i;
	char	**paths;

	i = 0;
	while (ev[i])
	{
		if (ft_strncmp("PATH=", ev[i], 5) == 0)
		{
			paths = find_sign_then_split(ev[i] + 5);
			if (!paths)
			{
				perror("Extract path no success");
				free_split(paths);
				exit (127);
			}
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*get_path_after_join(char **args, char	**ev_path, int i)
{
	char	*temp;
	char	*path;

	temp = NULL;
	path = NULL;
	temp = ft_strjoin("/", args[0]);
	if (!temp)
	{
		free_split(ev_path);
		return (NULL);
	}
	path = ft_strjoin(ev_path[i], temp);
	free(temp);
	return (path);
}

char	*find_exe_path(char **args, char **ev)
{
	char	*path;
	char	*exe_path;
	char	**ev_path;
	int		i;

	exe_path = NULL;
	ev_path = extract_path(ev);
	i = 0;
	while (ev_path[i])
	{
		path = get_path_after_join(args, ev_path, i);
		if (path)
		{
			if (access(path, X_OK) == 0)
			{
				exe_path = ft_strdup(path);
				free(path);
				break ;
			}
			free(path);
		}
		i++;
	}
	free_split(ev_path);
	return (exe_path);
}

char	*get_exe_path_if_slash(char *cmd, char *exe_path, char **args)
{
	if (if_space(cmd))
		exe_path = ft_strdup(args[0]);
	else
	{
		if (access(cmd, X_OK) == 0)
			exe_path = ft_strdup(cmd);
		else
		{
			perror("Dose not have permissions");
			free_split(args);
			exit (126);
		}
	}
	return (exe_path);
}

// int i = 0;
// while (args[i])
// {
//   fprintf(stderr, "%s\n", args[i]);
//	 i++;
// }
void	exe_cmd(char *cmd, char **args, char **ev)
{
	char	*exe_path;

	check_args(args);
	exe_path = NULL;
	if (if_slash(cmd) > 1)
		exe_path = get_exe_path_if_slash(cmd, exe_path, args);
	else
		exe_path = find_exe_path(args, ev);
	if (!exe_path)
	{
		perror("No vailable command or path");
		free_split(args);
		exit (127);
	}
	if (exe_path)
	{
		execve(exe_path, args, ev);
		perror("Error executions");
		free(exe_path);
	}
	free_split(args);
	exit (1);
}
