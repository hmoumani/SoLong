/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <hmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 16:38:49 by hmoumani          #+#    #+#             */
/*   Updated: 2021/06/21 19:58:43 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

static	char	*ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			return (s + i);
		}
		i++;
	}
	return (0);
}

static	char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	*p;

	i = 0;
	j = 0;
	len1 = ft_strlen_(s1);
	len2 = ft_strlen_(s2);
	p = malloc (len1 + len2 + 1);
	while (i < len1 + len2)
	{
		if (i < len1)
			p[i] = s1[i];
		else
			p[i] = s2[j++];
		i++;
	}
	p[i] = 0;
	return (p);
}

int	rest_(char *p, char **rest, char **line)
{
	char		*pfree;
	char		temp[1001];
	int			ret;

	while (1)
	{
		ret = read(0, &temp, 1000);
		if (!ret)
			break ;
		temp[ret] = 0;
		p = ft_strchr(temp, '\n');
		if (p)
		{
			*p = 0;
			pfree = *line;
			*line = ft_strjoin(*line, temp);
			free(pfree);
			*rest = ft_strdup(p + 1);
			return (1);
		}
		pfree = *line;
		*line = ft_strjoin(*line, temp);
		free(pfree);
	}
	return (0);
}

int	get_next_line(char **line)
{
	static char	*rest;
	char		*p;
	char		*pfree;

	*line = ft_strdup("");
	if (rest)
	{
		p = ft_strchr(rest, '\n');
		if (p)
		{
			*p = 0;
			pfree = *line;
			*line = ft_strdup(rest);
			free(pfree);
			pfree = rest;
			rest = ft_strdup(p + 1);
			free(pfree);
			return (1);
		}
		pfree = *line;
		*line = ft_strdup(rest);
		ft_double_free(&pfree, &rest, 1);
		rest = NULL;
	}
	return (rest_(NULL, &rest, line));
}
