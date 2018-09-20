/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthulo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 07:49:50 by tthulo            #+#    #+#             */
/*   Updated: 2018/09/16 09:12:59 by tthulo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_default_sort(t_dir *temp, t_dir *list, char *str)
{
	if (ft_strchr(str, 'r'))
		return (ft_strcmp(temp->cup->dir_name, list->cup->dir_name) < 0);
	return (ft_strcmp(temp->cup->dir_name, list->cup->dir_name) > 0);
}
