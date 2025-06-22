/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:14:42 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/22 09:54:36 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	count_words(char *str, char c)
{
	int	ch;
	int	count;
	int	i;

	i = 0;
	count = 0;
	ch = 1;
	while (str[i])
	{
		if (str[i] != c)
		{
			if (ch == 1)
			{
				count++;
				ch = 0;
			}
		}
		else
			ch = 1;
		i++;
	}
	return (count);
}

char	*allocate_copy_tab(int word_len, char *str, char **tab, int *tab_i)
{
	char	*word;
	int		i;

	word = (char *)malloc((word_len + 1) * sizeof(char));
	if (!word)
	{
		while (*tab_i >= 0)
		{
			free(tab[*tab_i]);
			(*tab_i)--;
		}
		free(tab);
		return (NULL);
	}
	i = 0;
	while (i < word_len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_fill_split(char **t, char *str, char c, int *idx)
{
	int	w_l;
	int	i;

	w_l = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (w_l > 0)
			{
				t[*idx] = allocate_copy_tab(w_l, &str[i - w_l], t, idx);
				(*idx)++;
				w_l = 0;
			}
		}
		else
			w_l++;
		i++;
	}
	if (w_l > 0)
		t[(*idx)++] = allocate_copy_tab(w_l, &str[i - w_l], t, idx);
	t[*idx] = NULL;
	return (t);
}

char	**ft_split(char	const *s, char c)
{
	char	**tab;
	char	*str;
	int		tab_i;

	tab_i = 0;
	str = (char *)s;
	tab = (char **)malloc((count_words(str, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab = ft_fill_split(tab, str, c, &tab_i);
	return (tab);
}
