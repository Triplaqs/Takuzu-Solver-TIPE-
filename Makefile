# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Nom de l'exécutable
TARGET = preuve

# Fichiers sources
SRCS = preuve.c takuzu.c
OBJS = $(SRCS:.c=.o)

# Headers
HEADERS = preuve.h takuzu.h

# Règle par défaut
all: $(TARGET)

# Édition de liens
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation des .c en .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJS) $(TARGET)

# Nettoyage complet
mrproper: clean

# Rebuild complet
re: mrproper all
