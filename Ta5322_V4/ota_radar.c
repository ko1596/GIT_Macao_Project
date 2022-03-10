
//********************************************************************
// 	ota_radar.c
// 				20211108 			Daniel
//********************************************************************

/*
	typedef struct  {
		UINT8  		cmd;
		UINT8 		nc01;
		UINT16 		Status_RadarA;
		UINT16 		Status_RadarB;
		UINT32 		nc02;
		UINT8  		FileName_radarOTA[256];
	}M0_RADAR_OTA_FRAME;

M0_RADAR_OTA_FRAME  	OTA_Radar


//====================================================================
***** 		Start to used Radar OTA
1.
Set Radar HEX file to OTA_Radar.FileName_radarOTA
		bzero( OTA_Radar.FileName_radarOTA, 256 );
		sprint( OTA_Radar.FileName_radarOTA "%s", Radar HEX filename )

2.
save radar parameter value to  /home/root/grids/EPM/firmware/radar/radarparam30.txt

3.
check  OTA_Radar.cmd == RADAR_OTACMD_NOTHING
	if( OTA_Radar.cmd == RADAR_OTACMD_NOTHING )		{
		OTA_Radar.cmd == RADAR_OTACMD_START  		//	Start Radar OTA
			- 	RADAR_OTACMD_INIT
			- 	RADAR_OTACMD_ERASE_PAGE
			- 	RADAR_OTACMD_PROGRAM_DATA
			- 	RADAR_OTACMD_SET_PARAMETER

		if( OTA_Radar.cmd == RADAR_OTACMD_NOTHING ) 	{
			Radar OTA Over
			Check  OTA_Radar.Status_RadarA & OTA_Radar.Status_RadarB
		}
	}


//====================================================================
***** 		Set Radar parameter
1.
save radar parameter value to  /home/root/grids/EPM/firmware/radar/radarparam30.txt

2.
call  radar_set_param( );

*/

#include "m0All_Header.h"




//********************************************************************
//	Global
M0_RADAR_OTA_FRAME  	OTA_Radar;


//====================================================================
//UINT8 	uartRadar_OTA_CmdState;
UINT8 	uartRadar_OTA_CmdRsp;

UINT8  	uartRadar_OTA_rBuf[256+64];
UINT8  	uartRadar_OTA_TxBuf[256+64];


//====================================================================
unsigned char   path_RadarOTA_HEX[128] = "/home/root/grids/EPM/firmware/radar/";

//---------------------------------------------------------------------

unsigned char   file_RadarOTA_HEX[128] = "/home/root/grids/EPM/firmware/radar/radar_FW.hex";

unsigned char   file_RadarOTA_FW_BIN11[128] = "/home/root/grids/EPM/firmware/radar/radarFW11.bin";
unsigned char   file_RadarOTA_FW_BIN12[128] = "/home/root/grids/EPM/firmware/radar/radarFW12.bin";

unsigned char   file_RadarOTA_FW_BIN01[128] = "/home/root/grids/EPM/firmware/radar/radarFW01.bin";
unsigned char   file_RadarOTA_FW_BIN02[128] = "/home/root/grids/EPM/firmware/radar/radarFW02.bin";

unsigned char   file_RadarOTA_SAVEBIN1[128] = "/home/root/grids/EPM/firmware/radar/fwSave1.bin";
unsigned char   file_RadarOTA_SAVEBIN2[128] = "/home/root/grids/EPM/firmware/radar/fwSave2.bin";

#if  	TST_W_HEX_TABLE
	unsigned char   file_RadarOTA_HEX_TABLE1[128] = "/home/root/grids/EPM/firmware/radar/RadarOTA_HexTable1.txt";
	unsigned char   file_RadarOTA_HEX_TABLE2[128] = "/home/root/grids/EPM/firmware/radar/RadarOTA_HexTable2.txt";
#endif  		//	#if  	TST_TxRx_COUNT


//====================================================================
//	OTA Radar Cmd;  		16bytes
unsigned char  Cmd_RadarOTA_Cmd_wBK1[] = 				{ 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4F };
unsigned char  Cmd_RadarOTA_Cmd_wBK2[] = 				{ 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4D };

