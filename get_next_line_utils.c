/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodrig2 <frodrig2@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 21:10:09 by frodrig2          #+#    #+#             */
/*   Updated: 2026/06/28 00:32:11 by frodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_remainder(t_list *lastnode, int newline_index)
{
	char	*remainder;
	int		i;
	int		j;

	remainder = malloc(BUFFER_SIZE + 1);
	if (!remainder)
		return (NULL);
	i = newline_index;
	j = 0;
	while (lastnode->buffer[++i])
		remainder[j++] = lastnode->buffer[i];
	remainder[j] = '\0';
}

void	lst_free_until(t_list **list_ptr, t_list *limit)
{
	t_list	*node;
	
	node = *list_ptr;
	while (node != limit)
	{
		*list_ptr = node->next;
		free(node->buffer);
		free(node);
		node = *list_ptr;
	}
}

void	lst_copyline(t_list *list, char *line)
{
	int	i;
	int	j;

	if (!list || !line)
	{
		if (line)
			free(line);
		return ;
	}
	j = 0;
	while (list)
	{
		i = 0;
		while (list->buffer[i])
		{
			line[j] = list->buffer[i++];
			if (line[j++] == '\n')
			{
				line[j] = '\0';
				return ;
			}
		}
		list = list->next;
	}
	line[j] = '\0';
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
