/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthulo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 10:03:03 by tthulo            #+#    #+#             */
/*   Updated: 2018/09/17 12:40:20 by tthulo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		free_list(t_dir *head)
{
	t_dir	*hold;

	while (head)
	{
		hold = head->next;
		if (head->cup->dir_name)
			ft_strdel(&head->cup->dir_name);
		if (head->cup->dir_path)
			ft_strdel(&head->cup->dir_path);
		if (head->cup->main_path)
			ft_strdel(&head->cup->main_path);
		if (head->cup->time)
			ft_strdel(&head->cup->time);
		if (head->cup->rwx)
			ft_strdel(&head->cup->rwx);
		free(head->cup);
		free(head);
		head = NULL;
		head = hold;
	}
}