unsigned char  Cmd_RadarOTA_Cmd_wOver[] = 			{ 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//unsigned char  Cmd_RadarOTA_Cmd_wOver = 			{ 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

unsigned char  Cmd_RadarOTA_Cmd_wRUNflash[] = 	{ 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };

unsigned char  Cmd_RadarOTA_Cmd_TEST[] = 	{ 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x99 };


//====================================================================
//	DownLoad Path
unsigned char   file_RadarOTA_DL_PATH[128] = "/home/root/grids/EPM/firmware/radar ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/";
unsigned char   file_RadarOTA_PATH[128] = "/home/root/grids/EPM/firmware/radar/";


//********************************************************************
extern 	int 	A53M0_Tx;
extern 	M0_UART_FIFO		A53M0_RxQ;

extern 	UINT8 	M0A53_Rx_Payload[];

extern 	time_t a53m0API_currentTime;
extern 	struct tm *a53m0API_current_tm;




//	TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	#if  TST_RADAR_OTA_STEP1
		char StrCmd[16];
	#endif  		//#if  TST_RADAR_OTA_STEP1




//********************************************************************
//
//********************************************************************
void  Radar_OTA_thread( void )
{
	//unsigned char  ota_StartTime[256];

	int  	res;
	int  	resA;
	int  	resB;





	OTA_Radar.cmd = RADAR_OTACMD_NOTHING;

	printf( "********** **********  Thread Radar_OTA_thread Start  ********** ********** \n" );

	while( 1 )		{

		if( OTA_Radar.cmd != RADAR_OTACMD_NOTHING )		{
			a53m0API_currentTime = time( NULL);
			a53m0API_current_tm = localtime (&a53m0API_currentTime);
		}



		//****************************************************************
		//	== RADAR_OTACMD_INIT
		if( OTA_Radar.cmd == RADAR_OTACMD_START )		{
			printf( "\n\n********** **********  Radar_OTA_thread : RADAR_OTACMD_START  ********** [%02d/%02d/%02d %02d:%02d:%02d] \n",
					((a53m0API_current_tm->tm_year+1900)-2000),
					a53m0API_current_tm->tm_mon + 1,
					a53m0API_current_tm->tm_mday,
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec	 );


			//	DownLoad HEX file  	========================================
			if( OTA_Radar_get_HEX( ) != 0 )		{
				printf( "\n********** **********  Radar_OTA_thread : RADAR_OTACMD_START  Error XXXXX \n\n");
				OTA_Radar.cmd = RADAR_OTACMD_NOTHING;
			}
			else  {
				sleep( 1 );
				printf( "\n********** **********  Radar_OTA_thread : RADAR_OTACMD_START  OOOOO OOOOO \n\n");
				OTA_Radar.cmd = RADAR_OTACMD_INIT;
			}
		}  		//if( OTA_Radar.cmd == RADAR_OTACMD_START )		{


		//****************************************************************
		//	== RADAR_OTACMD_INIT
		else if( OTA_Radar.cmd == RADAR_OTACMD_INIT )		{
			printf( "\n\n********** **********  Radar_OTA_thread : RADAR_OTACMD_INIT  ********** [%02d/%02d/%02d %02d:%02d:%02d] \n",
					((a53m0API_current_tm->tm_year+1900)-2000),
					a53m0API_current_tm->tm_mon + 1,
					a53m0API_current_tm->tm_mday,
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec	 );

			OTA_Radar.Status_RadarA = OTA_Radar.Status_RadarB = 0;

			//	Radar OTA Mode  Init  	------------------------------------
			if( OTA_Radar_Req_Init( ) != 0 )		{
				printf( "\n\n     XXXXX XXXXX  RADAR_OTACMD_INIT  Error !!!  Status: A[%04X] B[%04X]\n\n", OTA_Radar.Status_RadarA, OTA_Radar.Status_RadarB );
				OTA_Radar.cmd = RADAR_OTACMD_NOTHING;
			}
			else {
				OTA_Radar.cmd = RADAR_OTACMD_ERASE_PAGE;
				//OTA_Radar.cmd = RADAR_OTACMD_PROGRAM_DATA;  		//	TEST  !!!!!!!!!!!!!!
			}
		}  		//else if( OTA_Radar.cmd == RADAR_OTACMD_INIT )		{




		//****************************************************************			
		//	== RADAR_OTACMD_ERASE_PAGE
		else if( OTA_Radar.cmd == RADAR_OTACMD_ERASE_PAGE )		{
			usleep( 200000 );		//	200ms

			
			#if  TST_RADAR_OTA_STEP1
				printf( "  ..........  Press Any Key -  RADAR_OTACMD_ERASE_PAGE :  .......... \n");
				bzero( StrCmd, 16 );
				gets( StrCmd );
			#endif  		//#if  TST_RADAR_OTA_STEP1
			

			printf( "\n\n********** **********  Radar_OTA_thread : RADAR_OTACMD_ERASE_PAGE  ********** [%02d/%02d/%02d %02d:%02d:%02d] \n",
					((a53m0API_current_tm->tm_year+1900)-2000),
					a53m0API_current_tm->tm_mon + 1,
					a53m0API_current_tm->tm_mday,
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec	 );

			OTA_Radar.Status_RadarA = OTA_Radar.Status_RadarB = 0;

			//	Radar OTA Mode  Init  	------------------------------------
			if( OTA_Radar_Req_ErasePage( ) != 0 )		{
				printf( "\n\n     XXXXX XXXXX  RADAR_OTACMD_ERASE_PAGE  Error !!!  Status: A[%04X] B[%04X]\n\n", OTA_Radar.Status_RadarA, OTA_Radar.Status_RadarB );
				OTA_Radar.cmd = RADAR_OTACMD_NOTHING;
			}
			else {
				OTA_Radar.cmd = RADAR_OTACMD_PROGRAM_DATA;
			}
		}  		//else if( OTA_Radar.cmd == RADAR_OTACMD_ERASE_PAGE )		{




		//****************************************************************			
		//	== RADAR_OTACMD_PROGRAM_DATA
		else if( OTA_Radar.cmd == RADAR_OTACMD_PROGRAM_DATA )		{
			usleep( 500000 );		//	500ms

			#if  TST_RADAR_OTA_STEP1
				printf( "  ..........  Press Any Key -  RADAR_OTACMD_PROGRAM_DATA :  .......... \n");
				bzero( StrCmd, 16 );
				gets( StrCmd );
			#endif  		//#if  TST_RADAR_OTA_STEP1

			printf( "\n\n********** **********  Radar_OTA_thread : RADAR_OTACMD_PROGRAM_DATA  ********** [%02d/%02d/%02d %02d:%02d:%02d] \n",
					((a53m0API_current_tm->tm_year+1900)-2000),
					a53m0API_current_tm->tm_mon + 1,
					a53m0API_current_tm->tm_mday,
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec	 );

			OTA_Radar.Status_RadarA = OTA_Radar.Status_RadarB = 0;


			//	Radar OTA Mode  Init  	------------------------------------
			if( OTA_Radar_Req_ProgramData( ) != 0 )		{
				printf( "\n\n     XXXXX XXXXX  RADAR_OTACMD_PROGRAM_DATA  Error !!!  Status: A[%04X] B[%04X]\n\n", OTA_Radar.Status_RadarA, OTA_Radar.Status_RadarB );
				OTA_Radar.cmd = RADAR_OTACMD_NOTHING;
			}
			else {
				//OTA_Radar.cmd = RADAR_OTACMD_PROGRAM_DATA;
				OTA_Radar.cmd = RADAR_OTACMD_SET_PARAMETER;
			}
			//OTA_Radar.cmd = RADAR_OTACMD_NOTHING;
		}  		//else if( OTA_Radar.cmd == RADAR_OTACMD_PROGRAM_DATA )		{


		//****************************************************************			
		//	== RADAR_OTACMD_PROGRAM_DATA
		else if( OTA_Radar.cmd == RADAR_OTACMD_SET_PARAMETER )		{
			sleep( 2 );

			printf( "\n\n********** **********  Radar_OTA_thread : RADAR_OTACMD_SET_PARAMETER  ********** [%02d/%02d/%02d %02d:%02d:%02d] \n",
					((a53m0API_current_tm->tm_year+1900)-2000),
					a53m0API_current_tm->tm_mon + 1,
					a53m0API_current_tm->tm_mday,
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec	 );


			//uartA53M0_update_Radar_parameter( );
			if( radar_set_param( ) != 0 )		{
				printf( "\n\n     XXXXX XXXXX  RADAR_OTACMD_SET_PARAMETER  Error !!! \n\n" );
			}
			else 	{
				sleep( 11 );
			}

			printf( "\n ********** __________  Radar OTA  All Over - Radar Status: A[%04X] B[%04X] __________ **********  [%02d/%02d/%02d %02d:%02d:%02d] \n",
						OTA_Radar.Status_RadarA,
						OTA_Radar.Status_RadarB,
						((a53m0API_current_tm->tm_year+1900)-2000),
						a53m0API_current_tm->tm_mon + 1,
						a53m0API_current_tm->tm_mday,
						a53m0API_current_tm->tm_hour,
						a53m0API_current_tm->tm_min,
						a53m0API_current_tm->tm_sec	 );
			OTA_Radar.cmd = RADAR_OTACMD_NOTHING;
		}



		//================================================================
		//printf( "##\n" );
		//sleep( 3 );
		usleep( 250000 );  	//250ms
	}  		//while( 1 )		{

	printf( "\n__________ __________  Radar_OTA_thread : End  __________ __________ \n" );
}  		//void  Radar_OTA_thread( void )






















//******************************************************************************
//
//******************************************************************************
//	/home/root/grids/bin/radarparam.txt
//	M0_radarA_set		M0_radarB_set
int 	radar_set_param( void )
{
	FILE*	f_radarParam;
	unsigned char  R_lineBuf[256];

	int 	scan_interval;

	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf( "\n========== radar_set_param Start  ==========  [%02d/%02d/%02d %02d:%02d:%02d] \n\n",
			((a53m0API_current_tm->tm_year+1900)-2000),
						a53m0API_current_tm->tm_mon + 1,
						a53m0API_current_tm->tm_mday,
						a53m0API_current_tm->tm_hour,
						a53m0API_current_tm->tm_min,
						a53m0API_current_tm->tm_sec	 );

	if( (OTA_Radar.cmd != RADAR_OTACMD_NOTHING) && (OTA_Radar.cmd != RADAR_OTACMD_SET_PARAMETER) )	{
		printf( "\n XXXXX XXXXX  radar_set_param Error, Radar can not Set parameter Now  !!!!! \n\n" );
		return -1;
	}

	#if 	M0_RADAR_VER_30_210930
		f_radarParam = fopen( "/home/root/grids/EPM/firmware/radar/radarparam30.txt" , "r+b" ) ;
	#else  	//#if 	M0_RADAR_VER_30_210930
		f_radarParam = fopen( "/home/root/grids/bin/radarparam.txt" , "r+b" ) ;
	#endif  	//#if 	M0_RADAR_VER_30_210930

	
	if( f_radarParam )		{
		
		//	Read line 	--------------------------------------------------
		int rLength;
		int paramCnt = 0;

		while( !feof( f_radarParam ) )		{
			bzero( R_lineBuf, 256 );

			rLength = fscanf( f_radarParam, "%s", R_lineBuf );
			if( rLength <= 0 )		{				break;				}
			//printf("Rparam [%04d]  [%s][%04d] \n", rLength, R_lineBuf, atoi( R_lineBuf ) );
			//printf( "    line[%d] [%s] \n", rLength, R_lineBuf );

			switch( paramCnt )		{
				case 0:
					M0_radarA_set.radar_X = atoi( R_lineBuf );
					break;
				case 1:
					M0_radarA_set.radar_Y = atoi( R_lineBuf );
					break;
				case 2:
					M0_radarA_set.radar_L = atoi( R_lineBuf );
					break;
				case 3:
					M0_radarA_set.radar_W = atoi( R_lineBuf );
					break;
				case 4:
					M0_radarA_set.radar_H = atoi( R_lineBuf );
					break;
				case 5:
					M0_radarA_set.Z_m = atoi( R_lineBuf );
					break;
				case 6:
					M0_radarA_set.Z_p = atoi( R_lineBuf );
					break;
				case 7:
					M0_radarA_set.DoA_E_m = atoi( R_lineBuf );
					break;
				case 8:
					M0_radarA_set.DoA_E_p = atoi( R_lineBuf );
					break;
				case 9:
					M0_radarA_set.DoA_H_m = atoi( R_lineBuf );
					break;
				case 10:
					M0_radarA_set.DoA_H_p = atoi( R_lineBuf );
					break;
				case 11:
					M0_radarA_set.Theta = atoi( R_lineBuf );
					break;
				case 12:
					M0_radarA_set.Phi = atoi( R_lineBuf );
					break;
				case 13:
					M0_radarA_set.L_R = atoi( R_lineBuf );
					break;
				case 14:
					M0_radarA_set.Threshold_Boundary = atoi( R_lineBuf );
					break;
				case 15:
					M0_radarA_set.Threshold_A = atoi( R_lineBuf );
					break;
				case 16:
					M0_radarA_set.Threshold_B = atoi( R_lineBuf );
					break;
				case 17:
					M0_radarA_set.Peak_amount = atoi( R_lineBuf );
					break;
				case 18:
					M0_radarA_set.Compare_car = atoi( R_lineBuf );
					break;
				case 19:
					M0_radarA_set.Compare_emp = atoi( R_lineBuf );
					break;
				case 20:
					M0_radarA_set.Block_lim = atoi( R_lineBuf );
					break;

				case 21:
					M0_radarB_set.radar_X = atoi( R_lineBuf );
					break;
				case 22:
					M0_radarB_set.radar_Y = atoi( R_lineBuf );
					break;
				case 23:
					M0_radarB_set.radar_L = atoi( R_lineBuf );
					break;
				case 24:
					M0_radarB_set.radar_W = atoi( R_lineBuf );
					break;
				case 25:
					M0_radarB_set.radar_H = atoi( R_lineBuf );
					break;
				case 26:
					M0_radarB_set.Z_m = atoi( R_lineBuf );
					break;
				case 27:
					M0_radarB_set.Z_p = atoi( R_lineBuf );
					break;
				case 28:
					M0_radarB_set.DoA_E_m = atoi( R_lineBuf );
					break;
				case 29:
					M0_radarB_set.DoA_E_p = atoi( R_lineBuf );
					break;
				case 30:
					M0_radarB_set.DoA_H_m = atoi( R_lineBuf );
					break;
				case 31:
					M0_radarB_set.DoA_H_p = atoi( R_lineBuf );
					break;
				case 32:
					M0_radarB_set.Theta = atoi( R_lineBuf );
					break;
				case 33:
					M0_radarB_set.Phi = atoi( R_lineBuf );
					break;
				case 34:
					M0_radarB_set.L_R = atoi( R_lineBuf );
					break;
				case 35:
					M0_radarB_set.Threshold_Boundary = atoi( R_lineBuf );
					break;
				case 36:
					M0_radarB_set.Threshold_A = atoi( R_lineBuf );
					break;
				case 37:
					M0_radarB_set.Threshold_B = atoi( R_lineBuf );
					break;
				case 38:
					M0_radarB_set.Peak_amount = atoi( R_lineBuf );
					break;
				case 39:
					M0_radarB_set.Compare_car = atoi( R_lineBuf );
					break;
				case 40:
					M0_radarB_set.Compare_emp = atoi( R_lineBuf );
					break;
				case 41:
					M0_radarB_set.Block_lim = atoi( R_lineBuf );
					break;
			} 		//switch( paramCnt )		{
			paramCnt++;
		} 		//while( !feof()f_radarParam )		{

		printf( "radar_param_set :: \n" );
		printf( "  A: %d  %d \n", M0_radarA_set.radar_X, M0_radarA_set.Block_lim );
		printf( "  B: %d  %d \n", M0_radarB_set.radar_X, M0_radarB_set.Block_lim );
		printf("  __________ \n");

		uartA53M0_Set_Radar_Parameter( &M0_radarA_set, &M0_radarB_set );

		fclose( f_radarParam );
		return 0;
	} 	//if( f_radarParam )		{

	else 	{
		printf( "\n XXXXX XXXXX  radar_set_param Error, Can not open [radarparam30.txt]  !!!!! \n\n" );
		return -1;
	}

	uartA53M0_Set_Radar_Parameter( 0, 0 );
}  		//int 	radar_set_param( void )







//********************************************************************
//	Radar OTA
//********************************************************************
/*
unsigned char   file_RadarOTA_DL_PATH[128] = "/home/root/grids/EPM/firmware/radar ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/";
unsigned char   file_RadarOTA_PATH[128] = "/home/root/grids/EPM/firmware/radar/"
RadarOTA.cfg
*/
int  OTA_Radar_get_HEX( void )
{
	unsigned char	fileName[256];
	FILE* f_Hex;


	bzero( fileName, 256 );
	sprintf( fileName, "%s%s", path_RadarOTA_HEX, OTA_Radar.FileName_radarOTA );
	printf( "\n  ***** ***** OTA_Radar_get_HEX  -  [%s]  [%s]\n", 
				OTA_Radar.FileName_radarOTA,
				fileName );

	f_Hex = fopen( fileName, "r+b" );
	if( f_Hex )		{

		if( RadarFW_HEX_BIN( fileName ) == 0 )	{
			printf( "\n  OOOOO OOOOO OTA_Radar_get_HEX  \n" );
			return 0;
		}
		printf( "\n  XXXXX XXXXX OTA_Radar_get_HEX - RadarFW_HEX_BIN()  Error !!!!! \n" );
		return -1;

	}  		//if( f_Hex )		{

	else  	{
		printf( "\n  XXXXX XXXXX OTA_Radar_get_HEX - Open file  [%s]  Error !!!!! \n", OTA_Radar.FileName_radarOTA );
		return -1;
	}  		//if( f_Hex )		{			else
	return -1;
}  		//int  OTA_Radar_get_HEX( void )



//********************************************************************
//	Radar OTA
//********************************************************************
/*
unsigned char   file_RadarOTA_DL_PATH[128] = "/home/root/grids/EPM/firmware/radar ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/";
unsigned char   file_RadarOTA_PATH[128] = "/home/root/grids/EPM/firmware/radar/"
RadarOTA.cfg
*/
/*
int  OTA_Radar_HEX_DownLoad( void )
{
	unsigned char	sysCmdBuf[256];
	unsigned char	fileName[256];
	FILE* f_HexCfg;

	int  i;
	int  dat;


	printf( "\n  ***** ***** OTA_Radar_HEX_DownLoad  \n" );

	//	DownLoad  RadarOTA.cfg  		====================================
	bzero( sysCmdBuf, 256 );
	sprintf( sysCmdBuf, "rm %s%s", file_RadarOTA_PATH, "RadarOTA.cfg" );
	printf( "    -----[%s]\n", sysCmdBuf );
	system( sysCmdBuf );
	usleep( 20000 );

	bzero( sysCmdBuf, 256 );
	sprintf( sysCmdBuf, "wget -c -T30 -t3 -P %s%s", file_RadarOTA_DL_PATH, "RadarOTA.cfg" );
	printf( "    -----[%s]\n", sysCmdBuf );
	system( sysCmdBuf );

	bzero( sysCmdBuf, 256 );
	sprintf( sysCmdBuf, "%s%s", file_RadarOTA_PATH, "RadarOTA.cfg" );
	printf( "    -----[%s]\n", sysCmdBuf );


	f_HexCfg = fopen( sysCmdBuf, "r+b" );
	if( f_HexCfg )  	{
		// Get HEX filename from RadarOTA.cfg  	--------------------------
		bzero( fileName, 256 );
		int  i=0;
		while ( !feof( f_HexCfg ) )		{
			dat = fgetc( f_HexCfg );
			if( (dat<0x20) || (dat>0x7A) )	{
				break;
			}
			else if( (dat<=0x21) && (dat<=0x29) )  	{
				break;
			}

			fileName[i] = dat;
			i++;
		}  //while ( !feof( f_HexCfg ) )		{

		if( i <= 4 )		{
			fclose( f_HexCfg );
			printf( "\n  XXXXX XXXXX OTA_Radar_HEX_DownLoad - RadarOTA.cfg Error -2  !!!!! !!!!! \n" );
			return -1;
		}
		fclose( f_HexCfg );

		//----------------------------------------------------------------
		printf( "    ===== 21 fileName[%s]\n", fileName );

		bzero( sysCmdBuf, 256 );
		sprintf( sysCmdBuf, "rm %s%s", file_RadarOTA_PATH, fileName );
		printf( "    ===== 22 [%s]\n", sysCmdBuf );
		system( sysCmdBuf );
		usleep( 20000 );

		bzero( sysCmdBuf, 256 );
		sprintf( sysCmdBuf, "wget -c -T30 -t3 -P %s%s", file_RadarOTA_DL_PATH, fileName );
		printf( "    ===== 23 [%s]\n", sysCmdBuf );
		system( sysCmdBuf );

		bzero( sysCmdBuf, 256 );
		sprintf( sysCmdBuf, "%s%s", file_RadarOTA_PATH, fileName );
		printf( "    ===== 24 fileName[%s]\n", sysCmdBuf );

		f_HexCfg = fopen( sysCmdBuf, "r+b" );
		if( f_HexCfg )		{
			fclose( f_HexCfg );

			if( RadarFW_HEX_BIN( sysCmdBuf ) == 0 )	{
				printf( "\n  OOOOO OOOOO OTA_Radar_HEX_DownLoad  \n" );
				return 0;
			}
			printf( "\n  XXXXX XXXXX OTA_Radar_HEX_DownLoad - RadarOTA.cfg Error -3  !!!!! !!!!! \n" );
			return -1;
		}
		else {
			printf( "\n  XXXXX XXXXX OTA_Radar_HEX_DownLoad - RadarOTA.cfg Error -2  !!!!! !!!!! \n" );
			return -1;
		}

	}  		//if( f_HexCfg )  	{

	else 	{
		printf( "\n  XXXXX XXXXX OTA_Radar_HEX_DownLoad - RadarOTA.cfg Error !!!!! !!!!! \n" );
		return -1;
	}

	return 0;
}  		//int  OTA_Radar_HEX_DownLoad( void )
*/


//********************************************************************
//	Radar OTA
//********************************************************************
int  RadarFW_HEX_BIN( unsigned char* f_ota_hex_Name )
{
	FILE* 	f_radarHEX;
	FILE* 	f_radarBIN;
	FILE* 	f_tempBIN = NULL;

	long  	fw_addr_Start = 0;
	long  	fw_DataLength = 0;



	unsigned char  R_lineBuf[256];
	unsigned char  *dataPtr;

	int rLength;
	int line_cnt = 0;
	int byte_cnt = 0;

	uint16_t  	data_address = 0xFFFF;

	int     line_dataLength;
	int     fw_line_type;
	uint8_t data;

	int 	 ck_sum;
	int 	 fw_file_size;

	int  i;


	#if  	TST_W_HEX_TABLE
		FILE*  f_hexTable;
		int  cnt_line = 0;
		unsigned char  wBuf[32];
	#endif  		//	#if  	TST_TxRx_COUNT



	//printf( "  ==========     RadarFW_HEX_BIN : [%s] \n", f_ota_hex_Name );

	f_radarHEX = fopen( f_ota_hex_Name, "r+b" );
	if( f_radarHEX ) 		{
		printf( "  ----------  Open  [%s]  Success. \n", f_ota_hex_Name );

		//	clear files
		f_tempBIN = fopen( file_RadarOTA_FW_BIN01, "w+b");
		fclose( f_tempBIN );
		f_tempBIN = fopen( file_RadarOTA_FW_BIN02, "w+b");
		fclose( f_tempBIN );


		while( !feof( f_radarHEX ) )		{
			//	Read a new line
			bzero( R_lineBuf, 256 );

			rLength = fscanf( f_radarHEX, "%s", R_lineBuf );
			if( rLength <= 0 )		{				break;				}
			line_cnt++;

			dataPtr = R_lineBuf;
			if( *dataPtr == ':' ) 	{
				//printf( ":[%05d][", line_cnt );
				byte_cnt = 0;
				ck_sum = 0;
				dataPtr++;

				//		while 	================================================
				while( 1 ) 	{  		// a-line
					
					if( Str2Hex_2( dataPtr, &data ) > 0 )	{
						//printf( " %02X", data );
						ck_sum += data;

						if( byte_cnt == 0 )		{
							line_dataLength = data;
						}
						else if( byte_cnt == 1 )		{
							data_address = (data << 8);
						}
						else if( byte_cnt == 2 )		{
							data_address |= data;
						}

						else if( byte_cnt == 3 )		{
							fw_line_type = data;
						}

						//	Get Data   -------------------------------------------
						else if( byte_cnt == 4 )		{
							//	Data 1'st byte
							if( (fw_line_type == 0x04) && (line_dataLength == 2) )	{
								fw_addr_Start = (data << (8*3));
							}
							else if( fw_line_type == 0x00 )	{
								fw_DataLength += line_dataLength;
								fputc( data, f_tempBIN );  //	Save FW data
								#if  	TST_W_HEX_TABLE
									bzero(wBuf, 32);
									sprintf( wBuf, " 0x%02X,", data );
									fwrite( wBuf, 1, strlen(wBuf), f_hexTable );
									cnt_line++;
									if( cnt_line >= 16 )		{
										cnt_line = 0;
										fputc( 0x0D, f_hexTable );
										fputc( 0x0A, f_hexTable );
									}
								#endif  		//	#if  	TST_TxRx_COUNT
							}
						}
						else if( byte_cnt == 5 )		{
							//	Data 2'nd byte
							if( (fw_line_type == 0x04) && (line_dataLength == 2) )	{
								fw_addr_Start |= (data << (8*2));
							}
							else if( fw_line_type == 0x00 )	{
								fputc( data, f_tempBIN );  //	Save FW data
								#if  	TST_W_HEX_TABLE
									bzero(wBuf, 32);
									sprintf( wBuf, " 0x%02X,", data );
									fwrite( wBuf, 1, strlen(wBuf), f_hexTable );
									cnt_line++;
									if( cnt_line >= 16 )		{
										cnt_line = 0;
										fputc( 0x0D, f_hexTable );
										fputc( 0x0A, f_hexTable );
									}
								#endif  		//	#if  	TST_TxRx_COUNT
							}
						}
						else if( (byte_cnt < (line_dataLength+3)) && ( fw_line_type == 0x00) )		{
							//	Data
							if( fw_line_type == 0x00 )	{
								fputc( data, f_tempBIN );  //	Save FW data
								#if  	TST_W_HEX_TABLE
									bzero(wBuf, 32);
									sprintf( wBuf, " 0x%02X,", data );
									fwrite( wBuf, 1, strlen(wBuf), f_hexTable );
									cnt_line++;
									if( cnt_line >= 16 )		{
										cnt_line = 0;
										fputc( 0x0D, f_hexTable );
										fputc( 0x0A, f_hexTable );
									}
								#endif  		//	#if  	TST_TxRx_COUNT
							}
						}

						// 	Get Data & CKSUM
						else if( (byte_cnt == (line_dataLength+3)) && (line_dataLength > 2) )		{
							if( fw_line_type == 0x00 )	{
								fputc( data, f_tempBIN );  //	Save FW data
								#if  	TST_W_HEX_TABLE
									bzero(wBuf, 32);
									sprintf( wBuf, " 0x%02X,", data );
									fwrite( wBuf, 1, strlen(wBuf), f_hexTable );
									cnt_line++;
									if( cnt_line >= 16 )		{
										cnt_line = 0;
										fputc( 0x0D, f_hexTable );
										fputc( 0x0A, f_hexTable );
									}
								#endif  		//	#if  	TST_TxRx_COUNT
							}

							//	get CheckSum .......................................
							//printf( " C[%02X]", ((0x100-(ck_sum&0x00FF))&0x00FF) );
							//printf( " C[%02X-%08X-%02X]", ((0x100-(ck_sum&0x00FF))&0x00FF), fw_addr_Start, fw_line_type );
						}

						//	Read CK-sum value  -----------------------------------
						else if( byte_cnt == (line_dataLength+4) )		{
							//printf( "=%02x", data );

							//
							if( (fw_line_type == 0x04) && (line_dataLength == 2) )	{
								//printf( "xx%08X", fw_addr_Start );
								printf( "  - Radar HEX Address=[%08X] \n", fw_addr_Start );
								//	ASCLoader.hex : fw_addr_Start == 0x1FFF0000
								//if( fw_addr_Start == 0x0C000000 ) 	{
								if( (fw_addr_Start == 0x0C000000) || (fw_addr_Start == 0x1FFF0000) ) 	{
									//==================================================
									f_tempBIN = fopen( file_RadarOTA_FW_BIN01, "a+b");

									#if  	TST_W_HEX_TABLE
										f_hexTable = fopen( file_RadarOTA_HEX_TABLE1, "w");
										fclose( f_hexTable );
										f_hexTable = fopen( file_RadarOTA_HEX_TABLE2, "w");
										fclose( f_hexTable );

										f_hexTable = fopen( file_RadarOTA_HEX_TABLE1, "a+b");
									#endif  		//#if  	TST_W_HEX_TABLE
								}
								else if( fw_addr_Start == 0x0C020000 ) 	{
									fclose( f_tempBIN ); 	//	0x0C000000 section Over; 	file_RadarOTA_FW_BIN01

									#if  	TST_W_HEX_TABLE
										fclose( f_hexTable );
									#endif  		//#if  	TST_W_HEX_TABLE

									//	==> FW info. BIN file  .........................
									f_tempBIN = fopen( file_RadarOTA_FW_BIN01, "r+b");
									fseek(f_tempBIN, 0, SEEK_END);
									fw_file_size = ftell(f_tempBIN);
									fseek(f_tempBIN, 0, SEEK_SET);
									fclose( f_tempBIN );
									
									f_tempBIN = fopen( file_RadarOTA_FW_BIN01, "r+b");
									f_radarBIN = fopen( file_RadarOTA_FW_BIN11, "w+b");
										fputc( ((0x0C000000>>24) & 0x00FF), f_radarBIN );
										fputc( ((0x0C000000>>16) & 0x00FF), f_radarBIN );
										fputc( ((0x0C000000>>8) & 0x00FF), f_radarBIN );
										fputc( ((0x0C000000>>0) & 0x00FF), f_radarBIN );

										fputc( ((fw_file_size>>24) & 0x00FF), f_radarBIN );
										fputc( ((fw_file_size>>16) & 0x00FF), f_radarBIN );
										fputc( ((fw_file_size>>8) & 0x00FF), f_radarBIN );
										fputc( ((fw_file_size>>0) & 0x00FF), f_radarBIN );

										for( i=0 ; i<fw_file_size ; i++ )		{
											fputc( fgetc(f_tempBIN), f_radarBIN );
										}
									fclose( f_radarBIN );
									fclose( f_tempBIN );


									//==================================================
									f_tempBIN = fopen( file_RadarOTA_FW_BIN02, "a+b");

									#if  	TST_W_HEX_TABLE
										f_hexTable = fopen( file_RadarOTA_HEX_TABLE2, "a+b");
									#endif  		//#if  	TST_W_HEX_TABLE
								}
							} 		//if( (fw_line_type == 0x04) && (line_dataLength == 2) )	{

							else if( (fw_line_type == 0x05) )	{
								fclose( f_tempBIN ); 	//	//	0x0C020000 section Over; 	file_RadarOTA_FW_BIN02
								#if  	TST_W_HEX_TABLE
									fclose( f_hexTable );
								#endif  		//#if  	TST_W_HEX_TABLE

								//	==> FW info. BIN file  .........................
								f_tempBIN = fopen( file_RadarOTA_FW_BIN02, "r+b");
								fseek(f_tempBIN, 0, SEEK_END);
								fw_file_size = ftell(f_tempBIN);
								fseek(f_tempBIN, 0, SEEK_SET);
								fclose( f_tempBIN );
								
								f_tempBIN = fopen( file_RadarOTA_FW_BIN02, "r+b");
								f_radarBIN = fopen( file_RadarOTA_FW_BIN12, "w+b");
									fputc( ((0x0C020000>>24) & 0x00FF), f_radarBIN );
									fputc( ((0x0C020000>>16) & 0x00FF), f_radarBIN );
									fputc( ((0x0C020000>>8) & 0x00FF), f_radarBIN );
									fputc( ((0x0C020000>>0) & 0x00FF), f_radarBIN );

									fputc( ((fw_file_size>>24) & 0x00FF), f_radarBIN );
									fputc( ((fw_file_size>>16) & 0x00FF), f_radarBIN );
									fputc( ((fw_file_size>>8) & 0x00FF), f_radarBIN );
									fputc( ((fw_file_size>>0) & 0x00FF), f_radarBIN );

									for( i=0 ; i<fw_file_size ; i++ )		{
										fputc( fgetc(f_tempBIN), f_radarBIN );
									}
								fclose( f_radarBIN );
								fclose( f_tempBIN );
							}
						}


						dataPtr+=2;
						byte_cnt++;
					} 		//if( Str2Hex_2( dataPtr, &data ) > 0 )	{

					else{
						//printf( "] L[%02X]A[%04X]T[%02X]\n", line_dataLength, data_address, fw_line_type );
						break;
					} 		//if( Str2Hex_2( dataPtr, &data ) > 0 )	{  		else
				} 	//while( 1 ) 	{   	//// a-line
				//		while  End 	============================================

			} 		//if( *dataPtr == ':' ) 	{
			else 	{
				printf( " ::: XXXXX\n" );
				break;
			}
		}  		//while( !feof( f_radarHEX ) )		{

		fclose( f_radarHEX );
	}

	else {
		printf( "  XXXXX  Error!  Open  [%s]  fail !!!!!  \n", f_ota_hex_Name );
		return -1;
	}

	return 0;
} 		//void  RadarFW_HEX_BIN( unsigned char* f_ota_hex_Name )






//********************************************************************
//
//********************************************************************
void  Get_Radar_OTA_BinTxData( UINT8* InBuf, UINT8* OutBuf, int InLength )
{
	int  	i;
	UINT8* OutPtr = OutBuf + 2;

	UINT8  	ck_sum = 0x01;


	printf( "  ===== Get_Radar_OTA_BinTxData   InLength[%d] \n", InLength );
	bzero( OutBuf, (256+64) );
	OutBuf[0] = 0x01;  		//	ck_sum from here
	OutBuf[1] = 0x01;

	for( i=0 ; i<InLength ; i++ ) 	{
		*OutPtr = *InBuf;
		ck_sum ^= *InBuf;

		InBuf++;
		OutPtr++;
	}  		//for( i=0 ; i<InLength ; i++ ) 	{
	OutBuf[ 2+256+5 ] = ck_sum;


	//	TEST  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*
	int  cnt_line = 14;
	printf( "  ===== Get_Radar_OTA_BinTxData [ \n");
	for( i=0 ; i<(2+256+6) ; i++ )		{
		printf( "%02X ", OutBuf[i] );
		cnt_line++;
		if( cnt_line >= 16 )	{
			cnt_line = 0;
			printf( "\n" );
		}
	}

	printf( "]\n");
	*/
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}  		//void  Get_Radar_OTA_BinTxData( UINT8* InBuf, UINT8* OutBuf, int InLength )
























//********************************************************************
//	Radar OTA
//********************************************************************
void  RadarOTA_Rsp( UINT8* rx_payload, UINT16 length )
{
	int 	i;
	UINT8* rxPayloadPtr = rx_payload;

	int  cnt_line;


	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);

	#if 	TST_RXUART_SHOW_01
		printf( "  $$RadarOTA_Rsp:[[");
		for( i=0 ; i<10 ; i++ )		{
			printf( " %02X", rx_payload[i] );
		}
		printf( "]]\n");
	#endif  		//#if 	TST_RXUART_SHOW_01



	if( (*rxPayloadPtr == SUBTYPE_RADAR_A) || (*rxPayloadPtr == SUBTYPE_RADAR_B) )		{
		a53m0API_currentTime = time( NULL);
		a53m0API_current_tm = localtime (&a53m0API_currentTime);

		switch( rxPayloadPtr[1] ) 		{

			//--------------------------------------------------------------
			case OTA_RADAR_RUN_RECEIVED:
				uartRadar_OTA_CmdRsp = OTA_RADAR_RUN_RECEIVED;
				printf( "   OTA-Radar Cmd recevied. \n" );
				break;

			case OTA_RADAR_RUN_PW_OFF:
				printf( "   OTA-Radar PowerOFF. \n" );
				break;
			case OTA_RADAR_RUN_PW_ON:
				printf( "   OTA-Radar PowerON. \n" );
				break;

			case OTA_RADAR_RUN_OTA_MODE01:
				printf( "   OTA-Radar Mode - 01. \n" );
				break;
			case OTA_RADAR_RUN_OTA_MODE02:
				printf( "   OTA-Radar Mode - 02. \n" );
				break;
			case OTA_RADAR_RUN_OTA_MODE03:
				printf( "   OTA-Radar Mode - 03. \n" );
				break;

			case OTA_RADAR_RUN_OTA_MODE11:
				printf( "   OTA-Radar Mode - 11. \n" );
				break;
			case OTA_RADAR_RUN_OTA_MODE12:
				printf( "   OTA-Radar Mode - 12. \n" );
				break;
			case OTA_RADAR_RUN_OTA_MODE13:
				printf( "   OTA-Radar Mode - 13. \n" );
				break;
			case OTA_RADAR_RUN_OTA_MODE14:
				printf( "   OTA-Radar Mode - 14. \n" );
				break;

			//--------------------------------------------------------------
			case RADAR_OTACMD_INIT:
				uartRadar_OTA_CmdRsp = RADAR_OTACMD_INIT;
				OTA_Radar.Status_RadarA = rxPayloadPtr[2];
				OTA_Radar.Status_RadarA |= rxPayloadPtr[3]<<8;
				OTA_Radar.Status_RadarB = rxPayloadPtr[4];
				OTA_Radar.Status_RadarB |= rxPayloadPtr[5]<<8;
				printf( "   OTA-Radar :  RADAR_OTACMD_INIT Over.  :: Status: A[%04X] B[%04X]  __________ [%02d:%02d:%02d] \n",
						OTA_Radar.Status_RadarA,
						OTA_Radar.Status_RadarB,

						//((a53m0API_current_tm->tm_year+1900)-2000),
						//a53m0API_current_tm->tm_mon + 1,
						//a53m0API_current_tm->tm_mday,
						a53m0API_current_tm->tm_hour,
						a53m0API_current_tm->tm_min,
						a53m0API_current_tm->tm_sec	 );
				break;

			//--------------------------------------------------------------
			case RADAR_OTACMD_ERASE_PAGE:
				uartRadar_OTA_CmdRsp = RADAR_OTACMD_ERASE_PAGE;
				OTA_Radar.Status_RadarA = rxPayloadPtr[2];
				OTA_Radar.Status_RadarA |= rxPayloadPtr[3]<<8;
				OTA_Radar.Status_RadarB = rxPayloadPtr[4];
				OTA_Radar.Status_RadarB |= rxPayloadPtr[5]<<8;
				printf( "   OTA-Radar :  RADAR_OTACMD_ERASE_PAGE Over.  :: Status: A[%04X] B[%04X]  __________ [%02d:%02d:%02d] \n",
						OTA_Radar.Status_RadarA,
						OTA_Radar.Status_RadarB,

						//((a53m0API_current_tm->tm_year+1900)-2000),
						//a53m0API_current_tm->tm_mon + 1,
						//a53m0API_current_tm->tm_mday,
						a53m0API_current_tm->tm_hour,
						a53m0API_current_tm->tm_min,
						a53m0API_current_tm->tm_sec	 );
				break;

			//--------------------------------------------------------------
			case RADAR_OTACMD_PROGRAM_CMD:
			case RADAR_OTACMD_PROGRAM_DATA:
				uartRadar_OTA_CmdRsp = RADAR_OTACMD_PROGRAM_DATA;
				OTA_Radar.Status_RadarA = rxPayloadPtr[2];
				OTA_Radar.Status_RadarA |= rxPayloadPtr[3]<<8;
				OTA_Radar.Status_RadarB = rxPayloadPtr[4];
				OTA_Radar.Status_RadarB |= rxPayloadPtr[5]<<8;
				printf( "   OTA-Radar :  RADAR_OTACMD_PROGRAM_DATA Over.  :: Status: A[%04X] B[%04X]  __________ [%02d:%02d:%02d] \n",
						OTA_Radar.Status_RadarA,
						OTA_Radar.Status_RadarB,

						//((a53m0API_current_tm->tm_year+1900)-2000),
						//a53m0API_current_tm->tm_mon + 1,
						//a53m0API_current_tm->tm_mday,
						a53m0API_current_tm->tm_hour,
						a53m0API_current_tm->tm_min,
						a53m0API_current_tm->tm_sec	 );

				#if  	TST_RADAR_OTA_SHOW_PRGDATA
					printf( "     RADAR_OTACMD_PROGRAM_DATA [[");
					rxPayloadPtr++;
					for( i=0 ; i<(A53M0_RxQ.LENGTH-3-1) ; i++ )		{
						printf( " %02X", *rxPayloadPtr);
						switch( i )		{
							case 0:
								printf( " " );
								break;
							case 4:
								cnt_line = 0;
								printf( "\n " );
								break;

							default:
								cnt_line++;
								if( cnt_line >= 16 )	{
									printf( "\n " );
									cnt_line = 0;
								}
								break;
						}  		//switch( i )		{
						rxPayloadPtr++;
					} 		//for( i=0 ; i<(A53M0_RxQ.LENGTH-3-1) ; i++ )		{
					printf( " ]]\n\n" );
				#endif  		//#if  	TST_RADAR_OTA_SHOW_PRGDATA
				break;


			//==============================================================
			case OTA_RADAR_FUN_TEST1:
				printf( "  !!! TEST1[");
				rxPayloadPtr++;
				for( i=0 ; i<(A53M0_RxQ.LENGTH-3-1) ; i++ )		{
					printf( " %02X", *rxPayloadPtr);
					rxPayloadPtr++;
				} 		//for( i=0 ; i<(A53M0_RxQ.LENGTH-3-1) ; i++ )		{
				printf( "]\n" );
				break;

		}  	//switch( rxPayloadPtr[1] ) 		{
	}
	else {
		return;
	}

}  		//void  RadarOTA_Rsp( UINT8* rx_payload, UINT16 length )




















