/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodrig2 <frodrig2@students.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 20:17:22 by frodrig2          #+#    #+#             */
/*   Updated: 2026/06/17 20:23:41 by frodrig2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	int		fd;
	char	*filename;

	if (ac < 2)
	{
		filename = "test.txt";
		printf("No file given: reading from \"%s\" default file\n\n", filename);
	}
	else
	{
		filename = av[1];
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening the file");
		exit(1);
	}
	printf("Reading from \"%s\"\n\n", filename);
	if (close(fd) < 0)
	{
		perror("Error closing the file");
		exit(1);
	}
	return (0);
}
