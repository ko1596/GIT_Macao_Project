

#include "m0All_Header.h"


//********************************************************************
//	Global
unsigned char   A53M0_TxBuf[UARTA53M0_TX_BUFFER_SIZE];
int 	A53M0_TxLength;
int 	A53M0_Tx;

int  	flg_M0uart_Tx;


//====================================================================
struct timeb  	time_A53_awake1;
struct timeb  	time_A53_awake2;




//********************************************************************
//
//********************************************************************
void  uartA53M0_Tx_thread( int* fdPtr )
{
	int i;
  a53m0API_currentTime = time( NULL);
  a53m0API_current_tm = localtime (&a53m0API_currentTime);

  printf( "********** **********  Thread uartA53M0_Tx_thread Start  ********** ********** \n" );

  int res;

  
  //sleep( 0.5 );
  int tst_a53TxCnt = 1;

  flg_M0uart_Tx = 0;
  
  //******************************************************************
  while( 1 )  {

  	if( A53M0_TxLength > 0 )		{
			a53m0API_currentTime = time( NULL);
			a53m0API_current_tm = localtime (&a53m0API_currentTime);


	    res = write( fd_uartA53M0, A53M0_TxBuf, A53M0_TxLength );
	    if( res == -1 ) {
	      printf( "uartA53M0_Tx_thread XXXXXXXXXX res = [%d] \n", res );
	      usleep( 5000 );  	//5ms
	    }
	    else  {
	      //printf( "        ---------------------- res = [%d] \n", res );
	      //printf( "                                 res = [%d] \n", res );
	      A53M0_Tx += res;
	      //printf("  Tx[%d][%d]\n", res, A53M0_Tx );
	      if( A53M0_Tx >= A53M0_TxLength )	{
	      	usleep( 10000 );  	//10ms
	      	A53M0_TxLength = 0;
	      	flg_M0uart_Tx = 0;
				}
				usleep( 5000 );  	//5ms; 		20211115TR3L2
	    } 

	    //usleep( 50000 );  	//50ms
	    //usleep( 25000 );  	//25ms
	    //usleep( 10000 );  	//10ms
	    //usleep( 5000 );  	//5ms
  	} 	//if( A53M0_TxLength > 0 )		{
  	else 	{
  		//usleep( 100000 );  	//100ms
  		//usleep( 50000 );  	//50ms
  		//usleep( 40000 );  	//40ms
  		//usleep( 30000 );  	//30ms
  		//usleep( 25000 );  	//25ms
  		//usleep( 20000 );  	//20ms
  		usleep( 10000 );  	//10ms
  	}

  }   //while( 1 )  {

  printf( " ___________  Thread uartA53M0_Tx_thread End  ___________ \n\n" );  	
} 	//void  uartA53M0_Tx_thread( int* fdPtr )












//********************************************************************
//
//********************************************************************
void  A53_awake_thread( int* fdPtr )
{
	UINT32 	cnt = 0;
	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);

	uartA53M0_Set_M0_A53Status_Awake( );

	ftime( &time_A53_awake1 );
	ftime( &time_A53_awake2 );

	printf( "********** **********  Thread A53_awake_thread Start  ********** ********** \n" );

	//******************************************************************
	while( 1 )		{

		ftime( &time_A53_awake2 );
		if( ((time_A53_awake2.time*1000)+time_A53_awake2.millitm) - ((time_A53_awake1.time*1000)+time_A53_awake1.millitm) >  100 )		{  		//	100ms

			ftime( &time_A53_awake1 );

			if( (cnt % 2) == 0 )		{
				A53M_SleepState_gpio_H( );
			}
			else  	{
				A53M_SleepState_gpio_L( );
			}

			cnt++;
		}  		//	if(......................)

		usleep( 20000 );  			//	50ms
	}  		//while( 1 )		{
}  		//void  A53_awake_thread( int* fdPtr )











//********************************************************************
//
//********************************************************************
struct timeb  	time_wifiAP_ck1;
struct timeb  	time_wifiAP_ck2;

