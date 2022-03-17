#include <stdlib.h>
#include "gtkService.h"

int main(int argc, char **argv)
{
    // int buf;
    // int sb;
    int ret;

    long arg = strtol(argv[1], NULL, 10);
    long ar2 = strtol(argv[2], NULL, 10);
    printf("\n%d\n%d\n",(int) arg, (int) ar2);
    ret = settingFrameRate((int) arg);
    if (ret != 0) return -1;
    ret = settingHoverTime((int) ar2);
    if (ret != 0) return -1;
    pthread_create(&gtkThread, NULL, run, NULL);
    m0ServiceInit();

    pthread_join(gtkThread, NULL);
    // pthread_create(&serialThread, NULL, UartLoop, NULL);
    
    // while(1) {
    //     printf("------------功能選單------------\n");

    //     printf("1.輸入付款狀態\n");
    //     printf("2.設定車格狀態\n");
    //     printf("輸入功能:\n");
    //     scanf("%d", &buf);
        
    //     if(buf == 1) {
    //         printf("------------付款狀態------------\n");
    //         printf("0.付款成功\n");
    //         printf("1.付款失敗\n");
    //         scanf("%d", &buf);
    //         changePaySuccess(buf);
    //     }else if(buf == 2) {
            
    //         printf("------------修改車格狀態------------\n");
    //         printf("請輸入車格號碼: \n");
    //         scanf("%d", &sb);
    //         printf("所選車格號碼[%d] \n", sb);
    //         printf("0.PARKING_STATUS_EMPTY\n");
    //         printf("1.PARKING_STATUS_DEADLINE\n");
    //         printf("2.PARKING_STATUS_EXPIRED\n");
    //         printf("3.PARKING_STATUS_PAYMENT\n");
            
    //         printf("請輸入要改變的狀態: \n");

    //         scanf("%d", &buf);
    //         changeParingStatus(sb, buf);
    //     }
        
        // setPage(buf);
    // }

    return 0;
}