/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodrig2 <frodrig2@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 22:36:05 by frodrig2          #+#    #+#             */
/*   Updated: 2026/07/12 22:36:07 by frodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// Return index of 1st newline character in node; return -1 if not found
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

/* Return total lenth until the end of a line in list */
size_t	len_to_newline(t_list *list)
{
	int		i;
	size_t	len;

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

/* ---- LINKED LIST OPERATIONS --------------------------------- */

// Free nodes until 'limit' node; Free all nodes if 'limit' is NULL
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

// Return list's last node
t_list	*lst_lastnode(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

// Append new node containing given buffer to list and return the appended node
t_list	*lst_append(t_list **list_ptr, char *buffer)
{
	t_list	*newnode;
	t_list	*lastnode;

	if (!buffer || *buffer == '\0')
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
