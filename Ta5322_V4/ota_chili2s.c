

//********************************************************************
// 	ota_chili2s.c
// 				20220127 			Daniel
//********************************************************************

#include "m0All_Header.h"


//********************************************************************
//	Global
M0_CHILI2S_OTA_FRAME  	OTA_Chili2s;


//====================================================================
unsigned char   path_Chili2sOTA_BIN[128] = "/home/root/grids/EPM/firmware/chili2s/";



//********************************************************************
extern 	int 	A53M0_Tx;
extern 	M0_UART_FIFO		A53M0_RxQ;

extern 	UINT8 	M0A53_Rx_Payload[];

extern 	time_t a53m0API_currentTime;
extern 	struct tm *a53m0API_current_tm;










//********************************************************************
//
//********************************************************************
void  Chili2s_OTA_thread( void )
{

	OTA_Chili2s.cmd = CHILI2S_OTACMD_NOTHING;

	printf( "********** **********  Thread Chili2s_OTA_thread Start  ********** ********** \n" );

	while( 1 )		{
		if( OTA_Chili2s.cmd != CHILI2S_OTACMD_NOTHING )		{
			a53m0API_currentTime = time( NULL);
			a53m0API_current_tm = localtime (&a53m0API_currentTime);
		}

		//****************************************************************
		//	== CHILI2S_OTACMD_START
		//****************************************************************
		if( OTA_Chili2s.cmd == CHILI2S_OTACMD_START )		{
			printf( "\n\n********** **********  Chili2s_OTA_thread : CHILI2S_OTACMD_START  ********** [%02d/%02d/%02d %02d:%02d:%02d] \n",
					((a53m0API_current_tm->tm_year+1900)-2000),
					a53m0API_current_tm->tm_mon + 1,
					a53m0API_current_tm->tm_mday,
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec	 );


			//	Get BIN file  	============================================
			if( OTA_Chili2s_get_BIN( ) != 0 )		{
				printf( "\n********** **********  Chili2s_OTA_thread : CHILI2S_OTACMD_START  Error XXXXX \n\n");
				OTA_Chili2s.cmd = CHILI2S_OTACMD_NOTHING;
			}  		//if( OTA_Chili2s_get_BIN( ) != 0 )		{
			else 	{				
				printf( "\n********** **********  Chili2s_OTA_thread : CHILI2S_OTACMD_START  OOOOO OOOOO \n\n");
				usleep( 250000 );  	//250ms
				OTA_Chili2s.cmd = CHILI2S_OTACMD_INIT;
			}  		//if( OTA_Chili2s_get_BIN( ) != 0 )		{			else

		}  		//if( OTA_Chili2s.cmd == CHILI2S_OTACMD_START )		{




		//****************************************************************
		//	== CHILI2S_OTACMD_INIT
		//****************************************************************
		else if( OTA_Chili2s.cmd == CHILI2S_OTACMD_INIT )		{
			printf( "\n\n********** **********  Chili2s_OTA_thread : CHILI2S_OTACMD_INIT  ********** [%02d/%02d/%02d %02d:%02d:%02d] \n",
					((a53m0API_current_tm->tm_year+1900)-2000),
					a53m0API_current_tm->tm_mon + 1,
					a53m0API_current_tm->tm_mday,
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec	 );

			//	Get BIN file  	============================================
			if( OTA_Chili2s_Req_Init( ) != 0 )		{
				printf( "\n********** **********  Chili2s_OTA_thread : CHILI2S_OTACMD_INIT  Error XXXXX \n\n");
				OTA_Chili2s.cmd = CHILI2S_OTACMD_NOTHING;
			}  		//if( OTA_Chili2s_Req_Init( ) != 0 )		{
			else 	{
				printf( "\n********** **********  Chili2s_OTA_thread : CHILI2S_OTACMD_INIT  OOOOO OOOOO \n\n");
				usleep( 250000 );  	//250ms
				OTA_Chili2s.cmd = CHILI2S_OTACMD_PROGRAM_DATA;
				//OTA_Chili2s.cmd = CHILI2S_OTACMD_NOTHING;  		//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}  		//if( OTA_Chili2s_Req_Init( ) != 0 )		{ 		else
		}  		//else if( OTA_Chili2s.cmd == CHILI2S_OTACMD_INIT )		{


		//****************************************************************
		//	== CHILI2S_OTACMD_PROGRAM_DATA
		//****************************************************************
		else if( OTA_Chili2s.cmd == CHILI2S_OTACMD_PROGRAM_DATA )		{
			printf( "\n\n********** **********  Chili2s_OTA_thread : CHILI2S_OTACMD_PROGRAM_DATA  ********** [%02d/%02d/%02d %02d:%02d:%02d] \n",
					((a53m0API_current_tm->tm_year+1900)-2000),
					a53m0API_current_tm->tm_mon + 1,
					a53m0API_current_tm->tm_mday,
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec	 );

			//	Get BIN file  	============================================
			if( OTA_Chili2s_Req_ProgramData( ) != 0 )		{
				printf( "\n********** **********  Chili2s_OTA_thread : CHILI2S_OTACMD_PROGRAM_DATA  Error XXXXX \n\n");
				OTA_Chili2s.cmd = CHILI2S_OTACMD_NOTHING;
			}  		//if( OTA_Chili2s_Req_ProgramData( ) != 0 )		{
			else 	{				
				printf( "\n********** **********  Chili2s_OTA_thread : CHILI2S_OTACMD_PROGRAM_DATA  OOOOO OOOOO \n\n");
				usleep( 250000 );  	//250ms

				sleep( 10 );
				//	???  CK Chili2s reboot ????


				printf( "\n ********** __________  Chili2s OTA  All Over - Status: [%04X] __________ **********  [%02d/%02d/%02d %02d:%02d:%02d] \n",
							OTA_Chili2s.Status_OTA,
							((a53m0API_current_tm->tm_year+1900)-2000),
							a53m0API_current_tm->tm_mon + 1,
							a53m0API_current_tm->tm_mday,
							a53m0API_current_tm->tm_hour,
							a53m0API_current_tm->tm_min,
							a53m0API_current_tm->tm_sec	 );

				OTA_Chili2s.cmd = CHILI2S_OTACMD_NOTHING;
			}  		//if( OTA_Chili2s_Req_ProgramData( ) != 0 )		{			else

		}  		//else if( OTA_Chili2s.cmd == CHILI2S_OTACMD_PROGRAM_DATA )		{





		//****************************************************************
		//	== Waiting Chili2s ReBoot !!!!!!!
		//****************************************************************
		//????????????????????????????????????????????????????????????????


		//================================================================
		usleep( 250000 );  	//250ms
	}  		//while( 1 )		{
}  		//void  Chili2s_OTA_thread( void )

























//********************************************************************
//
//********************************************************************
UINT16  	OTA_Chili2s_Tx_Init( UINT16 record_Total, UINT32 file_size, UINT16 crc16_file )
{
	UINT16  crc16_Tx = 0;
	UINT8 *ptr_crcStart;

	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	//printf(" ========== uartA53M0_REQM0_OTA_Radar_Tst ---------- ---------- \n");

	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf(" ========== OTA_Chili2s_Tx_Init  [%02d:%02d:%02d] \n",
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec		);


	uartRadar_OTA_CmdRsp = OTA_RADAR_RUN_NULL;
	//==================================================================
	*txPtr = 0xCC; 				txPtr++;

	//	UARTcmd 	Len
	*txPtr = 0x00; 				txPtr++;
	*txPtr = 0x00; 				txPtr++;

	//	UARTcmd 	Cmd
	*txPtr = uart_REQ_FW_OTA;
	txPtr++;

	//	UARTcmd 	CRC
	*txPtr = 0x00; 				txPtr++;
	*txPtr = 0x00; 				txPtr++;

	*txPtr = SUBTYPE_CHILI2S;
	txPtr++;

	*txPtr = CHILI2S_OTACMD_INIT; 				txPtr++;  		//	SUB_CMD : Enter Update Mode

	//..................................................................
	*txPtr = record_Total & 0x00FF; 							txPtr++;
	*txPtr = (record_Total>>8) & 0x00FF; 					txPtr++;

	//	4D 32 33 2D 73 4C 45 44
	*txPtr = 0x4D; 				txPtr++;
	*txPtr = 0x32; 				txPtr++;
	*txPtr = 0x33; 				txPtr++;
	*txPtr = 0x2D; 				txPtr++;
	*txPtr = 0x73; 				txPtr++;
	*txPtr = 0x4C; 				txPtr++;
	*txPtr = 0x45; 				txPtr++;
	*txPtr = 0x44; 				txPtr++;

	*txPtr = file_size & 0x00FF;	 							txPtr++;
	*txPtr = (file_size>>8) & 0x00FF; 					txPtr++;
	*txPtr = (file_size>>16) & 0x00FF; 					txPtr++;
	*txPtr = (file_size>>24) & 0x00FF; 					txPtr++;

	*txPtr = crc16_file & 0x00FF; 							txPtr++;
	*txPtr = (crc16_file>>8) & 0x00FF; 					txPtr++;


	//==================================================================
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//------------------------------------------------------------------
	A53M0_Tx = 0;
	A53M0_TxLength = (txPtr - A53M0_TxBuf );

	return  crc16_Tx;
}  		//UINT16  	OTA_Chili2s_Tx_Init( UINT16 record_Total, UINT32 file_size, UINT16 crc16_file )


//********************************************************************
//
//********************************************************************
void  	OTA_Chili2s_Tx_ProgramData( UINT8* dataPtr, int length )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	//printf(" ========== uartA53M0_REQM0_OTA_Radar_Tst ---------- ---------- \n");

	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf(" ========== OTA_Chili2s_Tx_ProgramData    [%02d:%02d:%02d]  [%02d]  [%04X]-[%04X]\n",
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec,
					length,
					OTA_Chili2s.rec_No,
					OTA_Chili2s.rec_Total	);


	uartRadar_OTA_CmdRsp = OTA_RADAR_RUN_NULL;
	//==================================================================
	*txPtr = 0xCC; 				txPtr++;

	//	UARTcmd 	Len
	*txPtr = 0x00; 				txPtr++;
	*txPtr = 0x00; 				txPtr++;

	//	UARTcmd 	Cmd
	*txPtr = uart_REQ_FW_OTA;
	txPtr++;

	//	UARTcmd 	CRC
	*txPtr = 0x00; 				txPtr++;
	*txPtr = 0x00; 				txPtr++;

	*txPtr = SUBTYPE_CHILI2S;
	txPtr++;

	*txPtr = CHILI2S_OTACMD_PROGRAM_DATA; 				txPtr++;  		//	SUB_CMD : User Program Update

	//..................................................................
	*txPtr = OTA_Chili2s.rec_No; 							txPtr++;
	*txPtr = OTA_Chili2s.rec_No >> 8; 				txPtr++;
	*txPtr = OTA_Chili2s.rec_Total; 					txPtr++;
	*txPtr = OTA_Chili2s.rec_Total >> 8; 			txPtr++;

	for( int i=0 ; i<length ; i++ )		{
		*txPtr = *dataPtr;
		txPtr++;
		dataPtr++;
	}  		//for( int i=0 ; i<length ; i++ )		{

	//==================================================================
	//	Get length & CRC16
	A53M0_TxBuf[1] = (txPtr - A53M0_TxBuf -3) & 0x00FF;
	A53M0_TxBuf[2] = ((txPtr - A53M0_TxBuf -3)>>8) & 0x00FF;

	UINT16 crc16 = Get_ModBus_CRC16( (UINT8*)&A53M0_TxBuf[6], (txPtr - A53M0_TxBuf -3-3) );
	A53M0_TxBuf[4] = crc16 & 0x00FF;
	A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//------------------------------------------------------------------
	A53M0_Tx = 0;
	A53M0_TxLength = (txPtr - A53M0_TxBuf );

	//	TEST  	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*
		printf( "  --OTA_Chili2s_Tx_ProgramData [ " );
		for( int i=0 ; i<A53M0_TxLength ; i++ )		{
			printf( "%02X ", A53M0_TxBuf[i] );
		}
		printf( "] \n" );
		*/
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}  		//void  	OTA_Chili2s_Tx_ProgramData( UINT8* dataPtr, int length )






























