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