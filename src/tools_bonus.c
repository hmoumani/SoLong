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

void    render_fire(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_fire)
    {
        if (data->fires[i] != 0)
        {
            ft_rect(data, i + 1, data->fires[i], data->fire);
        }
        ++i;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

void    generate_fire(t_data *data)
{
    int i;

    i = 0;
    if (!data->is_win && get_time_stamp() - data->time_gen_fire > 1700000)
    {
        while (i < data->num_fire)
        {
            data->fires[i]++;

            data->fires[i] %= data->m_width;
            ++i;
        }

        data->time_gen_fire = get_time_stamp();
    }
}


int loop(t_data *data)
{
    static int coin_index = 0;
    static int fire_index = 0;
    if (!data->is_win && get_time_stamp() - data->time > 170000){
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
        render_fire(data);
        print_mov_count_screen(data);
        // printf("hrweihfglwgn %ld * %ld\n", get_time_stamp(), data->time);
    }
    generate_fire(data);
    if (!data->is_win && get_time_stamp() - data->time_fire > 250000)
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

    return (0);
}

