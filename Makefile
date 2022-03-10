
DIR = ./Ta5322_V4

CFLAGS = -Wall -Wextra -g
CFLAGS += $(shell pkg-config --cflags json-c --libs gtk+-3.0)
LDFLAGS = $(shell pkg-config --libs json-c --libs gtk+-3.0)
LIBS = -lpthread

TARGET = $(notdir $(CURDIR))

SRC = $(wildcard *.c)
SRC +=	$(DIR)/Ta53M0.c \
		$(DIR)/m0Uart_rx.c \
		$(DIR)/m0Uart_tx.c \
		$(DIR)/ml22q53.c \
		$(DIR)/ml22q53Flash.c \
		$(DIR)/ota_radar.c \
		$(DIR)/ota_chili2s.c


OBJS := $(patsubst %c, %o, $(SRC))

$(TARGET)_test:$(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(LIBS) -o $@ $^ 
%.o:%.c
	$(CC) $(LDFLAGS) $(CFLAGS) $(LIBS) -c -o $@ $< 

.PHONY: clean
clean:
	rm -f $(TARGET)_test *.all *.o
