/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthulo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 09:29:54 by tthulo            #+#    #+#             */
/*   Updated: 2018/09/20 15:55:50 by tthulo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_go_th(t_dir *head, char *l, t_dir **c, t_dir **i)
{
	int				total;
	char			*p;
	struct dirent	*dir;
	struct stat		inf;

	total = 0;
	while (head->cup->dir_inf != NULL && (dir = readdir(head->cup->dir_inf))
			!= NULL)
	{
		p = ft_dir_path(head->cup->dir_path, dir->d_name);
		if (lstat(p, &inf) == -1)
			ft_add_error(i, ft_new_list(inf, dir->d_name, p,
						head->cup->dir_path));
		else
			total += ft_add_list(c, ft_new_list(inf, dir->d_name, p,
						head->cup->dir_path), l);
	}
	free(p);
	return (total);
}

t_head		*init(t_head *cup)
{
	cup->line = ft_strnew(7);
	cup->l_head = NULL;
	return (cup);
}

int			main(int ac, char **av)
{
	int		i;
	t_head	*cup;

	cup = (t_head *)malloc(sizeof(t_head));
	cup = init(cup);
	i = ft_check_flags(&cup->line, av);
	cup->l_head = ft_check_dir(&av[i], cup->line, ac - i);
	ft_print_cor(cup->l_head, cup->line);
	free(cup->line);
	free_list(cup->l_head);
	free(cup);
	return (0);
}
