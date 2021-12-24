/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 23:10:55 by hmoumani          #+#    #+#             */
/*   Updated: 2021/12/14 23:10:58 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	ft_check_zero(t_data *data, int i, int j)
{
	char	**mp;

	mp = data->map;
	if (i - 1 < 0 || j - 1 < 0 || i + 1 >= data->m_height \
	|| j + 1 >= data->m_width)
		fatal("map misconfigured");
	else if (mp[i - 1][j] == ' ' || mp[i + 1][j] == ' ')
		fatal("map misconfigured");
	else if (mp[i][j - 1] == ' ' || mp[i][j + 1] == ' ')
		fatal("map misconfigured");
}

void	ft_check_player(t_data *data, int i, int j)
{
	if (data->player_x != 0)
		fatal("player duplicated");
	ft_check_zero(data, i, j);
	data->player_x = i;
	data->player_y = j;
}

void    check_map(t_data *data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			c = data->map[i][j];
			if (c == '0')
				ft_check_zero(data, i, j);
			else if (c =='P')
				ft_check_player(data, i, j);
			else if (c == 'E')
			{
				ft_check_zero(data, i, j);
				data->found_exit = 1;
			}
			else if (c == 'C')
			{
				ft_check_zero(data, i, j);
				data->coll_found += 1;
			}
			else if (c == '1')
				i += 0;
			else
				fatal("Invalid character in map");
			j++;
		}
		i++;
	}
	if (data->player_x == 0)
		fatal("404 Player not found");
	if (data->found_exit == 0)
		fatal("No exit found");
	if (data->coll_found == 0)
		fatal("No collectible found");
}

void    array_map(t_data *data)
{
	int count;
	int len;
	int i;
	t_list *tmp;

	count = ft_lstsize(data->lines);
	i = 0;
	tmp = data->lines;
	data->map = ft_malloc((count + 1) * sizeof(char *));
	len = -1;
	while (i < count)
	{
		if (len != -1 && len != ft_strlen(tmp->content))
			fatal("lenght of lines should be the same");
		data->map[i] = tmp->content;
		len = ft_strlen(tmp->content);
		tmp = tmp->next;
		i++;
	}
	data->m_width = len;
	data->m_height = count;
	data->map[i] = NULL;
	check_map(data);
}

void    fill_map(t_data *data, char const * const filename)
{
	int fd;
	int ret;
	char *line;

	line = NULL;
	ret = 1;
	fd = open(filename, O_RDONLY);
	while (ret > 0)
	{
		ret = get_next_line(&line, fd);
		if (ret < 0)
			break ;
		ft_lstadd_back(&data->lines, ft_lstnew(line));
	}
	array_map(data);
	data->num_fire = data->m_height - 2;
	data->fires = ft_malloc(data->num_fire * sizeof(int));
	int i = 0;
	while (i < data->num_fire)
		if (i % 2 == 0)
			data->fires[i++] = -1;
	else
		data->fires[i++] = -4;
			
}

int			get_color_window(int i, int j, t_texture *from)
{
	int y = j * from->width / WIN_WIDTH;
	int x = i * from->height / WIN_HEIGHT;
	if (from->width * from->height < x * from->width + y)
		return (0xeaf);
	return ((unsigned int *)from->addr)[x * from->width + y];
}

void    draw_background(t_data *data, t_texture *bg)
{
	int i;
	int j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			put_my_pixel(data, i , j, get_color_window(i, j, bg));
			++j;
		}
		++i;
	}
}

void    ft_draw_map(t_data *data)
{
	int i;
	int j;

	i = 0;
	draw_background(data, &data->bg);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				ft_rect(data, i, j, &data->brick);
			else if (data->map[i][j] == 'P')
				ft_rect(data, i, j, data->player);
			else if (data->map[i][j] == 'C')
				ft_rect(data, i, j, data->coin);
			else if (data->map[i][j] == 'E')
				ft_rect(data, i, j, &data->castle);
			j++;
		}
		i++;
	}
}

void    ft_render(t_data *data)
{
	clear_buffer(data);
	ft_draw_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

long	get_time_stamp(void)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	return (timev.tv_sec * (long)1000000 + timev.tv_usec);
}

void    init(t_data *data)
{
	t_texture txt;

	txt = (t_texture){0, 0, 0, 0, 0, 0, 0};
	*data = (t_data){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "so_long");
	data->image = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->mlx_data = mlx_get_data_addr(data->image, &data->bpp, &data->line_length, &data->endian);
	data->bg.img = mlx_xpm_file_to_image(data->mlx, "images/background.xpm", &data->bg.width, &data->bg.height);
	data->brick.img = mlx_xpm_file_to_image(data->mlx, "images/brick.xpm", &data->brick.width, &data->brick.height);
	data->m1.img = mlx_xpm_file_to_image(data->mlx, "images/mario1.xpm", &data->m1.width, &data->m1.height);
	data->u1.img = mlx_xpm_file_to_image(data->mlx, "images/up/1.xpm", &data->u1.width, &data->u1.height);
	data->u2.img = mlx_xpm_file_to_image(data->mlx, "images/up/2.xpm", &data->u2.width, &data->u2.height);
	data->d1.img = mlx_xpm_file_to_image(data->mlx, "images/down/1.xpm", &data->d1.width, &data->d1.height);
	data->d2.img = mlx_xpm_file_to_image(data->mlx, "images/down/2.xpm", &data->d2.width, &data->d2.height);
	data->r1.img = mlx_xpm_file_to_image(data->mlx, "images/right/1.xpm", &data->r1.width, &data->r1.height);
	data->r2.img = mlx_xpm_file_to_image(data->mlx, "images/right/2.xpm", &data->r2.width, &data->r2.height);
	data->l1.img = mlx_xpm_file_to_image(data->mlx, "images/left/1.xpm", &data->l1.width, &data->l1.height);
	data->l2.img = mlx_xpm_file_to_image(data->mlx, "images/left/2.xpm", &data->l2.width, &data->l2.height);
	data->c1.img = mlx_xpm_file_to_image(data->mlx, "images/coin/1.xpm", &data->c1.width, &data->c1.height);
	data->c2.img = mlx_xpm_file_to_image(data->mlx, "images/coin/2.xpm", &data->c2.width, &data->c2.height);
	data->c3.img = mlx_xpm_file_to_image(data->mlx, "images/coin/3.xpm", &data->c3.width, &data->c3.height);
	data->c4.img = mlx_xpm_file_to_image(data->mlx, "images/coin/4.xpm", &data->c4.width, &data->c4.height);
	data->c5.img = mlx_xpm_file_to_image(data->mlx, "images/coin/5.xpm", &data->c5.width, &data->c5.height);
	data->c6.img = mlx_xpm_file_to_image(data->mlx, "images/coin/6.xpm", &data->c6.width, &data->c6.height);
	data->f1.img = mlx_xpm_file_to_image(data->mlx, "images/fire/1.xpm", &data->f1.width, &data->f1.height);
	data->f2.img = mlx_xpm_file_to_image(data->mlx, "images/fire/2.xpm", &data->f2.width, &data->f2.height);
	data->f3.img = mlx_xpm_file_to_image(data->mlx, "images/fire/3.xpm", &data->f3.width, &data->f3.height);
	data->castle.img = mlx_xpm_file_to_image(data->mlx, "images/castle/2.xpm", &data->castle.width, &data->castle.height);
	data->img_win.img = mlx_xpm_file_to_image(data->mlx, "images/win.xpm", &data->img_win.width, &data->img_win.height);
	data->img_over.img = mlx_xpm_file_to_image(data->mlx, "images/over.xpm", &data->img_over.width, &data->img_over.height);
	if (!data->bg.img || !data->brick.img || !data->m1.img || !data->u1.img || !data->u2.img || !data->d1.img || !data->img_win.img || !data->img_over.img || !data->d2.img || !data->r1.img || !data->r2.img || !data->l1.img || !data->l2.img || !data->c1.img || !data->c2.img || !data->c3.img || !data->c4.img || !data->c5.img || !data->c6.img || !data->f1.img || !data->f2.img || !data->f3.img)
		fatal("images files should be in images/ folder");
	data->bg.addr = mlx_get_data_addr(data->bg.img, &data->bg.bpp, &data->bg.line_length, &data->bg.endian);
	data->brick.addr = mlx_get_data_addr(data->brick.img, &data->brick.bpp, &data->brick.line_length, &data->brick.endian);
	data->m1.addr = mlx_get_data_addr(data->m1.img, &data->m1.bpp, &data->m1.line_length, &data->m1.endian);
	data->u1.addr = mlx_get_data_addr(data->u1.img, &data->u1.bpp, &data->u1.line_length, &data->u1.endian);
	data->u2.addr = mlx_get_data_addr(data->u2.img, &data->u2.bpp, &data->u2.line_length, &data->u2.endian);
	data->d1.addr = mlx_get_data_addr(data->d1.img, &data->d1.bpp, &data->d1.line_length, &data->d1.endian);
	data->d2.addr = mlx_get_data_addr(data->d2.img, &data->d2.bpp, &data->d2.line_length, &data->d2.endian);
	data->l1.addr = mlx_get_data_addr(data->l1.img, &data->l1.bpp, &data->l1.line_length, &data->l1.endian);
	data->l2.addr = mlx_get_data_addr(data->l2.img, &data->l2.bpp, &data->l2.line_length, &data->l2.endian);
	data->r1.addr = mlx_get_data_addr(data->r1.img, &data->r1.bpp, &data->r1.line_length, &data->r1.endian);
	data->r2.addr = mlx_get_data_addr(data->r2.img, &data->r2.bpp, &data->r2.line_length, &data->r2.endian);
	data->c1.addr = mlx_get_data_addr(data->c1.img, &data->c1.bpp, &data->c1.line_length, &data->c1.endian);
	data->c2.addr = mlx_get_data_addr(data->c2.img, &data->c2.bpp, &data->c2.line_length, &data->c2.endian);
	data->c3.addr = mlx_get_data_addr(data->c3.img, &data->c3.bpp, &data->c3.line_length, &data->c3.endian);
	data->c4.addr = mlx_get_data_addr(data->c4.img, &data->c4.bpp, &data->c4.line_length, &data->c4.endian);
	data->c5.addr = mlx_get_data_addr(data->c5.img, &data->c5.bpp, &data->c5.line_length, &data->c5.endian);
	data->c6.addr = mlx_get_data_addr(data->c6.img, &data->c6.bpp, &data->c6.line_length, &data->c6.endian);
	data->f1.addr = mlx_get_data_addr(data->f1.img, &data->f1.bpp, &data->f1.line_length, &data->f1.endian);
	data->f2.addr = mlx_get_data_addr(data->f2.img, &data->f2.bpp, &data->f2.line_length, &data->f2.endian);
	data->f3.addr = mlx_get_data_addr(data->f3.img, &data->f3.bpp, &data->f3.line_length, &data->f3.endian);
	data->castle.addr = mlx_get_data_addr(data->castle.img, &data->castle.bpp, &data->castle.line_length, &data->castle.endian);
	data->img_win.addr = mlx_get_data_addr(data->img_win.img, &data->img_win.bpp, &data->img_win.line_length, &data->img_win.endian);
	data->img_over.addr = mlx_get_data_addr(data->img_over.img, &data->img_over.bpp, &data->img_over.line_length, &data->img_over.endian);
	data->player = &data->m1;
	data->coin = &data->c1;
	data->fire = &data->f1;
	data->time = get_time_stamp();
	data->time_fire = data->time;
	data->time_gen_fire = data->time_fire;
}

void    ft_left(t_data *data)
{
	static int pos = 0;
	if (data->player_y - 1 > 0 && data->map[data->player_x][data->player_y - 1] != '1' && (data->map[data->player_x][data->player_y - 1] != 'E' || data->coll_found == 0))
	{
		if (data->map[data->player_x][data->player_y - 1] == 'C')
			data->coll_found--;
		if (data->map[data->player_x][data->player_y - 1] == 'E' && data->coll_found == 0)
			data->is_win = TRUE;
		data->map[data->player_x][data->player_y] = '0';
		data->map[data->player_x][--data->player_y] = 'P';
		data->movements++;
		print_mov_count(data);
	}
	if (pos)
		data->player = &data->l1;
	else
		data->player = &data->l2;

	pos = !pos;
}

void    ft_right(t_data *data)
{
	static int pos = 0;
	if (data->player_y + 1 < data->m_width && data->map[data->player_x][data->player_y + 1] != '1' && (data->map[data->player_x][data->player_y + 1] != 'E' || data->coll_found == 0))
	{
		if (data->map[data->player_x][data->player_y + 1] == 'C')
			data->coll_found--;
		if (data->map[data->player_x][data->player_y + 1] == 'E' && data->coll_found == 0)
			data->is_win = TRUE;
		data->map[data->player_x][data->player_y] = '0';
		data->map[data->player_x][++data->player_y] = 'P';
		data->movements++;
		print_mov_count(data);
	}
	if (pos)
		data->player = &data->r1;
	else
		data->player = &data->r2;

	pos = !pos;
}

void    ft_up(t_data *data)
{
	static int pos = 0;
	if (data->player_x - 1 > 0 && data->map[data->player_x - 1][data->player_y] != '1' && (data->map[data->player_x - 1][data->player_y] != 'E' || data->coll_found == 0))
	{
		if (data->map[data->player_x - 1][data->player_y] == 'C')
			data->coll_found--;
		if (data->map[data->player_x - 1][data->player_y] == 'E' && data->coll_found == 0)
			data->is_win = TRUE;
		data->map[data->player_x][data->player_y] = '0';
		data->map[--data->player_x][data->player_y] = 'P';
		data->movements++;
		print_mov_count(data);
	}
	if (pos)
		data->player = &data->u1;
	else
		data->player = &data->u2;

	pos = !pos;
}

void    ft_down(t_data *data)
{
	static int pos = 0;
	if (data->player_x + 1 < data->m_width && data->map[data->player_x + 1][data->player_y] != '1' && (data->map[data->player_x + 1][data->player_y] != 'E' || data->coll_found == 0))
	{
		if (data->map[data->player_x + 1][data->player_y] == 'C')
			data->coll_found--;
		if (data->map[data->player_x + 1][data->player_y] == 'E' && data->coll_found == 0)
			data->is_win = TRUE;
		data->map[data->player_x][data->player_y] = '0';
		data->map[++data->player_x][data->player_y] = 'P';
		data->movements++;
		print_mov_count(data);
	}
	if (pos)
		data->player = &data->d1;
	else
		data->player = &data->d2;

	pos = !pos;
}

int     ft_exit(void)
{
	exit(0);
}

void    ft_win(t_data *data)
{
	clear_buffer(data);
	draw_background(data, &data->img_win);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	print_mov_count_screen(data);
}

void    ft_loss(t_data *data)
{
	data->is_win = -1;
	clear_buffer(data);
	draw_background(data, &data->img_over);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	// print_mov_count(data);
	print_mov_count_screen(data);

}

void    check_death(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_fire)
	{
		if (i == data->player_x - 1 && data->fires[i] == data->player_y)
			ft_loss(data);
		++i;
	}
}

int		key_press(int key, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (key == 53)
		ft_exit();
	if (data->is_win){
		// print_mov_count(data);
		print_mov_count_screen(data);
		return (0);
	}
	if (key == 1)
		ft_down(data);
	else if (key == 13)
		ft_up(data);
	else if (key == 0)
		ft_left(data);
	else if (key == 2)
		ft_right(data);
	check_death(data);
	if (data->is_win){
		if (data->is_win == -1)
			return (0);
		ft_win(data);
		return 0;
	}
	ft_render(data);
	render_fire(data);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;

	init(&data);
	if (argc != 2)
		fatal("Arguments");
	fill_map(&data, argv[1]);
	mlx_hook(data.win, 2, 1L << 0, key_press, (void *)&data);
	mlx_hook(data.win, 17, 1L << 17, ft_exit, (void *)0);
	ft_render(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
	mlx_loop_hook(data.mlx, loop, &data);

	mlx_loop(data.mlx);
}