//********************************************************************
//
//********************************************************************
int  	OTA_Radar_Req_Init( void )
{
	OTA_Radar_Tx_Init( );

	int  cnt_timeout = 0;
	while( 1 ) 	{  	//	Waiting Response
		usleep( 2000 );
		if( uartRadar_OTA_CmdRsp == RADAR_OTACMD_INIT ) 	{
			printf( "    Tst : OTA_Radar_Req_Init  - A[%04X] B[%04X] \n", OTA_Radar.Status_RadarA, OTA_Radar.Status_RadarB );
			if( (OTA_Radar.Status_RadarA==0) || (OTA_Radar.Status_RadarB==0) )	{
				printf( "  OTA_Radar_Req_Init  Over \n" );
				return 0;
			}
			else {
				printf( "  XXXXX XXXXX OTA_Radar_Req_Init  Error !!! \n" );
				return -1;
			}
		}

		//----------------------------------------------------------------
		cnt_timeout++;
		//if( cnt_timeout > 2500 ) 	{  //	2ms*2500=5s
		//if( cnt_timeout > 7500 ) 	{  //	2ms*7500=15s
		if( cnt_timeout > 10000 ) 	{  //	2ms*10000=20s
		//if( cnt_timeout > 15000 ) 	{  //	2ms*15000=30s
			a53m0API_currentTime = time( NULL);
			a53m0API_current_tm = localtime (&a53m0API_currentTime);
			printf( " !!! OTA_Radar_Req_Init : time-out  !!!   [%02d:%02d:%02d] \n",
					//((a53m0API_current_tm->tm_year+1900)-2000),
					//a53m0API_current_tm->tm_mon + 1,
					//a53m0API_current_tm->tm_mday,
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec	 );
			return -1;
		}
	}  	//while( 1 ) 	{

	return 0;
}  		//int  	OTA_Radar_Req_Init( void )




