

#include "m0All_Header.h"


//********************************************************************
//	Global
unsigned char   A53M0_RxBuf[UARTA53M0_RX_BUFFER_SIZE];
int 	A53M0_RxLength;
int 	A53M0_rx;

unsigned char   A53M0_Rx_QBuf[UARTA53M0_RX_Q_BUFFER_SIZE + 0x10];
M0_UART_FIFO		A53M0_RxQ;

UINT8 	M0A53_Rx_Payload[UARTA53M0_RX_BUFFER_SIZE];


UINT32 	crc_ErrorCnt = 0;

#if 	Tst_PW_Change
	int 	Tst_PW_ChangeCnt;
	int 	Tst_PrePW_state;
#endif 	//#if 	Tst_PW_Change



//********************************************************************
void  uartA53M0_uart_Clear( void );
int  uartA53M0_uart_Get( UINT8 *rx_data );

void 	uartM0_rsp_m0SysInfo( UINT8* rx_payload );
void 	uartM0_rsp_Dev( UINT8* rx_payload );
void 	uartM0_rsp_DevStatus( UINT8* rx_payload );
void 	uartM0_rsp_ENC( UINT8* rx_payload );
void 	uartM0_rsp_M0RTC( UINT8* rx_payload );
void 	uartM0_rsp_read_EEP( UINT8* rx_payload );

void 	uartM0_rsp_M0_Alarm( UINT8* rx_payload );
void 	uartM0_rsp_DummingTest( UINT8* rx_payload );

//====================================================================
extern 	struct timeb  	time_A53_awake1;
extern 	struct timeb  	time_A53_awake2;









