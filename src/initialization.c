/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 09:05:44 by hmoumani          #+#    #+#             */
/*   Updated: 2021/12/24 09:05:46 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	init3(t_data *d)
{
	d->player = &d->m1;
	d->coin = &d->c1;
	d->fire = &d->f1;
	d->time = get_time_stamp();
	d->time_fire = d->time;
	d->time_gen_fire = d->time_fire;
}

void	init2(t_data *d)
{
	d->u1.addr = mlx_data(d->u1.img, &d->u1.bpp, &d->u1.ln_len, &d->u1.endian);
	d->u2.addr = mlx_data(d->u2.img, &d->u2.bpp, &d->u2.ln_len, &d->u2.endian);
	d->d1.addr = mlx_data(d->d1.img, &d->d1.bpp, &d->d1.ln_len, &d->d1.endian);
	d->d2.addr = mlx_data(d->d2.img, &d->d2.bpp, &d->d2.ln_len, &d->d2.endian);
	d->l1.addr = mlx_data(d->l1.img, &d->l1.bpp, &d->l1.ln_len, &d->l1.endian);
	d->l2.addr = mlx_data(d->l2.img, &d->l2.bpp, &d->l2.ln_len, &d->l2.endian);
	d->r1.addr = mlx_data(d->r1.img, &d->r1.bpp, &d->r1.ln_len, &d->r1.endian);
	d->r2.addr = mlx_data(d->r2.img, &d->r2.bpp, &d->r2.ln_len, &d->r2.endian);
	d->c1.addr = mlx_data(d->c1.img, &d->c1.bpp, &d->c1.ln_len, &d->c1.endian);
	d->c2.addr = mlx_data(d->c2.img, &d->c2.bpp, &d->c2.ln_len, &d->c2.endian);
	d->c3.addr = mlx_data(d->c3.img, &d->c3.bpp, &d->c3.ln_len, &d->c3.endian);
	d->c4.addr = mlx_data(d->c4.img, &d->c4.bpp, &d->c4.ln_len, &d->c4.endian);
	d->c5.addr = mlx_data(d->c5.img, &d->c5.bpp, &d->c5.ln_len, &d->c5.endian);
	d->c6.addr = mlx_data(d->c6.img, &d->c6.bpp, &d->c6.ln_len, &d->c6.endian);
	d->f1.addr = mlx_data(d->f1.img, &d->f1.bpp, &d->f1.ln_len, &d->f1.endian);
	d->f2.addr = mlx_data(d->f2.img, &d->f2.bpp, &d->f2.ln_len, &d->f2.endian);
	d->f3.addr = mlx_data(d->f3.img, &d->f3.bpp, &d->f3.ln_len, &d->f3.endian);
	d->castle.addr = mlx_data(d->castle.img, &d->castle.bpp, &d->castle.ln_len,
			&d->castle.endian);
	d->img_win.addr = mlx_data(d->img_win.img, &d->img_win.bpp,
			&d->img_win.ln_len, &d->img_win.endian);
	d->img_over.addr = mlx_data(d->img_over.img, &d->img_over.bpp,
			&d->img_over.ln_len, &d->img_over.endian);
	init3(d);
}

void	init1(t_data *d)
{
	d->c2.img = xpm(d->mlx, "images/coin/2.xpm", &d->c2.width, &d->c2.height);
	d->c3.img = xpm(d->mlx, "images/coin/3.xpm", &d->c3.width, &d->c3.height);
	d->c4.img = xpm(d->mlx, "images/coin/4.xpm", &d->c4.width, &d->c4.height);
	d->c5.img = xpm(d->mlx, "images/coin/5.xpm", &d->c5.width, &d->c5.height);
	d->c6.img = xpm(d->mlx, "images/coin/6.xpm", &d->c6.width, &d->c6.height);
	d->f1.img = xpm(d->mlx, "images/fire/1.xpm", &d->f1.width, &d->f1.height);
	d->f2.img = xpm(d->mlx, "images/fire/2.xpm", &d->f2.width, &d->f2.height);
	d->f3.img = xpm(d->mlx, "images/fire/3.xpm", &d->f3.width, &d->f3.height);
	d->castle.img = xpm(d->mlx, "images/castle/2.xpm", &d->castle.width,
			&d->castle.height);
	d->img_win.img = xpm(d->mlx, "images/win.xpm", &d->img_win.width,
			&d->img_win.height);
	d->img_over.img = xpm(d->mlx, "images/over.xpm", &d->img_over.width,
			&d->img_over.height);
	if (!d->bg.img || !d->brick.img || !d->m1.img || !d->u1.img || !d->u2.img
		|| !d->d1.img || !d->img_win.img || !d->img_over.img || !d->d2.img
		|| !d->r1.img || !d->r2.img || !d->l1.img || !d->l2.img || !d->c1.img
		|| !d->c2.img || !d->c3.img || !d->c4.img || !d->c5.img || !d->c6.img
		|| !d->f1.img || !d->f2.img || !d->f3.img)
		fatal("images files should be in images/ folder");
	d->bg.addr = mlx_data(d->bg.img, &d->bg.bpp, &d->bg.ln_len, &d->bg.endian);
	d->brick.addr = mlx_data(d->brick.img, &d->brick.bpp, &d->brick.ln_len,
			&d->brick.endian);
	d->m1.addr = mlx_data(d->m1.img, &d->m1.bpp, &d->m1.ln_len, &d->m1.endian);
	init2(d);
}

void	init(t_data *d)
{
	ft_memset(d, 0, sizeof(*d));
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, WIN_WIDTH, WIN_HEIGHT, "so_long");
	d->image = mlx_new_image(d->mlx, WIN_WIDTH, WIN_HEIGHT);
	d->mlx_data = mlx_data(d->image, &d->bpp, &d->ln_len, &d->endian);
	d->bg.img = xpm(d->mlx, "images/bg.xpm", &d->bg.width, &d->bg.height);
	d->brick.img = xpm(d->mlx, "images/brick.xpm", &d->brick.width,
			&d->brick.height);
	d->m1.img = xpm(d->mlx, "images/mario1.xpm", &d->m1.width, &d->m1.height);
	d->u1.img = xpm(d->mlx, "images/up/1.xpm", &d->u1.width, &d->u1.height);
	d->u2.img = xpm(d->mlx, "images/up/2.xpm", &d->u2.width, &d->u2.height);
	d->d1.img = xpm(d->mlx, "images/down/1.xpm", &d->d1.width, &d->d1.height);
	d->d2.img = xpm(d->mlx, "images/down/2.xpm", &d->d2.width, &d->d2.height);
	d->r1.img = xpm(d->mlx, "images/right/1.xpm", &d->r1.width, &d->r1.height);
	d->r2.img = xpm(d->mlx, "images/right/2.xpm", &d->r2.width, &d->r2.height);
	d->l1.img = xpm(d->mlx, "images/left/1.xpm", &d->l1.width, &d->l1.height);
	d->l2.img = xpm(d->mlx, "images/left/2.xpm", &d->l2.width, &d->l2.height);
	d->c1.img = xpm(d->mlx, "images/coin/1.xpm", &d->c1.width, &d->c1.height);
	init1(d);
}
