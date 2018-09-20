/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthulo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 10:20:37 by tthulo            #+#    #+#             */
/*   Updated: 2018/09/16 09:07:00 by tthulo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_int_len(int n)
{
	int len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void		ft_pad(int n, char *s, int long_name)
{
	int len;

	len = n == 0 ? 1 : 0;
	if (s == NULL)
	{
		while (n)
		{
			n = n / 10;
			len++;
		}
	}
	else
		len = (int)ft_strlen(s);
	while (len < long_name)
	{
		ft_putchar(' ');
		len++;
	}
}

void		ft_print_time(t_dir *head)
{
	char	**temp;
	int		n;

	n = -1;
	temp = NULL;
	if ((time(NULL) - (head->cup->status.st_mtime)) > 15548400 ||
			(head->cup->status.st_mtime) > (time(NULL)))
	{
		temp = ft_strsplit(ctime(&head->cup->status.st_mtime), ' ');
		ft_putstr(temp[1]);
		write(1, "  ", 2);
		ft_putstr(temp[2]);
		write(1, "  ", 2);
		ft_putstr(ft_strtrim(temp[4]));
		write(1, " ", 1);
		while (temp[++n] != NULL)
			ft_strdel(&temp[n]);
		free(temp);
	}
	else
	{
		ft_putstr(head->cup->time);
		write(1, " ", 1);
	}
}

void		ft_print_long(t_dir *head, t_pad *cup)
{
	ft_putstr(head->cup->rwx);
	write(1, "  ", 2);
	ft_pad(head->cup->status.st_nlink, NULL, cup->link);
	ft_putstr(ft_itoa(head->cup->status.st_nlink));
	write(1, "  ", 2);
	ft_pad(0, head->cup->u_inf->pw_name, cup->user);
	ft_putstr(head->cup->u_inf->pw_name);
	write(1, "  ", 2);
	ft_pad(0, head->cup->g_inf->gr_name, cup->group);
	ft_putstr(head->cup->g_inf->gr_name);
	write(1, "  ", 2);
	ft_pad(head->cup->status.st_size, NULL, cup->size);
	ft_putstr(ft_itoa(head->cup->status.st_size));
	write(1, " ", 1);
	ft_print_time(head);
}

void		ft_print_d(t_dir *head, char *line, t_pad *cup)
{
	char *link;

	if (ft_strchr(line, 'l'))
		ft_print_long(head, cup);
	ft_putstr(head->cup->dir_name);
	if (ft_strchr(line, 'l') && S_ISLNK(head->cup->status.st_mode))
	{
		link = ft_strnew(255);
		readlink(head->cup->dir_path, link, 255);
		ft_putstr(" -> ");
		ft_putstr(link);
		ft_strdel(&link);
	}
	write(1, "\n", 1);
}
