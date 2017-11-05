OBJS = $(patsubst %.c,%.o,$(wildcard *.c))
CFLAGS = -std=c99 -Wall -Werror --pedantic -I../include 
CC = gcc
NAME = cquest
all: $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -lncurses
clean:
	rm -f $(OBJS)
fclean:
	rm -f $(OBJS) $(NAME)
re:
	make fclean all
