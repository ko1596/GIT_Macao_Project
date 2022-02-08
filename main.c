#include "gtkService.h"

int main(int argc, char *argv[])
{
    int buf;
    pthread_create(&gtkThread, NULL, run, NULL);
    pthread_create(&serialThread, NULL, UartLoop, NULL);
    
    while(1) {
        printf("請輸入數字：");
        scanf("%d", &buf);
        // setPage(buf);
    }

    return 0;
}