//********************************************************************
//
//********************************************************************
int  	OTA_Radar_Req_ErasePage( void )
{
	/*
	#if  TST_RADAR_OTA_STEP1
		printf( "  ..........  Press Any Key -  OTA_Radar_Req_ErasePage :  .......... \n");
		bzero( StrCmd, 16 );
		gets( StrCmd );
	#endif  		//#if  TST_RADAR_OTA_STEP1
	*/

	OTA_Radar_Tx_ErasePage( );

	int  cnt_timeout = 0;
	while( 1 ) 	{  	//	Waiting Response
		usleep( 2000 );
		if( uartRadar_OTA_CmdRsp == RADAR_OTACMD_ERASE_PAGE ) 	{
			if( (OTA_Radar.Status_RadarA==0) || (OTA_Radar.Status_RadarB==0) )	{
				printf( "  OTA_Radar_Req_ErasePage  Over \n" );
				return 0;
			}
			else {
				return -1;
			}
		}

		//----------------------------------------------------------------
		cnt_timeout++;
		//if( cnt_timeout > 2500 ) 	{  //	2ms*2500=5s
		//if( cnt_timeout > 7500 ) 	{  //	2ms*7500=15s
		if( cnt_timeout > 10000 ) 	{  //	2ms*10000=20s
		//if( cnt_timeout > 15000 ) 	{  //	2ms*15000=30s
			a53m0API_currentTime = time( NULL);
			a53m0API_current_tm = localtime (&a53m0API_currentTime);
			printf( " !!! OTA_Radar_Req_ErasePage : time-out  !!!   [%02d:%02d:%02d] \n",
					//((a53m0API_current_tm->tm_year+1900)-2000),
					//a53m0API_current_tm->tm_mon + 1,
					//a53m0API_current_tm->tm_mday,
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec	 );
			return -1;
		}
	}  	//while( 1 ) 	{

	return 0;
}  		//int  	OTA_Radar_Req_ErasePage( void )














