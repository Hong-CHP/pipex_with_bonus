/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 09:37:55 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/23 15:47:23 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

size_t	ft_strlen(const char *s);
void	ft_putstr(char *str);
int		if_slash(char *str);
int		if_space(char *str);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *s1, char *s2);
char	**find_sign_then_split(char *str);
char	**ft_split(char	const *s, char c);
void	free_split(char **str);
void	creat_pipe_fork_childs(int files[], int ac, char **av, char **ev);
int		creat_write_in_tmp_file(char **av);
void	creat_pipe_for_here_doc(int files[], char **av, char **ev);
void	pipex(int ac, char **av, char **ev);
void	here_doc(int ac, char **av, char **ev);
void	exe_cmd(char *cmd, char **args, char **ev);
void	error_exit(char *msg, int infile, int outfile);
int		check_limiter(char *str);
int		check_access(char *infile, char *outfile);
int		ck_here_donc(int ac, char **av);
int		ck_pipex(int ac, char **av);
char	**check_args(char **args);

#endif