void  wifiAP_ck_thread( void )
{
	int i;
  a53m0API_currentTime = time( NULL);
  a53m0API_current_tm = localtime (&a53m0API_currentTime);

  printf( "********** **********  Thread wifiAP_ck_thread Start  ********** ********** \n" );

  FILE *f_wifiAPlog;
  int  f_size;

  A53_CK_wifiAP_Enable = 0;

  uartA53M0_Set_M0_A53Status_Awake( );
  sleep( 15 );
  uartA53M0_Set_M0_A53Status_Awake( );

  ftime( &time_wifiAP_ck1 );
  ftime( &time_wifiAP_ck2 );

  //******************************************************************
  while( 1 )  {

  	usleep( 500000 ); 		//	500ms
  	
  	ftime( &time_wifiAP_ck2 );
  	//if( (((time_wifiAP_ck2.time*1000)+time_wifiAP_ck2.millitm)-((time_wifiAP_ck1.time*1000)+time_wifiAP_ck1.millitm) >=  2500) && (A53_CK_wifiAP_Enable == 0) )		{  		//	2sec
  	if( (((time_wifiAP_ck2.time*1000)+time_wifiAP_ck2.millitm)-((time_wifiAP_ck1.time*1000)+time_wifiAP_ck1.millitm) >=  2500) )			{  		//	2.5sec

  		ftime( &time_wifiAP_ck1 );

			a53m0API_currentTime = time( NULL);
			a53m0API_current_tm = localtime (&a53m0API_currentTime);

			//==============================================================
  		if( A53_CK_wifiAP_Enable >= 0 )		{

				system( "ifconfig uap0 | grep \"inet addr\" > /home/root/wifiAPlog" );
				usleep( 10000);  	//	10ms
				f_wifiAPlog = fopen( "/home/root/wifiAPlog", "r+b" );
				if( f_wifiAPlog )		{
					fseek ( f_wifiAPlog , 1 , SEEK_END );
					f_size = ftell( f_wifiAPlog );
					fseek ( f_wifiAPlog , 1 , SEEK_SET );

					if( f_size < 50 )		{
						printf( "\n    ++++++++++ ---------- WiFi-AP restart : [%02d/%02d/%02d %02d:%02d:%02d] 1\n",
															((a53m0API_current_tm->tm_year+1900)-2000),
															a53m0API_current_tm->tm_mon + 1,
															a53m0API_current_tm->tm_mday,
															a53m0API_current_tm->tm_hour,
															a53m0API_current_tm->tm_min,
															a53m0API_current_tm->tm_sec		 );
						system( "systemctl restart hostapd" );
					}  		//if( f_size < 10 )		{

					else  	{
						A53_CK_wifiAP_Enable = 0;
					}  		//if( f_size < 10 )		{				else

					fclose( f_wifiAPlog );
				}  	//if( f_wifiAPlog )		{

				else 	{
					printf( "\n    ++++++++++ ---------- WiFi-AP restart : [%02d/%02d/%02d %02d:%02d:%02d] 2\n",
														((a53m0API_current_tm->tm_year+1900)-2000),
														a53m0API_current_tm->tm_mon + 1,
														a53m0API_current_tm->tm_mday,
														a53m0API_current_tm->tm_hour,
														a53m0API_current_tm->tm_min,
														a53m0API_current_tm->tm_sec		 );
					system( "systemctl restart hostapd" );
				}  	//if( f_wifiAPlog )		{  				else

  		}  		//if( A53_CK_wifiAP_Enable >= 0 )		{

  	}  	//if( ((time_wifiAP_ck2.time*1000)+time_wifiAP_ck2.millitm)-((time_wifiAP_ck1.time*1000)+time_wifiAP_ck1.millitm) >=  2000 )		{  		//	2sec
  }  	//while( 1 )  {

}  	//void  wifiAP_ck_thread( void )




















//  ****************************************************************************
//  CRC16_CCITT_KERMIT
//  ZigBee use this
//  ****************************************************************************
UINT16  Get_Kermit_CRC16( UINT8* dataPtr, UINT32 length )
{
  UINT8   i;  
  UINT16  crc16 = 0x0000;
  

  while( length ) {
    crc16 ^= *dataPtr;
    

    for(i=0 ; i<8 ; i++)  {
      if(crc16 & 0x01)  { /* LSB(b0)=1 */
        //crc16 = (crc16>>1) ^ 0xA001;  //  CRC-16 (Modbus)
        crc16 = (crc16>>1) ^ 0x8408;  //  CRC-CCITT (Kermit)
      }
      else  {
        crc16 = crc16 >>1;
      }
    } //  for(i=0 ; i<8 ; i++)  {
    dataPtr++;
    length--;
  } //while( length )


  return  crc16;
}    //UINT16  Get_Kermit_CRC16( UINT8* dataPtr, UINT32 length )


