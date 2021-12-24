/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 09:41:13 by hmoumani          #+#    #+#             */
/*   Updated: 2021/12/24 09:41:18 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	ft_check_zero(t_data *data, int i, int j)
{
	char	**mp;

	mp = data->map;
	if (i - 1 < 0 || j - 1 < 0 || i + 1 >= data->m_height \
	|| j + 1 >= data->m_width)
		fatal("map misconfigured");
	else if (mp[i - 1][j] == ' ' || mp[i + 1][j] == ' ')
		fatal("map misconfigured");
	else if (mp[i][j - 1] == ' ' || mp[i][j + 1] == ' ')
		fatal("map misconfigured");
}

void	ft_check_player(t_data *data, int i, int j)
{
	if (data->player_x != 0)
		fatal("player duplicated");
	ft_check_zero(data, i, j);
	data->player_x = i;
	data->player_y = j;
}

void	check_missing_elements(t_data *data)
{
	if (data->player_x == 0)
		fatal("404 Player not found");
	if (data->found_exit == 0)
		fatal("No exit found");
	if (data->coll_found == 0)
		fatal("No collectible found");
}

void	check_map(t_data *data, int i)
{
	int		j;

	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == '0')
				ft_check_zero(data, i, j);
			else if (data->map[i][j] == 'P')
				ft_check_player(data, i, j);
			else if (data->map[i][j] == 'E')
			{
				ft_check_zero(data, i, j);
				data->found_exit = 1;
			}
			else if (data->map[i][j] == 'C')
			{
				ft_check_zero(data, i, j);
				data->coll_found += 1;
			}
			else if (data->map[i][j] != '1')
				fatal("Invalid character in map");
		}
	}
}

void	array_map(t_data *data)
{
	int		count;
	int		len;
	int		i;
	t_list	*tmp;

	count = ft_lstsize(data->lines);
	i = 0;
	tmp = data->lines;
	data->map = ft_malloc((count + 1) * sizeof(char *));
	len = -1;
	while (i < count)
	{
		if (len != -1 && len != ft_strlen(tmp->content))
			fatal("lenght of lines should be the same");
		data->map[i] = tmp->content;
		len = ft_strlen(tmp->content);
		tmp = tmp->next;
		i++;
	}
	data->m_width = len;
	data->m_height = count;
	data->map[i] = NULL;
	check_map(data, 0);
}
