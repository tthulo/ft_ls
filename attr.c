/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthulo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 11:24:49 by tthulo            #+#    #+#             */
/*   Updated: 2018/09/16 09:09:57 by tthulo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_b_size(t_dir *head, char *line)
{
	t_dir		*temp;
	int			n;
	int			len;

	n = 0;
	temp = head;
	while (temp)
	{
		if (ft_strchr(line, 'a') || temp->cup->dir_name[0] != '.')
			if ((len = ft_int_len(temp->cup->status.st_size)) > n)
				n = len;
		temp = temp->next;
	}
	return (n);
}

int		ft_b_user(t_dir *head, char *line)
{
	t_dir		*temp;
	int			n;
	int			len;

	n = 0;
	temp = head;
	while (temp)
	{
		if (ft_strchr(line, 'a') || temp->cup->dir_name[0] != '.')
			if ((len = (int)ft_strlen(temp->cup->u_inf->pw_name)) > n)
				n = len;
		temp = temp->next;
	}
	return (n);
}

int		ft_b_group(t_dir *head, char *line)
{
	t_dir		*temp;
	int			n;
	int			len;

	n = 0;
	temp = head;
	while (temp)
	{
		if (ft_strchr(line, 'a') || temp->cup->dir_name[0] != '.')
			if ((len = (int)ft_strlen(temp->cup->g_inf->gr_name)) > n)
				n = len;
		temp = temp->next;
	}
	return (n);
}

int		ft_b_link(t_dir *head, char *line)
{
	t_dir		*temp;
	int			n;
	int			len;

	n = 0;
	temp = head;
	while (temp)
	{
		if (ft_strchr(line, 'a') || temp->cup->dir_name[0] != '.')
			if ((len = ft_int_len(temp->cup->status.st_nlink)) > n)
				n = len;
		temp = temp->next;
	}
	return (n);
}

void	ft_b(t_dir *head, t_dir *temp2, char *line)
{
	t_pad *temp;

	temp = (t_pad *)malloc(sizeof(t_pad));
	temp->size = ft_b_size(head, line);
	temp->user = ft_b_user(head, line);
	temp->group = ft_b_group(head, line);
	temp->link = ft_b_link(head, line);
	while (temp2)
	{
		if ((ft_strchr(line, 'a') && temp2->cup->dir_name[0] == '.') ||
				temp2->cup->dir_name[0] != '.')
			ft_print_d(temp2, line, temp);
		temp2 = temp2->next;
	}
	free(temp);
}
