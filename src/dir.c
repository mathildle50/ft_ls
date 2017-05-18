/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:07:47 by mallard           #+#    #+#             */
/*   Updated: 2017/05/18 13:51:30 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_dir		*dirnew(char *path, char **file)
{
	t_dir			*new;

	new = (t_dir *)malloc(sizeof(t_dir));
	if (!new)
		return (0);
	new->file = file;
	new->path = path;
	new->rank = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		diradd(t_dir **file, t_dir *new)
{
	if (new && *file && file)
	{
		new->next = *file;
		new->prev = NULL;
		(*file)->prev = new;
		startdir(file);
	}
}

int			sizelst(t_dir **file)
{
	int		i;

	i = 0;
	startdir(file);
	while ((*file)->next != NULL)
	{
		*file = (*file)->next;
		i++;
	}
	return (i + 1);
}

void		startdir(t_dir **file)
{
	while ((*file)->prev != NULL)
		*file = (*file)->prev;
}

int			is_end(char *path, char *str)
{
	DIR				*dir;
	int				i;
	struct dirent	*sd;
	char			**tmp;
	struct stat		buf;

	dir = opendir(str);
	if (dir == NULL)
		return (0);
	while ((sd = readdir(dir)) != NULL)
	{
		lstat(double_path(str, sd->d_name), &buf);
		if (S_ISDIR(buf.st_mode) && ft_strncmp(sd->d_name, ".", 1))
			tmp = add_str_to_tab(tmp, double_path(path, sd->d_name));
	}
	closedir(dir);
	i = tablen(tmp);
	return (ft_strcmp(tmp[i] , str)) ? 0 : 1;
}
