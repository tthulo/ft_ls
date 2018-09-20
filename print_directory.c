/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthulo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 13:19:54 by tthulo            #+#    #+#             */
/*   Updated: 2018/09/20 15:53:38 by tthulo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_add_error(t_dir **head, t_dir *list)
{
	t_dir	*temp;

	if ((temp = *head) == NULL)
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
			temp = temp->next;
		}
}

void		ft_corr_print(t_dir *head, char *line, int total)
{
	static int	first;
	t_dir		*temp2;

	temp2 = head;
	first = 0;
	if (ft_strcmp(head->cup->main_path, ".") && ft_strchr(line, 'R'))
	{
		write(1, "\n./", 3);
		ft_putstr(head->cup->main_path);
		write(1, ":\n", 2);
	}
	if (ft_strchr(line, 'l') && temp2->next->next != NULL)
	{
		ft_putstr("total ");
		ft_putendl(ft_itoa(total));
	}
	ft_b(head, temp2, line);
	first = 1;
}

void		ft_loop_dir(t_dir *head, char *line)
{
	t_dir	*temp;

	temp = head;
	while (temp)
	{
		if (S_ISDIR(temp->cup->status.st_mode) && !ft_current_dir(temp))
		{
			if (ft_strchr(line, 'a') || temp->cup->dir_name[0] != '.')
				ft_dir_print(temp, line, 0);
		}
		temp = temp->next;
	}
}

void		ft_dir_print(t_dir *head, char *l, int t)
{
	t_dir			*corr;
	t_dir			*incor;

	corr = NULL;
	incor = NULL;
	if ((head->cup->dir_inf = opendir(head->cup->dir_path)) == NULL)
	{
		write(1, "\n", 1);
		ft_putstr(head->cup->dir_path);
		ft_putendl(":\nft_ls: Permission denied");
	}
	t = ft_go_th(head, l, &corr, &incor);
	corr == NULL ? 0 : ft_corr_print(corr, l, t);
	incor == NULL ? 0 : ft_print_error(incor);
	if (ft_strchr(l, 'R') && corr != NULL)
		ft_loop_dir(corr, l);
	free(incor);
	free_list(corr);
}

void		ft_print_cor(t_dir *head, char *line)
{
	t_dir		*temp;
	t_pad		*cup;

	temp = head;
	cup = (t_pad *)malloc(sizeof(t_pad));
	while (temp)
	{
		if (S_ISDIR(temp->cup->status.st_mode))
			ft_dir_print(temp, line, 0);
		else
		{
			cup->size = ft_b_size(head, line);
			cup->user = ft_b_user(head, line);
			cup->group = ft_b_group(head, line);
			cup->link = ft_b_link(head, line);
			ft_print_d(temp, line, cup);
		}
		temp = temp->next;
	}
	free(cup);
}