//********************************************************************
//
//********************************************************************
void  uartA53M0_Rx_thread( int* fdPtr )
{
	int i;
  a53m0API_currentTime = time( NULL);
  a53m0API_current_tm = localtime (&a53m0API_currentTime);

  int  Tst_M0_RxCnt;
  int  Tst_M0_RxLen;

	UINT8 	uart_data;
	UINT16 	crc16;

	int res;
	UINT8 *dataPtr;


#if 	Tst_PW_Change
	Tst_PW_ChangeCnt = 0;
#endif 	//#if 	Tst_PW_Change
  
  printf( "********** **********  Thread uartA53M0_Rx_thread Start  ********** ********** \n" );

  //	Device status Init. 	------------------------------------------
  M0_Status_Update = 0x0000;

  
  //==================================================================
  A53M0_RxQ.buffer = A53M0_Rx_QBuf;
  A53M0_RxQ.front = A53M0_RxQ.tail = A53M0_RxQ.buffull = 0;
  A53M0_RxQ.CMD = A53M0_RxQ.PTR = A53M0_RxQ.STATE = A53M0_RxQ.LENGTH = 0;


  //==================================================================
  //
  //==================================================================
  while( 1 )  {
    a53m0API_currentTime = time( NULL);
    a53m0API_current_tm = localtime (&a53m0API_currentTime);

    //================================================================
    res = read( *fdPtr, (A53M0_RxBuf), UARTA53M0_RX_BUFFER_SIZE );

    if( res > 0 )		{

			#if  	TST_AUTO_SLEEP
				ftime( &time_Tst_autu_sleep2 );
				ftime( &time_Tst_autu_sleep1 );
				Tst_Flg_Auto_Sleep = 1;
			#endif  		//#if  	TST_AUTO_SLEEP

    	#if 	TST_RXUART_SHOW_01
	    	printf("res[%04d]: [", res);
		    for( i=0 ; i<res ; i++ )	{
		    	A53M0_RxQ.buffer[ A53M0_RxQ.tail ] = A53M0_RxBuf[ i ];
		    	A53M0_RxQ.tail = (A53M0_RxQ.tail+1) & (UARTA53M0_RX_Q_BUFFER_SIZE - 1);
		    	printf(" %02X", A53M0_RxBuf[i]);
		    } 	//for( i=0 ; i<res ; i++ )	{
		    printf("]\n");
    	#else
		    #if 	TST_RXUART_SHOW_02
		    	printf("Rx res[%d]\n", res );
		    #endif 		//#if 	TST_RXUART_SHOW_02

				for( i=0 ; i<res ; i++ )	{
					A53M0_RxQ.buffer[ A53M0_RxQ.tail ] = A53M0_RxBuf[ i ];
					A53M0_RxQ.tail = (A53M0_RxQ.tail+1) & (UARTA53M0_RX_Q_BUFFER_SIZE - 1);
				} 	//for( i=0 ; i<res ; i++ )	{
    	#endif 	//TST_RXUART_SHOW_01  	

    	//==============================================================
    	//	Get UART Cmd string 
    	//==============================================================
    	//printf(" Cmd[");
    	#if  A53M0_UART_COMMAND
		  	while( uartA53M0_uart_Get( &uart_data ) )  {
		  		#if 	TST_RXUART_SHOW_01
		  			//printf(" $$%02X$$ ", uart_data);
		  		#endif  		//#if 	TST_RXUART_SHOW_01

		  		switch( A53M0_RxQ.STATE )  {
		  			case 0:
			        if(uart_data == 0xCC) {
			          A53M0_RxQ.PTR = 0;
			          A53M0_RxQ.LENGTH = 0xFF;
			          A53M0_RxQ.STATE = 1;
			        }
			        break;

		 				case 1:
			        A53M0_RxQ.LENGTH = uart_data;
			        A53M0_RxQ.STATE = 2;
		 					break;
		 				case 2:
			        A53M0_RxQ.LENGTH |= (uart_data<<8);
			        A53M0_RxQ.STATE = 3;
			        if( A53M0_RxQ.LENGTH > (UARTA53M0_RX_BUFFER_SIZE-3) )		{
			        	printf("RxM0  -xxxLENGTHxxx- [%05d]\n", A53M0_RxQ.LENGTH );
			        	uartA53M0_uart_Clear( );
			        } 	//if( A53M0_RxQ.LENGTH > (UARTA53M0_RX_BUFFER_SIZE-3) )		{
		 					break;

		 				case 3:
			        A53M0_RxQ.CMD = uart_data;
			        A53M0_RxQ.STATE = 4;
				  		#if 	TST_RXUART_SHOW_01
				  			printf(" $$%02X ", uart_data);
				  		#endif  		//#if 	TST_RXUART_SHOW_01
		 					break;

		 				case 4:
			        A53M0_RxQ.CRC = uart_data;
			        A53M0_RxQ.STATE = 5;
		 					break;
		 				case 5:
			        A53M0_RxQ.CRC |= (uart_data<<8);
			        A53M0_RxQ.STATE = 6;
		 					break;

		 				//============================================================
		 				//
		 				//============================================================
		 				case 6:
		 					//	Get payload data 
		 					M0A53_Rx_Payload[ A53M0_RxQ.PTR ] = uart_data;
		 					A53M0_RxQ.PTR++;

		 					if( A53M0_RxQ.PTR >= (A53M0_RxQ.LENGTH-3) )  {
		 						crc16 = Get_ModBus_CRC16( M0A53_Rx_Payload, A53M0_RxQ.PTR );
		 						if( crc16 == A53M0_RxQ.CRC ) 		{
		 							//printf( "\n" );
									a53m0API_currentTime = time( NULL);
									a53m0API_current_tm = localtime (&a53m0API_currentTime);
									/*
									printf("     ---------- A53_RxTime:  [%02d/%02d/%02d %02d:%02d:%02d] \n",
												((a53m0API_current_tm->tm_year+1900)-2000),
												a53m0API_current_tm->tm_mon + 1,
												a53m0API_current_tm->tm_mday,
												a53m0API_current_tm->tm_hour,
												a53m0API_current_tm->tm_min,
												a53m0API_current_tm->tm_sec );
												*/

		 							//**************************************************
		 							//	UART CMD
		 							//**************************************************
		 							switch( A53M0_RxQ.CMD )		{

		 								//==========================================================
		 								//  	uart_M0_WAKEUP_A53
		 								//==========================================================
		 								case uart_M0_WAKEUP_A53:
											//	ReStart WiFi AP  ---------------------------
		 									M0_Status_Update |= M0_DEV_UPDATE_WAKEUP;
		 									//A53M_SleepState_gpio_L( );  		//	A53 Active
		 									ftime( &time_A53_awake2 );
		 									ftime( &time_A53_awake1 );
		 									A53M_SleepState_gpio_H( );

											#if  	TST_AUTO_SLEEP
												ftime( &time_Tst_autu_sleep2 );
												ftime( &time_Tst_autu_sleep1 );
												Tst_Flg_Auto_Sleep = 1;
											#endif  		//#if  	TST_AUTO_SLEEP

		 									uartA53M0_Set_M0_A53Status_Awake( );
		 									A53M_SleepState_gpio_L( );
		 									A53_CK_wifiAP_Enable = 1;

		 									ftime( &time_wifiAP_ck2 );
  										time_wifiAP_ck1 = time_wifiAP_ck2;



											#if  	Tst_CK_SYSTEM_SLEEP
												system( "echo \"\" >> /home/root/sleeplog" );
												system( "echo \".....  uart_M0_WAKEUP_A53  - - - - - \" >> /home/root/sleeplog" );
												system( "date >> /home/root/sleeplog");
											#endif  		//#if  	Tst_CK_SYSTEM_SLEEP


											dataPtr = (UINT8*)&Msg_M0_wakeup_A53;
											for( i=0 ; i<sizeof(M0_WAKEUP_A53_FRAME) ; i++ )		{
												dataPtr[i] = M0A53_Rx_Payload[i];
											}

		 									#if  TST_M0_A53WAKEUP_PRINT
												printf( "    ++++++++++  A53 WakeUp : [%4X] [%02d/%02d/%02d %02d:%02d:%02d]  WakeUp-Msg[%08X] \n",
													M0_Status_Update,
													Msg_M0_wakeup_A53.mcu_RTC.Year,
													Msg_M0_wakeup_A53.mcu_RTC.Month,
													Msg_M0_wakeup_A53.mcu_RTC.Day,
													Msg_M0_wakeup_A53.mcu_RTC.Hour,
													Msg_M0_wakeup_A53.mcu_RTC.Minute,
													Msg_M0_wakeup_A53.mcu_RTC.Second,
													Msg_M0_wakeup_A53.msg	 );
		 									#endif  	//#if  TST_M0_A53WAKEUP_PRINT

											system( "systemctl restart hostapd" );
		 									break;

		 								//==========================================================
		 								case uart_M0_TIME_EVENT:
		 									M0_Status_Update |= M0_DEV_UPDATE_TIME_EVENT;

											#if  	Tst_CK_SYSTEM_SLEEP
												system( "echo \"\" >> /home/root/sleeplog" );
												system( "echo \".....  uart_M0_TIME_EVENT  ..... ..... .....\" >> /home/root/sleeplog" );
												system( "date >> /home/root/sleeplog");
											#endif  		//#if  	Tst_CK_SYSTEM_SLEEP

											dataPtr = (UINT8*)&Msg_M0_TimeEvent;
											for( i=0 ; i<sizeof(M0_TIME_EVENT_FRAME) ; i++ )		{
												dataPtr[i] = M0A53_Rx_Payload[i];
											}
		 									#if  TST_M0_A53WAKEUP_PRINT
												printf( "\n+++++ A53M0 TimeEvent  [%4X] [%02d/%02d/%02d %02d:%02d:%02d] Event_Msg[%08X] -",
													M0_Status_Update,
													Msg_M0_TimeEvent.mcu_RTC.Year,
													Msg_M0_TimeEvent.mcu_RTC.Month,
													Msg_M0_TimeEvent.mcu_RTC.Day,
													Msg_M0_TimeEvent.mcu_RTC.Hour,
													Msg_M0_TimeEvent.mcu_RTC.Minute,
													Msg_M0_TimeEvent.mcu_RTC.Second,
													Msg_M0_TimeEvent.msg	 );
												switch( Msg_M0_TimeEvent.msg )		{
													case SUBTYPE_TIME_EVENT_FEE_TIME_PRE_START:
														printf( "EVENT_FEE_TIME_PRE_START");
														#if  	Tst_CK_SYSTEM_SLEEP
															system( "echo \"      ..... ..... :: EVENT_FEE_TIME_PRE_START \" >> /home/root/sleeplog" );
														#endif  		//#if  	Tst_CK_SYSTEM_SLEEP
														break;
													case SUBTYPE_TIME_EVENT_FEE_TIME_START:
														printf( "EVENT_FEE_TIME_START");
														#if  	Tst_CK_SYSTEM_SLEEP
															system( "echo \"      ..... ..... :: EVENT_FEE_TIME_START \" >> /home/root/sleeplog" );
														#endif  		//#if  	Tst_CK_SYSTEM_SLEEP
														break;
													case SUBTYPE_TIME_EVENT_FEE_TIME_END:
														printf( "EVENT_FEE_TIME_END");
														#if  	Tst_CK_SYSTEM_SLEEP
															system( "echo \"      ..... ..... :: SUBTYPE_TIME_EVENT_FEE_TIME_END \" >> /home/root/sleeplog" );
														#endif  		//#if  	Tst_CK_SYSTEM_SLEEP
														break;
													case SUBTYPE_TIME_EVENT_HEARTBEAT:
														printf( "EVENT_HEARTBEAT");
														#if  	Tst_CK_SYSTEM_SLEEP
															system( "echo \"      ..... ..... :: SUBTYPE_TIME_EVENT_HEARTBEAT \" >> /home/root/sleeplog" );
														#endif  		//#if  	Tst_CK_SYSTEM_SLEEP
														break;
													case SUBTYPE_TIME_EVENT_FEE_FREE_TIME_CK:
														printf( "EVENT_FEE_FREE_TIME_CK");
														#if  	Tst_CK_SYSTEM_SLEEP
															system( "echo \"      ..... ..... :: EVENT_FEE_FREE_TIME_CK \" >> /home/root/sleeplog" );
														#endif  		//#if  	Tst_CK_SYSTEM_SLEEP
														break;
													case SUBTYPE_TIME_EVENT_RADAR_A_CC:
														printf( "EVENT_RADAR_A_CC");
														#if  	Tst_CK_SYSTEM_SLEEP
															system( "echo \"      ..... ..... :: SUBTYPE_TIME_EVENT_RADAR_A_CC \" >> /home/root/sleeplog" );
														#endif  		//#if  	Tst_CK_SYSTEM_SLEEP
														break;
													case SUBTYPE_TIME_EVENT_RADAR_B_CC:
														printf( "EVENT_RADAR_B_CC");
														#if  	Tst_CK_SYSTEM_SLEEP
															system( "echo \"      ..... ..... :: SUBTYPE_TIME_EVENT_RADAR_B_CC \" >> /home/root/sleeplog" );
														#endif  		//#if  	Tst_CK_SYSTEM_SLEEP
														break;
												}  		//switch( Msg_M0_TimeEvent.msg )		{
												printf( " \n" );
		 									#endif  	//#if  TST_M0_A53WAKEUP_PRINT
		 									break;


		 								//==========================================================
		 								case uart_RSP_M0_INFO:
		 									uartM0_rsp_m0SysInfo( M0A53_Rx_Payload );
		 									break;

		 								case uart_RSP_DEV:
		 									uartM0_rsp_Dev( M0A53_Rx_Payload );
		 									break;

		 								case uart_RSP_DEV_STATUS:
		 									uartM0_rsp_DevStatus( M0A53_Rx_Payload );
		 									break;

		 								case uart_RSP_M0_RTC:
		 									uartM0_rsp_M0RTC( M0A53_Rx_Payload );
		 									break;

		 								case uart_RSP_READ_EEPROM:
		 									uartM0_rsp_read_EEP( M0A53_Rx_Payload );
		 									break;

		 								case uart_RSP_ENC:
		 									uartM0_rsp_ENC( M0A53_Rx_Payload );
		 									break;

		 								case uart_RSP_ALARM:
		 									uartM0_rsp_M0_Alarm( M0A53_Rx_Payload );
		 									break;


		 								case uart_RSP_FW_OTA:
		 									switch( M0A53_Rx_Payload[0] ) 	{
		 										case SUBTYPE_RADAR_A:
		 										case SUBTYPE_RADAR_B:
		 											RadarOTA_Rsp( M0A53_Rx_Payload, A53M0_RxQ.LENGTH );
		 											break;

		 										case SUBTYPE_CHILI2S:
		 											Chili2SOTA_Rsp( M0A53_Rx_Payload, A53M0_RxQ.LENGTH );
		 											break;

		 									}  		//switch( M0A53_Rx_Payload[0] ) 	{
		 									
		 									
		 									break;

		 								case uart_RSP_M0_DUMMING:
		 									uartM0_rsp_DummingTest( M0A53_Rx_Payload );
		 									break;

		 							} 		//switch( A53M0_RxQ.CMD )		{
		 						} 		//if( crc16 == A53M0_RxQ.CRC ) 		{
		 						else	{
		 							crc_ErrorCnt++;
		 							printf("\n RxM0  -xxxCRCxxx-[%04X][%04X]  crcError[%012d]  !!!!! \n", crc16, A53M0_RxQ.CRC, crc_ErrorCnt );
		 						}

		 						//====================================================
		 						//printf(" uartA53M0_uart_Clear\n");
		 						uartA53M0_uart_Clear( );
		 					} 	//if( A53M0_RxQ.PTR >= A53M0_RxQ.LENGTH )  {
		 					break; 		////switch( A53M0_RxQ.STATE )  { 		case 6:


		 				//============================================================
		 				//============================================================
			      default:
			        //uartA53M0_uart_Clear( );
			        break;
		  		} 	//switch( A53M0_RxQ.STATE )  {
		  	} 	//while( uartA53M0_uart_Get( &uart_data ) )  {
		  	//printf("]\n");
	  	#endif 	//#if  A53M0_UART_COMMAND

		  //usleep( 10000 );   //  10ms
		  //usleep( 5000 );   //  5ms
    } 		//if( res > 0 )		{
    else {
    	//printf( ".r" );
    	//    	
    	//usleep( 100000 );   //  100ms
    	//usleep( 50000 );   //  50ms
    	//usleep( 30000 );   //  30ms
    	//usleep( 25000 );   //  25ms
    	//usleep( 20000 );   //  20ms
    	//usleep( 10000 );   //  10ms

    	//usleep( 3000 );   //  3ms    	
    	//usleep( 2000 );   //  2ms, 	OK
    	usleep( 1500 );   //  1.5ms,
    	//usleep( 1000 );   //  1ms, 	OK
    } 	//if( res < 1 )	{		else
  }
} 	//void  uartA53M0_Rx_thread( int* fdPtr )








