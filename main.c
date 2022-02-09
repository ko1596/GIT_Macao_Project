#include "gtkService.h"

int main()
{
    int buf;
    
    struct tm *p;

    finish = time(NULL);
    p = localtime(&finish);
    p->tm_hour+=2;
    finish = mktime(p); 

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