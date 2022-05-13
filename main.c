/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:22:38 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/14 00:18:35 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

char	*get_correct_path(char **paths, char **cmd)
{
	int	i;
	char	*a_path;

	i = 0;
	while (paths[i])
	{
		a_path = ft_strjoin(paths[i], "/");
		a_path = ft_strjoin(a_path, cmd[0]);
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

void execute_cmds(char **argv, char **env, int i)
{
	char	*a_path;
	char	**cmd;
	int		id;
	int		fd[2];

	if (pipe(fd) == -1)
		perror("Couldn't create pipe");
	id = fork();
	cmd = ft_split(argv[i], ' ');
	a_path = get_correct_path(get_paths(env), cmd);
	if (id == 0)
	{	
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execve(a_path, cmd, env);
	}
	waitpid(id, NULL, WNOHANG);
	dup2(fd[0], STDIN_FILENO);
	
}

void last_cmd(char **argv, char **env, int i)
{
	char	*a_path;
	char	**cmd;

	cmd = ft_split(argv[2 + i], ' ');
	a_path = get_correct_path(get_paths(env), cmd);
	execve(a_path, cmd, env);
}

int main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	i;

	i = 2;
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT, 0777);
	// printf("%d\n",fd[0]);
	// printf("%s\n",cmd[0]);
	// printf("%s\n",cmd[1]);
	// if (pipe(fd) == -1)
	// 	return (1);
	//a_path = get_correct_path(get_paths(env), cmd);
	//printf("%s\n", a_path);
	dup2(fd[0], STDIN_FILENO);
	while (i <= argc - 3)
	{
		execute_cmds(argv, env, i);
		i++;
	}
	dup2(fd[1], STDOUT_FILENO);
	last_cmd(argv, env, argc - 2);
	//return (0);
}