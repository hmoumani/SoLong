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
}

int			get_color_window(int i, int j, t_texture *from)
{
	int y = j * from->width / WIN_WIDTH;
	int x = i * from->height / WIN_HEIGHT;
	if (from->width * from->height < x * from->width + y)
		return (0xeaf);
    return ((unsigned int *)from->addr)[x * from->width + y];
}

void    draw_background(t_data *data)
{
    int i;
    int j;

    i = 0;
    // printf("hello from there\n");
    while (i < WIN_HEIGHT)
    {
        j = 0;
        while (j < WIN_WIDTH)
        {
            put_my_pixel(data, i , j, get_color_window(i, j, &data->bg));
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
    draw_background(data);
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (data->map[i][j] == '1')
                ft_rect(data, i, j, &data->brick);
            else if (data->map[i][j] == 'P')
                ft_rect(data, i, j, data->from);
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
    // print_mov_count(data);
    // ft_draw_player(data);
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
    *data = (t_data){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, 0, 0, 0, 0};
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
    data->castle.img = mlx_xpm_file_to_image(data->mlx, "images/castle/2.xpm", &data->castle.width, &data->castle.height);
    if (!data->bg.img || !data->brick.img || !data->m1.img || !data->u1.img || !data->u2.img || !data->d1.img || !data->d2.img || !data->r1.img || !data->r2.img || !data->l1.img || !data->l2.img || !data->c1.img || !data->c2.img || !data->c3.img || !data->c4.img || !data->c5.img || !data->c6.img)
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
    data->castle.addr = mlx_get_data_addr(data->castle.img, &data->castle.bpp, &data->castle.line_length, &data->castle.endian);
    data->from = &data->m1;
    data->coin = &data->c1;
    data->time = get_time_stamp();
}

void    ft_left(t_data *data)
{
    static int pos = 0;
    // printf("%d * %d * %c\n", data->player_x, data->player_y, data->map[data->player_x][data->player_y + 1]);
    if (data->player_y - 1 > 0 && data->map[data->player_x][data->player_y - 1] != '1' && (data->map[data->player_x][data->player_y - 1] != 'E' || data->coll_found == 0))
    {
        if (data->map[data->player_x][data->player_y - 1] == 'C')
            data->coll_found--;
        data->map[data->player_x][data->player_y] = '0';
        data->map[data->player_x][--data->player_y] = 'P';
        data->movements++;
        print_mov_count(data);
    }
    if (pos)
        data->from = &data->l1;
    else
        data->from = &data->l2;

    pos = !pos;
}

void    ft_right(t_data *data)
{
    static int pos = 0;
    // printf("%d * %d * %c\n", data->player_x, data->player_y, data->map[data->player_x][data->player_y + 1]);
    if (data->player_y + 1 < data->m_width && data->map[data->player_x][data->player_y + 1] != '1' && (data->map[data->player_x][data->player_y + 1] != 'E' || data->coll_found == 0))
    {
        if (data->map[data->player_x][data->player_y + 1] == 'C')
            data->coll_found--;
        data->map[data->player_x][data->player_y] = '0';
        data->map[data->player_x][++data->player_y] = 'P';
        data->movements++;
        print_mov_count(data);
    }
    if (pos)
        data->from = &data->r1;
    else
        data->from = &data->r2;

    pos = !pos;
}

void    ft_up(t_data *data)
{
    static int pos = 0;
    // printf("%d * %d * %c\n", data->player_x, data->player_y, data->map[data->player_x][data->player_y + 1]);
    if (data->player_x - 1 > 0 && data->map[data->player_x - 1][data->player_y] != '1' && (data->map[data->player_x - 1][data->player_y] != 'E' || data->coll_found == 0))
    {
        if (data->map[data->player_x - 1][data->player_y] == 'C')
            data->coll_found--;
        // data->player_x++;
        data->map[data->player_x][data->player_y] = '0';
        data->map[--data->player_x][data->player_y] = 'P';
        data->movements++;
        print_mov_count(data);
    }
    if (pos)
        data->from = &data->u1;
    else
        data->from = &data->u2;

    pos = !pos;
}

void    ft_down(t_data *data)
{
    static int pos = 0;
    // printf("%d * %d * %c\n", data->player_x, data->player_y, data->map[data->player_x][data->player_y + 1]);
    if (data->player_x + 1 < data->m_width && data->map[data->player_x + 1][data->player_y] != '1' && (data->map[data->player_x + 1][data->player_y] != 'E' || data->coll_found == 0))
    {
        if (data->map[data->player_x + 1][data->player_y] == 'C')
            data->coll_found--;
        // data->player_x++;
        data->map[data->player_x][data->player_y] = '0';
        data->map[++data->player_x][data->player_y] = 'P';
        data->movements++;
        print_mov_count(data);
    }
    if (pos)
        data->from = &data->d1;
    else
        data->from = &data->d2;

    pos = !pos;
}

int     ft_exit(void)
{
    exit(0);
}

int		key_press(int key, void *param)
{
    t_data *data;

    data = (t_data *)param;
    // (void)key;
	if (key == 53)
		ft_exit();
	else if (key == 1)
		ft_down(data);
	else if (key == 13)
		ft_up(data);
	else if (key == 0)
		ft_left(data);
	else if (key == 2)
		ft_right(data);
	ft_render(data);
	return (0);
}
#define MLX_SYNC_IMAGE_WRITABLE    1 
#define MLX_SYNC_WIN_FLUSH_CMD     2
#define MLX_SYNC_WIN_CMD_COMPLETED 3
int    mlx_sync(int cmd, void *ptr);

int loop(t_data *data)
{
    static int coin_index = 0;
    if (get_time_stamp() - data->time > 170000){
        if (coin_index == 0)
            data->coin = &data->c1;
        else if (coin_index == 1)
            data->coin = &data->c2;
        else if (coin_index == 2)
            data->coin = &data->c3;
        else if (coin_index == 3)
            data->coin = &data->c4;
        else if (coin_index == 4)
            data->coin = &data->c5;
        else if (coin_index == 5)
            data->coin = &data->c6;
        data->time = get_time_stamp();
        coin_index++;
        coin_index %= 6;
        ft_render(data);
        print_mov_count_screen(data);
        // printf("hrweihfglwgn %ld * %ld\n", get_time_stamp(), data->time);
    }
    // mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
    // sleep(1000);
    return (0);
}

int main(int argc, char **argv)
{
    t_data data;

    init(&data);
    if (argc != 2)
        fatal("Arguments");
    fill_map(&data, argv[1]);
    mlx_hook(data.win, 2, 1L << 0, key_press, (void *)&data);
	mlx_hook(data.win, 17, 1L << 17, ft_exit, (void *)0);
    ft_render(&data);
    // while (1){
        // mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, data.win);
        // mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data.image);
        // mlx_do_sync(data.mlx);
        // mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
        // mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, data.win);
        // mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, data.win);
    mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
    mlx_loop_hook(data.mlx, loop, &data);

    mlx_loop(data.mlx);

        // while (1) sleep(200);
    // }
}
