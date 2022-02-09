#include "gtkService.h"

int main()
{
    int buf;
    
    pthread_create(&gtkThread, NULL, run, &widget);
    pthread_create(&serialThread, NULL, UartLoop, NULL);
    
    while(1) {
        printf("請輸入數字：");
        scanf("%d", &buf);
        startani(widget.loading_bar);
        // setPage(buf);
    }

    return 0;
}