//******************************************************************************
//
//******************************************************************************
void  uartA53M0_uart_Clear( void )
{
  A53M0_RxQ.CMD = A53M0_RxQ.PTR = A53M0_RxQ.STATE = A53M0_RxQ.LENGTH = 0;
}   //void  uartM4_Clear_State( void )



//********************************************************************
//
//********************************************************************
int  uartA53M0_uart_Get( UINT8 *rx_data )
{
  if( (A53M0_RxQ.tail==A53M0_RxQ.front) && (!A53M0_RxQ.buffull) ) {
    return FAILURE;
  }

  //------------------------------------------------------------------
  *rx_data = A53M0_RxQ.buffer[ A53M0_RxQ.front ];
  A53M0_RxQ.front = (A53M0_RxQ.front + 1) & (UARTA53M0_RX_Q_BUFFER_SIZE - 1);
  
  if( (A53M0_RxQ.buffull) && (A53M0_RxQ.tail!=A53M0_RxQ.front) )    {
    A53M0_RxQ.buffull = 0;
  }

  return  SUCCESS;
} 	//int  uartA53M0_uart_Get( UINT8 *rx_data )

















/*

	Response from M0

*/
//********************************************************************
//
//********************************************************************
void 	uartM0_rsp_m0SysInfo( UINT8* rx_payload )
{
	UINT8 *dataPtr = (UINT8*)&M0_System_info;

	memset( dataPtr, 0x00, sizeof(M0_System_info) );
	memcpy( dataPtr, rx_payload, sizeof(M0_System_info) );

	M0_Status_Update |= M0_DEV_UPDATE_SYSINFO;


	//printf("\n----uartM0_rsp_m0SysInfo ========== ========== \n");
	#if 	TST_M0_SYSINFO_PRINT

		//#if 	!TST_TxRx_COUNT
		printf( "\n  **********  " );
		printf("RxM0 SysInfo FW : [");
		int  i;
		for (int i = 0; i < 32; ++i)
		{
			printf("%c", M0_System_info.FW_ver[i] );
		}
		printf("]");
		//#endif 	//#if 	!TST_TxRx_COUNT

		#if 	TST_TxRx_COUNT

			printf("-[%02d-%02d-%02d %02d:%02d:%02d] ", 
						M0_System_info.mcu_RTC.Year,
						M0_System_info.mcu_RTC.Month,
						M0_System_info.mcu_RTC.Day,
						M0_System_info.mcu_RTC.Hour,
						M0_System_info.mcu_RTC.Minute,
						M0_System_info.mcu_RTC.Second	);
		#else
			printf("-[%02d-%02d-%02d %02d:%02d:%02d] ", 
						M0_System_info.mcu_RTC.Year,
						M0_System_info.mcu_RTC.Month,
						M0_System_info.mcu_RTC.Day,
						M0_System_info.mcu_RTC.Hour,
						M0_System_info.mcu_RTC.Minute,
						M0_System_info.mcu_RTC.Second	);
		#endif 		//#if 	TST_TxRx_COUNT


		printf( "  **********  " );
		printf(" \n");

		//printf( "  ==========  " );
		printf("     Chili2S FW:[");
		for (int i = 0; i < 48; ++i)
		{
			printf("%c", M0_System_info.Chili2S_info.fw_ver[i] );
		}
		printf("]");
		printf("-[%02d-%02d-%02d %02d:%02d:%02d]  [%04X %04X %02d]", 
					M0_System_info.Chili2S_info.rtc.Year,
					M0_System_info.Chili2S_info.rtc.Month,
					M0_System_info.Chili2S_info.rtc.Day,
					M0_System_info.Chili2S_info.rtc.Hour,
					M0_System_info.Chili2S_info.rtc.Minute,
					M0_System_info.Chili2S_info.rtc.Second,
					M0_System_info.Chili2S_info.panid,
					M0_System_info.Chili2S_info.sAddr,
					M0_System_info.Chili2S_info.rf_channel	);
		
		printf(" \n");

		printf(" \n");
		//printf(" \n");
	#endif 	//#if 	TST_M0_SYSINFO_PRINT
} 		//void 	uartM0_rsp_m0SysInfo( UINT8* rx_payload )


//******************************************************************************
//
//******************************************************************************
//	printf("Rx uart_RSP_M0_RTC ---------- ---------- \n");
void 	uartM0_rsp_M0RTC( UINT8* rx_payload )
{
	UINT8	*dataPtr;
	int  	i;

	dataPtr = (UINT8*)&M0_rtc;
	for( i=0 ; i<sizeof(M0_RTC_TIME_FRAME) ; i++ )		{
		dataPtr[i] = rx_payload[i];
	} 		//for( i=0 ; i<sizeof(M0_RTC_TIME_FRAME) ; i++ )		{

	M0_Status_Update |= M0_DEV_UPDATE_RTC;

	//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	#if 	TST_M0_RTC_PRINT
		printf("RxM0 RTC : [%02d-%02d-%02d %02d:%02d:%02d] \n",
					M0_rtc.Year,
					M0_rtc.Month,
					M0_rtc.Day,
					M0_rtc.Hour,
					M0_rtc.Minute,
					M0_rtc.Second );
	#endif 	//#if 	TST_M0_RTC_PRINT
} 	//void 	uartM0_rsp_M0RTC( UINT8* rx_payload )





