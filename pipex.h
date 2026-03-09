/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 07:40:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/09 12:26:07 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef enum e_type
{
	TYPE_NIL;
	TYPE_CMD;
	TYPE_ARG;
}	t_type;

typedef struct s_thing
{
	t_type	type;
	char	*data;
	size_t	parent_idx;
	size_t	sibling_idx;
	size_t	child_idx;
}	t_thing;

typedef struct s_env
{
	t_arena	perm;
	t_arena	temp;
	t_thing	*nodes;
	size_t	pipe_head;
}	t_env;
#endif
