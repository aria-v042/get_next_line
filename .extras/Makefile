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

SRCS_DIR = .
SRCS = $(shell find $(SRCS_DIR) -maxdepth 1 -name '*.c')
OBJS = $(SRCS:.c=.o)

DEBUG_SRC ?= $(or $(filter %.c, $(MAKECMDGOALS)), test.c)
DEBUG_OUT = debug

ifneq ($(filter %.c, $(MAKECMDGOALS)),)
	%.c: ;
endif

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

debug:
	$(CC) $(CDEBUGFLAGS) $(DEBUG_SRC) -o $(DEBUG_OUT)

clean:
	rm -f $(NAME) $(DEBUG_OUT)

re: clean all

.PHONY: all debug clean re
