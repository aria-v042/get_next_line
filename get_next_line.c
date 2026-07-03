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
	t_list	*node;
	t_list	*lastnode;
	char	*remainder;

	if (!*list_ptr)
		return (-1);
	lastnode = lst_lastnode(*list_ptr);
	if ((get_remainder(lastnode, &remainder)) != 0)
		return (-1);
	node = *list_ptr;
	while (node != lastnode)
	{
		*list_ptr = node->next;
		free(node->buffer);
		free(node);
		node = *list_ptr;
	}
	free(lastnode->buffer);
	if (remainder && remainder[0])
		return (lastnode->buffer = remainder, 0);
	free(remainder);
	free(lastnode);
	*list_ptr = NULL;
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
	if (lst_copyline(list, line) != 0)
		return (NULL);
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
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		// end of file reached or read() error
		if (bytes_read <= 0)
		{
			if (bytes_read == -1)
				trim_list(list_ptr);
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		node = lst_append(list_ptr, buffer);
		if (!node)
			return ;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*buffer_list = NULL;
	char			*next_line;

	// check valid fd, BUFFER_SIZE; use read() to check file is open
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_into_list(&buffer_list, fd);
	if (!buffer_list)
		return (NULL);
	next_line = extract_line(buffer_list);
	if (trim_list(&buffer_list) != 0)
		return (NULL);
	return (next_line);
}