//******************************************************************************
//
//******************************************************************************
void 	uartM0_rsp_Dev( UINT8* rx_payload )
{
	UINT8*	dataPtr;
	int  	i;

	M0_SYS_PARAMETER_FRAM*  sysPara_Ptr;


	switch( rx_payload[0] )		{
		//==========================================================================
		case SUBTYPE_M0_SYS:
			#if  	Tst_CK_SYSTEM_SLEEP
				system( "echo \"\" >> /home/root/sleeplog" );
				system( "echo \"..... ..... SUBTYPE_M0_SYS  ********** ********** \" >> /home/root/sleeplog" );
			#endif  		//#if  	Tst_CK_SYSTEM_SLEEP

			sysPara_Ptr = (M0_SYS_PARAMETER_FRAM*)&rx_payload[i+1];
			printf( "Rx  uartM0_rsp_Dev  SUBTYPE_M0_SYS : fee_time.Fee_Start : [%02d:%02d:%02d] \n",
						sysPara_Ptr->fee_time.Fee_Start.Hour,
						sysPara_Ptr->fee_time.Fee_Start.Minute,
						sysPara_Ptr->fee_time.Fee_Start.Second	);
			printf( "Rx  uartM0_rsp_Dev  SUBTYPE_M0_SYS : fee_time.Fee_End :   [%02d:%02d:%02d] \n",
						sysPara_Ptr->fee_time.Fee_End.Hour,
						sysPara_Ptr->fee_time.Fee_End.Minute,
						sysPara_Ptr->fee_time.Fee_End.Second	);
			printf( "Rx  uartM0_rsp_Dev  SUBTYPE_M0_SYS : fee_time.period_FeeFree_CKcar : [%02d:%02d:%02d] \n",
						sysPara_Ptr->fee_time.period_FeeFree_CKcar.Hour,
						sysPara_Ptr->fee_time.period_FeeFree_CKcar.Minute,
						sysPara_Ptr->fee_time.period_FeeFree_CKcar.Second	);

			printf( "Rx  uartM0_rsp_Dev  SUBTYPE_M0_SYS : period_heartbeat : [%02d:%02d:%02d] \n",
						sysPara_Ptr->period_heartbeat.Hour,
						sysPara_Ptr->period_heartbeat.Minute,
						sysPara_Ptr->period_heartbeat.Second	);
			printf( "\n" );

			printf( "Rx  uartM0_rsp_Dev  SUBTYPE_M0_SYS : radarA.car_car_ck : [%02d:%02d:%02d] \n",
						sysPara_Ptr->radarA.car_car_ck.Hour,
						sysPara_Ptr->radarA.car_car_ck.Minute,
						sysPara_Ptr->radarA.car_car_ck.Second	);
			printf( "Rx  uartM0_rsp_Dev  SUBTYPE_M0_SYS : radarB.car_car_ck : [%02d:%02d:%02d] \n",
						sysPara_Ptr->radarB.car_car_ck.Hour,
						sysPara_Ptr->radarB.car_car_ck.Minute,
						sysPara_Ptr->radarB.car_car_ck.Second	);
			break;
	}  		//switch( rx_payload[0] )		{

}  		//void 	uartM0_rsp_Dev( UINT8* rx_payload )



