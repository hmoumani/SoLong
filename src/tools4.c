/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 09:44:36 by hmoumani          #+#    #+#             */
/*   Updated: 2021/12/24 09:44:39 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	fill_map(t_data *data, char const *const filename)
{
	int		fd;
	int		ret;
	char	*line;
	int		i;

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
	i = 0;
	while (i < data->num_fire)
		if (i % 2 == 0)
			data->fires[i++] = -1;
	else
		data->fires[i++] = -4;
}

int	get_color_window(int i, int j, t_texture *from)
{
	int	y;
	int	x;

	y = j * from->width / WIN_WIDTH;
	x = i * from->height / WIN_HEIGHT;
	if (from->width * from->height < x * from->width + y)
		return (0xeaf);
	return (((unsigned int *)from->addr)[x * from->width + y]);
}

void	draw_background(t_data *data, t_texture *bg)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			put_my_pixel(data, i, j, get_color_window(i, j, bg));
			++j;
		}
		++i;
	}
}

void	ft_draw_map(t_data *data)
{
	int	i;
	int	j;

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

void	ft_render(t_data *data)
{
	clear_buffer(data);
	ft_draw_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}
