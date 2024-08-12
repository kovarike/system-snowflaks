CC = gcc
CFLAGS = -Wall -g

# Nome do alvo principal
TARGET = snowflaks

# Arquivos fonte e objetos
SRCS = src/main.c src/uuid/uuid.c src/ip/ip.c src/crypto/crypto.c
OBJS = $(SRCS:.c=.o)

# Alvo principal
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regras para compilar os arquivos de objeto
src/main.o: src/main.c
	$(CC) $(CFLAGS) -c -o src/main.o src/main.c

src/uuid/uuid.o: src/uuid/uuid.c
	$(CC) $(CFLAGS) -c -o src/uuid/uuid.o src/uuid/uuid.c

src/ip/ip.o: src/ip/ip.c
	$(CC) $(CFLAGS) -c -o src/ip/ip.o src/ip/ip.c

src/crypto.o: src/crypto/crypto.c src/crypto/crypto.h
	$(CC) $(CFLAGS) -c -o src/crypto/crypto.o src/crypto/crypto.c

# Regra para limpar arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)