//  ****************************************************************************
//  CRC16 Modbus
//  ****************************************************************************
UINT16  Get_ModBus_CRC16( UINT8* dataPtr, UINT32 length )
{
  UINT8 i;
  UINT16  crc16 = 0xFFFF;   //  CRC-16 (Modbus)

  while( length ) {
    crc16 ^= *dataPtr;
    for(i=0 ; i<8 ; i++)  {
      if(crc16 & 0x01)  { /* LSB(b0)=1 */
        crc16 = (crc16>>1) ^ 0xA001;  //  CRC-16 (Modbus)
      }
      else  {
        crc16 = crc16 >>1;
      }
    } //  for(i=0 ; i<8 ; i++)  {
    dataPtr++;
    length--;
  } //while( length )

  return  crc16;
}     //UINT16  Get_ModBus_CRC16( UINT8* dataPtr, UINT32 length )




















//********************************************************************
//
//********************************************************************
void 	uartA53M0_Req_Dumming_Test( void )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	int  	i;


	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	#if 	TST_TxRx_COUNT
		ftime( &time_Tx );
		Tst_Tx_Cnt++;
		//printf(" ========== uartA53M0_Req_Dumming_Test  [%05d] \n", Tst_Tx_Cnt);

		//printf(" ========== uartA53M0_REQM0_SystemInfo ---------- ---------- Tx[%08d]\n", Tst_Tx_Cnt);
		//printf("  ****Tx[%08d]\n", Tst_Tx_Cnt);
	#else
		printf(" ========== uartA53M0_Req_Dumming_Test ---------- ---------- \n");
	#endif 		//#if 	TST_TxRx_COUNT


  *txPtr = 0xCC; 						txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_M0_DUMMING;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;

  //..................................................................
  *txPtr = 0x00; 						txPtr++; 		// Test sub-function

  //..................................................................
  //	Dumming Test Data
  for( i=0 ; i<1024 ; i++ )		{
  	*txPtr = i + 0x11;
  	txPtr++;
  }


	//------------------------------------------------------------------
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );

} 		//void 	uartA53M0_Req_Dumming_Test( void )





















//********************************************************************
//
//********************************************************************
void 	uartA53M0_SetM0_currentRTC( void )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf("\n ========== uartA53M0_SetM0_currentRTC ---------- [%02d/%02d/%02d %02d:%02d:%02d] \n",
			((a53m0API_current_tm->tm_year+1900)-2000),
			a53m0API_current_tm->tm_mon + 1,
			a53m0API_current_tm->tm_mday,
			a53m0API_current_tm->tm_hour,
			a53m0API_current_tm->tm_min,
			a53m0API_current_tm->tm_sec		 );



  *txPtr = 0xCC; 				txPtr++;

  //	UARTcmd 	Len
  *txPtr = 0x00; 				txPtr++;
  *txPtr = 0x00; 				txPtr++;

  //	UARTcmd 	Cmd
  *txPtr = uart_SET_M0_RTC;
  txPtr++;

  //	UARTcmd 	CRC
  *txPtr = 0x00; 				txPtr++;
  *txPtr = 0x00; 				txPtr++;

  //	RTC data
  *txPtr = ((a53m0API_current_tm->tm_year+1900)-2000);
  txPtr++;
  *txPtr = a53m0API_current_tm->tm_mon + 1;
  txPtr++;
  *txPtr = a53m0API_current_tm->tm_mday;
  txPtr++;
  *txPtr = a53m0API_current_tm->tm_hour;
  txPtr++;
  *txPtr = a53m0API_current_tm->tm_min;
  txPtr++;
  *txPtr = a53m0API_current_tm->tm_sec;
  txPtr++;


  //==================================================================
  int tx_length = txPtr - A53M0_TxBuf;
  A53M0_TxBuf[1] = (tx_length-3) & 0x00FF;
  A53M0_TxBuf[2] = ((tx_length-3) >>8 ) & 0x00FF;

  UINT16 	crc16 = Get_ModBus_CRC16( A53M0_TxBuf+6, 6 );
  A53M0_TxBuf[4] = crc16 & 0x00FF;
  A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	#if 	TST_DEBUF_PRINT_001
		int i;
		printf("TX uartA53M0_SetM0_currentRTC : [");
		for( i=0 ; i<tx_length ; i++ )		{
			printf(" %02X", A53M0_TxBuf[i]);
		}
		printf("]\n");
		
	#endif 	//#if 	TST_DEBUF_PRINT_001

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = tx_length;
} 	//void 	uartA53M0_SetM0_currentRTC( void )


