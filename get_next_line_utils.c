/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodrig2 <frodrig2@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 21:10:09 by frodrig2          #+#    #+#             */
/*   Updated: 2026/07/02 02:49:36 by frodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	lst_freeuntil(t_list **list_ptr, t_list *limit)
{
	t_list	*temp;

	if (!*list_ptr)
		return ;
	while (*list_ptr && *list_ptr != limit)
	{
		temp = (*list_ptr)->next;
		free((*list_ptr)->buffer);
		free((*list_ptr));
		(*list_ptr) = temp;
	}
}

size_t	len_to_newline(t_list *list)
{
	int		i;
	size_t	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->buffer[i])
		{
			++len;
			if (list->buffer[i] == '\n')
				return (len);
			++i;
		}
		list = list->next;
	}
	return (len);
}

t_list	*lst_lastnode(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	find_newline(t_list *node)
{
	int		i;

	if (!node)
		return (-1);
	i = 0;
	while (node->buffer[i])
	{
		if (node->buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

t_list	*lst_append(t_list **list_ptr, char *buffer)
{
	t_list	*newnode;
	t_list	*lastnode;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	newnode = malloc(sizeof(t_list));
	if (!newnode)
	{
		free(buffer);
		return (NULL);
	}
	newnode->buffer = buffer;
	newnode->next = NULL;
	if (!*list_ptr)
		*list_ptr = newnode;
	else
	{
		lastnode = lst_lastnode(*list_ptr);
		lastnode->next = newnode;
	}
	return (newnode);
}
