/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:15:17 by ttresori          #+#    #+#             */
/*   Updated: 2018/11/29 14:13:43 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

char	*get_home(t_file *s_file)
{
	int		i;
	char	**tmp;
	char	*returnt;

	returnt = NULL;
	tmp = NULL;
	i = -1;
	if (-1 != (i = search_env(s_file->env, s_file->size_env, "HOME=")))
	{
		if ((tmp = ft_strsplit(s_file->env[i], '=')))
		{
			if (!(returnt = ft_strdup(tmp[1])))
				return (NULL);
			free_split(tmp);
			return (returnt);
		}
	}
	return (NULL);
}

int		get_path(t_file *s_file)
{
	int		i;
	char	**tmp;

	i = search_env(s_file->env, s_file->size_env, "PATH=");
	if (i < 0)
	{
		s_file->path = NULL;
		return (1);
	}
	if (!(s_file->path = ft_strsplit(s_file->env[i], ':'))
	|| !(tmp = ft_strsplit(s_file->path[0], '=')))
		return (0);
	free(s_file->path[0]);
	if (!(s_file->path[0] = ft_strdup(tmp[1])))
		return (0);
	i = 0;
	while (tmp[i] != NULL)
		ft_strdel(&tmp[i++]);
	i = 0;
	while (s_file->path[i])
		i++;
	s_file->size_path = i + 1;
	free(tmp);
	return (1);
}
