/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:52:31 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/24 00:05:39 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_correct_path(char **paths, char **cmd)
{
	int		i;
	char	*a_path;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		a_path = ft_strjoin(temp, cmd[0]);
		if (access(a_path, F_OK) == 0)
			return (a_path);
		i++;
	}
	ft_putstr_fd("command not found ", 2);
	exit (EXIT_FAILURE);
}

char	**get_paths(char **env)
{
	int		i;
	char	**temp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{	
			ft_memmove(env[i], env[i] + 5, ft_strlen(env[i]));
			temp = ft_split(env[i], ':');
			return (temp);
		}
		i++;
	}
	exit (EXIT_FAILURE);
}
