CC=gcc
CFLAGS=-Werror -Wextra -Wall -O2 -fPIC -Iinclude
LDFLAGS=-shared -pthread
HOSTTYPE ?= $(shell uname -m)_$(shell uname -s)
TARGET=libft_malloc_$(HOSTTYPE).so

SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)

all: $(TARGET) symlink

%.o: %.c
	$(CC) -g $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) -g $(LDFLAGS) -o $@ $^

symlink:
	ln -sf $(TARGET) libft_malloc.so

clean:
	rm -f $(OBJS) $(TARGET) libft_malloc.so

re:
	make clean
	make

.PHONY: all clean symlink re