//********************************************************************
//
//********************************************************************
void 	uartA53M0_REQM0_RTC( void )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	printf(" ========== uartA53M0_REQM0_RTC ---------- ---------- \n");

  *txPtr = 0xCC; 				txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x01; 				txPtr++;
  *txPtr = 0x00; 				txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_M0_RTC;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = 4;
} 	//void 	uartA53M0_REQM0_RTC( void )


//********************************************************************
//
//********************************************************************
void 	uartA53M0_REQM0_SystemInfo( void )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	//printf(" ========== uartA53M0_REQM0_SystemInfo ---------- ---------- \n");

  *txPtr = 0xCC; 				txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x01; 				txPtr++;
  *txPtr = 0x00; 				txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_M0_INFO;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = 4;
} 		//void 	uartA53M0_REQM0_SystemInfo( void )





















//********************************************************************
//
//********************************************************************
//	Req. M0 temperature
void 	uartA53M0_REQM0_Temp( void )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	//printf(" ========== uartA53M0_REQM0_Temp ---------- ---------- \n");

  *txPtr = 0xCC; 						txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_DEV_STATUS;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;

	*txPtr = SUBTYPE_TEMPERATURE; 	txPtr++;


	//------------------------------------------------------------------
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], 1 );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
} 		//void 	uartA53M0_REQM0_Temp( void )


//********************************************************************
//
//********************************************************************
//	Req. M0 Power Meter 		LTC2944
#if  DELETE_FUNCTION

void 	uartA53M0_REQM0_PwMeter( void )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	//printf(" ========== uartA53M0_REQM0_PwMeter ---------- ---------- \n");

  *txPtr = 0xCC; 						txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_DEV_STATUS;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;

	*txPtr = SUBTYPE_PW_METER0; 	txPtr++;


	//------------------------------------------------------------------
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], 1 );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
}  		//void 	uartA53M0_REQM0_PwMeter( void )

#endif  	//#if  DELETE_FUNCTION


//********************************************************************
//
//********************************************************************
//	Req. M0 Power Meter 		LTC2944
void 	uartA53M0_REQM0_G_Sensor( void )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	//printf(" ========== uartA53M0_REQM0_G_Sensor ---------- ---------- \n");

  *txPtr = 0xCC; 						txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_DEV_STATUS;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;

	*txPtr = SUBTYPE_G_SENSOR; 	txPtr++;


	//------------------------------------------------------------------
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], 1 );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
}  		//void 	uartA53M0_REQM0_G_Sensor( void )


//********************************************************************
//
//********************************************************************
void 	uartA53M0_REQM0_Power( void )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	//printf(" ========== uartA53M0_REQM0_Power ---------- ---------- \n");

  *txPtr = 0xCC; 						txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_DEV_STATUS;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;

	*txPtr = SUBTYPE_ADC; 		txPtr++;


	//------------------------------------------------------------------
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], 1 );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
	//printf(" ... TEST uartA53M0_REQM0_Power [%d] [%02X] \n", (txPtr - A53M0_TxBuf), crc16 );
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
} 		//void 	uartA53M0_REQM0_Power( void )


//********************************************************************
//
//********************************************************************
void 	uartA53M0_REQM0_SelfTest( void )
{	unsigned char 	*txPtr = A53M0_TxBuf;
	int  i;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;


  a53m0API_currentTime = time( NULL);
  a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf(" ========== uartA53M0_REQM0_SelfTest ----------  [%02d/%02d/%02d %02d:%02d:%02d] \n",
			((a53m0API_current_tm->tm_year+1900)-2000),
			a53m0API_current_tm->tm_mon + 1,
			a53m0API_current_tm->tm_mday,
			a53m0API_current_tm->tm_hour,
			a53m0API_current_tm->tm_min,
			a53m0API_current_tm->tm_sec		 );

	if( (OTA_Radar.cmd != RADAR_OTACMD_NOTHING) && (OTA_Radar.cmd == RADAR_OTACMD_SET_PARAMETER) )	{
		printf( "\n XXXXX XXXXX  uartA53M0_REQM0_SelfTest Error, Radar can not Self-Test Now  !!!!! \n\n" );
		return;
	}


  *txPtr = 0xCC; 							txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_DEV_STATUS;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;

  *txPtr = SUBTYPE_SELFTEST; 		txPtr++;

	//------------------------------------------------------------------
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );

}  		//void 	uartA53M0_REQM0_SelfTest( void )



















