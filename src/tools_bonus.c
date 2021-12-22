/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 06:27:40 by hmoumani          #+#    #+#             */
/*   Updated: 2021/12/22 06:27:54 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void    print_mov_count(t_data *data)
{
    (void)data;
}

void    print_mov_count_screen(t_data *data)
{
    mlx_string_put(data->mlx, data->win, 10, 10, 0x258DDF, ft_itoa(data->movements));
}
