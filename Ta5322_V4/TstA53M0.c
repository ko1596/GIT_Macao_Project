

#include "m0All_Header.h"



//********************************************************************
//  Global
pthread_t thread_Keyboard_input;
pthread_t thread_Play_Voice;
pthread_t thread_Test01;

UINT32 	Bat_v;
UINT32 	Bat_i;

struct timeb  	time_prgStart;
struct timeb  	time_prgNow;


#if 	Tst_SLEEP_T01
	int  	flg_sleep;
	struct timeb  	time_sleepCK1;
	struct timeb  	time_sleepCK2;
#endif  		//#if 	Tst_SLEEP_T01


//====================================================================
unsigned char   file_RadarOTA_HEX00[128] = "/home/root/grids/EPM/firmware/radar/ASCLoader.hex";
unsigned char   file_RadarOTA_HEX11[128] = "/home/root/grids/EPM/firmware/radar/RB-60_3.0.1.2_1006.hex";
unsigned char   file_RadarOTA_HEX12[128] = "/home/root/grids/EPM/firmware/radar/RB-60_3.0.1.4_1102.hex";
unsigned char   file_RadarOTA_HEX13[128] = "/home/root/grids/EPM/firmware/radar/RB-60_3.0.1.5_1228.hex";


//====================================================================
M0_RTC_TIME_FRAME  	Tst_RTC;




//====================================================================
extern	int 	A53M0_Tx;
extern 	M0_UART_FIFO		A53M0_RxQ;


//====================================================================
void  	uartA53M0_SetM0_TestRTC( M0_RTC_TIME_FRAME* rtc );
void  	Tst_M0_Sys_Parameter_Default( void  );







