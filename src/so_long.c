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

int	ft_win(t_data *data)
{
	clear_buffer(data);
	draw_background(data, &data->img_win);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	print_mov_count_screen(data);
	return (0);
}

void	ft_loss(t_data *data)
{
	data->is_win = -1;
	clear_buffer(data);
	draw_background(data, &data->img_over);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	print_mov_count_screen(data);
}

void	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_fire)
	{
		if (i == data->player_x - 1 && data->fires[i] == data->player_y)
			ft_loss(data);
		++i;
	}
}

int	key_press(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == 53)
		ft_exit();
	if (data->is_win)
		return (print_mov_count_screen(data));
	if (key == 1)
		ft_down(data);
	else if (key == 13)
		ft_up(data);
	else if (key == 0)
		ft_left(data);
	else if (key == 2)
		ft_right(data);
	check_death(data);
	if (data->is_win)
	{
		if (data->is_win == -1)
			return (0);
		return (ft_win(data));
	}
	ft_render(data);
	render_fire(data);
	return (0);
}

int	main(int argc, char **argv)
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
