/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 23:18:49 by hmoumani          #+#    #+#             */
/*   Updated: 2021/12/14 23:18:51 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <math.h>
# include <limits.h>
# include <errno.h>
# define FALSE 0
# define TRUE 1
# define Error "Error\n"

typedef	struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

#endif
