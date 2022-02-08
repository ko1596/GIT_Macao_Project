CFLAGS = -Wall -Wextra -g 
TARGET = $(notdir $(CURDIR))
objs := $(patsubst %c, %o, $(shell ls *.c))
$(TARGET)_test:$(objs)
	$(CC) $(CFLAGS) -lpthread -o $@ $^ `pkg-config --cflags --libs gtk+-3.0`
%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $< `pkg-config --cflags --libs gtk+-3.0`
clean:
	rm -f $(TARGET)_test *.all *.o