//********************************************************************
//
//********************************************************************
int  	OTA_Radar_Req_ProgramData( void )
{
	FILE*  f_bin;
	int  	file_size;

	int  	r_index;

	int  i;
	int  j;
	int  k;
	int  cnt_line;
	int  cnt_TxPage = 1;

	int  cnt_timeout = 0;
	int  cnt_Tx = 0;


	//******************************************************************
	//	fw Bank0
	//******************************************************************
	sleep( 1 );
	printf( "\n" );
	printf( "\n" );
	printf( "\n" );
	printf( "\n" );
	printf( "\n" );
	printf( "\n" );
	printf( "\n  ***** ***** OTA_Radar_Req_ProgramData -BK1 \n" );

	f_bin = fopen( file_RadarOTA_FW_BIN01, "r+b");
	if( f_bin )		{
		fseek( f_bin, 0, SEEK_END);
		file_size = ftell( f_bin );
		printf( "     file_size[%d]\n", file_size );
		fseek( f_bin, 0, SEEK_SET);
	}
	else 	{
		printf( "  XXXXX  Error!  Open  [%s]  fail !!!!!  \n", file_RadarOTA_FW_BIN01 );
		return -1;
	}

	//	Set 0x0C000000  		============================================
	//		[00 00 0C 00 00 00 00 00 00 43 00 00 00 00 00 4F]
	uartRadar_OTA_CmdRsp = RADAR_OTACMD_WAITING;
	OTA_Radar_Tx_PrgCmdData( Cmd_RadarOTA_Cmd_wBK1, 16 );
	cnt_timeout = 0;
	while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
		#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE
		#else
			if( cnt_timeout > 5 )		{
				printf( "    XXXXX  OTA_Radar_Req_ProgramData  time-out !!!  [%d] \n", cnt_Tx );
				return -1;
			}
		#endif  		//#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE

		usleep( 20000 );  		//	20ms
		cnt_timeout++;
	}  		//while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
	cnt_Tx++;
	usleep( 1500000 );  		//	1.5s;		## 	1.05S

	//printf( "  !!!!! ***** OTA_Radar_Req_ProgramData - T10 [%d]\n", file_size );		//	!!!!!!!!!!!!!
	r_index = 0;
	cnt_line = 0;
	//printf( "  --[%s] [%d] [ \n", file_RadarOTA_FW_BIN01, file_size );
	for( i=0; i<file_size ; i++ ) 		{

		uartRadar_OTA_rBuf[ r_index % 256 ] = fgetc( f_bin );
		if( (r_index%256) >= (256-1) )	{

			printf( "  ===== bl_send_data TxCnt[%04X] \n", cnt_TxPage );  cnt_TxPage++;
			Get_Radar_OTA_BinTxData( uartRadar_OTA_rBuf, uartRadar_OTA_TxBuf, 256 );

			#if  TST_RADAR_OTA_SHOW_PRGDATA2
				printf( "Prg Data [ " );
				k = 14;
				for( j=0; j<(256+2+6) ; j++ )	{
					printf( "%02X ", uartRadar_OTA_TxBuf[j] );
					k++;
					if( k >= 16 )	{
						k = 0;
						printf( "\n" );
					}
				}
				printf( "]\n" );
			#endif  		//#if  TST_RADAR_OTA_SHOW_PRGDATA2

			//	Send program data  		======================================
			uartRadar_OTA_CmdRsp = RADAR_OTACMD_WAITING;
			OTA_Radar_Tx_PrgCmdData( uartRadar_OTA_TxBuf, 256+2+6 );
			cnt_timeout = 0;
			while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
				#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE
				#else
					if( cnt_timeout > 5 )		{
						printf( "    XXXXX  OTA_Radar_Req_ProgramData  time-out !!!  [%d] \n", cnt_Tx );
						return -1;
					}
				#endif  		//#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE

				usleep( 20000 );  		//	20ms
				cnt_timeout++;
			}  		//while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
			cnt_Tx++;
			
			usleep( 200000 );  		//	200ms;  ProgramDataSleep
		}  		//if( (r_index%256) >= (256-1) )	{

		//printf( "%02X ", uartRadar_OTA_rBuf[ r_index ] );
		cnt_line++;
		if( cnt_line >= 16 )		{
			cnt_line = 0;
			//printf( "\n" );
		}

		r_index++;
	}  		//for( i=0; i<file_size ; i++ ) 		{
	
	if( (file_size%256) > 0 )		{
		printf( "  ===== bl_send_data TxCnt[%04X] \n", cnt_TxPage );  cnt_TxPage++;
		Get_Radar_OTA_BinTxData( uartRadar_OTA_rBuf, uartRadar_OTA_TxBuf, (file_size%256) );

		#if  TST_RADAR_OTA_SHOW_PRGDATA2
			printf( "Prg Data [ " );
			k = 14;
			for( j=0; j<(256+2+6) ; j++ )	{
				printf( "%02X ", uartRadar_OTA_TxBuf[j] );
				k++;
				if( k >= 16 )	{
					k = 0;
					printf( "\n" );
				}
			}
			printf( "]\n" );
		#endif  		//#if  TST_RADAR_OTA_SHOW_PRGDATA2

		//	Send program data  		======================================		
		uartRadar_OTA_CmdRsp = RADAR_OTACMD_WAITING;
		OTA_Radar_Tx_PrgCmdData( uartRadar_OTA_TxBuf, 256+2+6 );
		cnt_timeout = 0;
		while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
			#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE
			#else
				if( cnt_timeout > 5 )		{
					printf( "    XXXXX  OTA_Radar_Req_ProgramData  time-out !!!  [%d] \n", cnt_Tx );
					return -1;
				}
			#endif  		//#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE

			usleep( 20000 );  		//	20ms
			cnt_timeout++;
		}  		//while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
		cnt_Tx++;
		
		usleep( 200000 );  		//	200ms;  ProgramDataSleep
	}  			//if( (file_size%256) > 0 )		{
	//printf( "] \n");
	fclose( f_bin );
	printf( "\n" );


	//	Program Data Over  		==========================================
	//		[02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00]
	usleep( 10000 );  		//	100ms
	uartRadar_OTA_CmdRsp = RADAR_OTACMD_WAITING;
	OTA_Radar_Tx_PrgCmdData( Cmd_RadarOTA_Cmd_wOver, 16 );
	cnt_timeout = 0;
	while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
		#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE
		#else
			if( cnt_timeout > 5 )		{
				printf( "    XXXXX  OTA_Radar_Req_ProgramData  time-out !!!  [%d] \n", cnt_Tx );
				return -1;
			}
		#endif  		//#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE

		usleep( 20000 );  		//	20ms
		cnt_timeout++;
	}  		//while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
	cnt_Tx++;

	sleep( 1 );
	printf( "\n" );
	printf( "\n" );
	printf( "\n" );
	printf( "\n" );
	printf( "\n" );
	printf( "\n" );
	//	TEST  	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//return 0;
	//printf( "\n  !!!!! _____  OTA_Radar_Req_ProgramData End  _____ !!!!! \n" );


	//******************************************************************
	//	fw Bank1
	//******************************************************************
	printf( "\n  ***** ***** OTA_Radar_Req_ProgramData -BK2 \n" );

	f_bin = fopen( file_RadarOTA_FW_BIN02, "r+b");
	if( f_bin )		{
		fseek( f_bin, 0, SEEK_END);
		file_size = ftell( f_bin );
		printf( "     file_size[%d]\n", file_size );
		fseek( f_bin, 0, SEEK_SET);
	}
	else 	{
		printf( "  XXXXX  Error!  Open  [%s]  fail !!!!!  \n", file_RadarOTA_FW_BIN01 );
		return -1;
	}

	//	Set 0x0C020000  		============================================
	//		[00 00 0C 02 00 00 00 00 00 43 00 00 00 00 00 4D]
	uartRadar_OTA_CmdRsp = RADAR_OTACMD_WAITING;
	OTA_Radar_Tx_PrgCmdData( Cmd_RadarOTA_Cmd_wBK2, 16 );
	cnt_timeout = 0;
	while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
		#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE
		#else
			if( cnt_timeout > 5 )		{
				printf( "    XXXXX  OTA_Radar_Req_ProgramData  time-out !!!  [%d] \n", cnt_Tx );
				return -1;
			}
		#endif  		//#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE

		usleep( 20000 );  		//	20ms
		cnt_timeout++;
	}  		//while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
	cnt_Tx++;
	usleep( 1500000 );  		//	1.5s;		## 	1.05S


	r_index = 0;
	cnt_line = 0;
	//printf( "  --[%s] [%d] [ \n", file_RadarOTA_FW_BIN01, file_size );
	for( i=0; i<file_size ; i++ ) 		{
		uartRadar_OTA_rBuf[ r_index % 256 ] = fgetc( f_bin );
		if( (r_index%256) >= (256-1) )	{
			printf( "  ===== bl_send_data TxCnt[%04X] \n", cnt_TxPage );  cnt_TxPage++;
			Get_Radar_OTA_BinTxData( uartRadar_OTA_rBuf, uartRadar_OTA_TxBuf, 256 );

			#if  TST_RADAR_OTA_SHOW_PRGDATA2
				printf( "Prg Data [ " );
				k = 14;
				for( j=0; j<(256+2+6) ; j++ )	{
					printf( "%02X ", uartRadar_OTA_TxBuf[j] );
					k++;
					if( k >= 16 )	{
						k = 0;
						printf( "\n" );
					}
				}
				printf( "]\n" );
			#endif  		//#if  TST_RADAR_OTA_SHOW_PRGDATA2

			//	Send program data  		======================================
			uartRadar_OTA_CmdRsp = RADAR_OTACMD_WAITING;
			OTA_Radar_Tx_PrgCmdData( uartRadar_OTA_TxBuf, 256+2+6 );
			cnt_timeout = 0;
			while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
				#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE
				#else
					if( cnt_timeout > 5 )		{
						printf( "    XXXXX  OTA_Radar_Req_ProgramData  time-out !!!  [%d] \n", cnt_Tx );
						return -1;
					}
				#endif  		//#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE

				usleep( 20000 );  		//	20ms
				cnt_timeout++;
			}  		//while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
			cnt_Tx++;
			
			usleep( 200000 );  		//	200ms;  ProgramDataSleep
		}  		//if( (r_index%256) >= (256-1) )	{

		//printf( "%02X ", uartRadar_OTA_rBuf[ r_index ] );
		cnt_line++;
		if( cnt_line >= 16 )		{
			cnt_line = 0;
			//printf( "\n" );
		}
		r_index++;
	}  		//for( i=0; i<file_size ; i++ ) 		{

	if( (file_size%256) > 0 )		{
		printf( "  ===== bl_send_data TxCnt[%04X] \n", cnt_TxPage );  cnt_TxPage++;
		Get_Radar_OTA_BinTxData( uartRadar_OTA_rBuf, uartRadar_OTA_TxBuf, (file_size%256) );

		#if  TST_RADAR_OTA_SHOW_PRGDATA2
			printf( "Prg Data [ " );
			k = 14;
			for( j=0; j<(256+2+6) ; j++ )	{
				printf( "%02X ", uartRadar_OTA_TxBuf[j] );
				k++;
				if( k >= 16 )	{
					k = 0;
					printf( "\n" );
				}
			}
			printf( "]\n" );
		#endif  		//#if  TST_RADAR_OTA_SHOW_PRGDATA2

		//	Send program data  		======================================
		uartRadar_OTA_CmdRsp = RADAR_OTACMD_WAITING;
		OTA_Radar_Tx_PrgCmdData( uartRadar_OTA_TxBuf, 256+2+6 );
		cnt_timeout = 0;
		while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
			#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE
			#else
				if( cnt_timeout > 5 )		{
					printf( "    XXXXX  OTA_Radar_Req_ProgramData  time-out !!!  [%d] \n", cnt_Tx );
					return -1;
				}
			#endif  		//#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE

			usleep( 20000 );  		//	20ms
			cnt_timeout++;
		}  		//while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
		cnt_Tx++;
		
		usleep( 200000 );  		//	200ms;  ProgramDataSleep
	}  			//if( (file_size%256) > 0 )		{
	//printf( "] \n");

	fclose( f_bin );
	printf( "\n" );

	//	Program Data Over  		==========================================
	//		[02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00]
	usleep( 10000 );  		//	100ms
	uartRadar_OTA_CmdRsp = RADAR_OTACMD_WAITING;
	OTA_Radar_Tx_PrgCmdData( Cmd_RadarOTA_Cmd_wOver, 16 );
	cnt_timeout = 0;
	while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
		#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE
		#else
			if( cnt_timeout > 5 )		{
				printf( "    XXXXX  OTA_Radar_Req_ProgramData  time-out !!!  [%d] \n", cnt_Tx );
				return -1;
			}
		#endif  		//#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE

		usleep( 20000 );  		//	20ms
		cnt_timeout++;
	}  		//while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
	cnt_Tx++;


	//	1 = Run from Flash  		========================================
	//		[00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 01]
	sleep( 1 );  		//	1s
	uartRadar_OTA_CmdRsp = RADAR_OTACMD_WAITING;
	OTA_Radar_Tx_PrgCmdData( Cmd_RadarOTA_Cmd_wRUNflash, 16 );
	cnt_timeout = 0;
	while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
		#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE
		#else
			if( cnt_timeout > 5 )		{
				printf( "    XXXXX  OTA_Radar_Req_ProgramData  time-out !!!  [%d] \n", cnt_Tx );
				return -1;
			}
		#endif  		//#if  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE

		usleep( 20000 );  		//	20ms
		cnt_timeout++;
	}  		//while( uartRadar_OTA_CmdRsp == RADAR_OTACMD_WAITING )		{
	cnt_Tx++;


	usleep( 200000 );  		//	200ms
	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf( "\n  _____ _____  OTA_Radar_Req_ProgramData End  _____ _____  [%02d:%02d:%02d] \n",
					a53m0API_current_tm->tm_hour,
					a53m0API_current_tm->tm_min,
					a53m0API_current_tm->tm_sec		);

	return 0;
}  		//int  	OTA_Radar_Req_ProgramData( void )




















