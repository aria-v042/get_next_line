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

BONUS_NAME = test_gnl_bonus
BONUS_DIR = $(ROOT)
BONUS_SRCS = $(shell find $(BONUS_DIR) -maxdepth 1 -name '*bonus.c')

TEST_SRC = test.c

DEBUG_SRC ?= $(or $(filter %.c, $(MAKECMDGOALS)), $(TEST_SRC))
DEBUG_OUT = debug

ifneq ($(filter %.c, $(MAKECMDGOALS)),)
	%.c: ;
endif

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) $(TEST_SRC) -o $(NAME)

bonus:
	$(CC) $(CFLAGS) $(BONUS_SRCS) $(TEST_SRC) -o $(BONUS_NAME)

debug:
	$(CC) $(CDEBUGFLAGS) $(SRCS) $(DEBUG_SRC) -o $(DEBUG_OUT)

clean:
	rm -f $(NAME) $(BONUS_NAME) $(DEBUG_OUT)

re: clean all

.PHONY: all bonus debug clean re
