/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:51:58 by hmoumani          #+#    #+#             */
/*   Updated: 2019/11/02 01:30:06 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)ft_malloc(sizeof(t_list));
	if (!new)
		fatal(NULL);
	if (!new)
		return (new);
	new->content = content;
	new->next = NULL;
	return (new);
}
