/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:55:51 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/25 18:38:42 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_join(char const *s1, char const *s2)
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

char	*read_stdin(char *limiter)
{
	char	*line;
	int		fd;

	fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	limiter = ft_join(limiter, "\n");
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(limiter, line, ft_strlen(limiter) + 1) || !line)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	return (".here_doc");
}

void	clean_here_doc(char *start)
{
	if (!ft_strncmp("here_doc", start, 8))
		unlink(".here_doc");
}
