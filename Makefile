CC=gcc
CFLAGS=-Werror -Wextra -Wall -O2 -fPIC -Iinclude -Ilibft
LDFLAGS=-shared -pthread -Llibft -lft
HOSTTYPE ?= $(shell uname -m)_$(shell uname -s)
TARGET=libft_malloc_$(HOSTTYPE).so

SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)

all: libft/libft.a $(TARGET) symlink

libft/libft.a:
	$(MAKE) -C libft
	$(MAKE) -C libft bonus

%.o: %.c
	$(CC) -g $(CFLAGS) -c $< -o $@

$(TARGET): libft/libft.a $(OBJS)
	$(CC) -g $(LDFLAGS) -o $@ $(OBJS)

symlink:
	ln -sf $(TARGET) libft_malloc.so

clean:
	rm -f $(OBJS) $(TARGET) libft_malloc.so
	$(MAKE) -C libft clean

re:
	make clean
	make

.PHONY: all clean symlink re