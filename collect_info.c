/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthulo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 08:36:59 by tthulo            #+#    #+#             */
/*   Updated: 2018/09/17 12:12:59 by tthulo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_dir	*ft_get_perm(t_dir *l)
{
	l->cup->rwx = ft_strnew(10);
	l->cup->rwx[0] = '-';
	l->cup->rwx[0] = (S_ISDIR(l->cup->status.st_mode)) ? 'd' : l->cup->rwx[0];
	l->cup->rwx[0] = (S_ISFIFO(l->cup->status.st_mode)) ? 'p' : l->cup->rwx[0];
	l->cup->rwx[0] = (S_ISCHR(l->cup->status.st_mode)) ? 'c' : l->cup->rwx[0];
	l->cup->rwx[0] = (S_ISBLK(l->cup->status.st_mode)) ? 'b' : l->cup->rwx[0];
	l->cup->rwx[0] = (S_ISSOCK(l->cup->status.st_mode)) ? 's' : l->cup->rwx[0];
	l->cup->rwx[0] = (S_ISLNK(l->cup->status.st_mode)) ? 'l' : l->cup->rwx[0];
	l->cup->rwx[1] = l->cup->status.st_mode & S_IRUSR ? 'r' : '-';
	l->cup->rwx[2] = l->cup->status.st_mode & S_IWUSR ? 'w' : '-';
	l->cup->rwx[3] = l->cup->status.st_mode & S_IXUSR ? 'x' : '-';
	l->cup->rwx[4] = l->cup->status.st_mode & S_IRGRP ? 'r' : '-';
	l->cup->rwx[5] = l->cup->status.st_mode & S_IWGRP ? 'w' : '-';
	l->cup->rwx[6] = l->cup->status.st_mode & S_IXGRP ? 'x' : '-';
	l->cup->rwx[7] = l->cup->status.st_mode & S_IROTH ? 'r' : '-';
	l->cup->rwx[8] = l->cup->status.st_mode & S_IWOTH ? 'w' : '-';
	l->cup->rwx[9] = l->cup->status.st_mode & S_IXOTH ? 'x' : '-';
	l->cup->u_inf = getpwuid(l->cup->status.st_uid);
	l->cup->g_inf = getgrgid(l->cup->status.st_gid);
	l->cup->time = ft_strsub(ctime(&l->cup->status.st_mtime), 4, 12);
	return (l);
}

int				ft_sort_check(t_dir *temp, t_dir *list, char *str)
{
	if (ft_strchr(str, 'S'))
	{
		if (temp->cup->status.st_size == list->cup->status.st_size)
			return (ft_default_sort(temp, list, str));
		if (ft_strchr(str, 'r'))
			return (temp->cup->status.st_size > list->cup->status.st_size);
		return (temp->cup->status.st_size < list->cup->status.st_size);
	}
	else if (ft_strchr(str, 't'))
	{
		if (temp->cup->status.st_mtime == list->cup->status.st_mtime)
			return (ft_default_sort(temp, list, str));
		if (ft_strchr(str, 'r'))
			return (temp->cup->status.st_mtime > list->cup->status.st_mtime);
		return (temp->cup->status.st_mtime < list->cup->status.st_mtime);
	}
	else
		return (ft_default_sort(temp, list, str));
}

t_dir			*ft_new_list(struct stat inf, char *dir_name, char *dir_path,
		char *main_path)
{
	t_dir	*list;

	if (!(list = (t_dir*)malloc(sizeof(t_dir))))
		ft_putstr("Failed to allocate memory.");
	if (!(list->cup = (t_info*)malloc(sizeof(t_info))))
		ft_putstr("Failed to allocate memory.");
	list->cup->dir_name = ft_strdup(dir_name);
	list->cup->status = inf;
	if (dir_path)
	{
		list->cup->dir_path = ft_strdup(dir_name);
		list = ft_get_perm(list);
	}
	else
		list->cup->dir_path = NULL;
	if (main_path)
		list->cup->main_path = ft_strdup(main_path);
	else
		list->cup->main_path = NULL;
	list->next = NULL;
	return (list);
}

int				ft_add_list(t_dir **head, t_dir *list, char *line)
{
	t_dir	*temp;

	if ((temp = *head) == NULL || ft_sort_check(temp, list, line) > 0)
	{
		*head = list;
		list->next = temp;
	}
	else
		while (temp)
		{
			if (temp->next == NULL)
			{
				temp->next = list;
				break ;
			}
			else if (ft_sort_check(temp->next, list, line) > 0)
			{
				list->next = temp->next;
				temp->next = list;
				break ;
			}
			temp = temp->next;
		}
	return (list->cup->status.st_blocks);
}
