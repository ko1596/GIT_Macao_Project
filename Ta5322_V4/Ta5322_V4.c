

//	******************************************************************
//		Ta5321_ALL
//	******************************************************************

#include "m0All_Header.h"



//====================================================================
extern  	int  		Tst_Auto_Sleep_Enable;




//********************************************************************
//
//********************************************************************
int main( int argc, char *argv[] )
{ 
  //unsigned char   wBuf[1024];
  //signal(SIGCHLD, SIG_IGN);

  int   pw_tst_period = 30;


  a53m0API_currentTime = time( NULL);
  a53m0API_current_tm = localtime (&a53m0API_currentTime);
  printf( "\n" );
  printf( "          [%s]  ---   %02d/%02d/%02d %02d:%02d:%02d   [%s] \n", 
  			dev_UART_A53M0, 
				((a53m0API_current_tm->tm_year+1900)-2000),
				a53m0API_current_tm->tm_mon + 1,
				a53m0API_current_tm->tm_mday,
				a53m0API_current_tm->tm_hour,
				a53m0API_current_tm->tm_min,
				a53m0API_current_tm->tm_sec,
  			FwVer_Ta53m0_API );
  printf( "\n" );


  printf( "argv[1]=[%s]\n", argv[1] );    //  =1, Correction time
  int flg_CorrectionTime = 0;
  if( argv[1] != NULL ) {
  	flg_CorrectionTime = atoi( argv[1] );
  	if( flg_CorrectionTime != 0 )	{
  		flg_CorrectionTime = 1;
  	}
  }

  printf( "argv[2]=[%s]\n", argv[2] );
	if( argv[2] != NULL ) {
  	pw_tst_period = atoi( argv[2] );  	
  	if( pw_tst_period == 0 )		{
  		pw_tst_period = 30;
  	}
  	printf( "pw_tst_period = [%d] \n", pw_tst_period );
  }



  //==================================================================
  unsigned char 	fname_folder[64];  
  bzero( fname_folder, 64 );
  /*
  sprintf( fname_folder, "mkdir ./TL_SAM" );
  system( fname_folder );
  bzero( fname_folder, 64 );
  sprintf( fname_folder, "chmod 777 -R ./TL_SAM" );
  system( fname_folder );

  bzero( fname_folder, 64 );
  sprintf( fname_folder, "mkdir ./radar" );
  system( fname_folder );

  bzero( fname_folder, 64 );
  sprintf( fname_folder, "chmod 777 -R ./radar" );
  system( fname_folder );
  */
	sprintf( fname_folder, "mkdir /home/root/grids/EPM/firmware/tl_sam" );
	system( fname_folder );
	bzero( fname_folder, 64 );
	sprintf( fname_folder, "chmod 777 -R /home/root/grids/EPM/firmware/tl_sam" );
	system( fname_folder );

	bzero( fname_folder, 64 );
	sprintf( fname_folder, "mkdir /home/root/grids/EPM/firmware/radar" );
	system( fname_folder );

	bzero( fname_folder, 64 );
	sprintf( fname_folder, "chmod 777 -R /home/root/grids/EPM/firmware/radar" );
	system( fname_folder );


  ftime( &time_prgStart );
  //system( "date > /home/root/Ta53Step" );







  //******************************************************************
	//******************************************************************
	//	A53_M0 API 		Start
	//******************************************************************

  //==================================================================
  //	open UART port  
  //==================================================================
  //fd_uartA53M0 = open( dev_UART_A53M0, O_RDWR | O_NOCTTY | O_NDELAY );
  //fd_uartA53M0 = open( dev_UART_A53M0, O_RDWR | O_NONBLOCK );
  fd_uartA53M0 = open( dev_UART_A53M0, O_RDWR );
  
  if(fd_uartA53M0 == -1){
    printf( "[%s]  xxxxx    open Error    xxxxx \n", dev_UART_A53M0 );
    return -1;
  }
  else {
    printf( "[%s]  open Success ======================================== \n", dev_UART_A53M0 );

    if(flock( fd_uartA53M0, LOCK_EX | LOCK_NB )==0)  {

	    struct termios uart_settings;
	    tcgetattr(fd_uartA53M0, &uart_settings);
	    //bzero(&uart_settings, sizeof(uart_settings));
	    uart_settings.c_cflag = UARTA53M0_SPEED | CS8 | CLOCAL | CREAD;
	    uart_settings.c_iflag = IGNPAR;
	    uart_settings.c_oflag = 0;
	    uart_settings.c_lflag = 0;
	    uart_settings.c_cc[VTIME] = 0;
	    //uart_settings.c_cc[VMIN] = 1;
	    uart_settings.c_cc[VMIN] = 0;

			cfsetispeed(&uart_settings,UARTA53M0_SPEED);
			cfsetospeed(&uart_settings,UARTA53M0_SPEED);
			
	    tcsetattr(fd_uartA53M0, TCSANOW, &uart_settings);
	    tcflush(fd_uartA53M0, TCIFLUSH);

    } 	//if(flock( fd_uartA53M0, LOCK_EX | LOCK_NB )==0)  {
    else	{
    	printf("XXXXXXXXXXXXXXXXXXX [%s]] was locked by other process.\n", dev_UART_A53M0 );
    	return -1;
    }

  } 	//if(fd_uartA53M0 == -1){				else


	A53M0_gpio_Init( );

	//sleep( 5 );

	//==================================================================
	//  gtk
	//==================================================================
	pthread_create(&gtkThread, NULL, run, NULL);
	//pthread_create(&serialThread, NULL, UartLoop, NULL);



	//==================================================================
	//  Create A53 rpmsg rx
	//==================================================================
	pthread_create(&thread_A53_awake, NULL, (void*)&A53_awake_thread, &fd_uartA53M0);


	//==================================================================
	//  Create A53 rpmsg rx
	//==================================================================
	pthread_create(&thread_uartA53M0_Rx, NULL, (void*)&uartA53M0_Rx_thread, &fd_uartA53M0);
	usleep( 10000 );


	//==================================================================
	//  Create A53 rpmsg Tx
	//==================================================================
	pthread_create(&thread_uartA53M0_Tx, NULL, (void*)&uartA53M0_Tx_thread, &fd_uartA53M0);
	usleep( 10000 );


	//==================================================================
	//  Create A53  WiFi AP check
	//==================================================================
	pthread_create(&thread_wifiAP_ck, NULL, (void*)&wifiAP_ck_thread, NULL);
	usleep( 10000 );


	//================================================================
	//  Create A53  ML22Q53, Voice play
	//==================================================================
	usleep( 5000 );
	pthread_create(&thread_ml22_PlayStart, NULL, (void*)&ml22_PlayStart_thread, NULL );
	usleep( 10000 );


	//==================================================================
	//  Radar OTA
	//==================================================================
	pthread_create(&thread_Radar_OTA, NULL, (void*)&Radar_OTA_thread, NULL);
	usleep( 10000 );


	//==================================================================
	//  Radar OTA
	//==================================================================
	pthread_create(&thread_Chili2s_OTA, NULL, (void*)&Chili2s_OTA_thread, NULL);
	usleep( 10000 );





  //	Test 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  printf( "\n\n  !!!!!  Test Thread  !!!!!\n\n" );

	pthread_create(&thread_tcp_Cmd, NULL, (void*)&Tst_tcp_cmd_thread, NULL);
	usleep( 100000 );


  //  Debug port Keyboard Input
	pthread_create(&thread_Keyboard_input, NULL, (void*)&Keyboard_input_thread, NULL);
	usleep( 100000 );

	//pthread_create(&thread_TST_LCD_LED, NULL, (void*)&Tst_ePaper_backLED_thread, NULL);
	//usleep( 100000 );

	//pthread_create(&thread_Test01, NULL, (void*)&Test01_thread, NULL);
	//usleep( 100000 );

	//pthread_create(&thread_Play_Voice, NULL, (void*)&Play_Voice_thread, NULL);
	//usleep( 100000 );

	//pthread_create(&thread_TST_SLEEP, NULL, (void*)&Tst_Sleep_thread, NULL);
	//usleep( 100000 );

	//pthread_create(&thread_Test2, NULL, (void*)&Test2_thread, NULL);
	//usleep( 100000 );


	//pthread_create(&thread_FrameBuffer, NULL, (void*)&Framebuffer_Tst_thread, NULL);
	//usleep( 100000 );

	#if  	TST_AUTO_SLEEP
		Tst_Auto_Sleep_Enable = 0;
		pthread_create(&thread_auto_sleep, NULL, (void*)&Tst_auto_sleep_thread, NULL);
		usleep( 100000 );
	#endif  		//#if  	TST_AUTO_SLEEP

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	#if  	Tst_CK_SYSTEM_SLEEP
		system( "echo \"\" >> /home/root/sleeplog" );
		system( "echo \"Ta5322_V4 program Start ===== ===== =====\" >> /home/root/sleeplog" );
		system( "date >> /home/root/sleeplog");
	#endif  		//#if  	Tst_CK_SYSTEM_SLEEP


  //******************************************************************
	//	A53_M0 API 		END
	//******************************************************************
	//******************************************************************


	uartA53M0_Set_M0_A53Status_Awake( );









  sleep( 1 );
  //------------------------------------------------------------------
  if( flg_CorrectionTime )  	{
	  uartA53M0_SetM0_currentRTC( );
	  //sleep( 1 );  	
  }

	//	TEST 		--------------------------------------------------------
	//	TL-SAM 		Encryption
	/*
	uint8_t 	dcu_fName[64];
	uint8_t 	dcu_Data[1024];

  a53m0API_currentTime = time( NULL);
  a53m0API_current_tm = localtime (&a53m0API_currentTime);
  sprintf( dcu_fName, "./TL_SAM/Enc%02d%02d%02d%02d%02d%02d",
				((a53m0API_current_tm->tm_year+1900)-2000),
				a53m0API_current_tm->tm_mon + 1,
				a53m0API_current_tm->tm_mday,
				a53m0API_current_tm->tm_hour,
				a53m0API_current_tm->tm_min,
				a53m0API_current_tm->tm_sec );

  for( int i=0 ; i<1000 ; i++ )		{
  	dcu_Data[i] = i+0x11;
  }
  uartA53M0_TLSAM_Encrypt( (uint8_t*)dcu_fName, (uint8_t*)dcu_Data, 16 );
  */
  sleep( 1 );



  	//------------------------------------------------------------------
	//	TEST 		--------------------------------------------------------
	//uartA53M0_Get_Radar_FWver( );

	//	TEST 		--------------------------------------------------------
	//	Set Radar-A/B parameter
	//uartA53M0_update_Radar_parameter( );
	//sleep( 1 );


  //	TEST 		--------------------------------------------------------
  printf("\n");
  //uartA53M0_Set_Chili2S_PAN_ADD( 0x3333, 0x0000, 16 );
  uartA53M0_REQM0_SystemInfo( );
  //sleep( 1 );


	#if 	TST_TxRx_COUNT
		Tst_Tx_Cnt = 0;
		Tst_Rx_Cnt = 0;
	#endif 	//#if 	TST_TxRx_COUNT
  //******************************************************************
  //	Waiting thread
  //******************************************************************
	//sleep( 1 );

	//uartA53M0_REQM0_Temp( );
	//uartA53M0_REQM0_Power( );
	//uartA53M0_REQM0_G_Sensor( );
	//uartA53M0_Req_Radar_Status( );
	A53_CK_wifiAP_Enable = 0;
	usleep( 500000 );   //  500ms

	printf( "\n ========== ========== while( 1 ) ========== ========== \n\n");

	struct timeb  	time_T11;
	struct timeb  	time_T12;

	struct timeb  	time_T21;
	struct timeb  	time_T22;
	//struct timeb  	time_T31;
	//struct timeb  	time_T32;

	ftime( &time_T11 );
	ftime( &time_T21 );
	//ftime( &time_T31 );
	int  	Bat_cnt = 0;

	int 	Tst_cnt_sleep_Start = 0;  
  while( 1 )  {
	  //----------------------------------------------------------------
	  //usleep(  15000 );   //  15ms
	  //usleep(  25000 );   //  25ms
	  //usleep(  50000 );   //  50ms
	  //usleep(  75000 );   //  75ms
	  //usleep( 90000 );   //  90ms
	  //usleep( 100000 );   //  100ms
	  //usleep( 120000 );   //  120ms
	  //usleep( 150000 );   //  150ms
	  usleep( 200000 );   //  200ms
	  //usleep( 500000 );   //  500ms

  	//sleep(1);
  	//sleep(2);
  	//sleep(3);
    //sleep(5);
    //sleep(10);
    //sleep(20);
  	//sleep(30);
    //sleep(60); 		//	1min
    //sleep(600);		//	10min

	  //	Test !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	  ftime( &time_T12 );
	  ftime( &time_T22 );
	  //ftime( &time_T32 );
	  //printf( "  %d  \n", ((time_T12.time*1000)+time_T12.millitm)-((time_T11.time*1000)+time_T11.millitm) );

	  //==========================================================================
	  //	Loop 1
	  //if( ((time_T12.time*1000)+time_T12.millitm)-((time_T11.time*1000)+time_T11.millitm) >  (60000 *30) )		{  		//	1min * 30
	  //if( ((time_T12.time*1000)+time_T12.millitm)-((time_T11.time*1000)+time_T11.millitm) >  (60000 *10) )		{  		//	1min * 10
	  if( ((time_T12.time*1000)+time_T12.millitm)-((time_T11.time*1000)+time_T11.millitm) >  60000 )		{  		//	60sec
	  //if( ((time_T12.time*1000)+time_T12.millitm)-((time_T11.time*1000)+time_T11.millitm) >  30000 )		{  		//	30sec
	  //if( ((time_T12.time*1000)+time_T12.millitm)-((time_T11.time*1000)+time_T11.millitm) >  20000 )		{  		//	20sec
	  //if( ((time_T12.time*1000)+time_T12.millitm)-((time_T11.time*1000)+time_T11.millitm) >  10000 )		{  		//	10sec
	  //if( ((time_T12.time*1000)+time_T12.millitm)-((time_T11.time*1000)+time_T11.millitm) >  5000 )		{  		//	5sec
	  //if( ((time_T12.time*1000)+time_T12.millitm)-((time_T11.time*1000)+time_T11.millitm) >  2000 )		{  		//	2sec
	  //if( ((time_T12.time*1000)+time_T12.millitm)-((time_T11.time*1000)+time_T11.millitm) >  1000 )		{  		//	1sec
	  //if( ((time_T12.time*1000)+time_T12.millitm)-((time_T11.time*1000)+time_T11.millitm) >  500 )		{  		//	0.5sec
	  	time_T11 = time_T12;

	  	//uartA53M0_REQM0_Temp( );

	  	/*
	  	if( OTA_Radar.cmd != RADAR_OTACMD_NOTHING )		{
				uartA53M0_REQM0_Power( );
				//usleep( 10000 );  	//	10ms
				
				uartA53M0_REQM0_G_Sensor( );
				//usleep( 10000 );  	//	10ms

				//uartA53M0_Req_Radar_Status( );

				uartA53M0_REQM0_SystemInfo( );
				//usleep( 10000 );  	//	10ms

				uartA53M0_REQM0_Temp( );
				//usleep( 10000 );  	//	10ms
			}
			*/


	  	//	Battery Cahnge 		------------------------------------------	  	
	  	/*
	  	if( Bat_cnt > 0 )		{
	  		uartA53M0_Set_Bat_Source( 0 );
	  		Bat_cnt = 0;
	  	}
	  	else 	{
	  		uartA53M0_Set_Bat_Source( 1 );
	  		Bat_cnt++;
	  	}
	  	*/

	  }

	  //==========================================================================
	  //	Loop 2
	  //if( ((time_T22.time*1000)+time_T22.millitm)-((time_T21.time*1000)+time_T21.millitm) >  30000 )		{  		//	30sec
	  //if( ((time_T22.time*1000)+time_T22.millitm)-((time_T21.time*1000)+time_T21.millitm) >  20000 )		{  		//	20sec
	  //if( ((time_T22.time*1000)+time_T22.millitm)-((time_T21.time*1000)+time_T21.millitm) >  10000 )		{  		//	10sec
	  //if( ((time_T22.time*1000)+time_T22.millitm)-((time_T21.time*1000)+time_T21.millitm) >  5000 )		{  		//	5sec
	  //if( ((time_T22.time*1000)+time_T22.millitm)-((time_T21.time*1000)+time_T21.millitm) >  3000 )		{  		//	3sec
	  //if( ((time_T22.time*1000)+time_T22.millitm)-((time_T21.time*1000)+time_T21.millitm) >  2000 )		{  		//	2sec
	  //if( ((time_T22.time*1000)+time_T22.millitm)-((time_T21.time*1000)+time_T21.millitm) >  1000 )		{  		//	1sec
	  if( ((time_T22.time*1000)+time_T22.millitm)-((time_T21.time*1000)+time_T21.millitm) >  (pw_tst_period*1000) )		{
	  	time_T21 = time_T22;

	  	uartA53M0_REQM0_Power( );

	  	//uartA53M0_REQM0_Temp( );
			//uartA53M0_REQM0_SystemInfo( );
			//uartA53M0_Req_Radar_Status( );

			Tst_cnt_sleep_Start++;
			if( Tst_cnt_sleep_Start >= 10 )		{
				//A53M_Sleep( );
				Tst_cnt_sleep_Start = 0;
			}
			
			
	  }

	  /*
	  //if( ((time_T32.time*1000)+time_T32.millitm)-((time_T31.time*1000)+time_T31.millitm) > (60000 * 1) )		{  		//	60sec * 5
	  if( ((time_T32.time*1000)+time_T32.millitm)-((time_T31.time*1000)+time_T31.millitm) > (30000) )		{  		//	30sec
	  	
	  	time_T31 = time_T32;

	  }
	  */

	  /*
		uartA53M0_REQM0_Temp( );
		uartA53M0_REQM0_Power( );
		uartA53M0_REQM0_SystemInfo( );
		*/


	  //	Test !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	  /*
    #if 	TST_TxRx_COUNT
    	if( Tst_Tx_Cnt >= 10000 )	{
    		break;
    	}
    #endif 		//#if 	TST_TxRx_COUNT
    */
  } 		//while( 1 )  {
  
  
  //printf("  __________ \n\nb");
  //pthread_join( thread_uartA53M0_Tx, NULL );
  //sleep( 15 );
  sleep( 2 );
  pthread_cancel( thread_uartA53M0_Rx );
  pthread_cancel( thread_uartA53M0_Tx );

  #if 	TST_TxRx_COUNT
  	//printf(" Tx[%08d]  Rx[%08d]\n", Tst_Tx_Cnt, Tst_Rx_Cnt );
  #endif 		//#if 	TST_TxRx_COUNT

  //  Ta5320I_ALL
  close(fd_uartA53M0);
  printf( " ___________     Ta5320I_ALL End     ___________ \n\n" );
}   //int main()


//  scp ./gpio2hl root@192.168.1.116:/home/root/Tgcc01
