

//	for 	Test		****************************************************

#ifndef _TEST_A53M0_H
#define _TEST_A53M0_H




//	TEST	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//#define 	TST_TxRx_COUNT								1

//#define 	TST_DEBUF_PRINT_001						1
//#define 	TST_RXUART_SHOW_01						1
//#define 	TST_RXUART_SHOW_02						1


#define 	TST_M0_MGC_DATA_PRINT					1
#define 	TST_M0_RTC_PRINT							1
#define 	TST_M0_A53WAKEUP_PRINT				1

#define 	TST_M0_SYSINFO_PRINT					1
#define 	TST_M0_G_DATA_PRINT						1
#define 	TST_M0_TEMP_PRINT							1
#define 	TST_M0_PW_METER_PRINT					1


#define 	TST_M0_A53WAKEUP_LOG					1


#define 	TST_M0_ADC_DATA_PRINT					1
#define 	Tst_PW_Change									1

#define 	TST_M0_RADAR_A_DATA_PRINT			1
#define 	TST_M0_RADAR_B_DATA_PRINT			1
#define 	TST_M0_RADAR_PRINT_ALL				1

#define 	TST_M0_LIDAR_DATA_PRINT				1

#define 	TST_M0_TLSAM_01								1
#define 	TST_M0_TLSAM_SAVE_FILE				1


//#define 	Tst_Radar_PW_OFFON						1
//#define  	Tst_JSON_T01 									1

//--------------------------------------------------------------------
//#define  	Tst_ML22_I2C_S1S2 						1

#define  	Tst_CK_SYSTEM_SLEEP 					1  		//	20220218

//--------------------------------------------------------------------
#define  	Tst_SLEEP_T01				 						1




//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//********************************************************************
//	define
/*
	root@imx8mmrom5721a1:~# cat /proc/bus/input/devices
	I: Bus=0019 Vendor=0000 Product=0000 Version=0000
	N: Name="30370000.snvs:snvs-powerkey"
	P: Phys=snvs-pwrkey/input0
	S: Sysfs=/devices/platform/30370000.snvs/30370000.snvs:snvs-powerkey/input/input0
	U: Uniq=
	H: Handlers=kbd event0 
	B: PROP=0
	B: EV=3
	B: KEY=10000000000000 0

	I: Bus=0019 Vendor=0001 Product=0001 Version=0100
	N: Name="gpio-keys"
	P: Phys=gpio-keys/input0
	S: Sysfs=/devices/platform/gpio-keys/input/input1
	U: Uniq=
	H: Handlers=kbd event1 
	B: PROP=0
	B: EV=3
	B: KEY=10000000000000 0

	root@imx8mmrom5721a1:~# ls -l /dev/input/
	total 0
	drwxr-xr-x 2 root root      80 May 27 03:20 by-path
	crw-rw---- 1 root input 13, 64 May 27 03:20 event0
	crw-rw---- 1 root input 13, 65 May 27 03:20 event1
*/
//#define INPUT_KEYBOARD 	"/dev/input/event1"


//********************************************************************
//	Global
extern 	pthread_t thread_Keyboard_input;
extern 	pthread_t thread_Play_Voice;
extern 	pthread_t thread_Test01;

extern 	pthread_t thread_TST_LCD_LED;
extern 	pthread_t thread_TST_SLEEP;

extern 	UINT32 	Bat_v;
extern 	UINT32 	Bat_i;

extern 	struct timeb  	time_prgStart;
extern 	struct timeb  	time_prgNow;

#if 	Tst_SLEEP_T01
	struct timeb  	time_sleepCK1;
	struct timeb  	time_sleepCK2;
#endif  		//#if 	Tst_SLEEP_T01





//********************************************************************
//  Function
void  Keyboard_input_thread( void );
void  Play_Voice_thread( void );
void  Test01_thread( void );

void 	TstA53M0_test( void );

void 	radar_param_down ( void );
void 	radar_param_set ( void );

void 	Tst_JSON_Fun( void );

void  Tst_ePaper_backLED_thread( void );
void  Tst_Sleep_thread( void );




//	OTA TEST  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
extern 	unsigned char   path_RadarOTA_HEX[];
extern 	unsigned char   file_RadarOTA_HEX[];

extern 	unsigned char   file_RadarOTA_FW_BIN11[];
extern 	unsigned char   file_RadarOTA_FW_BIN12[];


void 	uartA53M0_REQM0_OTA_Radar_Tst( int TstSelect );
void 	uartA53M0_SetM0_TestRTC( M0_RTC_TIME_FRAME* rtc );
void 	uartA53M0_Set_SysPower( UINT8 pwCtl, UINT8 OnOff );



#endif    //_TEST_A53M0_H

