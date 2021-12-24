/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 02:55:11 by hmoumani          #+#    #+#             */
/*   Updated: 2021/12/24 02:55:13 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	ft_brick_line(t_data *data, int x, int y, int pos)
{
	int	i;

	i = 0;
	while (i < (WIN_HEIGHT / data->m_height))
	{
		put_my_pixel(data, x + i, y, get_color(data, i, pos, data->from));
		i++;
	}
}

void	ft_rect(t_data *data, int x, int y, t_texture *from)
{
	int	i;

	i = 0;
	data->from = from;
	while (i < WIN_WIDTH / data->m_width)
	{
		ft_brick_line(data, x * (WIN_HEIGHT / data->m_height), (y
				* (WIN_WIDTH / data->m_width)) + i, i);
		i++;
	}
}

int	get_color(t_data *data, int i, int j, t_texture *from)
{
	int	y;
	int	x;

	y = j * from->width / (WIN_WIDTH / data->m_width);
	x = i * from->height / (WIN_HEIGHT / data->m_height);
	if (from->width * from->height < x * from->width + y)
		return (0xeaf);
	return (((unsigned int *)from->addr)[x * from->width + y]);
}
