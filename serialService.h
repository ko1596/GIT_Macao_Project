#ifndef SERIAL_SERVICE_H
#define SERIAL_SERVICE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <termios.h> // POSIX terminal control definitions
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 2048
#define UART_SPEED B1152000
#define UART_TOUCHPAD "/dev/ttyACM0"

struct Node
{
	uint8_t data;
	struct Node *next;
};

typedef struct Node Queue_Node;

Queue_Node *front;
Queue_Node *tail;
u_int16_t block[24];
u_int16_t unsorted_block[24];

pthread_t serialThread;

int commandState;
int count;
int blockCount;

void initQueue(void);

int initUart(int*);

void push(uint8_t);

uint8_t pop(void);

int set_interface_attribs(int, int, int);

int set_blocking(int, int);

void readTouchpad(int);

void processBlockData(void);

void *UartLoop(void *);

void sortBlocks(void);

#endif /*SERIAL_SERVICE_H*/