

#include "m0All_Header.h"



//********************************************************************
//  Global
	unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4    20220308B42";			// M0_ALPS_FRAME
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4    20220308B41";			// Device_SelfTest( );  DEV_SELFTEST_ERR_ALPS
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4    20220225B3eT0307B5c";			// 	ALPS + gtk

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4    20220225B3eT0303A3c";			// 	Test: TL_SAM
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4    20220225B3e";			//	A53_awake_thread( )

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4    20220224B28e";			//	Tst_auto_sleep_thread( )
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4    20220222B28b T5g";			//	Tst_auto_sleep_thread( )
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4    20220222B28b";			//	A53 Sleep A53M_SleepState_gpio_H

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4    20220217B27 0218T12";			//	#define  	Tst_CK_SYSTEM_SLEEP
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4    20220217B27 0218T07";			//	Tst_tcp_cmd_thread Socket Command
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4    20220217B27";			//	uartA53M0_Req_M0_Sys_parameter( )

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4  20220217B26T02";			//	M0_SYS_PARAMETER_FRAM
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4  20220216B21";			//	M0_SYS_PARAMETER_FRAM
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4  20220216B20";			//	ml22_Flash_Write( UINT8* filePtr )  /  ml22_Flash_Verify( UINT8* filePtr )
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4  20220216B14";			//	M0_SYS_PARAMETER_FRAM M0_Sys_Parameter; 	/ uartA53M0_Set_M0_Sys_parameter
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4  20220215B05";			//	uart_M0_TIME_EVENT

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4  20220209A27";			//	OTA-Chili2S
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4  20220208A12b";			//	OTA-Chili2S
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4  20220128A0c";			//	["/home/root/grids/EPM/firmware/ml22_voice/ml22_flash.bin"]
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4  20220128A09";			//	M0_WAKEUP_A53_FRAME Msg_M0_wakeup_A53;
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5322_V4  20220127A08";			//	OTA-Chili2S

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_V4  20220120B15";			//	uartA53M0_Set_Radar_ShowAllData()
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL V4  20220119B12";		//	Self-Test + CK OTA_Radar.cmd + K60168 skip time
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL   20220119B12";		//	Self-Test + CK OTA_Radar.cmd + K60168 skip time

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL   20220119B06";		//	Self-Test + CK OTA_Radar.cmd
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL   20220117B03";		//	Self-Test

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL   20220114A361";		// RadarOTA from DCU

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL   20220113A35e3";		//	"Prj316_radarOTA  20220105-031630"
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL   20220110A35c T37";		//	"Prj316_radarOTA  20220105-031630"
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL   20220104L16";		//	Radar OTA Tst
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL   20211230L03";		//	Radar OTA Tst


	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL   202112321K4f";

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL   202112321K4f";
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL   20211220K3  MIPI-Tst03";
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL   20211216K2  SleepTst";

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL  21T10c TstRadarOTA 20211125TR3M7 T0D0";
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL  21T10c TstRadarOTA 20211116TR3M6 T6";  		//	OTA_Radar_B_Verify_FWdata 50ms

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL  21T10c TstRadarOTA 20211109TR18";
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5321_ALL  20211026-21T10c TstRadarOTA T"; 		//	Radar OTA Test

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5320I_ALL  20211021-20Ij3T01"; 		//	Radar OTA Test
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5320I_ALL  20211015-20Ij3"; 		//	M0_RADAR_FRAME; car pre_car

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5320I_ALL  20211014-20Ij2"; 		//	M0_RADAR_FRAME; car pre_car

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5320I_ALL  20211006-20Ih56"; 		//	uartA53M0_Set_Radar_Parameter( &M0_radarA_set, &M0_radarB_set );
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5320I_ALL  20211004-20Ih52"; 		//	uartA53M0_Set_Radar_Parameter( &M0_radarA_set, &M0_radarB_set );
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5320I_ALL  20211004-20Ih31"; 		//	#defiine  TST_M0_RADAR_PRINT_ALL
	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5320I_ALL  20211001-20Ih2"; 		//	M0_RADAR_VER_30_210930

	//unsigned char   FwVer_Ta53m0_API[] = "iMX8mm Ta5320I_ALL  20210929-20Ig0"; 		// 	//	Battery CK logic; modify  M0_POWER_DATA_FRAME




//====================================================================
//  
//unsigned char   dev_UART_A53M0[] = "/dev/ttymxc2";
unsigned char   dev_UART_A53M0[] = "/dev/ttymxc3";


//********************************************************************
//  Global 		-- M0 device information
//********************************************************************
M0_SYS_PARAMETER_FRAM 	M0_Sys_Parameter;

UINT32 								M0_Status_Update;
M0_WAKEUP_A53_FRAME  	Msg_M0_wakeup_A53;
M0_TIME_EVENT_FRAME  	Msg_M0_TimeEvent;

M0_RTC_TIME_FRAME 		M0_rtc;

M0_SYSTEM_INFO 				M0_System_info;

M0_MGC_DATA_FRAME 		M0_mgc3130;

