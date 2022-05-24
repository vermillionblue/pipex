/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:18:52 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/16 15:10:08 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	charinset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	size_t	start;
	size_t	end;
	int		i;

	start = 0;
	i = 0;
	end = ft_strlen(s1);
	while (s1[start] && charinset(set, s1[start]))
		start++;
	while (end > start && charinset(set, s1[end - 1]))
		end--;
	p = malloc(end - start + 1);
	if (!p)
		return (NULL);
	while (start < end)
	{
		p[i] = s1[start];
		start++;
		i++;
	}
	p[i] = '\0';
	return (p);
}