//********************************************************************
//
//********************************************************************
void  Keyboard_input_thread( void )
{
	char key;
	char StrCmd[256];
	char StrValue[16];
	int 	StrLen;
	int  cmdValue;


	struct input_event 	event_in;

	printf( "********** **********  Thread Keyboard_input_thread Start  ********** ********** \n" );


	unsigned char 	eep_Tx_Buf[256];
	unsigned char 	eep_Rx_Buf[256];
	UINT16  eep_addr = 0x0000;

	int  	i;


	// 	TEST 		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	#if  	Tst_JSON_T01
		Tst_JSON_Fun( );
	#endif  		//#if  	Tst_JSON_T01
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	for( i=0 ; i<256 ; i++ )		{
		//eep_Tx_Buf[i] = i;
		eep_Tx_Buf[i] = 0x11;
	}



	while( 1 )		{

		bzero( StrCmd, 16 );
		bzero( StrValue, 16 );
		gets( StrCmd );
		StrLen = strlen( StrCmd );
		//printf( "\n keyIn[%s]-[%d] \n", StrCmd, StrLen );


		switch( StrLen ) 		{
			//==============================================================
			case 1:
				//	Test Change Battery Source 		A / B 	--------------------
				if( (strcmp( StrCmd, "A" )==0) || (strcmp( StrCmd, "a" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					uartA53M0_Set_Bat_Source( 0 );
				}
				else if( (strcmp( StrCmd, "B" )==0) || (strcmp( StrCmd, "b" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					uartA53M0_Set_Bat_Source( 1 );
				}

				//	Test A53 Sleep  	----------------------------------------
				else if( (strcmp( StrCmd, "S" )==0) || (strcmp( StrCmd, "s" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					printf( "          ---------- Keyboard_input_thread \n" );
					usleep( 100 );
					A53M_Sleep( );
				}


				//	TEST  	--------------------------------------------------
				else if( (strcmp( StrCmd, "t" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					uartA53M0_Set_Chili2S_PAN_ADD( 0x2222, 0x0000, 16 );
				}
				else if( (strcmp( StrCmd, "T" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					uartA53M0_Set_Chili2S_PAN_ADD( 0x7777, 0x0000, 17 );
				}
				break;


			//==============================================================
			case 2:
				//	Test  ML22Q53  	------------------------------------------
				if( (strcmp( StrCmd, "MV" )==0) || (strcmp( StrCmd, "mv" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );

					unsigned char  ml22_VoiceFile[256];
					bzero( ml22_VoiceFile, 256 );
					sprintf( ml22_VoiceFile, "%s", "/home/root/grids/EPM/firmware/ml22_voice/Hongkong_Voice_1_0_0.bin" );
					ml22_Flash_Verify( ml22_VoiceFile );
				}
				else if( (strcmp( StrCmd, "MW" )==0) || (strcmp( StrCmd, "mw" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					
					unsigned char  ml22_VoiceFile[256];
					bzero( ml22_VoiceFile, 256 );
					sprintf( ml22_VoiceFile, "%s", "/home/root/grids/EPM/firmware/ml22_voice/Hongkong_Voice_1_0_0.bin" );
					ml22_Flash_Write( ml22_VoiceFile );
				}

				//	Test Radar Set Param  	----------------------------------
				else if( (strcmp( StrCmd, "RS" )==0) || (strcmp( StrCmd, "rs" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					//uartA53M0_update_Radar_parameter( );
					system( "wget -c -T30 -t3 -P /home/root/grids/EPM/firmware/radar ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/radarparam30.txt" );
					sleep( 2 );
					radar_set_param( );
				}

				//	Test Read Status 	----------------------------------------
				else if( (strcmp( StrCmd, "R1" )==0) || (strcmp( StrCmd, "r1" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					//uartA53M0_REQM0_G_Sensor( );
					uartA53M0_Req_Radar_Status( );
					//uartA53M0_REQM0_Temp( );
				}

				//	Test M0 System Info.  	----------------------------------
				else if( (strcmp( StrCmd, "M0" )==0) || (strcmp( StrCmd, "m0" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					uartA53M0_REQM0_SystemInfo( );
				}

				break;


			//==============================================================
			case 3:
				//	Radar OTA Test 
				if( (strcmp( StrCmd, "RAV" )==0) || (strcmp( StrCmd, "rav" )==0) )	{
					RadarFW_HEX_BIN( file_RadarOTA_HEX );
				}
				/*
					unsigned char   file_RadarOTA_HEX00[128] = "/home/root/grids/EPM/firmware/radar/ASCLoader.hex";
					unsigned char   file_RadarOTA_HEX11[128] = "/home/root/grids/EPM/firmware/radar/RB-60_3.0.1.2_1006.hex";
					unsigned char   file_RadarOTA_HEX12[128] = "/home/root/grids/EPM/firmware/radar/RB-60_3.0.1.4_1102.hex";
					unsigned char   file_RadarOTA_HEX13[128] = "/home/root/grids/EPM/firmware/radar/RB-60_3.0.1.5_1228.hex";

					[wget -c -T30 -t3 -P /home/root/grids/EPM/firmware/radar ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/RB-60_3.0.1.5_1228.hex]
					[wget -c -T30 -t3 -P /home/root/grids/EPM/firmware/radar ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/RB-60_3.0.1.4_1102.hex]
					[wget -c -T30 -t3 -P /home/root/grids/EPM/firmware/radar ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/RB-60_3.0.1.2_1006.hex]

				*/

				else if( (strcmp( StrCmd, "RTC" )==0) || (strcmp( StrCmd, "rtc" )==0) )	{
					uartA53M0_SetM0_currentRTC( );
				}

				else if( (strcmp( StrCmd, "RS0" )==0) || (strcmp( StrCmd, "rs0" )==0) )	{
					uartA53M0_Set_Radar_ShowAllData( 0 );
				}
				else if( (strcmp( StrCmd, "RS1" )==0) || (strcmp( StrCmd, "rs1" )==0) )	{
					uartA53M0_Set_Radar_ShowAllData( 1 );
				}


				//	Test MIPI LCD FrameBuffer 	------------------------------
				else if( (strcmp( StrCmd, "D01" )==0) || (strcmp( StrCmd, "d01" )==0) )	{
					LCD_Disp_No = 01;
				}
				else if( (strcmp( StrCmd, "D02" )==0) || (strcmp( StrCmd, "d02" )==0) )	{
					LCD_Disp_No = 02;
				}
				else if( (strcmp( StrCmd, "D03" )==0) || (strcmp( StrCmd, "d03" )==0) )	{
					LCD_Disp_No = 03;
				}
				else if( (strcmp( StrCmd, "D04" )==0) || (strcmp( StrCmd, "d04" )==0) )	{
					LCD_Disp_No = 04;
				}
				else if( (strcmp( StrCmd, "D05" )==0) || (strcmp( StrCmd, "d05" )==0) )	{
					LCD_Disp_No = 05;
				}


				//============================================================
				//	Radar OTA  	----------------------------------------------
				else if( (strcmp( StrCmd, "RA0" )==0) || (strcmp( StrCmd, "ra0" )==0) )	{
					printf( " StrCmd-[%s] ::  DownLoad [radarparam30.txt]\n", StrCmd );

					system( "wget -c -T30 -t3 -P /home/root/grids/EPM/firmware/radar ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/radarparam30.txt" );
				}
				else if( (strcmp( StrCmd, "RA1" )==0) || (strcmp( StrCmd, "ra1" )==0) )	{
					printf( " StrCmd-[%s] ::  DownLoad [RB-60_3.0.1.2_1006]\n", StrCmd );

					bzero( OTA_Radar.FileName_radarOTA, 256 );
					sprintf( OTA_Radar.FileName_radarOTA, "RB-60_3.0.1.2_1006.hex" );
					system( "wget -c -T30 -t3 -P /home/root/grids/EPM/firmware/radar ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/RB-60_3.0.1.2_1006.hex" );

					printf( "\n  ----- TstA53M0  Radar OTA : [%s] \n\n", OTA_Radar.FileName_radarOTA);
				}
				else if( (strcmp( StrCmd, "RA2" )==0) || (strcmp( StrCmd, "ra2" )==0) )	{
					printf( " StrCmd-[%s] ::  DownLoad [RB-60_3.0.1.4_1102]\n", StrCmd );

					bzero( OTA_Radar.FileName_radarOTA, 256 );
					sprintf( OTA_Radar.FileName_radarOTA, "RB-60_3.0.1.4_1102.hex" );
					system( "wget -c -T30 -t3 -P /home/root/grids/EPM/firmware/radar ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/RB-60_3.0.1.4_1102.hex" );

					printf( "\n  ----- TstA53M0  Radar OTA : [%s] \n\n", OTA_Radar.FileName_radarOTA);
				}
				else if( (strcmp( StrCmd, "RA3" )==0) || (strcmp( StrCmd, "ra3" )==0) )	{
					printf( " StrCmd-[%s] ::  DownLoad [RB-60_3.0.1.5_1228.hex]\n", StrCmd );

					bzero( OTA_Radar.FileName_radarOTA, 256 );
					sprintf( OTA_Radar.FileName_radarOTA, "RB-60_3.0.1.5_1228.hex" );
					system( "wget -c -T30 -t3 -P /home/root/grids/EPM/firmware/radar ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/RB-60_3.0.1.5_1228.hex" );

					printf( "\n  ----- TstA53M0  Radar OTA : [%s] \n\n", OTA_Radar.FileName_radarOTA);
				}

				else if( (strcmp( StrCmd, "RAA" )==0) || (strcmp( StrCmd, "raa" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );

					//	TEST  	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					bzero( OTA_Radar.FileName_radarOTA, 256 );
					sprintf( OTA_Radar.FileName_radarOTA, "RB-60_3.0.1.5_1228.hex" );
					OTA_Radar_get_HEX( );
				}

				else if( (strcmp( StrCmd, "ROO" )==0) || (strcmp( StrCmd, "roo" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					printf( "\n **********  Radar_OTA_thread : RADAR_OTACMD_INIT  \n" );
					OTA_Radar.cmd = RADAR_OTACMD_START;
					printf( "\n **********  Radar_OTA_thread : -----------------  \n" );
				}


				//	Chili2s OTA  ---------------------------------------------
				else if( (strcmp( StrCmd, "COK" )==0) || (strcmp( StrCmd, "cok" )==0) )	{
					//printf( " StrCmd-[%s] \n", StrCmd );
					printf( "\n ----------  OTA_Chili2s.cmd = [%02X]  [%s]\n", OTA_Chili2s.cmd, OTA_Chili2s.FileName_OTA );
				}

				else if( (strcmp( StrCmd, "COO" )==0) || (strcmp( StrCmd, "coo" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					//printf( "\n **********  Radar_OTA_thread : RADAR_OTACMD_INIT  \n" );
					OTA_Chili2s.cmd = CHILI2S_OTACMD_START;
				}
				else if( (strcmp( StrCmd, "CO0" )==0) || (strcmp( StrCmd, "co0" )==0) )	{
					//printf( " StrCmd-[%s] \n", StrCmd );
					bzero( OTA_Chili2s.FileName_OTA, 256 );
					sprintf( OTA_Chili2s.FileName_OTA, "PKmeter_025a2_DL.bin" );
					printf( "Chili2s OTA file:[%s]-[%s] \n", StrCmd, OTA_Chili2s.FileName_OTA );
				}
				else if( (strcmp( StrCmd, "CO1" )==0) || (strcmp( StrCmd, "co1" )==0) )	{
					//printf( " StrCmd-[%s] \n", StrCmd );
					bzero( OTA_Chili2s.FileName_OTA, 256 );
					sprintf( OTA_Chili2s.FileName_OTA, "PKmeter_025a2OTAtst_DL.bin" );
					printf( "Chili2s OTA file:[%s]-[%s] \n", StrCmd, OTA_Chili2s.FileName_OTA );
				}


				//	Test  Gesture  	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				else if( (strcmp( StrCmd, "MT0" )==0) || (strcmp( StrCmd, "mt0" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					uartA53M0_Set_Gesture_SkipTime( 5 );  		//	500ms
				}
				else if( (strcmp( StrCmd, "MT1" )==0) || (strcmp( StrCmd, "mt1" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					uartA53M0_Set_Gesture_SkipTime( 30 );  		//	3s
				}
				else if( (strcmp( StrCmd, "MT2" )==0) || (strcmp( StrCmd, "mt2" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					uartA53M0_Set_Gesture_SkipTime( 100 );  		//	10s
				}

				//	Test  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				else if( (strcmp( StrCmd, "ROT" )==0) || (strcmp( StrCmd, "rot" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					OTA_Radar_Req_ProgramData( );
				}

				else if( (strcmp( StrCmd, "TTT" )==0) || (strcmp( StrCmd, "ttt" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					uartA53M0_REQM0_SelfTest( );
				}


				else  {
					memcpy( StrValue, StrCmd+2, StrLen-2 );
					StrCmd[2] = 0x00;
					StrCmd[3] = 0x00;
					cmdValue = (int)strtol( StrValue, NULL, 16 );
					printf( "  ---- 3 StrValue[%s] StrCmd[%s]  =[%d]\n", StrValue,StrCmd, cmdValue );

					if( (strcmp( StrCmd, "MP" )==0) || (strcmp( StrCmd, "mp" )==0) )	{
						printf( " StrCmd-[%s]-[%d] \n", StrCmd, cmdValue );
						ml22_voice_Play_Start( cmdValue );
					}
				}
				break;


			//==============================================================
			case 4:
				if( (strcmp( StrCmd, "SELF" )==0) || (strcmp( StrCmd, "self" )==0) )	{
					printf( " StrCmd-[%s] \n", StrCmd );
					uartA53M0_REQM0_SelfTest( );
				}


				//	M0 system parameter TST 	--------------------------------
				else if( (strcmp( StrCmd, "M0SS" )==0) || (strcmp( StrCmd, "m0ss" )==0) )	{
					uartA53M0_Req_M0_Sys_parameter( );
				}
				
				else if( (strcmp( StrCmd, "M0S0" )==0) || (strcmp( StrCmd, "m0s0" )==0) )	{
					//	default
					Tst_M0_Sys_Parameter_Default( );
				  uartA53M0_Set_M0_Sys_parameter( );
				}

				else if( (strcmp( StrCmd, "M0S1" )==0) || (strcmp( StrCmd, "m0s1" )==0) )	{
					Tst_M0_Sys_Parameter_Default( );
					M0_Sys_Parameter.period_heartbeat.Hour = 0;
					M0_Sys_Parameter.period_heartbeat.Minute = 0;
					M0_Sys_Parameter.period_heartbeat.Second = 22;

					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Hour = 0;
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Minute = 0;
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Second = 33;

					M0_Sys_Parameter.radarA.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarA.car_car_ck.Minute = 0;
					M0_Sys_Parameter.radarA.car_car_ck.Second = 44;
					M0_Sys_Parameter.radarB.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarB.car_car_ck.Minute = 0;
					M0_Sys_Parameter.radarB.car_car_ck.Second = 44;
				  uartA53M0_Set_M0_Sys_parameter( );
				  usleep( 150000 );		//	150ms
				  uartA53M0_REQM0_SystemInfo( );
				}

				else if( (strcmp( StrCmd, "M0S2" )==0) || (strcmp( StrCmd, "m0s2" )==0) )	{
					Tst_M0_Sys_Parameter_Default( );
					M0_Sys_Parameter.period_heartbeat.Hour = 0;
					M0_Sys_Parameter.period_heartbeat.Minute = 1;
					M0_Sys_Parameter.period_heartbeat.Second = 22;

					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Hour = 0;
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Minute = 1;
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Second = 33;

					M0_Sys_Parameter.radarA.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarA.car_car_ck.Minute = 1;
					M0_Sys_Parameter.radarA.car_car_ck.Second = 44;
					M0_Sys_Parameter.radarB.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarB.car_car_ck.Minute = 1;
					M0_Sys_Parameter.radarB.car_car_ck.Second = 44;
				  uartA53M0_Set_M0_Sys_parameter( );
				  usleep( 150000 );		//	150ms
				  uartA53M0_REQM0_SystemInfo( );
				}

				else if( (strcmp( StrCmd, "M0S3" )==0) || (strcmp( StrCmd, "m0s3" )==0) )	{
					//	Test  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					Tst_M0_Sys_Parameter_Default( );
					Tst_RTC.Year = 11;
					Tst_RTC.Month = 1;
					Tst_RTC.Day = 1;
					Tst_RTC.Hour = 23;
					Tst_RTC.Minute = 35;
					Tst_RTC.Second = 33;
					uartA53M0_SetM0_TestRTC( &Tst_RTC );


					M0_Sys_Parameter.period_heartbeat.Hour = 0;
					M0_Sys_Parameter.period_heartbeat.Minute = 1;
					M0_Sys_Parameter.period_heartbeat.Second = 2;

					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Hour = 0;
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Minute = 1;
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Second = 1;

					M0_Sys_Parameter.fee_time.Fee_Free_Enable = 1;
					M0_Sys_Parameter.fee_time.Fee_Start.Hour = 23;
					M0_Sys_Parameter.fee_time.Fee_Start.Minute = 49;
					M0_Sys_Parameter.fee_time.Fee_Start.Second = 33;
					
					M0_Sys_Parameter.fee_time.Fee_End.Hour = 23;
					M0_Sys_Parameter.fee_time.Fee_End.Minute = 56;
					M0_Sys_Parameter.fee_time.Fee_End.Second = 44;

					M0_Sys_Parameter.radarA.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarA.car_car_ck.Minute = 1;
					M0_Sys_Parameter.radarA.car_car_ck.Second = 5;
					M0_Sys_Parameter.radarB.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarB.car_car_ck.Minute = 2;
					M0_Sys_Parameter.radarB.car_car_ck.Second = 5;
				  uartA53M0_Set_M0_Sys_parameter( );
				  usleep( 150000 );		//	150ms
				  uartA53M0_REQM0_SystemInfo( );
				}
				else if( (strcmp( StrCmd, "M0S4" )==0) || (strcmp( StrCmd, "m0s4" )==0) )	{
					//	Test  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					Tst_M0_Sys_Parameter_Default( );
					Tst_RTC.Year = 11;
					Tst_RTC.Month = 1;
					Tst_RTC.Day = 1;
					Tst_RTC.Hour = 23;
					Tst_RTC.Minute = 54;
					Tst_RTC.Second = 11;
					uartA53M0_SetM0_TestRTC( &Tst_RTC );


					M0_Sys_Parameter.period_heartbeat.Hour = 0;
					M0_Sys_Parameter.period_heartbeat.Minute = 0;
					M0_Sys_Parameter.period_heartbeat.Second = 22;

					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Hour = 0;
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Minute = 0;
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Second = 33;

					M0_Sys_Parameter.fee_time.Fee_Free_Enable = 1;
					M0_Sys_Parameter.fee_time.Fee_Start.Hour = 23;
					M0_Sys_Parameter.fee_time.Fee_Start.Minute = 57;
					M0_Sys_Parameter.fee_time.Fee_Start.Second = 33;
					
					M0_Sys_Parameter.fee_time.Fee_End.Hour = 0;
					M0_Sys_Parameter.fee_time.Fee_End.Minute = 2;
					M0_Sys_Parameter.fee_time.Fee_End.Second = 44;

					M0_Sys_Parameter.radarA.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarA.car_car_ck.Minute = 0;
					M0_Sys_Parameter.radarA.car_car_ck.Second = 44;
					M0_Sys_Parameter.radarB.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarB.car_car_ck.Minute = 0;
					M0_Sys_Parameter.radarB.car_car_ck.Second = 44;
				  uartA53M0_Set_M0_Sys_parameter( );
				  usleep( 150000 );		//	150ms
				  uartA53M0_REQM0_SystemInfo( );
				}
				else if( (strcmp( StrCmd, "M0R1" )==0) || (strcmp( StrCmd, "m0r1" )==0) )	{
					M0_Sys_Parameter.radarA.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarA.car_car_ck.Minute = 1;
					M0_Sys_Parameter.radarA.car_car_ck.Second = 5;
					M0_Sys_Parameter.radarB.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarB.car_car_ck.Minute = 2;
					M0_Sys_Parameter.radarB.car_car_ck.Second = 5;
				  uartA53M0_Set_M0_Sys_parameter( );
				  usleep( 150000 );		//	150ms
				  uartA53M0_REQM0_SystemInfo( );
				}




				else if( (strcmp( StrCmd, "RTC0" )==0) || (strcmp( StrCmd, "rtc0" )==0) )	{
					Tst_RTC.Year = 11;
					Tst_RTC.Month = 1;
					Tst_RTC.Day = 1;
					Tst_RTC.Hour = 19;
					Tst_RTC.Minute = 45;
					Tst_RTC.Second = 0;
					uartA53M0_SetM0_TestRTC( &Tst_RTC );
				}


				//	LCD BackLight LED TST 	----------------------------------
				else if( (strcmp( StrCmd, "LED0" )==0) || (strcmp( StrCmd, "led0" )==0) )	{
					//printf( " StrCmd-[%s] \n", StrCmd );
					printf( "\n  Test - A53M_LCD_BackLight_OFF \n" );
					A53M_LCD_BackLight_OFF( );
				}
				else if( (strcmp( StrCmd, "LED1" )==0) || (strcmp( StrCmd, "led1" )==0) )	{
					//printf( " StrCmd-[%s] \n", StrCmd );
					printf( "\n  Test - A53M_LCD_BackLight_ON \n" );
					A53M_LCD_BackLight_ON( );
				}

				//	Test USB Hub power 	--------------------------------------
				else if( (strcmp( StrCmd, "USB0" )==0) || (strcmp( StrCmd, "usb0" )==0) )	{
					printf( "\n  Test - USB hub power Off \n" );
					A53M_USB_HUB_power_Off( );
				}
				else if( (strcmp( StrCmd, "USB1" )==0) || (strcmp( StrCmd, "usb1" )==0) )	{
					printf( "\n  Test - USB hub power On \n" );
					A53M_USB_HUB_power_On( );
				}

				else 	{
					memcpy( StrValue, StrCmd+2, StrLen-2 );
					StrCmd[2] = 0x00;
					StrCmd[3] = 0x00;
					cmdValue = (int)strtol( StrValue, NULL, 16 );
					printf( "  ---- 4 StrValue[%s] StrCmd[%s]  =[%d]\n", StrValue,StrCmd, cmdValue );

					if( (strcmp( StrCmd, "MP" )==0) || (strcmp( StrCmd, "mp" )==0) )	{
						printf( " StrCmd-[%s]-[%d] \n", StrCmd, cmdValue );
						ml22_voice_Play_Start( cmdValue );
					}
				}

				break;

		}  	//switch( StrLen ) 		{




		//================================================================
		//printf( " ___________ sleep \n" );
		//usleep( 100000 );   //  100ms
		//usleep( 200000 );   //  200ms
		usleep( 500000 );   //  500ms
		//usleep( 1000000 );   //  1000ms
	} 		//while( 1 )		{
} 		//void  Keyboard_input_thread( void )























//********************************************************************
//
//********************************************************************
/*
	typedef struct {
	  UINT8   Year;
	  UINT8   Month;
	  UINT8   Day;
	  UINT8   WeekDay;

	  UINT8   Hour;
	  UINT8   Minute;
	  UINT8   Second;  
	  UINT8   nc;
	}M0_RTC_TIME_FRAME;
*/
void 	uartA53M0_SetM0_TestRTC( M0_RTC_TIME_FRAME* rtc )
{
	unsigned char 	*txPtr = A53M0_TxBuf;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf("\n ========== uartA53M0_SetM0_TestRTC  ::  [%02d/%02d/%02d %02d:%02d:%02d] \n",
			rtc->Year,
			rtc->Month,
			rtc->Day,
			rtc->Hour,
			rtc->Minute,
			rtc->Second );



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

  *txPtr = rtc->Year;  					txPtr++;
  *txPtr = rtc->Month;  				txPtr++;
  *txPtr = rtc->Day;  					txPtr++;
  *txPtr = rtc->Hour;  					txPtr++;
  *txPtr = rtc->Minute;  				txPtr++;
  *txPtr = rtc->Second;  				txPtr++;


  //==================================================================
  int tx_length = txPtr - A53M0_TxBuf;
  A53M0_TxBuf[1] = (tx_length-3) & 0x00FF;
  A53M0_TxBuf[2] = ((tx_length-3) >>8 ) & 0x00FF;

  UINT16 	crc16 = Get_ModBus_CRC16( A53M0_TxBuf+6, 6 );
  A53M0_TxBuf[4] = crc16 & 0x00FF;
  A53M0_TxBuf[5] = (crc16>>8) & 0x00FF;

	//==================================================================
  A53M0_Tx = 0;
  A53M0_TxLength = tx_length;
} 	//void 	uartA53M0_SetM0_TestRTC( M0_RTC_TIME_FRAME* rtc )


//********************************************************************
//
//********************************************************************
//	OnOff=0,  PowerOff;		=1, PowerOn
//	pwCtl =
//					0x01,		A53 power CTL.
void 	uartA53M0_Set_SysPower( UINT8 pwCtl, UINT8 OnOff )
{
	unsigned char 	*txPtr = A53M0_TxBuf;
	int  i;

	while( (A53M0_TxLength != 0) || (flg_M0uart_Tx > 0) )	{
		usleep( 10000 );	//	10ms;
	}
	flg_M0uart_Tx = 1;

	printf(" ========== uartA53M0_Set_SysPower ---------- [%02X][%02X] \n", pwCtl, OnOff);


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

  *txPtr = SUBTYPE_SYS_PW; 		txPtr++;
  
	*txPtr = pwCtl; 							txPtr++;
	*txPtr = OnOff; 							txPtr++;

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
}  		//void 	uartA53M0_Set_SysPower( UINT8 pwCtl, UINT8 OnOff )


















//******************************************************************************
//
//******************************************************************************
void 	TstA53M0_test( void )
{
	struct sched_param 	my_params;
	cpu_set_t mask;

	return;
} 		//void 	TstA53M0_test( void )


//******************************************************************************
//
//******************************************************************************
//	radarparam.txt
//	wput ./radarparam.txt ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/
//	wget -c -T30 -t3 -P /home/root/grids/bin ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/radarparam.txt
void 	radar_param_down ( void )
{
	char	sysCmdBuf[256];

	#if 	M0_RADAR_VER_30_210930
		bzero( sysCmdBuf, 256 );	
		sprintf( sysCmdBuf, "rm /home/root/grids/EPM/firmware/radar/radarparam30.txt" );
		system( sysCmdBuf );
		usleep( 20000 );

		bzero( sysCmdBuf, 256 );
		sprintf( sysCmdBuf, "wget -c -T30 -t3 -P /home/root/grids/EPM/firmware/radar ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/radarparam30.txt" );
		printf( "  ***** radar_param_down : [%s] \n", sysCmdBuf );
		system( sysCmdBuf );

	#else  	//#if 	M0_RADAR_VER_30_210930
		bzero( sysCmdBuf, 256 );	
		sprintf( sysCmdBuf, "rm /home/root/grids/bin/radarparam.txt" );
		system( sysCmdBuf );
		usleep( 20000 );

		bzero( sysCmdBuf, 256 );
		sprintf( sysCmdBuf, "wget -c -T30 -t3 -P /home/root/grids/bin ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/radarparam.txt" );
		system( sysCmdBuf );

	#endif  	//#if 	M0_RADAR_VER_30_210930

} 		//void 	radar_param_down ( void )


//******************************************************************************
//
//******************************************************************************
//	/home/root/grids/bin/radarparam.txt
//	M0_radarA_set		M0_radarB_set
void 	radar_param_set ( void )
{
	FILE*	f_radarParam;
	unsigned char  R_lineBuf[256];

	int 	scan_interval;

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
		return;
	} 	//if( f_radarParam )		{

	uartA53M0_Set_Radar_Parameter( 0, 0 );
} 		//void 	radar_param_set ( void )


//******************************************************************************
//
//******************************************************************************
void 	uartA53M0_update_Radar_parameter( void )
{
	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf( "\n========== Thread uartA53M0_update_Radar_parameter Start  ==========  [%02d/%02d/%02d %02d:%02d:%02d] \n\n",
			((a53m0API_current_tm->tm_year+1900)-2000),
						a53m0API_current_tm->tm_mon + 1,
						a53m0API_current_tm->tm_mday,
						a53m0API_current_tm->tm_hour,
						a53m0API_current_tm->tm_min,
						a53m0API_current_tm->tm_sec	 );
			
	radar_param_down( );
	usleep( 500000 );
	radar_param_set( );
}  	//void 	uartA53M0_update_Radar_parameter( void )










//********************************************************************
//
//********************************************************************
// 	Test  "system" / "popen"
void 	Tst_JSON_Fun01( void )
{
	char	sysCmdBuf[4096];

	printf( "\n" );
	printf(" __________  Tst_JSON_Fun01 __________\n");

	printf("\n __________  Tst_JSON_Fun01  T01\n");
	bzero( sysCmdBuf, 4096 );
	//sprintf( sysCmdBuf, "wget ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/radarparam.txt" );
	sprintf( sysCmdBuf, "wget -c -T30 -t3 -P /home/root/grids/bin ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/radarparam.txt" );
	system( sysCmdBuf );

	
	printf("\n __________  Tst_JSON_Fun01  T02\n");
	bzero( sysCmdBuf, 4096 );
	sprintf( sysCmdBuf, "wget -c -T30 -t3 -P /home/root/grids/bin ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/radarparam.TTT" );
	system( sysCmdBuf );

	
	printf("\n __________  Tst_JSON_Fun01  T03\n");
	bzero( sysCmdBuf, 4096 );
	FILE* pp;

	if((pp = popen("ls -l", "r")) == NULL) 	{
		printf("popen() error!\n");
		return;
	}

	while (fgets(sysCmdBuf, sizeof sysCmdBuf, pp)) {  
	   printf("  popen r[%s]", sysCmdBuf);  
	}  
	printf( "-----\n" );
	pclose(pp);  

	printf("\n __________  Tst_JSON_Fun01  T04\n");
	bzero( sysCmdBuf, 4096 );
	//FILE* pp;

	if((pp = popen("llllls -l", "r")) == NULL) 	{
		printf("popen() error!\n");
		return;
	}

	while (fgets(sysCmdBuf, sizeof sysCmdBuf, pp)) {  
	   printf("  popen r[%s]", sysCmdBuf);  
	}  
	printf( "-----\n" );
	pclose(pp);  


	printf( "\n" );
} 		//void 	Tst_JSON_Fun01( void )



//********************************************************************
//
//********************************************************************
// 	Test  "system" / "popen"
unsigned char   FILE_JSON_TEST[128] = "/home/root/grids/bin/getParam.txt";

void 	Tst_JSON_Fun( void )
{
	printf( "\n" );
	printf(" __________  Tst_JSON_Fun __________ [%s]\n", FILE_JSON_TEST);


	FILE *f_json;
	int  	f_size;
	char* jsonBuf;

	
	f_json = fopen( FILE_JSON_TEST, "r+b");
	
	if( f_json == NULL ) 	{
		printf( "  xxxxx  Tst_JSON_Fun, Open [%s] Error !!!  xxxxx\n", FILE_JSON_TEST );
		return;
	}
	//printf( "  Tst_JSON_Fun, Open [%s] Ready. \n", FILE_JSON_TEST );

	// 	Get File Size
	fseek( f_json, 0, SEEK_END);
	f_size = ftell( f_json );
	fseek( f_json, 0, SEEK_SET);
	printf( "  Tst_JSON_Fun, Open [%s] Ready.  [%d]\n", FILE_JSON_TEST, f_size );

	jsonBuf = malloc( (f_size/4)*4+16 );

	if( !jsonBuf )		{
		printf( "  xxxxx  Tst_JSON_Fun, malloc Fial  xxxxx\n" );
		return;
	}
	fread( jsonBuf, f_size, 1, f_json );
	/*
	printf( "\n[[" );
	for( int i=0 ; i<f_size ; i++ ) 	{
		printf( " %c", jsonBuf[i] );
	}
	printf( "]]\n" );
	*/
	fclose( f_json );


	//  	JSON Start  ==================================================

	struct json_object *Jobj_main;

	Jobj_main = json_tokener_parse( jsonBuf );
	//printf("1-tokener parse: %s\n", json_object_to_json_string(Jobj_main));
	if( json_object_to_json_string(Jobj_main) == NULL )	{
		printf( "  xxxxx  Tst_JSON_Fun, Get JSON Fial  xxxxx\n" );
		free( jsonBuf );
		return;
	}
	printf( "  Tst_JSON_Fun, Get JSON [[%s]]\n", json_object_to_json_string(Jobj_main) );
	printf( "\n" );
	


	struct json_object *Jobj_Params1 = json_object_object_get(Jobj_main, "Params1");
	if( Jobj_Params1 == NULL )		{
		printf( "  xxxxx  Tst_JSON_Fun, Get JSON Fial 2 xxxxx\n" );
		free( jsonBuf );
		return;
	}


	struct json_object *Jobj_rb60p1 = json_object_object_get(Jobj_Params1, "rb60p1");
	struct json_object *Jobj_rb60p2 = json_object_object_get(Jobj_Params1, "rb60p2");

	if( (Jobj_rb60p1 == NULL) || (Jobj_rb60p2 == NULL ) )		{
	//if( (Jobj_rb60p1 == NULL) )		{
		printf( "  xxxxx  Tst_JSON_Fun, Get JSON Fial 3 xxxxx\n" );
		free( jsonBuf );
		return;
	}

	int  	i;
	//  Jobj_rb60p1  	------------------------------------------------------
	printf( "  ----------  rb60p1 : [" );
	for( i=0 ; i<8 ; i++ )		{
		printf( " %d", json_object_get_int(json_object_array_get_idx(Jobj_rb60p1, i)) );
	}
	printf( " ]\n" );


	//  Jobj_rb60p2  	------------------------------------------------------
	printf( "  ----------  rb60p2 : [" );
	for( i=0 ; i<8 ; i++ )		{
		printf( " %d", json_object_get_int(json_object_array_get_idx(Jobj_rb60p2, i)) );
	}
	printf( " ]\n" );


	//json_object_put(Jobj_rb60p1);
	//json_object_put(Jobj_rb60p2);
	//json_object_put(Jobj_Params1);

	json_object_put(Jobj_main);

printf(" __________  Tst_JSON_Fun --- End \n");

	//==================================================================
	free( jsonBuf );

	printf( "\n" );
} 		//void 	Tst_JSON_Fun( void )











pthread_t thread_TST_LCD_LED;



//********************************************************************
//
//********************************************************************
void  Tst_ePaper_backLED_thread( void )
{
	printf( "********** **********  Thread Tst_ePaper_backLED_thread Start  ********** ********** \n" );


	while( 1 )  	{
		
		//	LED On 		----------------------------------------------------
		if( A53_CK_wifiAP_Enable == 0 ) 	{
			//printf( "$**\n" );
			A53M_LCD_BackLight_ON( );
		}
		else {
			//printf( "$--\n" );
			A53M_LCD_BackLight_OFF( );
		}
		//usleep( 850000 );   //  850ms
		usleep( 400000 );   //  400ms

		//	LED Off 		--------------------------------------------------
		//printf( "$____\n" );
		A53M_LCD_BackLight_OFF( );
		//usleep( 150000 );   //  150ms
		usleep( 100000 );   //  100ms
	}  		//while( 1 )  	{
}  	//void  Tst_ePaper_backLED_thread( void )





pthread_t thread_TST_SLEEP;
int  	sleep_phase;

//********************************************************************
//
//********************************************************************
void  Tst_Sleep_thread( void )
{
	printf( "\n********** **********  Thread Tst_Sleep_thread Start  ********** ********** \n" );
	sleep_phase = 6;

	while( 1 )	{
		sleep( 2 );
		system( "date >> /home/root/Ta53Step" );


		ftime( &time_prgNow );
		//if( ((time_prgNow.time*1000)+time_prgNow.millitm) - ((time_prgStart.time*1000)+time_prgStart.millitm) >  ((60000 *1) + 333) )		{
		
		if( ((time_prgNow.time*1000)+time_prgNow.millitm) - ((time_prgStart.time*1000)+time_prgStart.millitm) 
			>=  ((10000 *sleep_phase) +83 ) )		{
			sleep_phase++;
			if( sleep_phase >6 )	{
				sleep_phase = 6;
			}
			
			//time_prgStart = time_prgNow;
			ftime( &time_prgStart );
			ftime( &time_prgNow );

			//printf( "          ---------- Tst_Sleep_thread \n" );
			printf( "\n  ########## ##########  Tst_Sleep_thread  ########## ########## \n" );
			usleep( 100 );
			A53M_Sleep( );
			//ftime( &time_prgStart );
			//ftime( &time_prgNow );

		}
	}  	//while( 1 )	{

}  	//void  Tst_Sleep_thread( void )














//********************************************************************
//
//********************************************************************
void  Play_Voice_thread( void )
{
		int  	voice_number = 0;

	while( 1 )		{
		/* ????????????
		if( OTA_Radar.cmd != RADAR_OTACMD_NOTHING )		{
				ml22_voice_Play_Start( voice_number );

				voice_number++;
				if( voice_number >= 0x0E )		{
					voice_number = 0;
				}
		}
		*/

		//usleep( 300000 );		//300ms
		//usleep( 100000 );  	//100ms
		sleep( 2 );
	}  		//while( 1 )		{
}  		//void  Play_Voice_thread( int* fdPtr )


//********************************************************************
//
//********************************************************************
void  Test01_thread( void )
{
	while( 1 )		{
		//if( OTA_Radar.cmd != RADAR_OTACMD_NOTHING )		{
				//sleep( 3 );
				//ml22_voice_Play_Start( 4 );

				//printf( "    ---- Test01 command\n" );
				//usleep( 300000 );		//300ms
				uartA53M0_REQM0_SystemInfo( );
				uartA53M0_REQM0_Power( );
				uartA53M0_REQM0_G_Sensor( );
				uartA53M0_REQM0_Temp( );
		//}  		//if( OTA_Radar.cmd != RADAR_OTACMD_NOTHING )		{

		usleep( 277777 );		//300ms
		//usleep( 300000 );		//300ms
		//usleep( 100000 );  	//100ms
		//sleep( 2 );
	}  		//while( 1 )		{
}  		//void  Test01_thread( void )

















//********************************************************************
//
//********************************************************************
void  	Tst_M0_Sys_Parameter_Default( void  )
{
	M0_Sys_Parameter.power_reset_wdt.Hour = 0;
	M0_Sys_Parameter.power_reset_wdt.Minute = 11;
	M0_Sys_Parameter.power_reset_wdt.Second = 0;

	//	Radar 	======================================================
	M0_Sys_Parameter.radarA.exist = 1;
	M0_Sys_Parameter.radarA.car_car_ck.Hour = 0;
	M0_Sys_Parameter.radarA.car_car_ck.Minute = 30;
	M0_Sys_Parameter.radarA.car_car_ck.Second = 0;

	M0_Sys_Parameter.radarB.exist = 1;
	M0_Sys_Parameter.radarB.car_car_ck.Hour = 0;
	M0_Sys_Parameter.radarB.car_car_ck.Minute = 30;
	M0_Sys_Parameter.radarB.car_car_ck.Second = 0;

	//	Fee Time 	======================================================
	M0_Sys_Parameter.fee_time.Fee_Free_Enable = 1;
	M0_Sys_Parameter.fee_time.nc1 = 0x11;
	M0_Sys_Parameter.fee_time.nc2 = 0x22;

	M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Hour = 0;
	M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Minute = 30;
	M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Second = 0;

	M0_Sys_Parameter.fee_time.Fee_Start.Hour = 8;
	M0_Sys_Parameter.fee_time.Fee_Start.Minute = 00;
	M0_Sys_Parameter.fee_time.Fee_Start.Second = 0;
	M0_Sys_Parameter.fee_time.Fee_End.Hour = 20;
	M0_Sys_Parameter.fee_time.Fee_End.Minute = 00;
	M0_Sys_Parameter.fee_time.Fee_End.Second = 0;

	//	HeartBeart		==================================================
	M0_Sys_Parameter.period_heartbeat.Hour = 0;
	M0_Sys_Parameter.period_heartbeat.Minute = 10;
	M0_Sys_Parameter.period_heartbeat.Second = 0;

	M0_Sys_Parameter.radarA.car_car_ck.Hour = 0;
	M0_Sys_Parameter.radarA.car_car_ck.Minute = 30;
	M0_Sys_Parameter.radarA.car_car_ck.Second = 0;
	M0_Sys_Parameter.radarB.car_car_ck.Hour = 0;
	M0_Sys_Parameter.radarB.car_car_ck.Minute = 30;
	M0_Sys_Parameter.radarB.car_car_ck.Second = 0;
}  		//void  	Tst_M0_Sys_Parameter_Default( void  )