M0_POWER_DATA_FRAME 	M0_power;

M0_TEMP_DATA_FRAME 		M0_temperature;

M0_RADAR_FRAME 				M0_radarA;
M0_RADAR_FRAME 				M0_radarB;
M0_RADAR_SET_FRAME 		M0_radarA_set;
M0_RADAR_SET_FRAME 		M0_radarB_set;

PARKMETER_VOS_MSG_FRAME 		M0_Lidar;

M0_G_SENSOR_FRAME  		g_icm_Data;

M0_ALPS_FRAME  				M0_alps;

M0_TLSAM_DATA_FRAME 	M0_TLSAM_DATA;

M0_DEV_SELF_TEST 			M0_Device_SelfTest;






//====================================================================
pthread_t thread_A53_awake;
pthread_t thread_uartA53M0_Tx;
pthread_t thread_uartA53M0_Rx;
pthread_t thread_wifiAP_ck;
pthread_t thread_Radar_OTA;
pthread_t thread_Chili2s_OTA;

int fd_uartA53M0;


//====================================================================
//	fd_GPIO
int 	fd_gpio_A53_SleepState;
int 	fd_gpio_epaper_backled_state;
int 	fd_gpio_usb_hub_power;

int 	fd_gpio_value_CBUSYB;
int 	fd_gpio_value_RESETB;
int 	fd_gpio_value_IRCSB;
int 	fd_gpio_value_IRON;
int 	fd_gpio_value_CSB;


//********************************************************************
//  Global 		-- M0 device
M0_SYSTEM_INFO 				M0_System_info;
M0_MGC_DATA_FRAME 		M0_mgc3130;


//====================================================================
//	Local Global
time_t a53m0API_currentTime;
struct tm *a53m0API_current_tm;

int  tx_period;
int  tx_No;

int  A53_CK_wifiAP_Enable;  		// =1, Enable CK WiFi AP


// 	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int index_rx = 0;

#if 	TST_TxRx_COUNT
	uint32_t 	Tst_Tx_Cnt;
	uint32_t 	Tst_Rx_Cnt;

	struct timeb  	time_Tx;
	struct timeb  	time_Rx;
#endif 	//#if 	TST_TxRx_COUNT












//********************************************************************
//
//********************************************************************
void  A53M0_gpio_Init( void )
{
	char 	str_cmd[256];
	int  	fd_gpio_dir;
	int  	wRes;

	printf( "**********   A53M_Sleep_gpio_init  **********  \n" );

	//==================================================================
	//	A53 status - Active or Sleep
	//		# S40 GPIO4_IO12 -- Linux-108 -- export gpio10
	bzero( str_cmd, 256 );
	sprintf( str_cmd, "/sys/class/gpio/gpio%d/direction", GPIO_A53_EXPORTNO_SLEEP_STATE );
	//printf( "  ==[%s] \n", str_cmd );
	fd_gpio_dir = open( str_cmd, O_WRONLY );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}
	wRes = write( fd_gpio_dir, "out", sizeof("out"));
	close( fd_gpio_dir );

	bzero( str_cmd, 256 );
	sprintf( str_cmd, "/sys/class/gpio/gpio%d/value", GPIO_A53_EXPORTNO_SLEEP_STATE );
	fd_gpio_A53_SleepState = open( str_cmd, O_RDWR );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}


	//==================================================================
	//	ePaper BackLight LED ON/OFF
	//		# P119   -- export gpio13
	bzero( str_cmd, 256 );
	sprintf( str_cmd, "/sys/class/gpio/gpio%d/direction", GPIO_EPAPER_BACKLED_STATE );
	fd_gpio_dir = open( str_cmd, O_WRONLY );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}
	//write( fd_gpio_dir, "out", sizeof("out"));
	wRes = write( fd_gpio_dir, "out", sizeof("out"));
	close( fd_gpio_dir );

	bzero( str_cmd, 256 );
	sprintf( str_cmd, "/sys/class/gpio/gpio%d/value", GPIO_EPAPER_BACKLED_STATE );
	fd_gpio_epaper_backled_state = open( str_cmd, O_RDWR );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}


	//==================================================================
	//	USB HUB Power Enable
	//		# P117 USB HUB Power -- linux-510 -- export gpio3 
	/*
	bzero( str_cmd, 256 );
	sprintf( str_cmd, "/sys/class/gpio/gpio%d/direction", GPIO_USB_HUB_POWER );
	fd_gpio_dir = open( str_cmd, O_WRONLY );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}
	//write( fd_gpio_dir, "out", sizeof("out"));
	wRes = write( fd_gpio_dir, "out", sizeof("out"));
	close( fd_gpio_dir );

	bzero( str_cmd, 256 );
	sprintf( str_cmd, "/sys/class/gpio/gpio%d/value", GPIO_USB_HUB_POWER );
	fd_gpio_usb_hub_power = open( str_cmd, O_RDWR );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}
	*/


	printf( "\n" );
	//==================================================================
	A53M_LCD_BackLight_OFF( );
	//A53M_USB_HUB_power_On( );		//????????????????????????
}  		//void  A53M0_gpio_Init( void )










