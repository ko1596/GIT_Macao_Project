#include "gtkService.h"

int main()
{
    int buf;
    
    struct tm *p;

    finish = time(NULL);
    p = localtime(&finish);
    p->tm_hour+=2;
    finish = mktime(p); 

    parkingData[0].parkingStatus = 0;
    parkingData[1].parkingStatus = 1;
    parkingData[2].parkingStatus = 2;
    parkingData[3].parkingStatus = 3;
    parkingData[4].parkingStatus = 3;
    parkingData[5].parkingStatus = 2;
    parkingData[6].parkingStatus = 1;
    parkingData[7].parkingStatus = 0;

    parkingData[1].deadline = time(NULL);
    p = localtime(&parkingData[1].deadline);
    p->tm_hour+=2;
    parkingData[1].deadline = mktime(p); 

    parkingData[6].deadline = time(NULL);
    p = localtime(&parkingData[6].deadline);
    p->tm_hour+=1;
    parkingData[6].deadline = mktime(p); 

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