//********************************************************************
//
//********************************************************************
/*
	//------------------------------------------------------------------------------
	typedef struct  {
		UINT8 	Hour;
		UINT8 	Minute;
		UINT8 	Second;
		UINT8 	nc;
	}TIME_PERIOD_FRAME;

	typedef struct  {
		TIME_PERIOD_FRAME  		Fee_Start;
		TIME_PERIOD_FRAME  		Fee_End;
		TIME_PERIOD_FRAME  		period_FeeFree_CKcar;  		//	for  TIMER*
		UINT8 								Fee_Free_Enable;
		UINT8 								flg_FeeTime;  		//=0, Not Fee Free;		=1, Fee Free
		UINT16 	nc;
	}FEE_PARAM_FRAME;

	typedef struct  {
		UINT8  								exist;  				//=1, Radar exist;		=0, No Radar
		UINT8  								nc01;
		UINT8  								nc02;
		UINT8  								nc03;
		TIME_PERIOD_FRAME  		car_car_ck; 		// CK. second
	}RADAR_PARAM_FRAME;

	//------------------------------------------------------------------------------
	typedef struct  {
		FEE_PARAM_FRAME 						fee_time;

		RADAR_PARAM_FRAME 					radarA;
		RADAR_PARAM_FRAME 					radarB;

		TIME_PERIOD_FRAME  					period_heartbeat;

		TIME_PERIOD_FRAME  					power_reset_wdt;
	}M0_SYS_PARAMETER_FRAM;
*/
//	M0_SYS_PARAMETER_FRAM 	M0_Sys_Parameter;
void 	uartA53M0_Set_M0_Sys_parameter( void )
{
	int  i;

	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	printf(" ========== uartA53M0_Set_M0_Sys_parameter( ) ========== ========== \n");

  *txPtr = 0xCC; 							txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_SET_DEV;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;

  *txPtr = SUBTYPE_M0_SYS; 		txPtr++;

  //------------------------------------------------------------------
  unsigned char 	*dataBuf = (unsigned char*)&M0_Sys_Parameter;
  for( i=0 ; i<sizeof(M0_SYS_PARAMETER_FRAM) ; i++ )		{
  	*txPtr = *dataBuf;
  	dataBuf++;
  	txPtr++;
  }


	//==================================================================
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
}  		//void 	uartA53M0_Set_M0_Sys_parameter( void )



//********************************************************************
//
//********************************************************************
void 	uartA53M0_Req_M0_Sys_parameter( void )
{
	int  i;

	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	printf(" ========== uartA53M0_Req_M0_Sys_parameter( ) ========== ========== \n");

  *txPtr = 0xCC; 							txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_DEV_STATUS;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;

  *txPtr = SUBTYPE_M0_SYS; 		txPtr++;


	//==================================================================
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
}  		//void 	uartA53M0_Req_M0_Sys_parameter( void )




//********************************************************************
//
//********************************************************************
void 	uartA53M0_Set_M0_A53Status_Awake( void )
{
	int  i;

	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	printf(" ========== uartA53M0_Set_M0_A53Status_Awake( ) ========== ========== \n");

  *txPtr = 0xCC; 							txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_SET_DEV;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;

  *txPtr = SUBTYPE_A53_AWAKESLEEP; 	txPtr++;
  *txPtr = 0x01; 							txPtr++;


	//==================================================================
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
}  		//void 	uartA53M0_Set_M0_A53Status_Awake( void )


