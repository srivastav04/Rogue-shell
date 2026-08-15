CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = shell

SRC = src/main.c \
      src/parser.c \
      src/executor.c \
	  src/history.c \
      src/builtin.c

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)