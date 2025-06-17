/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:15:09 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/17 11:44:45 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "pipex.h"

char	*cut_line(char *dest, char **rest)
{
	char	*line;
	int		end;

	if (!dest)
		return (NULL);
	end = 0;
	while (dest[end] != '\n' && dest[end] != '\0')
		end++;
	if (dest[end] == '\n')
		line = ft_substr(dest, 0, end + 1);
	else
		line = ft_substr(dest, 0, end);
	if (dest[end] != '\0')
		*rest = ft_strdup(&dest[end + 1]);
	else
		*rest = NULL;
	return (line);
}

char	*allo_init_buf(int fd, char **dest)
{
	char	*buff;
	int		bytes_read;
	char	*temp;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (!*dest)
		*dest = ft_strdup("");
	bytes_read = 1;
	while (bytes_read > 0 && ft_strchr(*dest, '\n') == NULL)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buff);
			return (*dest);
		}
		buff[bytes_read] = '\0';
		temp = *dest;
		*dest = ft_strjoin(*dest, buff);
		free(temp);
	}
	free(buff);
	return (*dest);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*rest;
	char		*temp;
	static char	*dest;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = allo_init_buf(fd, &dest);
	if (!temp)
		return (NULL);
	dest = temp;
	if (!dest || dest[0] == '\0')
	{
		free(dest);
		dest = NULL;
		return (NULL);
	}
	line = cut_line(dest, &rest);
	free(dest);
	dest = rest;
	return (line);
}