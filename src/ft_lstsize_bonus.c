/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 00:23:41 by hmoumani          #+#    #+#             */
/*   Updated: 2019/11/01 00:52:35 by hmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*curr;

	curr = lst;
	i = 0;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

int	ft_is_end_with(char *s, char *s1)
{
	int	len;
	int	i;
	int	len1;

	len = ft_strlen(s);
	len1 = ft_strlen(s1);
	i = 0;
	while (len - i >= 0)
	{
		if (s[len - i] != s1[len1 - i])
			return (0);
		if (i == len1)
			return (1);
		i++;
	}
	return (1);
}
