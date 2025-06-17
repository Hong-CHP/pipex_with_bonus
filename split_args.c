/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:14:42 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/17 14:17:43 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    free_split(char **str)
{
    int i;

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
    int i;
    
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

char	**ft_fill_split(char **tab, char *str, char c, int *tab_i)
{
	int	word_len;
	int	i;

	word_len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (word_len > 0)
			{
				tab[*tab_i] = allocate_copy_tab(word_len, &str[i - word_len], tab, tab_i);
				(*tab_i)++;
				word_len = 0;
			}
		}
		else
			word_len++;
		i++;
	}
	if (word_len > 0)
		tab[(*tab_i)++] = allocate_copy_tab(word_len, &str[i - word_len], tab, tab_i);
	tab[*tab_i] = NULL;
	return (tab);
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