//******************************************************************************
//
//******************************************************************************
void 	uartM0_rsp_DevStatus( UINT8* rx_payload )
{
	UINT8*	dataPtr;
	int  	i;

	M0_SYS_PARAMETER_FRAM*  sysPara_Ptr;

	#if  	Tst_CK_SYSTEM_SLEEP
		UINT8  	logBuf[256];
	#endif  		//#if  	Tst_CK_SYSTEM_SLEEP


	#if 	TST_RXUART_SHOW_01
		printf( "[[1");
		printf( " %02X", rx_payload[0] );
		printf( " %02X", rx_payload[1] );
		printf( " %02X", rx_payload[2] );
		printf( " %02X", rx_payload[3] );
		printf( " %02X", rx_payload[4] );
		printf( " %02X", rx_payload[5] );
		printf( "]]\n");
	#endif  		//#if 	TST_RXUART_SHOW_01


	switch( rx_payload[0] )		{

		//==========================================================================
		case SUBTYPE_M0_SYS:
			#if  	Tst_CK_SYSTEM_SLEEP
				system( "echo \"\" >> /home/root/sleeplog" );
				system( "echo \"..... ..... SUBTYPE_M0_SYS  ********** ********** \" >> /home/root/sleeplog" );
			#endif  		//#if  	Tst_CK_SYSTEM_SLEEP

			sysPara_Ptr = (M0_SYS_PARAMETER_FRAM*)&rx_payload[i+1];
			printf( "Rx  uartM0_rsp_DevStatus.SUBTYPE_M0_SYS : fee_time.Fee_Start : [%02d:%02d:%02d] \n",
						sysPara_Ptr->fee_time.Fee_Start.Hour,
						sysPara_Ptr->fee_time.Fee_Start.Minute,
						sysPara_Ptr->fee_time.Fee_Start.Second	);
			printf( "Rx  uartM0_rsp_DevStatus.SUBTYPE_M0_SYS : fee_time.Fee_End :   [%02d:%02d:%02d] \n",
						sysPara_Ptr->fee_time.Fee_End.Hour,
						sysPara_Ptr->fee_time.Fee_End.Minute,
						sysPara_Ptr->fee_time.Fee_End.Second	);
			printf( "Rx  uartM0_rsp_DevStatus.SUBTYPE_M0_SYS : fee_time.period_FeeFree_CKcar : [%02d:%02d:%02d] \n",
						sysPara_Ptr->fee_time.period_FeeFree_CKcar.Hour,
						sysPara_Ptr->fee_time.period_FeeFree_CKcar.Minute,
						sysPara_Ptr->fee_time.period_FeeFree_CKcar.Second	);

			printf( "Rx  uartM0_rsp_DevStatus.SUBTYPE_M0_SYS : period_heartbeat : [%02d:%02d:%02d] \n",
						sysPara_Ptr->period_heartbeat.Hour,
						sysPara_Ptr->period_heartbeat.Minute,
						sysPara_Ptr->period_heartbeat.Second	);
			printf( "\n" );

			printf( "Rx  uartM0_rsp_DevStatus.SUBTYPE_M0_SYS : radarA.car_car_ck : [%02d:%02d:%02d] \n",
						sysPara_Ptr->radarA.car_car_ck.Hour,
						sysPara_Ptr->radarA.car_car_ck.Minute,
						sysPara_Ptr->radarA.car_car_ck.Second	);
			printf( "Rx  uartM0_rsp_DevStatus.SUBTYPE_M0_SYS : radarB.car_car_ck : [%02d:%02d:%02d] \n",
						sysPara_Ptr->radarB.car_car_ck.Hour,
						sysPara_Ptr->radarB.car_car_ck.Minute,
						sysPara_Ptr->radarB.car_car_ck.Second	);
			break;

		//==========================================================================
		case SUBTYPE_MGC3130:
			M0_Status_Update |= M0_DEV_UPDATE_MGC;

			#if  	Tst_CK_SYSTEM_SLEEP
				system( "echo \"..... ..... SUBTYPE_MGC3130 \" >> /home/root/sleeplog" );
			#endif  		//#if  	Tst_CK_SYSTEM_SLEEP

			dataPtr = (UINT8*)&M0_mgc3130;
			for( i=0 ; i<sizeof(M0_MGC_DATA_FRAME) ; i++ )		{
				dataPtr[i] = rx_payload[i+1];
			}

			// 	TEST		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			#if 	TST_M0_MGC_DATA_PRINT
				//printf("RxM0 MGC : [%02d-%02d-%02d %02d:%02d:%02d]  M0_Status_Update[%04X] mgc[%02d]\n",
				printf("\n ********** RxM0 MGC : [%02d-%02d-%02d %02d:%02d:%02d]  M0_Status_Update[%04X] ---------- ---------- ---------- mgc[%02d] \n\n",
							M0_mgc3130.mcu_RTC.Year,
							M0_mgc3130.mcu_RTC.Month,
							M0_mgc3130.mcu_RTC.Day,
							M0_mgc3130.mcu_RTC.Hour,
							M0_mgc3130.mcu_RTC.Minute,
							M0_mgc3130.mcu_RTC.Second,
							M0_Status_Update,
							M0_mgc3130.mgc	);
				
			#endif 	//#if 	TST_M0_MGC_DATA_PRINT
			break;

		//==========================================================================
		case SUBTYPE_ALPS:
			M0_Status_Update |= M0_DEV_UPDATE_ALPS;

			dataPtr = (UINT8*)&M0_alps;
			for( i=0 ; i<sizeof(M0_ALPS_FRAME) ; i++ )		{
				dataPtr[i] = rx_payload[i+1];
			}

			// 	TEST		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			#if 	TST_M0_MGC_DATA_PRINT

				/*
				printf("***** RxM0 ALPS : [%02d-%02d-%02d %02d:%02d:%02d] \n",
							M0_alps.mcu_RTC.Year,
							M0_alps.mcu_RTC.Month,
							M0_alps.mcu_RTC.Day,
							M0_alps.mcu_RTC.Hour,
							M0_alps.mcu_RTC.Minute,
							M0_alps.mcu_RTC.Second,
							M0_Status_Update	);
					*/
				//printf("***** RxM0 ALPS :  [%02X]--[%02X] ", M0_alps.pre_key, M0_alps.key );
				printf("***** RxM0 ALPS :  [%02d-%02d-%02d %02d:%02d:%02d]    [%02X]--[%02X] ",
							M0_alps.mcu_RTC.Year,
							M0_alps.mcu_RTC.Month,
							M0_alps.mcu_RTC.Day,
							M0_alps.mcu_RTC.Hour,
							M0_alps.mcu_RTC.Minute,
							M0_alps.mcu_RTC.Second,
							M0_alps.pre_key, M0_alps.key  );

				/*
				int  	i_max = 0;
				int   v_max = 0;
				for( i=0; i<24; ++i )		{
					if( M0_alps.data[i] > v_max )		{
						i_max = i;
						v_max = M0_alps.data[i];
					}
				}  		//for( i=0; i<24; ++i )		{

				for( i=0; i<24; ++i )		{
					if( (i%6) == 0 )		{
						printf( "\n  -" );
					}

					if( i == i_max )		{
						printf( "   *%04X", M0_alps.data[i] );
					}
					else  	{
						printf( "    %04X", M0_alps.data[i] );
					}
				}  		//for( i=0; i<24; ++i )		{
					*/
				printf( " \n" );
				
			#endif 	//#if 	TST_M0_MGC_DATA_PRINT
			break;


		//==========================================================================
		case SUBTYPE_G_SENSOR:
			M0_Status_Update |= M0_DEV_UPDATE_G_SENSOR;

			#if  	Tst_CK_SYSTEM_SLEEP
				system( "echo \"..... ..... SUBTYPE_G_SENSOR \" >> /home/root/sleeplog" );
			#endif  		//#if  	Tst_CK_SYSTEM_SLEEP

			dataPtr = (UINT8*)&g_icm_Data;
			for( i=0 ; i<sizeof(M0_G_SENSOR_FRAME) ; i++ )		{
				dataPtr[i] = rx_payload[i+1];
			}

			// 	TEST		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			#if 	TST_M0_G_DATA_PRINT
				printf("RxM0 G-sensor : [%02d-%02d-%02d %02d:%02d:%02d]  M0_Status_Update[%04X]  G:XYZ[%04d %04d %04d] INT[%04d %04d %04d]\n",
							g_icm_Data.mcu_RTC.Year,
							g_icm_Data.mcu_RTC.Month,
							g_icm_Data.mcu_RTC.Day,
							g_icm_Data.mcu_RTC.Hour,
							g_icm_Data.mcu_RTC.Minute,
							g_icm_Data.mcu_RTC.Second,
							M0_Status_Update,
							g_icm_Data.stk8ba53.acc_X,
							g_icm_Data.stk8ba53.acc_Y,
							g_icm_Data.stk8ba53.acc_Z,
							g_icm_Data.stk8ba53.acc_INT_X,
							g_icm_Data.stk8ba53.acc_INT_Y,
							g_icm_Data.stk8ba53.acc_INT_Z		);
			#endif 	//#if 	TST_M0_G_DATA_PRINT
			break;


		//==========================================================================
		case SUBTYPE_ADC:
			M0_Status_Update |= M0_DEV_UPDATE_ADC_1;

			#if  	Tst_CK_SYSTEM_SLEEP
				system( "echo \"..... ..... SUBTYPE_ADC \" >> /home/root/sleeplog" );
			#endif  		//#if  	Tst_CK_SYSTEM_SLEEP

			dataPtr = (UINT8*)&M0_power;
			for( i=0 ; i<sizeof(M0_POWER_DATA_FRAME) ; i++ )		{
				dataPtr[i] = rx_payload[i+1];
			}

			// 	TEST		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			#if 	TST_M0_ADC_DATA_PRINT
				if( M0_power.pw_EN != Tst_PrePW_state )		{
					Tst_PW_ChangeCnt = 0;
				}

				if( M0_power.V_Solar == 99000 ) 	{
					M0_power.V_Solar = 9999;
				}
				if( M0_power.V_DC == 99000 ) 	{
					M0_power.V_DC = 9999;
				}

				#if  	TST_M0_PW_METER_PRINT
				printf("PW : %02d-%02d-%02d %02d:%02d:%02d%c%04X%c%04d%c%04d%c%04d%c%02X%c%04d%c%04d%c%04d%c%04d%c%04d%c%03d%c%06d%c%04d\n",
							M0_power.mcu_RTC.Year,
							M0_power.mcu_RTC.Month,
							M0_power.mcu_RTC.Day,
							M0_power.mcu_RTC.Hour,
							M0_power.mcu_RTC.Minute,
							M0_power.mcu_RTC.Second,
							0x20,
							M0_Status_Update,
							0x20,
							M0_power.adc0,
							0x20,
							M0_power.adc1,
							0x20,
							M0_power.adc2,
							0x20,
							M0_power.pw_EN,

							0x20,
							M0_power.V_batA,
							0x20,
							M0_power.V_batB,
							0x20,
							M0_power.V_Solar,
							0x20,
							M0_power.V_DC,


							0x20,
							M0_power.pw_meter.bat_v,
							0x20,
							M0_power.pw_meter.bat_i,
							0x20,
							M0_power.pw_meter.temp,
							0x20,
							Tst_PW_ChangeCnt
							);
				#endif  	//#if  	TST_M0_PW_METER_PRINT

				Tst_PW_ChangeCnt ++;
				Tst_PrePW_state = M0_power.pw_EN;
			#elif 	TST_M0_ADC_DATA_PRINT2
				
			#endif 	//#if 	TST_M0_ADC_DATA_PRINT
			break;


		//==========================================================================
		case SUBTYPE_RTC:
			break;


		//==========================================================================
		case SUBTYPE_TEMPERATURE:
			M0_Status_Update |= M0_DEV_UPDATE_TEMP;

			dataPtr = (UINT8*)&M0_temperature;
			for( i=0 ; i<sizeof(M0_TEMP_DATA_FRAME) ; i++ )		{
				dataPtr[i] = rx_payload[i+1];
			}
			
			#if 	TST_M0_TEMP_PRINT
				printf("RxM0 TEMP : [%02d-%02d-%02d %02d:%02d:%02d]  M0_Status_Update[%04X] temp.[%d] \n",
							M0_temperature.mcu_RTC.Year,
							M0_temperature.mcu_RTC.Month,
							M0_temperature.mcu_RTC.Day,
							M0_temperature.mcu_RTC.Hour,
							M0_temperature.mcu_RTC.Minute,
							M0_temperature.mcu_RTC.Second,
							M0_Status_Update,
							M0_temperature.temp0	);
			#endif 		//#if 	TST_M0_TEMP_PRINT
			break;


		//==========================================================================
		case SUBTYPE_PW_METER0:

			break;


		//==========================================================================
		case SUBTYPE_RADAR_A:
			dataPtr = (UINT8*)&M0_radarA;
			for( i=0 ; i<sizeof(M0_RADAR_FRAME) ; i++ )		{
				dataPtr[i] = rx_payload[i+1];
			}

			M0_Status_Update |= M0_DEV_UPDATE_RADAR_A;

			#if  	Tst_CK_SYSTEM_SLEEP
				//system( "echo \"..... ..... SUBTYPE_RADAR_A \" >> /home/root/sleeplog" );
				bzero( logBuf, 256 );
				sprintf( logBuf, "echo \"..... ..... SUBTYPE_RADAR_A CC[%d]-[%d] \" >> /home/root/sleeplog",
							M0_radarB.car,
							M0_radarB.pre_car  );
				system( logBuf );
			#endif  		//#if  	Tst_CK_SYSTEM_SLEEP

			// 	TEST		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			#if 	TST_M0_RADAR_A_DATA_PRINT

				#if  !TST_M0_RADAR_PRINT_ALL
					printf("RxM0 RadarA30 [%02d-%02d-%02d %02d:%02d:%02d] FW%02X%02X%02X%02X  car[%d-%d] Result[%d-%d] Obj[%d-%d] [%d,%d,%d,%d,%d] LR%d  \n",

								M0_radarA.mcu_RTC.Year,
								M0_radarA.mcu_RTC.Month,
								M0_radarA.mcu_RTC.Day,
								M0_radarA.mcu_RTC.Hour,
								M0_radarA.mcu_RTC.Minute,
								M0_radarA.mcu_RTC.Second,

								M0_radarA.FW_version[0],
								M0_radarA.FW_version[1],
								M0_radarA.FW_version[2],
								M0_radarA.FW_version[3],

								M0_radarA.car,
								M0_radarA.pre_car,

								M0_radarA.data.Result,
								M0_radarA.pre_Result,
								M0_radarA.data.Object_type,
								M0_radarA.pre_Object_type,

								M0_radarA.data.radar_X,
								M0_radarA.data.radar_Y,
								M0_radarA.data.radar_L,
								M0_radarA.data.radar_W,
								M0_radarA.data.radar_H,

								M0_radarA.data.L_R		);

				#else  		//#if  !TST_M0_RADAR_PRINT_ALL
					printf("\nRadarA30 [%02d-%02d-%02d %02d:%02d:%02d] FW%02X%02X%02X%02X  car[%d-%d] Result[%d-%d] Obj[%d-%d] XYLWH[%d,%d,%d,%d,%d]  %d %d  LR-%d \n",

								M0_radarA.mcu_RTC.Year,
								M0_radarA.mcu_RTC.Month,
								M0_radarA.mcu_RTC.Day,
								M0_radarA.mcu_RTC.Hour,
								M0_radarA.mcu_RTC.Minute,
								M0_radarA.mcu_RTC.Second,

								M0_radarA.FW_version[0],
								M0_radarA.FW_version[1],
								M0_radarA.FW_version[2],
								M0_radarA.FW_version[3],

								M0_radarA.car,
								M0_radarA.pre_car,

								M0_radarA.data.Result,
								M0_radarA.pre_Result,
								M0_radarA.data.Object_type,
								M0_radarA.pre_Object_type,

								M0_radarA.data.radar_X,
								M0_radarA.data.radar_Y,
								M0_radarA.data.radar_L,
								M0_radarA.data.radar_W,
								M0_radarA.data.radar_H,

								M0_radarA.data.Theta,
								M0_radarA.data.Phi,
								M0_radarA.data.L_R	);

					printf("         [%d %d %d %d %d %d] [%d %d %d %d %d %d %d %d]  obj1[%d,%d,%d,%d,%d] obj2[%d,%d,%d,%d,%d] obj3[%d,%d,%d,%d,%d]\n",
								M0_radarA.data.Z_m,
								M0_radarA.data.Z_p,
								M0_radarA.data.DoA_E_m,
								M0_radarA.data.DoA_E_p,
								M0_radarA.data.DoA_H_m,
								M0_radarA.data.DoA_H_p,

								M0_radarA.data.Threshold_Boundary,
								M0_radarA.data.Threshold_A,
								M0_radarA.data.Threshold_B,
								M0_radarA.data.Peak_amount,
								M0_radarA.data.Compare_car,
								M0_radarA.data.Compare_emp,
								M0_radarA.data.Block_lim,
								M0_radarA.data.Block_index,

								M0_radarA.data.Range_Object1,
								M0_radarA.data.x_Object1,
								M0_radarA.data.y_Object1,
								M0_radarA.data.z_Object1,
								M0_radarA.data.Power_Object1,

								M0_radarA.data.Range_Object2,
								M0_radarA.data.x_Object2,
								M0_radarA.data.y_Object2,
								M0_radarA.data.z_Object2,
								M0_radarA.data.Power_Object2,

								M0_radarA.data.Range_Object3,
								M0_radarA.data.x_Object3,
								M0_radarA.data.y_Object3,
								M0_radarA.data.z_Object3,
								M0_radarA.data.Power_Object3		);
				#endif  	//#if  !TST_M0_RADAR_PRINT_ALL

			#endif 		//#if 	TST_M0_RADAR_A_DATA_PRINT
			break;


		//==========================================================================
		case SUBTYPE_RADAR_B:
			dataPtr = (UINT8*)&M0_radarB;
			for( i=0 ; i<sizeof(M0_RADAR_FRAME) ; i++ )		{
				dataPtr[i] = rx_payload[i+1];
			}

			M0_Status_Update |= M0_DEV_UPDATE_RADAR_B;

			#if  	Tst_CK_SYSTEM_SLEEP
				//system( "echo \"..... ..... SUBTYPE_RADAR_B \" >> /home/root/sleeplog" );
				bzero( logBuf, 256 );
				sprintf( logBuf, "echo \"..... ..... SUBTYPE_RADAR_B CC[%d]-[%d] \" >> /home/root/sleeplog",
							M0_radarB.car,
							M0_radarB.pre_car  );
				system( logBuf );
			#endif  		//#if  	Tst_CK_SYSTEM_SLEEP

			// 	TEST		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			#if 	TST_M0_RADAR_B_DATA_PRINT

				#if  !TST_M0_RADAR_PRINT_ALL
					printf("RxM0 RadarB30 [%02d-%02d-%02d %02d:%02d:%02d] FW%02X%02X%02X%02X  car[%d-%d] Result[%d-%d] Obj[%d-%d] [%d,%d,%d,%d,%d] LR%d  \n",

								M0_radarB.mcu_RTC.Year,
								M0_radarB.mcu_RTC.Month,
								M0_radarB.mcu_RTC.Day,
								M0_radarB.mcu_RTC.Hour,
								M0_radarB.mcu_RTC.Minute,
								M0_radarB.mcu_RTC.Second,

								M0_radarB.FW_version[0],
								M0_radarB.FW_version[1],
								M0_radarB.FW_version[2],
								M0_radarB.FW_version[3],

								M0_radarB.car,
								M0_radarB.pre_car,

								M0_radarB.data.Result,
								M0_radarB.pre_Result,
								M0_radarB.data.Object_type,
								M0_radarB.pre_Object_type,

								M0_radarB.data.radar_X,
								M0_radarB.data.radar_Y,
								M0_radarB.data.radar_L,
								M0_radarB.data.radar_W,
								M0_radarB.data.radar_H,

								M0_radarB.data.L_R		);

				#else  		//#if  !TST_M0_RADAR_PRINT_ALL
					printf("\nRadarB30 [%02d-%02d-%02d %02d:%02d:%02d] FW%02X%02X%02X%02X  car[%d-%d] Result[%d-%d] Obj[%d-%d] XYLWH[%d,%d,%d,%d,%d]  %d %d  LR-%d \n",

								M0_radarB.mcu_RTC.Year,
								M0_radarB.mcu_RTC.Month,
								M0_radarB.mcu_RTC.Day,
								M0_radarB.mcu_RTC.Hour,
								M0_radarB.mcu_RTC.Minute,
								M0_radarB.mcu_RTC.Second,

								M0_radarB.FW_version[0],
								M0_radarB.FW_version[1],
								M0_radarB.FW_version[2],
								M0_radarB.FW_version[3],

								M0_radarB.car,
								M0_radarB.pre_car,

								M0_radarB.data.Result,
								M0_radarB.pre_Result,
								M0_radarB.data.Object_type,
								M0_radarB.pre_Object_type,

								M0_radarB.data.radar_X,
								M0_radarB.data.radar_Y,
								M0_radarB.data.radar_L,
								M0_radarB.data.radar_W,
								M0_radarB.data.radar_H,

								M0_radarB.data.Theta,
								M0_radarB.data.Phi,
								M0_radarB.data.L_R	);

					printf("         [%d %d %d %d %d %d] [%d %d %d %d %d %d %d %d]  obj1[%d,%d,%d,%d,%d] obj2[%d,%d,%d,%d,%d] obj3[%d,%d,%d,%d,%d]\n",
								M0_radarB.data.Z_m,
								M0_radarB.data.Z_p,
								M0_radarB.data.DoA_E_m,
								M0_radarB.data.DoA_E_p,
								M0_radarB.data.DoA_H_m,
								M0_radarB.data.DoA_H_p,

								M0_radarB.data.Threshold_Boundary,
								M0_radarB.data.Threshold_A,
								M0_radarB.data.Threshold_B,
								M0_radarB.data.Peak_amount,
								M0_radarB.data.Compare_car,
								M0_radarB.data.Compare_emp,
								M0_radarB.data.Block_lim,
								M0_radarB.data.Block_index,

								M0_radarB.data.Range_Object1,
								M0_radarB.data.x_Object1,
								M0_radarB.data.y_Object1,
								M0_radarB.data.z_Object1,
								M0_radarB.data.Power_Object1,

								M0_radarB.data.Range_Object2,
								M0_radarB.data.x_Object2,
								M0_radarB.data.y_Object2,
								M0_radarB.data.z_Object2,
								M0_radarB.data.Power_Object2,

								M0_radarB.data.Range_Object3,
								M0_radarB.data.x_Object3,
								M0_radarB.data.y_Object3,
								M0_radarB.data.z_Object3,
								M0_radarB.data.Power_Object3		);
				#endif  	//#if  !TST_M0_RADAR_PRINT_ALL

			#endif 		//#if 	TST_M0_RADAR_B_DATA_PRINT
			break;

		//==========================================================================
		case SUBTYPE_LIDAR:
			dataPtr = (UINT8*)&M0_Lidar;
			for( i=0 ; i<sizeof(PARKMETER_VOS_MSG_FRAME) ; i++ )		{
				dataPtr[i] = rx_payload[i+1];
			}

			M0_Status_Update |= M0_DEV_UPDATE_LIDAR;

			#if  	Tst_CK_SYSTEM_SLEEP
				system( "echo \"..... ..... SUBTYPE_LIDAR \" >> /home/root/sleeplog" );
			#endif  		//#if  	Tst_CK_SYSTEM_SLEEP

			#if  	TST_M0_LIDAR_DATA_PRINT
				printf("RxM0 Lidar  [%02d-%02d-%02d %02d:%02d:%02d]  src[%04X]  Lidar[%04d-%04d-%04d] Pre[%04d-%04d-%04d] Car[%d-%d] shoot[%d-%d] fee-%d\n",

							M0_Lidar.mcu_RTC.Year,
							M0_Lidar.mcu_RTC.Month,
							M0_Lidar.mcu_RTC.Day,
							M0_Lidar.mcu_RTC.Hour,
							M0_Lidar.mcu_RTC.Minute,
							M0_Lidar.mcu_RTC.Second,

							M0_Lidar.srcAddr,

							M0_Lidar.lidarData.Distance,
							M0_Lidar.lidarData.Strength,
							M0_Lidar.lidarData.Temp,

							M0_Lidar.pre_lidarData.Distance,
							M0_Lidar.pre_lidarData.Strength,
							M0_Lidar.pre_lidarData.Temp,
							M0_Lidar.car,
							M0_Lidar.pre_car,
							M0_Lidar.shoot,
							M0_Lidar.pre_shoot,
							M0_Lidar.parking_fee_status		);
				printf("\n");
			#endif  	//#if  	TST_M0_LIDAR_DATA_PRINT
			break;

		//==========================================================================
		case SUBTYPE_SELFTEST:
			dataPtr = (UINT8*)&M0_Device_SelfTest;
			for( i=0 ; i<sizeof(M0_DEV_SELF_TEST) ; i++ )		{
				dataPtr[i] = rx_payload[i+1];
			}

			M0_Status_Update |= M0_DEV_UPDATE_M0_SELFTEST;

			printf("\nRxM0 Devices Self-Test  [%02d-%02d-%02d %02d:%02d:%02d]  M0 devices Self-Test:[%08X] \n\n",
							M0_Device_SelfTest.mcu_RTC.Year,
							M0_Device_SelfTest.mcu_RTC.Month,
							M0_Device_SelfTest.mcu_RTC.Day,
							M0_Device_SelfTest.mcu_RTC.Hour,
							M0_Device_SelfTest.mcu_RTC.Minute,
							M0_Device_SelfTest.mcu_RTC.Second,

							M0_Device_SelfTest.Device_SelfCheck);
			break;


		//==========================================================================
		//==========================================================================
		default:

			#if  	Tst_CK_SYSTEM_SLEEP
				system( "echo \"..... ..... default ??? \" >> /home/root/sleeplog" );
			#endif  		//#if  	Tst_CK_SYSTEM_SLEEP

			printf( "RxM0   device SUBTYPE_??? \n" );
			break;


	} 	//switch( rx_payload[0] )		{
} 	//void 	uartM0_rsp_DevStatus( UINT8* rx_payload )




