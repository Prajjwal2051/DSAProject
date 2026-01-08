CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
TARGET = task_scheduler
SRC_DIR = src
INC_DIR = include
OBJS = main.o task.o linked_list.o queue.o priority_queue.o scheduler.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c $(INC_DIR)/scheduler.h
	$(CC) $(CFLAGS) -c main.c

task.o: $(SRC_DIR)/task.c $(INC_DIR)/task.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/task.c

linked_list.o: $(SRC_DIR)/linked_list.c $(INC_DIR)/linked_list.h $(INC_DIR)/task.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/linked_list.c

queue.o: $(SRC_DIR)/queue.c $(INC_DIR)/queue.h $(INC_DIR)/task.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/queue.c

priority_queue.o: $(SRC_DIR)/priority_queue.c $(INC_DIR)/priority_queue.h $(INC_DIR)/task.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/priority_queue.c

scheduler.o: $(SRC_DIR)/scheduler.c $(INC_DIR)/scheduler.h $(INC_DIR)/task.h $(INC_DIR)/queue.h $(INC_DIR)/priority_queue.h $(INC_DIR)/linked_list.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/scheduler.c

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