//********************************************************************
//
//********************************************************************
void 	uartA53M0_Set_M0_A53Status_Sleep( void )
{
	int  i;

	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	printf(" ========== uartA53M0_Set_M0_A53Status_Sleep( ) ========== ========== \n");

  *txPtr = 0xCC; 							txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_SET_DEV;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;

  *txPtr = SUBTYPE_A53_AWAKESLEEP; 	txPtr++;
  *txPtr = 0x00; 							txPtr++;


	//==================================================================
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
}  		//void 	uartA53M0_Set_M0_A53Status_Sleep( void )










//********************************************************************
//
//********************************************************************
void 	uartA53M0_Set_Chili2S_PAN_ADD( UINT16 panid, UINT16 sAddr, UINT8 rf_channel )
{
	int  i;

	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	printf(" ========== uartA53M0_Set_Chili2S_PAN_ADD ========== ========== \n");

  *txPtr = 0xCC; 							txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_SET_DEV;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;

  *txPtr = SUBTYPE_LIDAR; 		txPtr++;

  //------------------------------------------------------------------
  *txPtr = 0xFD; 						txPtr++;

  *txPtr = (UINT8)panid; 						txPtr++;
  *txPtr = (UINT8)(panid>>8); 			txPtr++;
  *txPtr = (UINT8)sAddr; 						txPtr++;
  *txPtr = (UINT8)(sAddr>>8); 			txPtr++;

  *txPtr = (UINT8)rf_channel; 						txPtr++;


	//==================================================================
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
}  	//void 	uartA53M0_Set_Chili2S_PAN_ADD( UINT16 panid, UINT16 sAddr )












//********************************************************************
//
//********************************************************************
//	CMD 	uart_REQ_DEV_STATUS
//		SUBTYPE_RADAR_A						0x21
//		SUBTYPE_RADAR_B						0x22
void 	uartA53M0_Req_Radar_Status( void )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	//printf(" ========== uartA53M0_REQM0_Radar Status ---------- ---------- \n");

  *txPtr = 0xCC; 						txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_DEV_STATUS;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;

	*txPtr = SUBTYPE_RADAR_A; 		txPtr++;

	//------------------------------------------------------------------
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], 1 );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
} 		//void 	uartA53M0_Req_Radar_Status( void )


//********************************************************************
//
//********************************************************************
//	CMD 	21
//		SUBTYPE_RADAR_A						0x21
//		SUBTYPE_RADAR_B						0x22
void 	uartA53M0_Get_Radar_FWver( void )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	printf(" ========== uartA53M0_Get_Radar_FWver ==========  ========== \n");

  *txPtr = 0xCC; 							txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_DEV_FW_VER;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;

 	*txPtr = SUBTYPE_RADAR_A; 	txPtr++;

	//------------------------------------------------------------------
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
} 		//void 	uartA53M0_Get_Radar_FWver( void )


//********************************************************************
//
//********************************************************************
void 	uartA53M0_Set_Radar_Parameter( M0_RADAR_SET_FRAME* radarA_set_Ptr, M0_RADAR_SET_FRAME* radarB_set_Ptr )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;


	M0_RADAR_SET_FRAME 	param_null;
	UINT8* 	dataPtr;
	int  i;

	printf(" ========== uartA53M0_Set_Radar_Parameter ---------- ---------- \n");
	if( (radarA_set_Ptr == 0) || (radarB_set_Ptr == 0) )		{		
		memset( (UINT8*)&param_null, 0x00, sizeof(M0_RADAR_SET_FRAME) );
		param_null.L_R = 0xFF;
		printf(" .......... uartA53M0_Set_Radar_Parameter  param=0 \n");
	}

	printf( "\n uartA53M0_Set_Radar_Parameter TEST : [" );

	//==================================================================
  *txPtr = 0xCC; 						txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_DEV_RESTART;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;

	*txPtr = SUBTYPE_RADAR_A; 		txPtr++; 			//	*txPtr = SUBTYPE_RADAR_B; 		txPtr++;


	#if 	M0_RADAR_VER_30_210930
		//	Radar A
		if( radarA_set_Ptr == 0 )	{
			radarA_set_Ptr = (M0_RADAR_SET_FRAME*)&param_null;
		}
		
		dataPtr = radarA_set_Ptr;
		for( i=0 ; i<sizeof(M0_RADAR_SET_FRAME) ; i++ )		{
			*txPtr = *dataPtr;
			printf( " %02X", *txPtr );
			txPtr++;
			dataPtr++;
		}

		//	Radar B
		if( radarB_set_Ptr == 0 )	{
			radarB_set_Ptr = (M0_RADAR_SET_FRAME*)&param_null;
		}
		
		dataPtr = radarB_set_Ptr;
		for( i=0 ; i<sizeof(M0_RADAR_SET_FRAME) ; i++ )		{
			*txPtr = *dataPtr;
			printf( " %02X", *txPtr );
			txPtr++;
			dataPtr++;
		}
		printf( "] TEST \n\n" );

	#else  	//#if 	M0_RADAR_VER_30_210930
	#endif  	//#if 	M0_RADAR_VER_30_210930

	//------------------------------------------------------------------
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
} 		//void 	uartA53M0_Set_Radar_Parameter( M0_RADAR_SET_FRAME* radarA_set_Ptr, M0_RADAR_SET_FRAME* radarB_set_Ptr )




