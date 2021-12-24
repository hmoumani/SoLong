/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 06:31:43 by hmoumani          #+#    #+#             */
/*   Updated: 2021/12/23 06:31:47 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	draw_fire(t_data *data)
{
	static int	fire_index = 0;

	generate_fire(data);
	if (!data->is_win && get_time_stamp() - data->time_fire > 170000)
	{
		if (fire_index == 0)
			data->fire = &data->f1;
		else if (fire_index == 1)
			data->fire = &data->f2;
		else if (fire_index == 2)
			data->fire = &data->f3;
		data->time_fire = get_time_stamp();
		fire_index++;
		fire_index %= 3;
		render_fire(data);
		check_death(data);
	}
}
