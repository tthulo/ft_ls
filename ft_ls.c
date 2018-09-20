/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthulo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 09:07:35 by tthulo            #+#    #+#             */
/*   Updated: 2018/09/17 12:35:01 by tthulo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_options(char *argv, char *s, int i)
{
	s[0] = '-';
	while (argv[++i])
	{
		if (!(ft_strchr(FLAGS, argv[i])))
		{
			ft_putstr("ft_ls: invalid option -- ");
			ft_putchar(argv[i]);
			ft_putstr(FLAGS);
			exit(0);
		}
		else
			s[i] = argv[i];
	}
	s[i] = '\0';
	return (s);
}

int			ft_check_flags(char **line, char **argv)
{
	int		i;
	int		j;
	char	*temp;
	char	str[7];

	i = 0;
	j = 0;
	temp = ft_strnew(10);
	while (argv[++i] && (argv[i][0] == '-'))
	{
		if (argv[i][0] != '-')
			break ;
		temp = ft_options(argv[i], temp, 0);
		while (*temp != '\0')
		{
			if (!(ft_strchr(str, *temp)))
				str[j++] = *temp;
			temp++;
		}
	}
	str[j] = 0;
	*line = ft_strdup(str);
	temp = NULL;
	ft_strdel(&temp);
	return (i);
}
