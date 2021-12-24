/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 00:37:40 by hmoumani          #+#    #+#             */
/*   Updated: 2019/11/03 00:24:38 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (*alst == NULL)
		*alst = new;
	else if (alst)
	{
		last = ft_lstlast(*alst);
		last->next = new;
	}
}

void	*xpm(void *mlx_ptr, char *filename, int *width, int *height)
{
	return (mlx_xpm_file_to_image(mlx_ptr, filename, width, height));
}

void	*mlx_data(void *img_ptr, int *bits_per_pixel, int *size, int *endian)
{
	return (mlx_get_data_addr(img_ptr, bits_per_pixel, size, endian));
}
