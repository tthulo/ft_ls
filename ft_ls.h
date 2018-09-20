/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthulo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 08:41:13 by tthulo            #+#    #+#             */
/*   Updated: 2018/09/17 12:31:20 by tthulo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <string.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/dir.h>
# include "libft/libft.h"
# define FLAGS "alrRSt"

typedef struct			s_pad
{
	int					size;
	int					user;
	int					group;
	int					link;
}						t_pad;

typedef struct			s_info
{
	char				*dir_name;
	char				*dir_path;
	char				*main_path;
	char				*time;
	char				*rwx;
	DIR					*dir_inf;
	struct stat			status;
	struct passwd		*u_inf;
	struct group		*g_inf;
}						t_info;

typedef struct			s_dir
{
	t_info				*cup;
	struct s_dir		*next;
}						t_dir;

typedef	struct			s_head
{
	char				*line;
	t_dir				*l_head;
}						t_head;

char					*ft_options(char *argv, char *s, int i);
char					*ft_dir_path(char *dir_path, char *dir_name);
int						ft_b_size(t_dir *head, char *line);
int						ft_b_group(t_dir *head, char *line);
int						ft_b_link(t_dir *head, char *line);
int						ft_b_user(t_dir *head, char *line);
int						ft_check_flags(char **line, char **argv);
int						ft_current_dir(t_dir *head);
int						ft_default_sort(t_dir *temp, t_dir *list,
		char *str);
int						ft_go_th(t_dir *head, char *l, t_dir **c,
		t_dir **i);
int						ft_int_len(int n);
int						ft_add_list(t_dir **head, t_dir *list, char
		*line);
t_dir					*ft_check_dir(char **argv, char *lnk, int argc);
t_dir					*ft_new_list(struct stat inf, char *dir_name, char
		*dir_path, char *main_path);
t_dir					*ft_sort_lists(t_dir *head);
t_head					*ft_init_inf(t_head *bowl);
void					ft_add_error(t_dir **head, t_dir *list);
void					ft_b(t_dir *head, t_dir *temp2, char *line);
void					ft_dir_print(t_dir *head, char *line, int total);
void					ft_print_error(t_dir *wrng);
void					free_list(t_dir *head);
void					ft_print_cor(t_dir *head, char *line);
void					ft_print_d(t_dir *head, char *line, t_pad *cup);
void					ft_print_lng(t_dir *head, t_pad *cup);
void					ft_time_print(t_dir *head);

#endif
