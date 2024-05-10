CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = main
SRCS = main.c verificationFormat/verificationFormat.c extractionChamps/extraireChampsIP.c affichageChamps/afficherChamps.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)
    $(CC) -o $(TARGET) $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
    $(CC) -o $(SRCS)

affichageChamps/afficherChamps.c : affichageChamps/afficherChamps.h extractionChamps/extraireChampsIP.h 
    verificationFormat/verificationFormat.h
    $(CC) -c affichageChamps/afficherChamps.c

extractionChamps/extraireChampsIP.c : extractionChamps/extraireChampsIP.h verificationFormat/verificationFormat.h
    $(CC) -c extractionChamps/extraireChampsIP.c

verificationFormat/verificationFormat.c : verificationFormat/verificationFormat.h
    $(CC) -c verificationFormat/verificationFormat.c

clean:
    rm -f $(OBJS) $(TARGET)