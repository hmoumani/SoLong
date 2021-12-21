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
	if (data->player_x != -1)
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
                data->coll_found = 1;
            }
            else if (c == '1')
                i += 0;
            else
                fatal("Invalid character in map");
			j++;
		}
		i++;
	}
    if (data->player_x == -1)
        fatal("404 Player not found");
    if (data->found_exit == -1)
        fatal("No exit found");
    if (data->coll_found == -1)
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

void    draw_background(t_data *data)
{
    
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
                ft_square(data, i, j);
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

void    init(t_data *data)
{
    t_texture txt;

    txt = (t_texture){0, 0, 0, 0, 0, 0, 0};
    *data = (t_data){0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0, 0, 0, txt, txt, txt, txt, txt};
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "so_long");
    data->image = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
    data->mlx_data = mlx_get_data_addr(data->image, &data->bpp, &data->line_length, &data->endian);
    data->bg.img = mlx_xpm_file_to_image(data->mlx, "images/background.xpm", &data->bg.width, &data->bg.height);
    data->brick.img = mlx_xpm_file_to_image(data->mlx, "images/brick.xpm", &data->brick.width, &data->brick.height);
    data->m1.img = mlx_xpm_file_to_image(data->mlx, "images/mario1.xpm", &data->m1.width, &data->m1.height);
    data->m2.img = mlx_xpm_file_to_image(data->mlx, "images/mario2.xpm", &data->m2.width, &data->m2.height);
    data->m3.img = mlx_xpm_file_to_image(data->mlx, "images/mario3.xpm", &data->m3.width, &data->m3.height);
    if (!data->bg.img || !data->brick.img || !data->m1.img || !data->m2.img || !data->m3.img)
        fatal("images files should be in images/ folder");
    data->bg.addr = mlx_get_data_addr(data->bg.img, &data->bg.bpp, &data->bg.line_length, &data->bg.endian);
    data->brick.addr = mlx_get_data_addr(data->brick.img, &data->brick.bpp, &data->brick.line_length, &data->brick.endian);
    data->m1.addr = mlx_get_data_addr(data->m1.img, &data->m1.bpp, &data->m1.line_length, &data->m1.endian);
    data->m2.addr = mlx_get_data_addr(data->m2.img, &data->m2.bpp, &data->m2.line_length, &data->m2.endian);
    data->m3.addr = mlx_get_data_addr(data->m3.img, &data->m3.bpp, &data->m3.line_length, &data->m3.endian);
}

int main(int argc, char **argv)
{
    t_data data;
    init(&data);
    if (argc != 2)
        fatal("Arguments");
    fill_map(&data, argv[1]);
    ft_render(&data);
    mlx_loop(data.mlx);
}
