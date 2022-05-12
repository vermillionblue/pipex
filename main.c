/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:22:38 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/12 16:12:15 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_correct_path(char **paths, char **argv)
{
	int	i;
	char	*a_path;

	i = 0;
	while (paths[i])
	{
		a_path = ft_strjoin(paths[i], "/");
		a_path = ft_strjoin(a_path, argv[2]);
		if (access(a_path, F_OK) == 0)
			return (a_path);
		free(a_path);
		i++;
	}
	return (NULL);
}

char **get_paths(char **env)
{
	int	i;

	i = 0;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			ft_memmove(env[i], env[i] + 5, ft_strlen(env[i]));
			return (ft_split(env[i], ':'));
		}
	}
	return (NULL);
}

int main(int argc, char **argv, char **env)
{
	int	fd[2];
	char *a_path;
	int	file;
	int	i;
	int	id;
	char	*buf;

	i = 0;
	file = open(argv[1], O_RDONLY);
	if (pipe(fd) == -1)
		return (1);
	a_path = get_correct_path(get_paths(env), argv);
	//printf("%s\n", a_path);
	id = fork();
	if (id == 0)
	{
		read(file, buf, 50); // if -1
		execve(a_path, buf, env);
		//write if -1
	}
	wait(NULL);
	
}