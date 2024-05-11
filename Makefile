CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
TARGET = main
OBJ = obj/main.o obj/afficherChamps.o

$(TARGET): $(OBJ)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

obj/main.o: main.c
    $(CC) $(CFLAGS) -c -o $@ $<

obj/afficherChamps.o: obj/afficherChamps.c
    $(CC) $(CFLAGS) -c -o $@ $<

clean:
    rm -f $(TARGET) $(OBJ)