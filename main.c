/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:22:38 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/24 00:09:17 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_double(char **string)
{
	int	i;

	i = 0;
	while (string[i] != NULL)
	{
		free(string[i]);
		i++;
	}
	free(string[i]);
	free(string);
}

void	execute_cmds(char **env, char **paths, char *argv)
{
	char	*a_path;
	char	**cmd;
	int		id;
	int		fd[2];

	check_pipe(pipe(fd));
	check_fork(id = fork());
	if (id == 0)
	{
		cmd = ft_split(argv, ' ');
		a_path = get_correct_path(paths, cmd);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(a_path, cmd, env) == -1)
			exit (EXIT_FAILURE);
	}
	waitpid(id, NULL, WNOHANG);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
}

int	exec_last(int argc, char **argv, char **env, char **paths)
{
	int		id;
	char	**cmd;
	char	*a_path;
	int		status;

	check_fork(id = fork());
	if (id == 0)
	{
		cmd = ft_split(argv[argc - 2], ' ');
		a_path = get_correct_path(paths, cmd);
		execve(a_path, cmd, env);
		free(a_path);
		free_double(cmd);
		exit (EXIT_FAILURE);
	}
	waitpid(id, &status, WNOHANG);
	return (status);
}

void	set_fds(int fd[2], char **argv, int argc, int *i)
{
	if (!ft_strncmp("here_doc", argv[1], 8))
	{	
		fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		here_doc(argv[2]);
		*i = *i + 1;
	}
	else
	{
		fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		fd[0] = open(argv[1], O_RDONLY);
		dup2(fd[0], STDIN_FILENO);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	char	**paths;
	int		status;
	int		i;

	i = 1;
	if (argc < 5)
		return (1);
	set_fds(fd, argv, argc, &i);
	paths = get_paths(env);
	while (++i < argc - 2)
		execute_cmds(env, paths, argv[i]);
	dup2(fd[1], STDOUT_FILENO);
	status = exec_last(argc, argv, env, paths);
	free_double(paths);
	return (status);
}
