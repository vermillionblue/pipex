#include "libft/libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

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
	int	i;
	int	id;
	char	*buf;

	i = 0;
	fd[0] = open(argv[1], O_RDONLY);
	if (pipe(fd) == -1)
		return (0);
	a_path = get_correct_path(get_paths(env), argv);
	//printf("%s\n", a_path);

	id = fork();
	if (id == 0)
	{
		read(fd[0], buf, 50);
		execve(a_path, buf, env);
	}
	wait(NULL);

}