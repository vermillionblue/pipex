/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:55:51 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/24 00:04:35 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_stdin(char *limiter, int fd[2])
{
	char	*line;

	limiter = ft_sttrjoin(limiter, "\n");
	close(fd[0]);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(limiter, line, ft_strlen(limiter) + 1) || !line)
			exit(1);
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
}

void	here_doc(char *limiter)
{
	int		id;
	int		fd[2];

	check_pipe(pipe(fd));
	check_fork(id = fork());
	if (id == 0)
		read_stdin(limiter, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
	}
}
