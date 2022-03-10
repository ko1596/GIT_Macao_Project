#include "M0Service.h"

int m0ServiceInit(void) {
    fd_uartA53M0 = open(dev_UART_A53M0, O_RDWR | O_NOCTTY | O_NDELAY);

    if(fd_uartA53M0 == -1)
	{
		printf("[%s] xxxx   open Error   xxxx \n", dev_UART_A53M0);
		return -1;
	}
    else
	{
		printf("[%s] Open Success ============\n", dev_UART_A53M0);
	
		if(flock(fd_uartA53M0, LOCK_EX | LOCK_NB) == 0)
		{
			struct termios uart_settings;
			tcgetattr(fd_uartA53M0, &uart_settings);
			bzero(&uart_settings, sizeof(uart_settings));
			uart_settings.c_cflag = UARTA53M0_SPEED | CS8 | CLOCAL | CREAD;
			uart_settings.c_iflag = IGNPAR;
			uart_settings.c_oflag = 0;
			uart_settings.c_lflag = 0;
			uart_settings.c_cc[VTIME] = 0;
			uart_settings.c_cc[VMIN] = 1;

			cfsetispeed(&uart_settings, UARTA53M0_SPEED);
			cfsetospeed(&uart_settings, UARTA53M0_SPEED);
			tcsetattr(fd_uartA53M0, TCSANOW, &uart_settings);
		
		}
		else
		{
			printf("XXXXXXXX [%s] was locked by other process.\n", dev_UART_A53M0);
			return -1;
		}
	}

    A53M0_gpio_Init();

   	//==================================================================
	//  Create A53 rpmsg rx
	//==================================================================
	pthread_create(&thread_A53_awake, NULL, (void*)&A53_awake_thread, &fd_uartA53M0);

	//==================================================================
	//  Create A53 rpmsg rx
	//==================================================================
	pthread_create(&thread_uartA53M0_Rx, NULL, (void*)&uartA53M0_Rx_thread, &fd_uartA53M0);

	//==================================================================
	//  Create A53 rpmsg Tx
	//==================================================================
	pthread_create(&thread_uartA53M0_Tx, NULL, (void*)&uartA53M0_Tx_thread, &fd_uartA53M0);

	//==================================================================
	//  Create A53  WiFi AP check
	//==================================================================
	// pthread_create(&thread_wifiAP_ck, NULL, (void*)&wifiAP_ck_thread, NULL);

	//================================================================
	//  Create A53  ML22Q53, Voice play
	//==================================================================
	pthread_create(&thread_ml22_PlayStart, NULL, (void*)&ml22_PlayStart_thread, NULL );

	//==================================================================
	//  Radar OTA
	//==================================================================
	pthread_create(&thread_Radar_OTA, NULL, (void*)&Radar_OTA_thread, NULL);


	//==================================================================
	//  Radar OTA
	//==================================================================
	pthread_create(&thread_Chili2s_OTA, NULL, (void*)&Chili2s_OTA_thread, NULL);

    uartA53M0_REQM0_SystemInfo();

    return 0;
}