//******************************************************************************
//
//******************************************************************************
/*
	typedef struct  {
	 UINT8         FW_version[2];
	 UINT16         status;
	 UINT8         name[64];
	 UINT32         dataLength;
	 UINT8         data[1600];
	}M0_TLSAM_FRAME;
*/
void 	uartM0_rsp_ENC( UINT8* rx_payload )
{
	uint8_t*	dataPtr;
	int  	i;

	printf("\n");
	printf("RxM0     uartM0_rsp_ENC ---------- ---------- \n" );

	memset( (uint8_t*)&(M0_TLSAM_DATA.tlsam_Data), 0x00, sizeof(M0_TLSAM_FRAME) );

	dataPtr = (uint8_t*)&(M0_TLSAM_DATA.tlsam_Data);
	for( i=0 ; i<A53M0_RxQ.LENGTH ; i++ )		{
		*dataPtr = *rx_payload;
		dataPtr++;
		rx_payload++;
	}


	// 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	#if 	TST_M0_TLSAM_01
		/*
		printf("    [" );
		for( int i=0 ; i<M0_TLSAM_DATA.tlsam_Data.dataLength ; i++ )		{
			printf(" %02X", M0_TLSAM_DATA.tlsam_Data.data[i] );
		}
		printf("]\n");
		*/
		printf("    [%02X]-[%02X][%02X] \n", M0_TLSAM_DATA.tlsam_Data.status, M0_TLSAM_DATA.tlsam_Data.FW_version[0], M0_TLSAM_DATA.tlsam_Data.FW_version[1] );
		printf("    [%04d] [%s] \n", M0_TLSAM_DATA.tlsam_Data.dataLength, M0_TLSAM_DATA.tlsam_Data.name );
		#if 	TST_TxRx_COUNT
			Tst_Rx_Cnt ++;

			a53m0API_currentTime = time( NULL);
			a53m0API_current_tm = localtime (&a53m0API_currentTime);
			printf("    __________ __________ __________ ---------- %02d/%02d/%02d %02d:%02d:%02d  Tst_Rx_Cnt[%04d]\n",
						((a53m0API_current_tm->tm_year+1900)-2000),
						a53m0API_current_tm->tm_mon + 1,
						a53m0API_current_tm->tm_mday,
						a53m0API_current_tm->tm_hour,
						a53m0API_current_tm->tm_min,
						a53m0API_current_tm->tm_sec,
						Tst_Rx_Cnt );
		#endif 	//#if 	TST_TxRx_COUNT
	#endif 		//#if 	TST_M0_TLSAM_01

	if( (strlen(M0_TLSAM_DATA.tlsam_Data.name)>0) && (M0_TLSAM_DATA.tlsam_Data.dataLength>0) )		{
		M0_Status_Update |= M0_DEV_UPDATE_TLSAM;
	} 		//if( (strlen(M0_TLSAM_DATA.tlsam_Data.name)>0) && (M0_TLSAM_DATA.tlsam_Data.dataLength>0) )		{

	// 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	#if TST_M0_TLSAM_SAVE_FILE
		FILE *f_tlsam;
		unsigned char f_name[128];
		
		//	save binary file 		----------------------------------------------------
		bzero( f_name, 64 );
		sprintf( f_name, "%s.tlsam", M0_TLSAM_DATA.tlsam_Data.name );
		printf( "  --1--  f_name :[%s] \n", f_name );

		if( (M0_Status_Update & M0_DEV_UPDATE_TLSAM) > 0 )		{
			f_tlsam = fopen( f_name, "w+b" );
			if( f_tlsam )		{
				fwrite( M0_TLSAM_DATA.tlsam_Data.data, 1, M0_TLSAM_DATA.tlsam_Data.dataLength, f_tlsam );
				fclose( f_tlsam );
			} 		//if( f_tlsam )		{
		} 		//if( strlen(M0_TLSAM_DATA.tlsam_Data.name) > 0 )		{

		//	save text file 		------------------------------------------------------
		unsigned char put_Data[16];
		bzero( f_name, 64 );
		sprintf( f_name, "%s.txt", M0_TLSAM_DATA.tlsam_Data.name );
		printf( "  --2--  f_name :[%s] \n", f_name );

		if( (M0_Status_Update & M0_DEV_UPDATE_TLSAM) > 0 )		{
			f_tlsam = fopen( f_name, "w+b" );
			if( f_tlsam )		{
				for( i=0 ; i<M0_TLSAM_DATA.tlsam_Data.dataLength ; i++ )		{
					bzero( put_Data, 16 );
					sprintf( put_Data, "%02X", M0_TLSAM_DATA.tlsam_Data.data[i] );
					fwrite( put_Data, 1, strlen(put_Data), f_tlsam );

					if( i < (M0_TLSAM_DATA.tlsam_Data.dataLength-1) )	{
						putc( 0x20, f_tlsam );
					}
				} 		//for( i=0 ; i<M0_TLSAM_DATA.tlsam_Data.dataLength ; i++ )		{
				
				fclose( f_tlsam );
			} 		//if( f_tlsam )		{
		} 		//if( strlen(M0_TLSAM_DATA.tlsam_Data.name) > 0 )		{
	#endif 		//#if TST_M0_TLSAM_SAVE_FILE

	printf("\n");
} 		//void 	uartM0_rsp_ENC( UINT8* rx_payload )












