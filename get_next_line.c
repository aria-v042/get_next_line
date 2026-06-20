/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodrig2 <frodrig2@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 20:59:22 by frodrig2          #+#    #+#             */
/*   Updated: 2026/06/15 21:01:51 by frodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*buffer_list = NULL;
	char			*next_line;

	// check valid fd, BUFFER_SIZE; use read() to check file is open
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	create_list(&buffer_list, fd);
	if (!buffer_list)
		return (NULL);
	next_line = get_line(buffer_list);
	cleanup_list(&buffer_list);
	return (next_line);
}
