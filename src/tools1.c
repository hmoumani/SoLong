/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 23:33:00 by hmoumani          #+#    #+#             */
/*   Updated: 2021/12/14 23:33:01 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

void    fatal(const char * const str)
{
    if (str)
        printf("%s%s\n", ERROR, str);
    else
        printf("%s %s\n", ERROR, strerror(errno));
    exit(1);
}

void    *ft_malloc(size_t size)
{
    void *p;

    p = malloc(size);
    if (p == NULL)
        fatal("malloc failed");
    return (p);
}

void	put_my_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < WIN_HEIGHT && y < WIN_HEIGHT)
	{
		dst = data->mlx_data + (x * data->line_length + y * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	clear_buffer(t_data *data)
{
	int i;

	i = 0;
	while (i < data->line_length)
	{
		data->mlx_data[i++] = 0;
	}
}


void		ft_hor_line(t_data *data, int x, int y, int color, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		put_my_pixel(data, x + i, y, color);
		i++;
	}
}

void		ft_square(t_data *data, int x, int y, int color)
{
	int i;

	i = 0;
	while (i < 200)
	{
		ft_hor_line(data, x * 200, y + i * 200, color, 200);
		i++;
	}
}