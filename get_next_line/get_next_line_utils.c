/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <hmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 16:52:21 by hmoumani          #+#    #+#             */
/*   Updated: 2021/06/21 19:55:01 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

int	ft_double_free(char **p1, char **p2, int ret)
{
	free(*p1);
	free(*p2);
	return (ret);
}

int	ft_strlen_(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *s)
{
	int		i;
	int		len;
	char	*p;

	i = 0;
	len = ft_strlen_(s);
	p = malloc (len + 1);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = 0;
	return (p);
}
