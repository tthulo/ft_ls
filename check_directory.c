/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthulo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:52:00 by tthulo            #+#    #+#             */
/*   Updated: 2018/09/17 12:27:31 by tthulo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_print_error(t_dir *wrng)
{
	t_dir	*temp;

	temp = wrng;
	while (temp)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(temp->cup->dir_name);
		ft_putendl(": No such file or directory");
		temp = temp->next;
	}
	return ;
}

t_dir		*ft_check_dir(char **argv, char *lnk, int argc)
{
	struct stat	info;
	int			i;
	t_dir		*right;
	t_dir		*wrong;

	right = NULL;
	wrong = NULL;
	i = -1;
	while (argv[++i])
	{
		if (lstat(argv[i], &info) == -1)
			ft_add_list(&wrong, ft_new_list(info, argv[i], argv[i], NULL), lnk);
		else
			ft_add_list(&right, ft_new_list(info, argv[i], argv[i], NULL), lnk);
	}
	if (argc == 0)
	{
		if (lstat(".", &info) != -1)
			ft_add_list(&right, ft_new_list(info, ".", ".", NULL), lnk);
	}
	ft_print_error(ft_sort_lists(wrong));
	free(wrong);
	return (right);
}

int			ft_current_dir(t_dir *head)
{
	if (ft_strcmp(head->cup->dir_name, ".") == 0
		|| ft_strcmp(head->cup->dir_name, "..") == 0)
		return (1);
	return (0);
}

char		*ft_dir_path(char *dir_path, char *dir_name)
{
	char *new_path;
	char *temp;

	temp = ft_strjoin(dir_path, "/");
	new_path = ft_strjoin(temp, dir_name);
	ft_strdel(&temp);
	return (new_path);
}

t_dir		*ft_sort_lists(t_dir *head)
{
	t_dir		*d_temp;
	t_info		*i_temp;

	d_temp = head;
	while (d_temp && d_temp->next)
	{
		if (ft_strcmp(d_temp->cup->dir_name, d_temp->next->cup->dir_name) > 0)
		{
			i_temp = d_temp->next->cup;
			d_temp->next->cup = d_temp->cup;
			d_temp->cup = i_temp;
			d_temp = head;
		}
		else
			d_temp = d_temp->next;
	}
	return (head);
}
