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

int	get_remainder(t_list *lastnode, char **remainderptr)
{
	char	*remainder;
	int		i;
	int		j;

	remainder = NULL;
	i = find_newline(lastnode);
	if (i >= 0)
	{
		remainder = malloc(BUFFER_SIZE + 1);
		if (!remainder)
			return (-1);
		j = 0;
		while (lastnode->buffer[++i])
			remainder[j++] = lastnode->buffer[i];
		remainder[j] = '\0';
	}
	*remainderptr = remainder;
	return (0);
}

int	trim_list(t_list **list_ptr)
{
	t_list	*lastnode;
	char	*remainder;

	if (!*list_ptr)
		return (0);
	lastnode = lst_lastnode(*list_ptr);
	if (get_remainder(lastnode, &remainder) != 0)
		return (-1);
	if (!remainder || remainder[0] == '\0')
	{
		free(remainder);
		lst_freeuntil(list_ptr, NULL);
		return (0);
	}
	lst_freeuntil(list_ptr, lastnode);
	free(lastnode->buffer);
	lastnode->buffer = remainder;
	return (0);
}

char	*extract_line(t_list *list)
{
	size_t	len;
	char	*line;
	int		i;

	if (!list)
		return (NULL);
	len = len_to_newline(list);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->buffer[i])
		{
			line[len] = list->buffer[i++];
			if (line[len++] == '\n')
				return (line[len] = '\0', line);
		}
		list = list->next;
	}
	line[len] = '\0';
	return (line);
}

int	read_into_list(t_list **list_ptr, int fd)
{
	char	*buffer;
	int		bytes_read;
	t_list	*node;

	node = *list_ptr;
	while (find_newline(node) < 0)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (-1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		// end of file reached or read() error
		if (bytes_read <= 0)
		{
			free(buffer);
			if (bytes_read == 0)
				return (0);
			else
				return (-1);
		}
		buffer[bytes_read] = '\0';
		node = lst_append(list_ptr, buffer);
		if (!node)
			return (-1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*buffer_list = NULL;
	char			*next_line;

	// check valid fd, BUFFER_SIZE; use read() to check file is open
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_into_list(&buffer_list, fd) != 0)
	{
		lst_freeuntil(&buffer_list, NULL);
		return (NULL);
	}
	next_line = extract_line(buffer_list);
	if (!next_line)
	{
		lst_freeuntil(&buffer_list, NULL);
		return (NULL);
	}
	if (trim_list(&buffer_list) != 0)
		lst_freeuntil(&buffer_list, NULL);
	return (next_line);
}