//********************************************************************
//
//********************************************************************
//	show=0,  Normale; 		show=1, Show ALL Radar data
void 	uartA53M0_Set_Radar_ShowAllData( uint8_t show )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	printf(" ========== uartA53M0_Set_Radar_ShowAllData ==========  [%d] \n", show);

  *txPtr = 0xCC; 							txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_SET_DEV;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;

 	*txPtr = SUBTYPE_RADAR_A; 	txPtr++;
 	//*txPtr = SUBTYPE_RADAR_B; 	txPtr++;

 	*txPtr = 0x00; 							txPtr++;  		//	ShowAllData Function
 	*txPtr = show; 							txPtr++;  		//	=0, No ShowALL;  =1, ShowALL

	//------------------------------------------------------------------
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
} 		//void 	uartA53M0_Set_Radar_ShowAllData( uint8_t show )























//********************************************************************
//
//********************************************************************
//	BatA_B =0,	Bat_A
//	BatA_B =1,	Bat_B
void 	uartA53M0_Set_Bat_Source( UINT8 BatA_B )
{
	unsigned char 	*txPtr = A53M0_TxBuf;
	int  i;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;


	if( BatA_B == 0 )	{
		printf(" ========== uartA53M0_Set_Bat_Source ---------- A \n");
	}
	else if( BatA_B == 1 )	{
		printf(" ========== uartA53M0_Set_Bat_Source ---------- B \n");
	}
	else 	{
		return;
	}
	


  *txPtr = 0xCC; 							txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_SET_DEV;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;

  *txPtr = SUBTYPE_PW_BAT; 		txPtr++;
  
	*txPtr = 0x00; 							txPtr++;		//	Reserve
	*txPtr = BatA_B; 						txPtr++;		//	select Bat_A / Bat_B


	//------------------------------------------------------------------
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );

} 		//void 	uartA53M0_Set_Bat_Source( UINT8 BatA_B )




//********************************************************************
//
//********************************************************************
//	UINT16 time; 100ms
void 	uartA53M0_Set_Gesture_SkipTime( UINT16 time )
{
	unsigned char 	*txPtr = A53M0_TxBuf;
	int  i;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	printf(" ========== uartA53M0_Set_Gesture_SkipTime ---------- [%04X][%d] \n", time, time);


  *txPtr = 0xCC; 							txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_SET_DEV;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;

  *txPtr = SUBTYPE_MGC3130; 		txPtr++;
  
	*txPtr = time; 							txPtr++;
	*txPtr = (time >> 8); 						txPtr++;

	//------------------------------------------------------------------
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
}  		//void 	uartA53M0_Set_Gesture_SkipTime( UINT16 time )



















