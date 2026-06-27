/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodrig2 <frodrig2@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 21:10:09 by frodrig2          #+#    #+#             */
/*   Updated: 2026/06/27 22:55:19 by frodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*lst_lastnode(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	lst_hasnewline(t_list *list)
{
	int		i;
	t_list	*lastnode;

	if (!list)
		return (0);
	lastnode = lst_lastnode(list);
	if (!lastnode)
		return (0);
	i = 0;
	while (lastnode->buffer[i])
	{
		if (lastnode->buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
