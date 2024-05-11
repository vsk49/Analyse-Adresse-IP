CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
TARGET = main
SRCS = src/main.c src/afficherChamps.c src/verificationFormat.c src/extraireChampsIP.c
OBJS = $(SRCS:src/%.c=obj/%.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)