//******************************************************************************
//
//******************************************************************************
//case uart_RSP_ALARM:
void 	uartM0_rsp_M0_Alarm( UINT8* rx_payload )
{
	M0_ALARM_A53_FRAME 	m0_Alarm;

	memcpy( (uint8_t*)&m0_Alarm, rx_payload, sizeof(M0_ALARM_A53_FRAME) );


	//	Alarm Sub-Type;			M0 alarm A53
	switch( m0_Alarm.alarm )		{

		case uart_ALARM_TEMP:
			break;


		#if  	Tst_Radar_PW_OFFON
			case uart_ALARM_RADAR_PWON:
				memcpy( (uint8_t*)&m0_Alarm, rx_payload, sizeof(m0_Alarm) );
				printf("RxM0     uartM0_rsp_M0_Alarm : uart_ALARM_RADAR_PWON ---------- ---------- [%02d-%02d-%02d %02d:%02d:%02d] \n",
							m0_Alarm.mcu_RTC.Year,
							m0_Alarm.mcu_RTC.Month,
							m0_Alarm.mcu_RTC.Day,
							m0_Alarm.mcu_RTC.Hour,
							m0_Alarm.mcu_RTC.Minute,
							m0_Alarm.mcu_RTC.Second );

				radar_param_set( );
				break;

			case uart_ALARM_RADAR_PWOFF:
				memcpy( (uint8_t*)&m0_Alarm, rx_payload, sizeof(m0_Alarm) );
				printf("RxM0     uartM0_rsp_M0_Alarm : uart_ALARM_RADAR_PWOFF ---------- ---------- [%02d-%02d-%02d %02d:%02d:%02d] \n",
							m0_Alarm.mcu_RTC.Year,
							m0_Alarm.mcu_RTC.Month,
							m0_Alarm.mcu_RTC.Day,
							m0_Alarm.mcu_RTC.Hour,
							m0_Alarm.mcu_RTC.Minute,
							m0_Alarm.mcu_RTC.Second );

				radar_param_down( );
				break;
		#endif 		//#if  	Tst_Radar_PW_OFFON

	} 		//switch( m0_Alarm.alarm )		{

} 		//void 	uartM0_rsp_M0_Alarm( UINT8* rx_payload )