//********************************************************************
//
//********************************************************************
//	A53M_SleepState_gpio_H( );  		//	A53 Sleep
void  A53M_SleepState_gpio_H( void )
{
	int  wRes = write( fd_gpio_A53_SleepState, "1" ,sizeof("1"));
}  		//void  A53M_SleepState_gpio_H( void )

//********************************************************************
//
//********************************************************************
//	A53M_SleepState_gpio_L( );  		//	A53 Active
void  A53M_SleepState_gpio_L( void )
{
	int  wRes = write( fd_gpio_A53_SleepState, "0" ,sizeof("0"));
}  		//void  A53M_SleepState_gpio_H( void )




//********************************************************************
//
//********************************************************************
void  A53M_LCD_BackLight_ON( void )
{
	int wRes = write( fd_gpio_epaper_backled_state, "1" ,sizeof("1"));
}  		//void  A53M_LCD_BackLight_ON( void )

//********************************************************************
//
//********************************************************************
void  A53M_LCD_BackLight_OFF( void )
{
	int wRes = write( fd_gpio_epaper_backled_state, "0" ,sizeof("0"));
}  		//void  A53M_LCD_BackLight_OFF( void )




//********************************************************************
//
//********************************************************************
void  A53M_USB_HUB_power_Off( void )
{
	int wRes = write( fd_gpio_usb_hub_power, "1" ,sizeof("1"));
}  		//void  A53M_USB_HUB_power_Off( void )

//********************************************************************
//
//********************************************************************
void  A53M_USB_HUB_power_On( void )
{
	int wRes = write( fd_gpio_usb_hub_power, "0" ,sizeof("0"));
}  		//void  A53M_USB_HUB_power_On( void )












//********************************************************************
//
//********************************************************************
//====================================================================
extern 	struct timeb  	time_A53_awake1;
extern 	struct timeb  	time_A53_awake2;

void  A53M_Sleep( void )
{
	#if  	TST_AUTO_SLEEP
		Tst_Flg_Auto_Sleep = 0;
		ftime( &time_Tst_autu_sleep2 );
		ftime( &time_Tst_autu_sleep1 );
		time_Tst_autu_sleep1 = time_Tst_autu_sleep2;
	#endif  		//#if  	TST_AUTO_SLEEP

	#if  	Tst_CK_SYSTEM_SLEEP
		system( "echo \"\" >> /home/root/sleeplog" );
		system( "echo \"Ta5322_V4 Sleep  _____ _____ _____ _____ _____ \" >> /home/root/sleeplog" );
		system( "date >> /home/root/sleeplog");
	#endif  		//#if  	Tst_CK_SYSTEM_SLEEP




	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf( "\n **********  Set A53 to SLEEP MODE - mem  **********  [%02d/%02d/%02d %02d:%02d:%02d] \n",
			((a53m0API_current_tm->tm_year+1900)-2000),
			a53m0API_current_tm->tm_mon + 1,
			a53m0API_current_tm->tm_mday,
			a53m0API_current_tm->tm_hour,
			a53m0API_current_tm->tm_min,
			a53m0API_current_tm->tm_sec		 );

	time_A53_awake1 = time_A53_awake2;
	uartA53M0_Set_M0_A53Status_Sleep( );
	usleep( 50000 );  		//	50ms

	//==================================================================
		//A53M_SleepState_gpio_H( );  		//	A53 Sleep
	printf( "    $$$$$$$$$$  [echo mem > /sys/power/state] \n" );
	A53_CK_wifiAP_Enable = 0;
	ftime( &time_wifiAP_ck2 );
	time_wifiAP_ck1 = time_wifiAP_ck2;

	A53M_LCD_BackLight_OFF( );
	M0_Status_Update |= M0_DEV_UPDATE_WAKEUP;
	system( "echo mem > /sys/power/state" );
	usleep( 200000 );   //  200ms
}  	//void  A53M_Sleep( void )













//********************************************************************
//
//********************************************************************
int  Str2Hex_2( unsigned char* strPtr, uint8_t* dataPtr )
{	
	unsigned char*  ptr = strPtr;
	uint8_t  data = 0;

	int  i;

	for( i=0 ; i<2 ; i++ )		{
		if( (ptr[i] >= 0x30)&&(ptr[i] <= 0x39) )	{
			data <<= 4;
			data |= (ptr[i] - 0x30);
		}
		
		else if( (ptr[i] >= 0x41)&&(ptr[i] <= 0x46) )	{
			data <<= 4;
			data |= (ptr[i] - 0x37);
		}

		else if( (ptr[i] >= 0x61)&&(ptr[i] <= 0x66) )	{
			data <<= 4;
			data |= (ptr[i] - 0x57);
		}

		else  {
			return 0;
		}
	}  	//for( i=0 ; i<2 ; i++ )		{

		*dataPtr = data;
	return 1;
}  		//int  Str2Hex_2( unsigned char*, uint8_t* dataPtr )

