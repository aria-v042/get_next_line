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

// NO BONUS: testing get_next_line() with a single file descriptor
int	main(int ac, char **av)
{
	int		fd;
	char	*filename;
	char	*line;
	int		line_num;

	// if args are passed, use 1st as filename, otherwise use default
	if (ac < 2)
	{
		filename = "file.txt";
		printf("No file given: reading from \"%s\" default file\n\n", filename);
	}
	else
	{
		filename = av[1];
	}

	// open given file; check for errors
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening the file");
		exit(1);
	}

	// inform what file is being read
	printf("Reading from \"%s\"...\n\n", filename);

	// read file line-by-line; print each line
	line_num = 0;
	while ((line = get_next_line(fd)))
	{
		printf("%i: %s\n", ++line_num, line);
	}

	// close file and return; check for errors
	if (close(fd) < 0)
	{
		perror("Error closing the file");
		exit(1);
	}
	return (0);
}
