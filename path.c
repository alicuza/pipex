/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:39:37 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/22 19:01:10 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_var(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

static inline int	check_path(char *path)
{
	return (access(path, F_OK | X_OK) != -1);
}

size_t	get_prefix(t_arena *data, char *path_var, int env_off, int size)
{
	size_t	offset;

	if (!path_var || !size)
	{
		offset = arena_strlcpy(data, "./", 3);
		data->used--;
		return (offset);
	}
	offset = arena_strlcpy(data, path_var + env_off, size + 1);
	data->used--;
	if (data->buf[data->used - 2] != '/')
	{
		arena_strlcpy(data, "/", 2);
		data->used--;
	}
	return (offset);
}

char	*find_in_path(t_arena *data, char *path_var, char *cmd)
{
	int		size;
	int		env_off;
	size_t	offset;

	env_off = 5;
	size = ft_indchr(path_var + env_off, ':');
	if (size == -1)
		size = ft_strlen(path_var + env_off);
	while (*path_var)
	{
		offset = get_prefix(data, path_var, env_off, size);
		arena_strlcpy(data, cmd, ft_strlen(cmd) + 1);
		if (check_path(data->buf + offset))
			return (data->buf + offset);
		arena_restore(data, offset);
		if (path_var[env_off + size] == '\0')
			break ;
		env_off += size + 1;
		size = ft_indchr(path_var + env_off, ':');
		if (size == -1)
			size = ft_strlen(path_var + env_off);
	}
	return (NULL);
}

char	*get_cmd_path(t_env *env, char *path_var, int node_idx)
{
	size_t	offset;
	char	**cmdv;

	cmdv = (char **)(env->data->buf + env->node[node_idx].data_idx);
	if (!cmdv[0])
		return (NULL);
	if (ft_strchr(cmdv[0], '/'))
		return (cmdv[0]);
	if (!path_var)
	{
		offset = get_prefix(env->data, NULL, 0, 0);
		arena_strlcpy(env->data, cmdv[0], ft_strlen(cmdv[0]) + 1);
		if (check_path(env->data->buf + offset))
			return (env->data->buf + offset);
		return (NULL);
	}
	return (find_in_path(env->data, path_var, cmdv[0]));
}
