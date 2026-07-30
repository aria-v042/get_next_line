# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frodrig2 <frodrig2@students.42porto.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/17 20:24:03 by frodrig2          #+#    #+#              #
#    Updated: 2026/06/17 21:35:46 by frodrig2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test_gnl
ROOT = ..

CC = cc
ifdef BUFFER_SIZE
	COPTS = -DBUFFER_SIZE=$(BUFFER_SIZE)
endif
CFLAGS = -Wall -Wextra -Werror -I$(ROOT) $(COPTS)
CDEBUGFLAGS = -Wall -Wextra -g -I$(ROOT) $(COPTS)

SRCS_DIR = $(ROOT)
SRCS = $(shell find $(SRCS_DIR) -maxdepth 1 -name '*.c' -not -name '*bonus.c')

TEST_SRC = test.c

ifneq ($(filter %.c, $(MAKECMDGOALS)),)
	%.c: ;
endif

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) $(TEST_SRC) -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all clean re
