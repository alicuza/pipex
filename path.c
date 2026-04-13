/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:39:37 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/23 18:17:39 by sancuta          ###   ########.fr       */
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
	if (data->buf[data->used - 1] != '/')
	{
		arena_strlcpy(data, "/", 2);
		data->used--;
	}
	return (offset);
}

char	*get_first(t_arena *data, char *path, int *pos, char *cmd)
{
	size_t	offset;

	if (pos[0] == -1)
		return (NULL);
	offset = get_prefix(data, path, pos[0], pos[1]);
	arena_strlcpy(data, cmd, ft_strlen(cmd) + 1);
	return (data->buf + offset);
}

char	*find_in_path(t_arena *data, char *path_var, char *cmd)
{
	int		env_off;
	int		size;
	int		first[2];
	size_t	offset;

	first[0] = -1;
	env_off = 5;
	while (*path_var && path_var[env_off])
	{
		size = ft_indchr(path_var + env_off, ':');
		if (size == -1)
			size = ft_strlen(path_var + env_off);
		offset = get_prefix(data, path_var, env_off, size);
		arena_strlcpy(data, cmd, ft_strlen(cmd) + 1);
		if (access(data->buf + offset, X_OK) != -1)
			return (data->buf + offset);
		if (first[0] == -1 && access(data->buf + offset, F_OK) != -1)
		{
			first[0] = env_off;
			first[1] = size;
		}
		arena_restore(data, offset);
		env_off += size + (path_var[env_off + size] != '\0');
	}
	return (get_first(data, path_var, first, cmd));
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
		return (env->data->buf + offset);
	}
	return (find_in_path(env->data, path_var, cmdv[0]));
}
