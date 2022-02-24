#include "gtkService.h"

int main()
{
    int buf;
    int sb;
    struct tm *p;

    parkingData[0].parkingStatus = 0;
    parkingData[1].parkingStatus = 1;
    parkingData[2].parkingStatus = 2;
    parkingData[3].parkingStatus = 3;
    parkingData[4].parkingStatus = 3;
    parkingData[5].parkingStatus = 2;
    parkingData[6].parkingStatus = 1;
    parkingData[7].parkingStatus = 0;

    parkingData[0].parkNum = 21;
    parkingData[1].parkNum = 22;
    parkingData[2].parkNum = 23;
    parkingData[3].parkNum = 24;
    parkingData[4].parkNum = 25;
    parkingData[5].parkNum = 26;
    parkingData[6].parkNum = 27;
    parkingData[7].parkNum = 28;

    parkingData[1].deadline = time(NULL);
    p = localtime(&parkingData[1].deadline);
    p->tm_hour+=2;
    p->tm_min+=13;
    parkingData[1].deadline = mktime(p); 

    parkingData[6].deadline = time(NULL);
    p = localtime(&parkingData[6].deadline);
    p->tm_min+=1;
    parkingData[6].deadline = mktime(p); 

    pthread_create(&gtkThread, NULL, run, &widget);
    pthread_create(&serialThread, NULL, UartLoop, NULL);
    
    while(1) {
        printf("------------功能選單------------\n");
        printf("1.啟動讀取條動畫\n");
        printf("2.輸入付款狀態\n");
        printf("3.設定車格狀態\n");
        printf("4.開/關spinner動畫\n");
        printf("輸入功能:\n");
        scanf("%d", &buf);
        
        if(buf == 1) {
            startani(widget.loading_bar);
        }else if(buf == 2) {
            printf("------------付款狀態------------\n");
            printf("1.付款成功\n");
            printf("2.付款失敗\n");
            scanf("%d", &buf);
            paySuccess = buf;
        }else if(buf == 3) {
            
            printf("------------修改車格狀態------------\n");
            printf("請輸入車格號碼: \n");
            scanf("%d", &sb);
            printf("所選車格號碼[%d] \n", sb);
            printf("0.PARKING_STATUS_EMPTY\n");
            printf("1.PARKING_STATUS_DEADLINE\n");
            printf("2.PARKING_STATUS_EXPIRED\n");
            printf("3.PARKING_STATUS_PAYMENT\n");
            
            printf("請輸入要改變的狀態: \n");

            scanf("%d", &buf);
            parkingData[sb].parkingStatus = buf;
            updateParkingData();
        }else if(buf ==4) {
            spinnerStatus = !spinnerStatus;
        }
        
        // setPage(buf);
    }

    return 0;
}