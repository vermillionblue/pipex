/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 22:06:36 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/14 00:33:32 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int												i;
	unsigned char									*p;
	unsigned char									*p2;

	p = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	while ((p[i] != '\0' || p2[i] != '\0') && n > 0)
	{
		if (p[i] != p2[i])
		{
			return (p[i] - p2[i]);
		}
		else
		{
			i++;
			n--;
		}
	}
	return (0);
}
