/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 23:10:55 by hmoumani          #+#    #+#             */
/*   Updated: 2021/12/14 23:10:58 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void    array_map(t_data *data)
{
    int len;

    len = ft_lstsize(data->lines);
    data->map = ft_malloc(len + 1);
    

}

void    fill_map(t_data *data, char const * const filename)
{
    int fd;
    int ret;
    char *line;

    line = NULL;
    ret = 1;
    fd = open(filename, O_RDONLY);
    while (ret > 0)
    {
        ret = get_next_line(&line, fd);
        if (ret < 0)
            break ;
        ft_lstadd_back(&data->lines, ft_lstnew(line));
    }
    array_map(data);
}

void    init(t_data *data)
{
    *data = (t_data){NULL, NULL};
}

int main(int argc, char **argv)
{
    t_data data;
    init(&data);
    if (argc != 2)
        fatal("Arguments");
    fill_map(&data, argv[1]);
        
}
