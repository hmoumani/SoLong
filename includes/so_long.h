/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 23:18:49 by hmoumani          #+#    #+#             */
/*   Updated: 2021/12/14 23:18:51 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <math.h>
# include <limits.h>
# include <errno.h>
# include "get_next_line.h"
# define FALSE 0
# define TRUE 1
# define ERROR "Error\n"
# define WIN_WIDTH 2600
# define WIN_HEIGHT 1200

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*image;
	char			*mlx_data;
	t_list			*lines;
	char			**map;
	int				m_width;
	int				m_height;
	int				player_x;
	int				player_y;
	int				found_exit;
	int				coll_found;
	int				bpp;
	int				line_length;
	int				endian;
}					t_data;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **alst, t_list *new);
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);
int					ft_strlen(char *s);
void				ft_square(t_data *data, int x, int y, int color);
void				clear_buffer(t_data *data);
#endif
