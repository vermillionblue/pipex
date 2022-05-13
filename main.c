/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:22:38 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/14 01:44:44 by danisanc         ###   ########.fr       */
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
	ft_putstr_fd("Command '", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("' not found :( \n", 2);
	exit (0);
}

int	ft_strnncmp(const char *s1, const char *s2, size_t n)
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


char **get_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnncmp(env[i], "PATH", 4) == 0)
		{
			ft_memmove(env[i], env[i] + 5, ft_strlen(env[i]));
			return (ft_split(env[i], ':'));
		}
		i++;
	}
	return (NULL);
}

void execute_cmds(char **argv, char **env, int i, char **paths)
{
	char	*a_path;
	char	**cmd;
	int		id;
	int		fd[2];

	if (pipe(fd) == -1)
		perror("Couldn't create pipe");
	id = fork();
	cmd = ft_split(argv[i], ' ');
	a_path = get_correct_path(paths, cmd);
	if (id == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		if (execve(a_path, cmd, env) == 0)
			perror("cannot execute");
	}
	waitpid(id, NULL, WNOHANG);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void last_cmd(char **argv, char **env, int i, char **paths)
{
	char	*a_path;
	char	**cmd;

	cmd = ft_split(argv[i], ' ');
	a_path = get_correct_path(paths, cmd);
	execve(a_path, cmd, env);
}

int main(int argc, char **argv, char **env)
{
	int		fd[2];
	char	**paths;
	char	*a_path;
	char	**cmd;
	int		i;

	i = 2;
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT  | O_TRUNC, 0777);
	paths = get_paths(env);
	dup2(fd[0], STDIN_FILENO);
	while (i < argc - 2)
	{
		execute_cmds(argv, env, i, paths);
		i++;
	}
	dup2(fd[1], STDOUT_FILENO);
	cmd = ft_split(argv[argc - 2], ' ');
	a_path = get_correct_path(paths, cmd);
	if (execve(a_path, cmd, env) == 0)
			perror("cannot execute");
	return (0);
}