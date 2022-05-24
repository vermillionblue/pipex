/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:11:57 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/16 15:12:26 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	alloc_strns(char const *s, char	**arr, char c)
{
	int	k;
	int	sec;
	int	f;

	k = 0;
	sec = 0;
	f = 0;
	while (s[k] != '\0')
	{
		sec = 0;
		if (s[k] != c && s[k] != '\0')
		{
			while (s[k] != c && s[k] != '\0')
			{
				k++;
				sec++;
			}
			arr[f] = (char *)ft_calloc(sec + 1, sizeof(char ));
			f++;
		}
		else
			k++;
	}
}

static int	count_strns(const char *s, char c)
{
	int	k;
	int	f;

	k = 0;
	f = 0;
	while (s[k] != '\0')
	{
		if (s[k] != c && s[k] != '\0')
		{
			while (s[k] != c && s[k] != '\0')
				k++;
			f++;
		}
		else
			k++;
	}
	return (f);
}

static void	char_insert(char const *s, char **arr, char c)
{
	int	k;
	int	sec;
	int	f;

	f = 0;
	k = 0;
	sec = 0;
	while (s[k] != '\0')
	{
		sec = 0;
		if (s[k] != c && s[k] != '\0')
		{
			while (s[k] != c && s[k] != '\0')
			{
				arr[f][sec] = s[k];
				sec++;
				k++;
			}
			arr[f][sec] = '\0';
			f++;
		}
		else
			k++;
	}
	arr[f] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		num_strns;
	char	set[1];

	if (!s)
		return (0);
	set[0] = c;
	s = ft_strtrim(s, set);
	num_strns = count_strns(s, c);
	arr = (char **)ft_calloc(num_strns + 1, sizeof(char *));
	alloc_strns(s, arr, c);
	char_insert(s, arr, c);
	free((char *)s);
	return (arr);
}