//********************************************************************
//
//********************************************************************
void 	uartA53M0_TLSAM_Encrypt( uint8_t *enc_file_name, uint8_t *enc_data, uint16_t enc_dataLength )
{
	unsigned char 	*txPtr = A53M0_TxBuf;
	int  i;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;


	printf(" ========== uartA53M0_TLSAM_Encrypt ========== [%s] \n", enc_file_name);

	if( enc_dataLength > 1000 )		{
		printf("    !!!!!  uartA53M0_TLSAM_Encrypt Data too much [%d]  !!!!! \n", enc_dataLength);
		return;
	}
	

  *txPtr = 0xCC; 						txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_ENC;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 						txPtr++;
  *txPtr = 0x00; 						txPtr++;

  //..................................................................
  //	reserve
  *txPtr = 0x00; 						txPtr++;

  //..................................................................
  //	enc_file_name
  unsigned char  fname[64];
  bzero( fname, 64 );
  sprintf( fname, "%s", enc_file_name );

  printf( "  fname Tx[" );
  for( i=0 ; i<64 ; i++ )		{
  	*txPtr = fname[i]; 						txPtr++;
  	printf( " %02X", fname[i] );
  }
  printf( "] \n" );

  //..................................................................
  //	enc_dataLength
  *txPtr = (enc_dataLength>>8) & 0x00FF; 			txPtr++;
  *txPtr = (enc_dataLength) & 0x00FF; 			txPtr++;

  //..................................................................
  //	enc_data
  printf( "\n" );
  printf( "  enc_data Tx[" );
  for( i=0 ; i<enc_dataLength ; i++ )		{
  	*txPtr = enc_data[i]; 						txPtr++;
  	printf( " %02X", enc_data[i] );
  }
  printf( "] \n" );


	//------------------------------------------------------------------
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );

	#if 	TST_TxRx_COUNT
		//Tst_Tx_Cnt ++;

		a53m0API_currentTime = time( NULL);
		a53m0API_current_tm = localtime (&a53m0API_currentTime);			
		printf("    __________ __________ __________ __________ %02d/%02d/%02d %02d:%02d:%02d  Tst_Tx_Cnt[%04d]\n", 
					((a53m0API_current_tm->tm_year+1900)-2000),
					a53m0API_current_tm->tm_mon + 1,
					a53m0API_current_tm->tm_mday,
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec,
					Tst_Tx_Cnt );
		printf("\n");
	#endif 	//#if 	TST_TxRx_COUNT
} 		//void 	uartA53M0_TLSAM_Encrypt( uint8_t *enc_file_name, uint8_t *enc_data, uint8_t enc_dataLength )

















//********************************************************************
//
//********************************************************************
void 	uartA53M0_EEPROM_Save( uint16_t addr, uint16_t length, uint8_t* dataPtr )
{
	unsigned char 	*txPtr = A53M0_TxBuf;
	int  i;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	printf(" ========== uartA53M0_EEPROM_Save ---------- ---------- \n");

	//==================================================================
  *txPtr = 0xCC; 							txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_SAVE_EEPROM;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;

	//
	*txPtr = addr & 0x00FF; 					txPtr++;
	*txPtr = (addr>>8) & 0x00FF; 			txPtr++;
	*txPtr = length & 0x00FF; 				txPtr++;
	*txPtr = (length>>8) & 0x00FF; 		txPtr++;

	//
	uint8_t* 	ptr = dataPtr;
	for( i=0 ; i<length ; i++ )		{
		*txPtr = *ptr;
		txPtr++;
		ptr++;
	} 		//for( i=0 ; i<length ; i++ )		{


	//------------------------------------------------------------------
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );
} 		//void 	uartA53M0_EEPROM_Save( uint16_t addr, uint16_t length, uint8_t* dataPtr )


//********************************************************************
//
//********************************************************************
void 	uartA53M0_EEPROM_Read( uint16_t addr, uint16_t length, uint8_t* dataPtr )
{
	unsigned char 	*txPtr = A53M0_TxBuf;
	int  i;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;


	printf(" ========== uartA53M0_EEPROM_Read ---------- ---------- \n");

	//==================================================================
  *txPtr = 0xCC; 							txPtr++;
  //	UARTcmd 	Len
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;
  //	UARTcmd 	Cmd
  *txPtr = uart_REQ_READ_EEPROM;
  txPtr++;
  //	UARTcmd 	crc16
  *txPtr = 0x00; 							txPtr++;
  *txPtr = 0x00; 							txPtr++;

	//
	*txPtr = addr & 0x00FF; 					txPtr++;
	*txPtr = (addr>>8) & 0x00FF; 			txPtr++;
	*txPtr = length & 0x00FF; 				txPtr++;
	*txPtr = (length>>8) & 0x00FF; 		txPtr++;

	//------------------------------------------------------------------
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = (txPtr - A53M0_TxBuf );

} 		//void 	uartA53M0_EEPROM_Read( uint16_t addr, uint16_t length, uint8_t* dataPtr )



//********************************************************************
//  	Radar F/W OTA
//********************************************************************

