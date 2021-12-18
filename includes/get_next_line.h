/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <hmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 17:45:57 by hmoumani          #+#    #+#             */
/*   Updated: 2021/06/21 19:58:08 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# define BUFFER_SIZE 100

char	*ft_strdup(char *s);
int		ft_strlen_(char *s);
int		ft_double_free(char **p1, char **p2, int ret);
int		get_next_line(char **line, int fd);
void    *ft_malloc(size_t size);
void    fatal(const char *const str);

#endif
