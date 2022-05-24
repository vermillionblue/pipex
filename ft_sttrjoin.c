/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sttrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:19:33 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/23 15:36:28 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_sttrjoin(char const *s1, char const *s2)
{
	int		i;
	int		k;
	char	*p;
	int		j;

	j = 0;
	i = ft_strlen((char *)s1);
	k = ft_strlen((char *)s2);
	p = malloc(k + i + 1);
	if (p == NULL)
		return (NULL);
	while (j < i)
	{
		p[j] = s1[j];
		j++;
	}
	j = 0;
	while (j < k)
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + k] = '\0';
	return (p);
}