//********************************************************************
//
//********************************************************************
void 	OTA_Radar_Tx_Init( void )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	//printf(" ========== uartA53M0_REQM0_OTA_Radar_Tst ---------- ---------- \n");

	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf(" ========== OTA_Radar_Tx_Init  [%02d:%02d:%02d] \n",
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

	*txPtr = SUBTYPE_RADAR_A;
	//*txPtr = SUBTYPE_RADAR_B;
	txPtr++;

	*txPtr = RADAR_OTACMD_INIT;
	txPtr++;

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
}  		//void 	OTA_Radar_Tx_Init( void )


//********************************************************************
//
//********************************************************************
void 	OTA_Radar_Tx_ErasePage( void )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	//printf(" ========== uartA53M0_REQM0_OTA_Radar_Tst ---------- ---------- \n");

	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf(" ========== OTA_Radar_Tx_ErasePage  [%02d:%02d:%02d] \n",
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

	*txPtr = SUBTYPE_RADAR_A;
	//*txPtr = SUBTYPE_RADAR_B;
	txPtr++;

	*txPtr = RADAR_OTACMD_ERASE_PAGE;
	txPtr++;

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
}  		//void 	OTA_Radar_Tx_ErasePage( void )




//********************************************************************
//
//********************************************************************
void 	OTA_Radar_Tx_PrgCmdData( UINT8* txBuf, int length )
{
	unsigned char 	*txPtr = A53M0_TxBuf;
	int  i;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	//printf(" ========== uartA53M0_REQM0_OTA_Radar_Tst ---------- ---------- \n");

	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf(" ========== OTA_Radar_Tx_PrgCmdData  [%02d:%02d:%02d] \n",
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

	*txPtr = SUBTYPE_RADAR_A;
	//*txPtr = SUBTYPE_RADAR_B;
	txPtr++;

	*txPtr = RADAR_OTACMD_PROGRAM_DATA;
	txPtr++;

	for( i=0 ; i < length ; i++ )		{
		*txPtr = *txBuf;
		txPtr++;
		txBuf++;
	}  		//for( int i=0 ; i < Length ; i++ )		{
	/*
	*txPtr = 0x11;  		txPtr++;
	*txPtr = 0x22;  		txPtr++;
	*txPtr = 0x33;  		txPtr++;
	*txPtr = 0x44;  		txPtr++;
	*/

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
}  		//void 	OTA_Radar_Tx_PrgCmdData( UINT8* txBuf, int length )

