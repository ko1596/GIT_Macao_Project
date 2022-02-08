
#include "serialService.h"

void initQueue(void) {
	front = NULL;
	tail = NULL;
	commandState = 0;
	count = 0;
	blockCount = 0;
}

int initUart(int *fd) {
	*fd = open(UART_TOUCHPAD, O_RDWR); //讀寫模式開啟
	if (*fd < 0)
	{
		printf("Can't open device %s.\n", UART_TOUCHPAD);
		return -1;
	}

	set_interface_attribs(*fd, B115200, 0); // set speed to 115,200 bps, 8n1 (no parity)
	set_blocking(*fd, 0);				   // set no blockin

	usleep((7 + 25) * 100); // sleep enough to transmit the 7 plus
							// receive 25:  approx 100 uS per char transmit
	return 0;
}

void push(uint8_t data)
{
	Queue_Node *new_add_node;
	new_add_node = (Queue_Node *)malloc(sizeof(struct Node));
	
	new_add_node->data = data;
	new_add_node->next = NULL;

	if (tail == NULL||front==NULL)
	{
		front = new_add_node;
	}		
	else
		tail->next = new_add_node;
	
	
	tail = new_add_node;
}

uint8_t pop()
{
	Queue_Node *pt = front;
	uint8_t i = front->data;
	front = front->next;
	free(pt);
	return i;
}

int set_interface_attribs(int fd, int speed, int parity)
{
	struct termios tty;
	if (tcgetattr(fd, &tty) != 0)
	{
		return 1;
	}

	cfsetospeed(&tty, speed);
	cfsetispeed(&tty, speed);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit chars
	// disable IGNBRK for mismatched speed tests; otherwise receive break
	// as \000 chars
	tty.c_iflag &= ~IGNBRK; // disable break processing
	tty.c_lflag = 0;		// no signaling chars, no echo,
							// no canonical processing
	tty.c_oflag = 0;		// no remapping, no delays
	tty.c_cc[VMIN] = 0;		// read doesn't block
	tty.c_cc[VTIME] = 5;	// 0.5 seconds read timeout

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

	tty.c_cflag |= (CLOCAL | CREAD);   // ignore modem controls,
									   // enable reading
	tty.c_cflag &= ~(PARENB | PARODD); // shut off parity
	tty.c_cflag |= parity;
	tty.c_cflag &= ~CSTOPB;
	// tty.c_cflag &= ~CRTSCTS;

	if (tcsetattr(fd, TCSANOW, &tty) != 0)
	{
		return 1;
	}
	return 0;
}

int set_blocking(int fd, int should_block)
{
	struct termios tty;
	memset(&tty, 0, sizeof tty);
	if (tcgetattr(fd, &tty) != 0)
		return 1;

	tty.c_cc[VMIN] = should_block ? 1 : 0;
	tty.c_cc[VTIME] = 5; // 0.5 seconds read timeout

	if (tcsetattr(fd, TCSANOW, &tty) != 0)
		return 1;

	return 0;
}

void readTouchpad(int fd) {
	int res;
	uint8_t rx_buffer[BUFFER_SIZE];

	res = read(fd, rx_buffer, BUFFER_SIZE);

	for (int i = 0; i < res; i++)
		push(rx_buffer[i]);
}

void processBlockData(void) {
	u_int8_t dataCommand;

	while (front != NULL) {
		dataCommand = pop();
		switch (commandState)
		{
			case 0:
				sortBlocks();
				if(dataCommand == 0x12) commandState = 1;
				break;
			case 1:
				if(dataCommand == 0x34) commandState = 2;
				break;
			case 2:
				if(count%2 == 0)
				{
					unsorted_block[blockCount] = dataCommand;
				}						
				else
				{
					unsorted_block[blockCount] |= (dataCommand << 8);
					blockCount++;
				}

				count++;
				if(count == 48)
				{
					count = 0;
					commandState = 0;
					blockCount = 0;
				}
				break;

			default:
				break;
		}
	}
}

void *UartLoop(void *parm)
{
	int fd;
	
	initUart(&fd);

	while (1)
	{
		readTouchpad(fd);
		processBlockData();
	}

	close(fd);
	return 0;
}

void sortBlocks() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			block[i * 4 + j] = unsorted_block[(5 - i) + 6 * j];
		}
	}
}