CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = main.c ie_parse.c
OBJS = main.o ie_parse.o

TARGET = ie_parse_demo

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c ie_parse.h
	$(CC) $(CFLAGS) -c main.c

ie_parse.o: ie_parse.c ie_parse.h
	$(CC) $(CFLAGS) -c ie_parse.c

clean:
	rm -f $(OBJS) $(TARGET)