//********************************************************************
//
//********************************************************************
int  	OTA_Chili2s_get_BIN( void )
{
	unsigned char	fileName[256];
	FILE* f_BIN;

	UINT8 *f_Buf;
	int  	i;


	bzero( fileName, 256 );
	sprintf( fileName, "%s%s", path_Chili2sOTA_BIN, OTA_Chili2s.FileName_OTA );
	printf( "\n  ***** ***** OTA_Chili2s_get_BIN  -  [%s]  [%s]\n", 
				OTA_Chili2s.FileName_OTA,
				fileName );

	f_BIN = fopen( fileName, "r+b" );
	if( f_BIN )		{
		fseek( f_BIN, 0, SEEK_END);
		OTA_Chili2s.file_size = ftell( f_BIN );
		fseek( f_BIN, 0, SEEK_SET);

		f_Buf = malloc( (OTA_Chili2s.file_size/4)*4 + 32 );
		for( i=0 ; i<OTA_Chili2s.file_size ; i++ )		{
			f_Buf[i] = (UINT8)fgetc( f_BIN );
		}

		OTA_Chili2s.crc16_file =  Get_Kermit_CRC16( f_Buf, OTA_Chili2s.file_size );

		OTA_Chili2s.rec_No = 0;
		OTA_Chili2s.rec_Total = OTA_Chili2s.file_size / OTA_CHILI2S_PROGRAMDATA_SIZE;
		if( (OTA_Chili2s.file_size % OTA_CHILI2S_PROGRAMDATA_SIZE) > 0 )		{
			OTA_Chili2s.rec_Total++;
		}

		printf( "    ::  [%s] \n", 
					fileName );
		printf( "    ::  f_Size[%d][%06X] crc16[%04X]  rec_Total[%d][%04X] \n", 
					OTA_Chili2s.file_size, 
					OTA_Chili2s.file_size,
					OTA_Chili2s.crc16_file, 
					OTA_Chili2s.rec_Total,
					OTA_Chili2s.rec_Total );

		free( f_Buf );
		fclose( f_BIN );
		return 0;
	}  		//if( f_BIN )		{

	else  	{
		printf( "\n  XXXXX XXXXX OTA_Chili2s_get_BIN - Open file  [%s]  Error !!!!! \n", OTA_Chili2s.FileName_OTA );
		return -1;
	}  		//if( f_Hex )		{			else

	return -1;
}  		//int  	OTA_Chili2s_get_BIN( void )








