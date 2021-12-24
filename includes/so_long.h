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
# include <sys/time.h>
# include "get_next_line.h"
# define FALSE 0
# define TRUE 1
# define ERROR "Error\n"
# define WIN_WIDTH 2100
# define WIN_HEIGHT 800

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				height;
	int				width;
	int				bpp;
	int				ln_len;
	int				endian;
}					t_texture;

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
	int				ln_len;
	int				endian;
	int				width;
	int				heigth;
	t_texture		bg;
	t_texture		brick;
	t_texture		m1;
	t_texture		u1;
	t_texture		u2;
	t_texture		d1;
	t_texture		d2;
	t_texture		r1;
	t_texture		r2;
	t_texture		l1;
	t_texture		l2;
	t_texture		c1;
	t_texture		c2;
	t_texture		c3;
	t_texture		c4;
	t_texture		c5;
	t_texture		c6;
	t_texture		castle;
	t_texture		img_win;
	t_texture		img_over;
	t_texture		f1;
	t_texture		f2;
	t_texture		f3;
	t_texture		*player;
	t_texture		*from;
	t_texture		*coin;
	t_texture		*fire;
	long			time;
	long			time_fire;
	long			time_gen_fire;
	int				movements;
	int				is_win;
	int				num_fire;
	int				*fires;
}					t_data;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **alst, t_list *new);
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);
int					ft_strlen(char *s);
void				ft_rect(t_data *data, int x, int y, t_texture *from);
void				clear_buffer(t_data *data);
int					get_color(t_data *data, int i, int j, t_texture *from);
void				put_my_pixel(t_data *data, int x, int y, int color);
char				*ft_itoa(int n);
void				print_mov_count(t_data *data);
int					print_mov_count_screen(t_data *data);
void				*ft_memset(void *s, int c, size_t n);
int					loop(t_data *data);
void				ft_render(t_data *data);
long				get_time_stamp(void);
void				render_fire(t_data *data);
void				check_death(t_data *data);
void				draw_fire(t_data *data);
void				generate_fire(t_data *data);
void				init(t_data *data);
void				array_map(t_data *data);
void				draw_background(t_data *data, t_texture *bg);
void				ft_draw_map(t_data *data);
void				fill_map(t_data *data, char const *const filename);
void				ft_left(t_data *data);
void				ft_right(t_data *data);
void				ft_up(t_data *data);
void				ft_down(t_data *data);
int					ft_exit(void);
void				*xpm(void *mlx_ptr, char *file, int *width, int *height);
void				*mlx_data(void *img_ptr, int *pp, int *size, int *endian);
int					ft_is_end_with(char *s, char *s1);
#endif
