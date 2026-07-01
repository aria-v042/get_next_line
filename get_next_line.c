/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodrig2 <frodrig2@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 20:59:22 by frodrig2          #+#    #+#             */
/*   Updated: 2026/07/01 22:03:48 by frodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	trim_list(t_list **list_ptr)
{
	t_list	*lastnode;
	char	*remainder;
	int		newline_index;

	if (!*list_ptr)
		return (-1);
	remainder = NULL;
	lastnode = lst_lastnode(*list_ptr);
	newline_index = find_newline(lastnode);
	if (newline_index >= 0)
	{
		remainder = get_remainder(lastnode, newline_index);
		if (!remainder)
			return (-1);
	}
	lst_freeuntil(list_ptr, lastnode);
	lst_resolvelast(list_ptr, lastnode, remainder);
	return (0);
}

char	*extract_line(t_list *list)
{
	size_t	len;
	char	*line;

	if (!list)
		return (NULL);
	len = len_to_newline(list);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	lst_copyline(list, line);
	return (line);
}

void	read_into_list(t_list **list_ptr, int fd)
{
	char	*buffer;
	int		bytes_read;
	t_list	*node;

	node = *list_ptr;
	while (find_newline(node) < 0)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
		{
			// debug:
			printf("Error: failed to allocate memory for buffer string");
			return ;
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		// end of file reached or read() error
		if (bytes_read <= 0)
		{
			// debug:
			printf("Warning: end of file reached or read() error.\n");
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		node = lst_append(list_ptr, buffer);
		if (!node)
		{
			// debug:
			printf("Error: failed to append new node to the buffer list");
			return ;
		}
	}
}

char	*get_next_line(int fd)
{
	static t_list	*buffer_list = NULL;
	char			*next_line;

	// check valid fd, BUFFER_SIZE; use read() to check file is open
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		// debug:
		printf("Error: invalid fd, buffer size, or read() failure.");
		return (NULL);
	}
	read_into_list(&buffer_list, fd);
	if (!buffer_list)
	{
		// debug:
		printf("Error: failed to create buffer list");
		return (NULL);
	}
	next_line = extract_line(buffer_list);
	if (trim_list(&buffer_list))
	{
		// debug:
		printf("Error: failed to trim the buffer list");
		return (NULL);
	}
	return (next_line);
}