//********************************************************************
//
//********************************************************************
int  	OTA_Chili2s_Req_Init( void )
{
	OTA_Chili2s.Status_OTA = OTA_CHILI2S_WAITING;
	OTA_Chili2s_Tx_Init( OTA_Chili2s.rec_Total, OTA_Chili2s.file_size, OTA_Chili2s.crc16_file );


	int  cnt_timeout = 0;
	while( 1 ) 	{  	//	Waiting Response
		usleep( 2000 );
		if( OTA_Chili2s.Status_OTA == OTA_CHILI2S_SUCCESS )		{
			printf( "  OTA_Chili2s_Req_Init  Over \n" );
			return 0;
		}

		//----------------------------------------------------------------
		cnt_timeout++;
		if( cnt_timeout > 1000 ) 	{  //	2ms*1000=2s
			a53m0API_currentTime = time( NULL);
			a53m0API_current_tm = localtime (&a53m0API_currentTime);
			printf( " !!! OTA_Chili2s_Req_Init : time-out  !!!   [%02d:%02d:%02d] \n",
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec	 );
			return -1;
		}
	}  		//while( 1 ) 	{  	//	Waiting Response

	return 0;
}  		//int  	OTA_Chili2s_Req_Init( void )


//********************************************************************
//
//********************************************************************
int  	OTA_Chili2s_Req_ProgramData( void )
{
	unsigned char	fileName[256];
	FILE* f_BIN;

	UINT8 *f_Buf;
	UINT8 *dataPtr;
	UINT32  	file_size = OTA_Chili2s.file_size;

	int  cnt_timeout = 0;


	bzero( fileName, 256 );
	sprintf( fileName, "%s%s", path_Chili2sOTA_BIN, OTA_Chili2s.FileName_OTA );

	f_BIN = fopen( fileName, "r+b" );
	if( f_BIN )		{
		f_Buf = malloc( (OTA_Chili2s.file_size/4)*4 + 32 );
		if( f_Buf )		{
			//	Read file to f_Buf
			for( int i=0 ; i<OTA_Chili2s.file_size ; i++ )	{
				f_Buf[i] = (unsigned char)fgetc( f_BIN );
			}

			//
			dataPtr = f_Buf;
			OTA_Chili2s.rec_No = 1;

			while( 1 ) 	{
				//	Tx ProgramData  ==========================================
				if( file_size >= OTA_CHILI2S_PROGRAMDATA_SIZE )		{
					OTA_Chili2s.Status_OTA = OTA_CHILI2S_WAITING;
					OTA_Chili2s_Tx_ProgramData( dataPtr, OTA_CHILI2S_PROGRAMDATA_SIZE );
					file_size -= OTA_CHILI2S_PROGRAMDATA_SIZE;
					dataPtr += OTA_CHILI2S_PROGRAMDATA_SIZE;
				}
				else {
					OTA_Chili2s.Status_OTA = OTA_CHILI2S_WAITING;
					OTA_Chili2s_Tx_ProgramData( dataPtr, file_size );
					file_size = 0;
				}

				//	Wait Response  ===========================================
				cnt_timeout = 0;
				while( 1 )  	{
					usleep( 2000 );
					if( OTA_Chili2s.Status_OTA == OTA_CHILI2S_SUCCESS )		{
						printf( "  OTA_Chili2s_Req_Init  Over \n" );
						break;
					}

					//----------------------------------------------------------
					cnt_timeout++;
					if( cnt_timeout > 500 ) 	{  //	2ms*500=1s
						a53m0API_currentTime = time( NULL);
						a53m0API_current_tm = localtime (&a53m0API_currentTime);
						printf( " !!! OTA_Chili2s_Req_ProgramData : time-out  !!!   [%02d:%02d:%02d] \n",
								a53m0API_current_tm->tm_hour,
								a53m0API_current_tm->tm_min,
								a53m0API_current_tm->tm_sec	 );
						return -1;
					}
				}  		//while( 1 )  	{

				if( file_size == 0 )	{
					break;
				}

				OTA_Chili2s.rec_No++;
				usleep( 100000 );  		//	100ms
			}  		//while( 1 ) 	{

			free( f_Buf );
		}  		//if( f_Buf )		{
		fclose( f_BIN );
	}  		//if( f_BIN )		{

	return 0;
}  		//int  	OTA_Chili2s_Req_ProgramData( void )


