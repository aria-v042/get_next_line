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

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// NO BONUS: testing get_next_line() with a single file descriptor
int	main(int ac, char **av)
{
	int		fd;
	char	*filename;
	char	*line;
	int		line_num;

	printf("\n");
	printf(ANSI_COLOR_CYAN "///" ANSI_COLOR_MAGENTA "-============================================-" ANSI_COLOR_CYAN "/" ANSI_COLOR_MAGENTA "\n");
	printf(ANSI_COLOR_CYAN "//        ARIACORE: GET_NEXT_LINE TESTER        //" ANSI_COLOR_MAGENTA "\n");
	printf(ANSI_COLOR_CYAN "/" ANSI_COLOR_MAGENTA "-============================================-" ANSI_COLOR_CYAN "///" ANSI_COLOR_MAGENTA "\n");
	printf(ANSI_COLOR_RESET);
	printf("\n");

	// if args are passed, use 1st as filename, otherwise use default
	if (ac < 2)
	{
		filename = "file.txt";
		printf(ANSI_COLOR_CYAN "No file given: reading from \"" ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_CYAN "\" default file.\n\n" ANSI_COLOR_RESET, filename);
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
	printf(ANSI_COLOR_CYAN "Reading from \"" ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_CYAN "\":\n\n" ANSI_COLOR_RESET, filename);

	// read file line-by-line; print each line
	line_num = 0;
	while ((line = get_next_line(fd)))
	{
		printf(ANSI_COLOR_CYAN "%i: " ANSI_COLOR_RESET "%s", ++line_num, line);
		free(line);
	}

	// close file and return; check for errors
	if (close(fd) < 0)
	{
		printf("\n");
		perror("Error closing the file");
		exit(1);
	}
	else
	{
		// inform of file closure
		printf(ANSI_COLOR_CYAN "\n\"" ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_CYAN "\" file closed.\n" ANSI_COLOR_RESET, filename);
	}

	return (0);
}
