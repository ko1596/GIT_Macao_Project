
###export PKG_CONFIG_PATH+=/usr/local/lib/pkgconfig
###export ARCH+=arm64
###export CROSS_COMPILE+=/usr/bin/aarch64-linux-gnu-gcc
###export JSON_C_DIR+=/usr/local/

PWD = $(shell pwd)
##SRC = testjsonc.c

TARGET = Ta5322_V4

####CC=aarch64-linux-gnu-gcc
#CC=gcc

##CFLAGS += $(--cflags json-c)
##LDFLAGS += $(--libs json-c)
CFLAGS += $(shell pkg-config --cflags json-c --libs gtk+-3.0)
LDFLAGS += $(shell pkg-config --libs json-c --libs gtk+-3.0)
LDFLAGS += -pthread


OBJS = 	./Ta5322_V4.o \
				./Ta53M0.o \
				./m0Uart_rx.o \
				./m0Uart_tx.o \
				./ml22q53.o \
				./ml22q53Flash.o \
				./getDcuParam.o \
				./ota_radar.o \
				./ota_chili2s.o \
				./gtkService.o \
				./Tst2.o \
				./TstA53M0.o


all: $(OBJS) $(TARGET)

$(TARGET): 
	$(CC) $(OBJS) $(LDFLAGS) $(CFLAGS) -o $@ 

clean:
	rm -f $(TARGET) *.elf *.gdb *.o
	rm -f $(OBJS)
