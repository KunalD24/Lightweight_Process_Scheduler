CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g -D_XOPEN_SOURCE=700
SRCS = src/context.c src/scheduler.c src/thread.c src/timer.c src/main.c
OBJS = $(SRCS:.c=.o)
TARGET = lightweight_scheduler

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)	