//********************************************************************
//
//********************************************************************
int  	OTA_Chili2s_CK_ReBoot( void )
{

	return 0;
}  		//int  	OTA_Chili2s_CK_ReBoot( void )












//********************************************************************
//	Radar OTA
//********************************************************************
void  Chili2SOTA_Rsp( UINT8* rx_payload, UINT16 length )
{
	int 	i;
	UINT8* rxPayloadPtr = rx_payload;

	//int  cnt_line;

	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);

	//	TEST  	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*
		printf( "    $$Chili2SOTA_Rsp:[[");
		for( i=0 ; i<(length-3) ; i++ )		{
			printf( " %02X", rx_payload[i] );
		}
		printf( "]]\n");
		*/
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	if( *rxPayloadPtr == SUBTYPE_CHILI2S )		{

		OTA_Chili2s.Status_OTA = rxPayloadPtr[1];

		switch( OTA_Chili2s.Status_OTA ) 		{
			case OTA_CHILI2S_SUCCESS:
				printf( "    ___Chili2SOTA_Rsp :  OTA_CHILI2S_SUCCESS  [%02d:%02d:%02d] \n",
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec		);
				break;

			case OTA_CHILI2S_ERR_CRC:
				printf( "    ___Chili2SOTA_Rsp :  XXXXX  OTA_CHILI2S_ERR_CRC  !!!!!  [%02d:%02d:%02d]\n",
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec		);
				break;

			case OTA_CHILI2S_ERR_REC:
				printf( "    ___Chili2SOTA_Rsp :  XXXXX  OTA_CHILI2S_ERR_REC  !!!!!  [%02d:%02d:%02d]\n",
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec		);
				break;

			case OTA_CHILI2S_ERR_TIMEOUT:
				printf( "    ___Chili2SOTA_Rsp :  XXXXX  OTA_CHILI2S_ERR_TIMEOUT  !!!!!  [%02d:%02d:%02d]\n",
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec		);
				break;

			case OTA_CHILI2S_TEST:
				printf( "    ___Chili2SOTA_Rsp :  OTA_CHILI2S_TEST --  [%02d:%02d:%02d] \n",
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec		);
				break;
		}  		//switch( rxPayloadPtr[1] ) 		{

	}  		//if( *rxPayloadPtr == SUBTYPE_CHILI2S )		{
}  		//void  Chili2SOTA_Rsp( UINT8* rx_payload, UINT16 length )

