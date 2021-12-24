/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 09:47:36 by hmoumani          #+#    #+#             */
/*   Updated: 2021/12/24 09:47:37 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	ft_left(t_data *data)
{
	static int	pos = 0;

	if (data->player_y - 1 > 0 && data->map[data->player_x][data->player_y - 1]
		!= '1' && (data->map[data->player_x][data->player_y - 1] != 'E' ||
		data->coll_found == 0))
	{
		if (data->map[data->player_x][data->player_y - 1] == 'C')
			data->coll_found--;
		if (data->map[data->player_x][data->player_y - 1] == 'E'
			&& data->coll_found == 0)
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

void	ft_right(t_data *data)
{
	static int	pos = 0;

	if (data->player_y + 1 < data->m_width
		&& data->map[data->player_x][data->player_y + 1] != '1'
		&& (data->map[data->player_x][data->player_y + 1] != 'E'
		|| data->coll_found == 0))
	{
		if (data->map[data->player_x][data->player_y + 1] == 'C')
			data->coll_found--;
		if (data->map[data->player_x][data->player_y + 1] == 'E'
			&& data->coll_found == 0)
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

void	ft_up(t_data *data)
{
	static int	pos = 0;

	if (data->player_x - 1 > 0
		&& data->map[data->player_x - 1][data->player_y] != '1'
		&& (data->map[data->player_x - 1][data->player_y] != 'E'
		|| data->coll_found == 0))
	{
		if (data->map[data->player_x - 1][data->player_y] == 'C')
			data->coll_found--;
		if (data->map[data->player_x - 1][data->player_y] == 'E'
			&& data->coll_found == 0)
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

void	ft_down(t_data *data)
{
	static int	pos = 0;

	if (data->player_x + 1 < data->m_width
		&& data->map[data->player_x + 1][data->player_y] != '1'
		&& (data->map[data->player_x + 1][data->player_y] != 'E'
		|| data->coll_found == 0))
	{
		if (data->map[data->player_x + 1][data->player_y] == 'C')
			data->coll_found--;
		if (data->map[data->player_x + 1][data->player_y] == 'E'
			&& data->coll_found == 0)
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

int	ft_exit(void)
{
	exit(0);
}
