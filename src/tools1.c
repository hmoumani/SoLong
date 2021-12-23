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

	if (x >= 0 && y >= 0 && x < WIN_HEIGHT && y < WIN_WIDTH && color != 1)
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

int			get_color(t_data *data, int i, int j, t_texture *from)
{
	int y = j * from->width / (WIN_WIDTH / data->m_width);
	int x = i * from->height / (WIN_HEIGHT / data->m_height);
	if (from->width * from->height < x * from->width + y)
		return (0xeaf);
	return ((unsigned int *)from->addr)[x * from->width + y];
}

void		ft_brick_line(t_data *data, int x, int y, int pos, t_texture *from)
{
	int i;

	i = 0;
	(void)pos;
	while (i < (WIN_HEIGHT / data->m_height))
	{
		// printf("%d * %d\n", pos, i);
		put_my_pixel(data, x + i, y, get_color(data, i, pos, from));
		i++;
	}
}

void		ft_rect(t_data *data, int x, int y, t_texture *from)
{
	int i;

	i = 0;
	while (i < WIN_WIDTH / data->m_width)
	{
		ft_brick_line(data, x * (WIN_HEIGHT / data->m_height), (y * (WIN_WIDTH / data->m_width)) + i, i, from);
		i++;
	}
}
