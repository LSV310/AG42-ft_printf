/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:18:51 by agruet            #+#    #+#             */
/*   Updated: 2024/11/19 12:05:30 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_tab(char **tab, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
		free(tab[i++]);
	free(tab);
	return (NULL);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	new_word;
	int	count;

	i = 0;
	new_word = 1;
	count = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] != c)
		{
			if (new_word)
			{
				new_word = 0;
				count++;
			}
		}
		else
			new_word = 1;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		words;
	int		i;
	int		j;
	int		k;

	words = count_words(s, c);
	tab = ft_calloc(words + 1, sizeof(char *));
	if (!tab || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j] && i < words)
	{
		while (s[j] && s[j] == c)
			j++;
		k = j;
		while (s[j] && s[j] != c)
			j++;
		tab[i] = ft_calloc(j - k + 1, sizeof(char));
		if (!tab[i])
			return (free_tab(tab, i));
		ft_strlcpy(tab[i++], s + k, j - k + 1);
	}
	return (tab);
}
