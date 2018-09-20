/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthulo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 23:18:58 by tthulo            #+#    #+#             */
/*   Updated: 2018/08/17 23:19:05 by tthulo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char *memdup;

	if (!(memdup = ft_strnew(n)))
		return (NULL);
	ft_strncpy(memdup, s1, n);
	return (memdup);
}