//******************************************************************************
//
//******************************************************************************
void 	uartM0_rsp_read_EEP( UINT8* rx_payload )
{
	printf("RxM0     uartM0_rsp_read_EEP ---------- ---------- \n" );

	uint16_t  	Addr;
	uint16_t  	Length;


	Addr = *rx_payload;
	Addr |= *(rx_payload+1) << 8;

	Length = *(rx_payload+2);
	Length |= *(rx_payload+3) << 8;

	printf( "  A[%04X] L[%04d] : [", Addr, Length );
	for( int i=0 ; i < Length ; i++ )		{
		if( (i%16)==0 )		{
			printf( "\n" );
		}
		printf( " %02X", *(rx_payload+4+i) );
	}
	printf( "]\n" );

} 		//void 	uartM0_rsp_read_EEP( UINT8* rx_payload )


//******************************************************************************
//
//******************************************************************************
void 	uartM0_rsp_DummingTest( UINT8* rx_payload )
{
	int  dataLength = 0;;
	int  i;

		#if 	TST_TxRx_COUNT
			uint32_t 	Rx_M0 = 0;

			ftime( &time_Rx );

			Rx_M0 = *rx_payload;
			Rx_M0 |= *(rx_payload+1) << 8;
			Rx_M0 |= *(rx_payload+2) << 16;
			Rx_M0 |= *(rx_payload+3) << 24;

			Tst_Rx_Cnt++;
			//printf("  ****Rx[%04d][%08d]\n", A53M0_RxQ.LENGTH, Tst_Rx_Cnt );
			//printf("  - Rx[%04d][%05d][%05d]\n", A53M0_RxQ.LENGTH, Tst_Rx_Cnt, Rx_M0 );
			printf("  - Rx[%05d][%05d] [%05d]  x%04d-%ldms\n", 
						Tst_Tx_Cnt, 
						Tst_Rx_Cnt, 
						Rx_M0, 
						crc_ErrorCnt,
						((time_Rx.time*1000)+time_Rx.millitm)-((time_Tx.time*1000)+time_Tx.millitm) );
		#else


			dataLength = A53M0_RxQ.LENGTH -3;
			printf( "  ===== uartM0_rsp_DummingTest [%d]  : [", A53M0_RxQ.LENGTH );
			for (int i = 0; i < (dataLength); ++i)
			{
				printf( " %02X", *rx_payload );
				*rx_payload++;
			}


			printf( "] \n\n" );


		#endif 		//#if 	TST_TxRx_COUNT

} 		//void 	uartM0_rsp_DummingTest( UINT8* rx_payload )

