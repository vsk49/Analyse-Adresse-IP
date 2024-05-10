CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = main
SRCS = main.c verificationFormat/verificationFormat.c extractionChamps/extraireChampsIP.c affichageChamps/afficherChamps.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $@ $^

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS) $(TARGET)

.PHONY: all clean