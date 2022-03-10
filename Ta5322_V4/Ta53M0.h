

//********************************************************************
//  Ta53M0.h
//********************************************************************

#ifndef TA53M0_UART_H
#define TA53M0_UART_H




//********************************************************************
//	System H/W Define
//	SW1-2  	==========================================================
#define  	SW2_FUN_RADAR  		0;		//SW2-ON
#define  	SW2_FUN_ALPS  		1;		//SW2-OFF


//********************************************************************
//	define
#define   UARTA53M0_TX_BUFFER_SIZE    	2048
//#define   UARTA53M0_RX_BUFFER_SIZE    	(2048+1024)
#define   UARTA53M0_RX_BUFFER_SIZE    	2048
#define   UARTA53M0_SPEED    						B115200
//#define   UARTA53M0_SPEED    						B460800
#define   UARTA53M0_RX_Q_BUFFER_SIZE    0x1000 		//	4096


//	GPIO export number  	============================================
#define  	GPIO_A53_EXPORTNO_SLEEP_STATE 				10
#define  	GPIO_EPAPER_BACKLED_STATE 						13
#define  	GPIO_USB_HUB_POWER				 						3

#define  	GPIO_MAP_EXPORTNO_ML22_CBUSYB 				6
#define  	GPIO_MAP_EXPORTNO_ML22_RESETB 				7
#define  	GPIO_MAP_EXPORTNO_ML22_IRCSB 					8
#define  	GPIO_MAP_EXPORTNO_ML22_IRON 					9


//====================================================================
//  A53 <==> M0  	UART Command
#define    uart_REQ_M0_DUMMING 			0x00
#define    uart_RSP_M0_DUMMING 			0x80


#define    uart_REQ_M0_INFO 				0x01
#define    uart_RSP_M0_INFO 				0x81

#define    uart_M0_WAKEUP_A53 			0x82
#define    uart_M0_TIME_EVENT 			0x83

#define    uart_REQ_DEV_FW_VER 			0x21

#define    uart_SET_DEV 						0x50
#define    uart_RSP_DEV 						0xD0

#define    uart_REQ_DEV_STATUS 			0x51
#define    uart_RSP_DEV_STATUS 			0xD1

#define    uart_REQ_SAVE_EEPROM 		0x5A
#define    uart_RSP_SAVE_EEPROM 		0xDA

#define    uart_REQ_READ_EEPROM 		0x5B
#define    uart_RSP_READ_EEPROM 		0xDB

#define    uart_REQ_DEV_RESTART			0x5F
#define    uart_RSP_DEV_RESTART			0xDF

#define    uart_REQ_ENC							0x68
#define    uart_RSP_ENC							0xE8

#define    uart_SET_M0_RTC 					0x60
#define    uart_REQ_M0_RTC 					0x60
#define    uart_RSP_M0_RTC 					0xE0

#define    uart_REQ_ALARM 					0x70
#define    uart_RSP_ALARM 					0xF0


#define    uart_REQ_FW_OTA 					0x7C
#define    uart_RSP_FW_OTA 					0xFC


//====================================================================
//	Alarm Sub-Type;			M0 alarm A53
//	#define    uart_REQ_ALARM 					0x70
//	#define    uart_RSP_ALARM 					0xF0
#define    uart_ALARM_TEMP 								0x10

#define    uart_ALARM_RADAR_PWOFF					0x70
#define    uart_ALARM_RADAR_PWON					0x71


//====================================================================
//	ATSAML22 M0
//====================================================================


//====================================================================
//	Radar OTA
//====================================================================
//#define 	uart_REQ_FW_OTA 					0x7C
//#define 	uart_RSP_FW_OTA 					0xFC

//#define 	SUBTYPE_RADAR_A						0x21
//#define 	SUBTYPE_RADAR_B						0x22


//	OTA_RADAR_FUNCTION 	==============================================
//	Command  	--------------------------------------------------------
//	A53 ==> M0
#define  	RADAR_OTACMD_NOTHING 								0x00

#define  	RADAR_OTACMD_SET_PARAMETER					0xA0

#define  	RADAR_OTACMD_START									0x01 		//	***** Start OTA action
#define  	RADAR_OTACMD_INIT										0x10
#define  	RADAR_OTACMD_ERASE_PAGE							0x20
#define  	RADAR_OTACMD_PROGRAM_DATA						0x30
#define  	RADAR_OTACMD_PROGRAM_CMD						0x31

#define  	RADAR_OTACMD_WAITING								0xFF

//	OTA Status  	----------------------------------------------------
//	M0 ==> A53  status
#define 	OTA_RADAR_RUN_NULL								0x00
#define 	OTA_RADAR_RUN_RECEIVED						0x01 		//	OTA Command received
#define 	OTA_RADAR_RUN_PW_OFF							0x02
#define 	OTA_RADAR_RUN_PW_ON								0x03
#define 	OTA_RADAR_RUN_OTA_MODE01					0x04
#define 	OTA_RADAR_RUN_OTA_MODE02					0x05
#define 	OTA_RADAR_RUN_OTA_MODE03					0x06

#define 	OTA_RADAR_RUN_OTA_MODE11					0x11
#define 	OTA_RADAR_RUN_OTA_MODE12					0x12
#define 	OTA_RADAR_RUN_OTA_MODE13					0x13
#define 	OTA_RADAR_RUN_OTA_MODE14					0x14

#define 	OTA_RADAR_FUN_TEST1								0xF0 		//	OTA Function TEST1

//	OTA Error  	------------------------------------------------------
#define 	OTA_RADAR_ERR_OTA_INIT_00D5							0x0001  		//	0000 0000  0000 0001
#define 	OTA_RADAR_ERR_OTA_INIT_4096							0x0002  		//	0000 0000  0000 0010
#define 	OTA_RADAR_ERR_OTA_INIT_ASC							0x0004  		//	0000 0000  0000 0100
#define 	OTA_RADAR_ERR_OTA_INIT_WPROTECT					0x0008  		//	0000 0000  0000 1000

#define 	OTA_RADAR_ERR_OTA_ERASE_PAGE1						0x0010  		//	0000 0000  0001 0000
#define 	OTA_RADAR_ERR_OTA_ERASE_PAGE2						0x0020  		//	0000 0000  0010 0000

#define 	OTA_RADAR_ERR_OTA_PROGRAM01							0x0100  		//	0000 0001  0000 0000
#define 	OTA_RADAR_ERR_OTA_PROGRAM02							0x0200  		//	0000 0010  0000 0000
#define 	OTA_RADAR_ERR_OTA_PROGRAM_55						0x0400  		//	0000 0100  0000 0000

#define 	OTA_RADAR_ERR_OTA_HEX_DOWNLOAD					0x2000  		//	0010 0000  0000 0000
#define 	OTA_RADAR_ERR_OTA_HEX										0x4000  		//	0100 0000  0000 0000
#define 	OTA_RADAR_ERR_OTA_OTHER									0x8000  		//	1000 0000  0000 0000




//====================================================================
//	Chili2s OTA
//====================================================================
//	OTA Chili2s Function 	============================================
//	Command  	--------------------------------------------------------
//	A53 ==> M0
#define  	CHILI2S_OTACMD_NOTHING								0x00

#define  	CHILI2S_OTACMD_START									0x01

#define  	CHILI2S_OTACMD_INIT										0x10
#define  	CHILI2S_OTACMD_PROGRAM_DATA						0x30


//--------------------------------------------------------------------
//	Chili2s OTA Status
#define  	OTA_CHILI2S_SUCCESS										0x00
#define  	OTA_CHILI2S_ERR_CRC										0x10
#define  	OTA_CHILI2S_ERR_REC										0x20
#define  	OTA_CHILI2S_ERR_TIMEOUT								0xE0
#define  	OTA_CHILI2S_TEST											0xF0
#define  	OTA_CHILI2S_WAITING										0xFF

/*
//	OTA Status  	----------------------------------------------------
//	M0 ==> A53  status
#define 	OTA_CHILI2S_RUN_NULL								0x00
#define 	OTA_CHILI2S_RUN_RECEIVED						0x01 		//	OTA Command received
#define 	OTA_CHILI2S_FUN_TEST1								0xF0 		//	OTA Function TEST1

//	OTA Error  	------------------------------------------------------

#define 	OTA_CHILI2S_ERR_OTA_INIT_00D5							0x0001  		//	0000 0000  0000 0001
#define 	OTA_CHILI2S_ERR_OTA_INIT_4096							0x0002  		//	0000 0000  0000 0010
#define 	OTA_CHILI2S_ERR_OTA_INIT_ASC							0x0004  		//	0000 0000  0000 0100
#define 	OTA_CHILI2S_ERR_OTA_INIT_WPROTECT					0x0008  		//	0000 0000  0000 1000

#define 	OTA_CHILI2S_ERR_OTA_ERASE_PAGE1						0x0010  		//	0000 0000  0001 0000
#define 	OTA_CHILI2S_ERR_OTA_ERASE_PAGE2						0x0020  		//	0000 0000  0010 0000

#define 	OTA_CHILI2S_ERR_OTA_PROGRAM01							0x0100  		//	0000 0001  0000 0000
#define 	OTA_CHILI2S_ERR_OTA_PROGRAM02							0x0200  		//	0000 0010  0000 0000
#define 	OTA_CHILI2S_ERR_OTA_PROGRAM_55						0x0400  		//	0000 0100  0000 0000

#define 	OTA_CHILI2S_ERR_OTA_HEX_DOWNLOAD					0x2000  		//	0010 0000  0000 0000
#define 	OTA_CHILI2S_ERR_OTA_HEX										0x4000  		//	0100 0000  0000 0000
#define 	OTA_CHILI2S_ERR_OTA_OTHER									0x8000  		//	1000 0000  0000 0000
*/







//********************************************************************
//  Global 		-- M0 device information
//********************************************************************
//====================================================================
extern 	int 	fd_gpio_A53_SleepState;
extern 	int 	fd_gpio_epaper_backled_state;
extern 	int 	fd_gpio_usb_hub_power;

extern 	int 	fd_gpio_value_CBUSYB;
extern 	int 	fd_gpio_value_RESETB;
extern 	int 	fd_gpio_value_IRCSB;
extern 	int 	fd_gpio_value_IRON;
extern 	int 	fd_gpio_value_CSB;


//====================================================================
/*
		New information upload from M0 	----------------------------------
#define  	M0_DEV_UPDATE_RTC 					0x00000001  		//0000 0000  0000 0000  0000 0000  0000 0001
#define  	M0_DEV_UPDATE_MGC 					0x00000002  		//0000 0000  0000 0000  0000 0000  0000 0010
#define  	M0_DEV_UPDATE_G_SENSOR			0x00000004  		//0000 0000  0000 0000  0000 0000  0000 0100
#define  	M0_DEV_UPDATE_TEMP					0x00000008  		//0000 0000  0000 0000  0000 0000  0000 1000

#define  	M0_DEV_UPDATE_ADC_1					0x00001000  		//0000 0000  0000 0000  0001 0000  0000 0000
#define  	M0_DEV_UPDATE_ADC_2					0x00002000  		//0000 0000  0000 0000  0010 0000  0000 0000
#define  	M0_DEV_UPDATE_ADC_3					0x00004000  		//0000 0000  0000 0000  0100 0000  0000 0000

#define  	M0_DEV_UPDATE_RADAR_A				0x00000010  		//0000 0000  0000 0000  0000 0000  0001 0000
#define  	M0_DEV_UPDATE_RADAR_B				0x00000020  		//0000 0000  0000 0000  0000 0000  0010 0000
#define  	M0_DEV_UPDATE_ALPS					0x00000040  		//0000 0000  0000 0000  0000 0000  0100 0000
#define  	M0_DEV_UPDATE_LIDAR					0x00000080  		//0000 0000  0000 0000  0000 0000  1000 0000

#define  	M0_DEV_UPDATE_PWMETER0			0x00000100  		//0000 0000  0000 0000  0000 0001  0000 0000
#define  	M0_DEV_UPDATE_PWMETER1			0x00000200  		//0000 0000  0000 0000  0000 0010  0000 0000
#define  	M0_DEV_UPDATE_PWMETER2			0x00000400  		//0000 0000  0000 0000  0000 0100  0000 0000
#define  	M0_DEV_UPDATE_PWMETER3			0x00000800  		//0000 0000  0000 0000  0000 1000  0000 0000

#define  	M0_DEV_UPDATE_TLSAM					0x08000000  		//0000 1000  0000 0000  0000 0000  0000 0000

#define  	M0_DEV_UPDATE_WAKEUP				0x10000000  		//0001 0000  0000 0000  0000 0000  0000 0000
#define  	M0_DEV_UPDATE_M0_SELFTEST		0x20000000  		//0010 0000  0000 0000  0000 0000  0000 0000
#define  	M0_DEV_UPDATE_TIME_EVENT		0x40000000  		//0100 0000  0000 0000  0000 0000  0000 0000
#define  	M0_DEV_UPDATE_SYSINFO				0x80000000  		//1000 0000  0000 0000  0000 0000  0000 0000
*/
extern 	UINT32 						M0_Status_Update;

/*
typedef struct  {
	UINT32 	Device_SelfCheck;
	M0_RTC_TIME_FRAME  		mcu_RTC;
}M0_DEV_SELF_TEST;

M0_Device_SelfTest.Device_SelfCheck  ::
		#define  	DEV_SELFTEST_ERR_RTC  											0x0001  		//	0000 0000  0000 0001
		#define  	DEV_SELFTEST_ERR_GESTURE  									0x0002  		//	0000 0000  0000 0010
		#define  	DEV_SELFTEST_ERR_G_SENSOR  									0x0004  		//	0000 0000  0000 0100

		#define  	DEV_SELFTEST_ERR_RADAR_A  									0x0008  		//	0000 0000  0000 1000
		#define  	DEV_SELFTEST_ERR_RADAR_B  									0x0010  		//	0000 0000  0001 0000

		#define  	DEV_SELFTEST_ERR_ALPS  											0x0080  		//	0000 0000  1000 0000

		#define  	DEV_SELFTEST_ERR_LTC2644  									0x0100  		//	0000 0001  0000 0000
		#define  	DEV_SELFTEST_ERR_LM75  											0x0200  		//	0000 0010  0000 0000
		#define  	DEV_SELFTEST_ERR_STK8BA53  									0x0400  		//	0000 0100  0000 0000
		#define  	DEV_SELFTEST_ERR_K60168  										0x0800  		//	0000 1000  0000 0000

		#define  	DEV_SELFTEST_ERR_EEPROM  										0x1000  		//	0001 0000  0000 0000

		#define  	DEV_SELFTEST_ERR_CHILI2S  									0x8000  		//	1000 0000  0000 0000
*/
extern 	M0_DEV_SELF_TEST 	M0_Device_SelfTest;

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
extern 	M0_RTC_TIME_FRAME 	M0_rtc;


/*
	typedef struct  {
	  UINT8           FW_ver[32];
	  M0_RTC_TIME_FRAME  mcu_RTC;

	  //  TEST !!!
	  UINT32 	sysTick;
	  UINT32  TstCnt;   //  TEST
	  UINT32  TstBuf_t; 
	  UINT32  uartM0_RxCnt;
	}M0_SYSTEM_INFO;
*/
extern 	M0_SYSTEM_INFO 				M0_System_info;

/*
	typedef struct  {
	  UINT32 mgc;
	  M0_RTC_TIME_FRAME  mcu_RTC;
	}M0_MGC_DATA_FRAME;
*/
extern 	M0_MGC_DATA_FRAME 		M0_mgc3130;

/*
	12 bits ADC; 0 ~ 4095
	6.2V ~ 8.4V
	//	8.4V	:	ADC 	3445 ~ 3430
	//	8.0V	:	ADC[]
	//	6.2V	:	ADC[]


//  DC Power Meter 		----------------------------------------------------------
//	LTC2944
typedef struct  {
	UINT32 								bat_v;
	UINT32 								bat_i;
	UINT32 								temp;	
	M0_RTC_TIME_FRAME  		mcu_RTC;
}M0_PW_METER_DATA_FRAME;

//  ADC   ----------------------------------------------------------------------
#define 	PW_EN_BAT_A			0x01		//	0001
#define 	PW_EN_BAT_B			0x02		//	0010
#define 	PW_EN_DC_IN			0x04		//	0100
#define 	PW_EN_SOLAR			0x08		//	1000

typedef struct  {
	UINT32 V_batA;
	UINT32 V_batB;
	UINT32 V_Solar;
	UINT32 V_DC;

	UINT32 adc0;
	UINT32 adc1;
	UINT32 adc2;
	UINT32 adc3;

	UINT32 pw_EN;		//	bit0,	Bat_A
									//	bit1,	Bat_B
									//	bit2,	DC_In
									//	bit3,	Solar

	M0_PW_METER_DATA_FRAME 		pw_meter;

	M0_RTC_TIME_FRAME  mcu_RTC;
}M0_POWER_DATA_FRAME;
*/
extern 	M0_POWER_DATA_FRAME 	M0_power;

/*
	typedef struct  {
		UINT32 								temp0; 		//	xxx.xx;  negative : 0x80000000 true
		M0_TEMP_ALARMM_FRAME	alarm;
		M0_RTC_TIME_FRAME  		mcu_RTC;
	}M0_TEMP_DATA_FRAME;
*/
extern	M0_TEMP_DATA_FRAME 		M0_temperature;

/*
	typedef struct  {
		UINT32 								bat_v;
		UINT32 								bat_i;
		UINT32 								temp;	
		M0_RTC_TIME_FRAME  		mcu_RTC;
	}M0_PW_METER_DATA_FRAME;
*/
//extern 	M0_PW_METER_DATA_FRAME	M0_PwMeter;


/*
	//  	RB-60P(3.0) UART Portocol_210930.pdf
	typedef struct  {
		UINT16 		radar_X;
		
		UINT16 		radar_Y;
		UINT16 		radar_L;

		UINT16 		radar_W;
		UINT16 		radar_H;

		UINT8 		Z_m;
		UINT8 		Z_p;
		UINT8 		DoA_E_m;
		UINT8 		DoA_E_p;

		UINT8 		DoA_H_m;
		UINT8 		DoA_H_p;
		UINT8 		Theta;
		UINT8 		Phi;

		UINT8 		L_R;
		UINT8 		Threshold_Boundary;
		UINT16 		Threshold_A;

		UINT16 		Threshold_B;
		UINT8  		Peak_amount;
		UINT8  		Compare_car;

		UINT8  		Compare_emp;
		UINT8  		nc01;
		UINT16 		Block_lim;
	}M0_RADAR_SET_FRAME;
	

	typedef struct  {
		UINT8 		Result;
		UINT8 		Current_status;
		UINT8 		Object_type;
		UINT8 		Current_amount;

		UINT16 		radar_X;
		UINT16 		radar_Y;

		UINT16 		radar_L;
		UINT16 		radar_W;

		UINT16 		radar_H;
		UINT8 		Z_m;
		UINT8 		Z_p;

		UINT8 		DoA_E_m;
		UINT8 		DoA_E_p;
		UINT8 		DoA_H_m;
		UINT8 		DoA_H_p;

		UINT8 		Theta;
		UINT8 		Phi;
		UINT8 		L_R;
		UINT8 		Threshold_Boundary;

		UINT16 		Threshold_A;
		UINT16 		Threshold_B;

		UINT8  		Peak_amount;
		UINT8  		Compare_car;
		UINT8  		Compare_emp;
		UINT8  		nc01;

		UINT16 		Block_lim;
		UINT16 		Block_index;

		UINT16 		Range_Object1;
		UINT16 		x_Object1;

		UINT16 		y_Object1;
		UINT16 		z_Object1;

		UINT16 		Power_Object1;
		UINT16 		Range_Object2;

		UINT16 		x_Object2;
		UINT16 		y_Object2;

		UINT16 		z_Object2;
		UINT16 		Power_Object2;
		UINT16 		Range_Object3;

		UINT16 		x_Object3;
		UINT16 		y_Object3;

		UINT16 		z_Object3;
		UINT16 		Power_Object3;
	}M0_RADAR_DATA_FRAME;

	typedef struct  {
		UINT8 								FW_version[4];
		M0_RADAR_DATA_FRAME		data;

		UINT8 	pre_Result;
		UINT8 	pre_Object_type;
		UINT8 	car;  				//	M0:20211014-031270
		UINT8 	pre_car; 			//	M0:20211014-031270

		M0_RTC_TIME_FRAME  		mcu_RTC;
	}M0_RADAR_FRAME;
*/
extern 	M0_RADAR_FRAME 				M0_radarA;
extern 	M0_RADAR_FRAME 				M0_radarB;

/*
typedef struct  {
	UINT16 		radar_X;
	
	UINT16 		radar_Y;
	UINT16 		radar_L;

	UINT16 		radar_W;
	UINT16 		radar_H;
	UINT8 		Theta;

	UINT8 		Phi;
	UINT8 		L_R;
	//UINT8 		scan_interval;
}M0_RADAR_SET_FRAME;
*/
extern 	M0_RADAR_SET_FRAME 		M0_radarA_set;
extern 	M0_RADAR_SET_FRAME 		M0_radarB_set;


/*
	typedef struct  {
		UINT8  		cmd;
		UINT8 		nc01;
		UINT16 		Status_RadarA;
		UINT16 		Status_RadarB;
		UINT32 		nc02;
		UINT8  		FileName_radarOTA[256];
	}M0_RADAR_OTA_FRAME;

	OTA_Radar.cmd =
	//	A53 ==> M0
	#define  	RADAR_OTACMD_NOTHING 								0x00
	#define  	RADAR_OTACMD_SET_PARAMETER					0xA0
	#define  	RADAR_OTACMD_START									0x01 		***** Start OTA action
	#define  	RADAR_OTACMD_INIT										0x10
	#define  	RADAR_OTACMD_ERASE_PAGE							0x20
	#define  	RADAR_OTACMD_PROGRAM_DATA						0x30
	#define  	RADAR_OTACMD_PROGRAM_CMD						0x31



	OTA_Radar.Status_RadarA =
	OTA_Radar.Status_RadarB =
	#define 	OTA_RADAR_ERR_OTA_INIT_00D5							0x0001  		//	0000 0000  0000 0001
	#define 	OTA_RADAR_ERR_OTA_INIT_4096							0x0002  		//	0000 0000  0000 0010
	#define 	OTA_RADAR_ERR_OTA_INIT_ASC							0x0004  		//	0000 0000  0000 0100
	#define 	OTA_RADAR_ERR_OTA_INIT_WPROTECT					0x0008  		//	0000 0000  0000 1000

	#define 	OTA_RADAR_ERR_OTA_ERASE_PAGE1						0x0010  		//	0000 0000  0001 0000
	#define 	OTA_RADAR_ERR_OTA_ERASE_PAGE2						0x0020  		//	0000 0000  0010 0000

	#define 	OTA_RADAR_ERR_OTA_PROGRAM01							0x0100  		//	0000 0001  0000 0000
	#define 	OTA_RADAR_ERR_OTA_PROGRAM02							0x0400  		//	0000 0100  0000 0000

	#define 	OTA_RADAR_ERR_OTA_HEX_DOWNLOAD					0x2000  		//	0010 0000  0000 0000
	#define 	OTA_RADAR_ERR_OTA_HEX										0x4000  		//	0100 0000  0000 0000
	#define 	OTA_RADAR_ERR_OTA_OTHER									0x8000  		//	1000 0000  0000 0000
*/
extern 	M0_RADAR_OTA_FRAME  	OTA_Radar;


/*
	typedef struct  {
		UINT8  		cmd;
		UINT8 		nc01;
		UINT16 		Status_OTA;
		
		UINT32  	file_size;
		UINT16  	crc16_file;
		UINT16  	nc02;

		UINT16  	rec_No;
		UINT16  	rec_Total;

		UINT8  		FileName_OTA[256];
	}M0_CHILI2S_OTA_FRAME;

	//====================================================================
	//	OTA Chili2s Function 	============================================
	//	Command  	--------------------------------------------------------
	//	A53 ==> M0
	#define  	CHILI2S_OTACMD_NOTHING 							0x00

	#define  	CHILI2S_OTACMD_START								0x01 		//	***** Start OTA action
	#define  	CHILI2S_OTACMD_INIT									0x10
	#define  	CHILI2S_OTACMD_PROGRAM_DATA					0x30

	#define  	CHILI2S_OTACMD_WAITING							0xFF

	//	OTA Status  	----------------------------------------------------
	//	M0 ==> A53  status
	#define 	OTA_CHILI2S_RUN_NULL								0x00
	#define 	OTA_CHILI2S_RUN_RECEIVED						0x01 		//	OTA Command received
	#define 	OTA_CHILI2S_FUN_TEST1								0xF0 		//	OTA Function TEST1

	//	OTA Error  	------------------------------------------------------
	#define 	OTA_CHILI2S_ERR_OTA_INIT_00D5							0x0001  		//	0000 0000  0000 0001
	#define 	OTA_CHILI2S_ERR_OTA_INIT_4096							0x0002  		//	0000 0000  0000 0010
	#define 	OTA_CHILI2S_ERR_OTA_INIT_ASC							0x0004  		//	0000 0000  0000 0100
	#define 	OTA_CHILI2S_ERR_OTA_INIT_WPROTECT					0x0008  		//	0000 0000  0000 1000

	#define 	OTA_CHILI2S_ERR_OTA_ERASE_PAGE1						0x0010  		//	0000 0000  0001 0000
	#define 	OTA_CHILI2S_ERR_OTA_ERASE_PAGE2						0x0020  		//	0000 0000  0010 0000

	#define 	OTA_CHILI2S_ERR_OTA_PROGRAM01							0x0100  		//	0000 0001  0000 0000
	#define 	OTA_CHILI2S_ERR_OTA_PROGRAM02							0x0200  		//	0000 0010  0000 0000
	#define 	OTA_CHILI2S_ERR_OTA_PROGRAM_55						0x0400  		//	0000 0100  0000 0000

	#define 	OTA_CHILI2S_ERR_OTA_HEX_DOWNLOAD					0x2000  		//	0010 0000  0000 0000
	#define 	OTA_CHILI2S_ERR_OTA_HEX										0x4000  		//	0100 0000  0000 0000
	#define 	OTA_CHILI2S_ERR_OTA_OTHER									0x8000  		//	1000 0000  0000 0000
*/
extern 	M0_CHILI2S_OTA_FRAME  	OTA_Chili2s;


/*
typedef struct  _vos_lidar{
	UINT16  	Distance;
	UINT16  	Strength;

	UINT16  	Temp;
	UINT16  	nc1;
}VOS_LIDAR_FRAME;

typedef struct  _parkmeter_lidar_msg{
	UINT16  	srcAddr;
	UINT16  	Dist;

	VOS_LIDAR_FRAME  	lidarData;
	VOS_LIDAR_FRAME  	pre_lidarData;

	UINT8  	car;
	UINT8  	pre_car;

	UINT8  	parking_fee_status;
	UINT8  	nc01;
	
	M0_RTC_TIME_FRAME 	mcu_RTC;
}PARKMETER_VOS_MSG_FRAME;

*/
extern 	PARKMETER_VOS_MSG_FRAME 				M0_Lidar;

/*
// 	STK8BA53
typedef struct _icm20602_data_frame_{
	//	mg
	UINT32	acc_X;
	UINT32	acc_Y;
	UINT32	acc_Z;
	
	UINT8		acc_wom_X;
	UINT8		acc_wom_Y;
	UINT8		acc_wom_Z;
	
	UINT8 	flg_INT;

	UINT32	acc_INT_X;
	UINT32	acc_INT_Y;
	UINT32	acc_INT_Z;
}STK8BA53_DATA_FRAME;

typedef struct  {
	STK8BA53_DATA_FRAME 	stk8ba53;
	M0_RTC_TIME_FRAME  		mcu_RTC;
}M0_G_SENSOR_FRAME;
*/
extern 	M0_G_SENSOR_FRAME  g_icm_Data;


/*
	typedef struct  {
		UINT16  	key;
		UINT16  	pre_key;
		M0_RTC_TIME_FRAME  		mcu_RTC;
	}M0_ALPS_FRAME;
*/
M0_ALPS_FRAME  				M0_alps;


/*
	//	#define    uart_M0_WAKEUP_A53 			0x82
	typedef struct  {
		UINT32 	msg;
		M0_RTC_TIME_FRAME  	mcu_RTC;
	}M0_WAKEUP_A53_FRAME;

	//	msg_WakeUp_A53.msg
	#define  	SUBTYPE_WAKEUP_NOTHING 								0x0000
	#define  	SUBTYPE_WAKEUP_DEV_STATUS_UPDATE 			0x0001

	#define  	SUBTYPE_WAKEUP_CHILI2S_BOOT 					0x0010

*/
extern 	M0_WAKEUP_A53_FRAME  	Msg_M0_wakeup_A53;

/*
	//	#define    uart_M0_TIME_EVENT 			0x83

	typedef struct  {
		UINT32 	msg;
		M0_RTC_TIME_FRAME  	mcu_RTC;
	}M0_TIME_EVENT_FRAME;

	//	Msg_M0_TimeEvent.msg
	//		#define    uart_M0_TIME_EVENT 			0x83
	#define  	SUBTYPE_TIME_EVENT_FEE_TIME_PRE_START			0x0100
	#define  	SUBTYPE_TIME_EVENT_FEE_TIME_START					0x0101
	#define  	SUBTYPE_TIME_EVENT_FEE_TIME_END						0x0108

	#define  	SUBTYPE_TIME_EVENT_HEARTBEAT							0x0110
	#define  	SUBTYPE_TIME_EVENT_FEE_FREE_TIME_CK				0x0111

	#define  	SUBTYPE_TIME_EVENT_RADAR_A_CC							0x0201
	#define  	SUBTYPE_TIME_EVENT_RADAR_B_CC							0x0211
*/
extern 	M0_TIME_EVENT_FRAME  	Msg_M0_TimeEvent;

/*
	typedef struct  {
		UINT8 								FW_version[2];
		UINT16 								status;
		UINT8 								name[64];
		UINT32 								dataLength;
		UINT8 								data[1600];
	}M0_TLSAM_FRAME;

typedef struct  {
	M0_TLSAM_FRAME 		tlsam_Data;
	uint8_t 					status;
	uint8_t 					nc1;
	uint8_t 					nc2;
	uint8_t 					nc3;
}M0_TLSAM_DATA_FRAME;
*/
extern 	M0_TLSAM_DATA_FRAME			M0_TLSAM_DATA;

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
extern 	M0_SYS_PARAMETER_FRAM 	M0_Sys_Parameter;





//********************************************************************
//	A53-M0 Global
extern 	unsigned char   FwVer_Ta53m0_API[];

extern	unsigned char   dev_UART_A53M0[];

extern	pthread_t thread_A53_awake;
extern	pthread_t thread_uartA53M0_Tx;
extern	pthread_t thread_uartA53M0_Rx;
extern	pthread_t thread_wifiAP_ck;
extern	pthread_t thread_Radar_OTA;
extern	pthread_t thread_Chili2s_OTA;


extern 	int fd_uartA53M0;


extern	unsigned char   A53M0_TxBuf[];
extern	unsigned char   A53M0_RxBuf[];
extern	int 	A53M0_TxLength;
extern	int 	A53M0_RxLength;

extern	int  	flg_M0uart_Tx;


//	------------------------------------------------------------------
//	Local Global
extern	time_t a53m0API_currentTime;
extern	struct tm *a53m0API_current_tm;

extern  int  tx_period;
extern  int  tx_No;

extern  int  A53_CK_wifiAP_Enable;


//	ML22Q535  --------------------------------------------------------
extern 	unsigned char   dev_I2C_ML22[];
extern 	int  fd_ml22_i2c;

extern 	unsigned char   dev_SPI_ML22[];
extern 	int  fd_ml22_spi;

//	wifiAP_ck_thread  ------------------------------------------------
extern	struct timeb  	time_wifiAP_ck1;
extern	struct timeb  	time_wifiAP_ck2;




//********************************************************************
//  Function
extern	void  A53_awake_thread( int* fdPtr );
extern	void  uartA53M0_Tx_thread( int* fdPtr );
extern	void  uartA53M0_Rx_thread( int* fdPtr );
extern	void  wifiAP_ck_thread( void );

extern 	void  Radar_OTA_thread( void );
extern 	void  Chili2s_OTA_thread( void );

extern 	UINT16  Get_Kermit_CRC16( UINT8* dataPtr, UINT32 length );
extern 	UINT16  Get_ModBus_CRC16( UINT8* dataPtr, UINT32 length );



// 	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
extern 	int index_rx;

#if 	TST_TxRx_COUNT
	extern 	uint32_t 	Tst_Tx_Cnt;
	extern 	uint32_t 	Tst_Rx_Cnt;

	extern 	struct timeb  	time_Tx;
	extern 	struct timeb  	time_Rx;
#endif 	//#if 	TST_TxRx_COUNT

// TEST   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define   TST_TX_REQ_M0_SYS 			1








//******************************************************************************
//	API Function
//******************************************************************************
extern 	void  A53M_req_M0API_VER( void );  				//	Request A53-M0 API Version

//	M0 System 		--------------------------------------------------------------
extern 	void 	uartA53M0_REQM0_SystemInfo( void ); 		// Resp.: 	(M0_SYSTEM_INFO)M0_System_info

extern 	void 	uartA53M0_SetM0_currentRTC( void ); 		//	DateTime of Linux
extern 	void 	uartA53M0_REQM0_RTC( void ); 						// Resp.: 	(M0_RTC_TIME_FRAME)M0_rtc

extern 	void 	uartA53M0_REQM0_SelfTest( void );  			//	resp:  M0_DEV_SELF_TEST 	M0_Device_SelfTest;


//	M0 - Devices 		------------------------------------------------------------
//	ADC
extern 	void 	uartA53M0_REQM0_Power( void ); 						// Resp. 		(M0_POWER_DATA_FRAME)M0_power


//	M0 - Devices 		------------------------------------------------------------
//	Temperature, 	LM75A
extern	void 	uartA53M0_REQM0_Temp( void );

//	M0 - Devices 		------------------------------------------------------------
//	Power Meter 	LTC29444
//extern	void 	uartA53M0_REQM0_PwMeter( void );


//	Radar 		------------------------------------------------------------------
extern 	void 	uartA53M0_Set_Radar_Parameter( M0_RADAR_SET_FRAME* radarA_set_Ptr, M0_RADAR_SET_FRAME* radarB_set_Ptr );
extern 	void 	uartA53M0_Req_Radar_Status( void );
extern 	void 	uartA53M0_update_Radar_parameter( void );

//	show=0,  Normale; 		show=1, Show ALL Radar data
extern 	void 	uartA53M0_Set_Radar_ShowAllData( uint8_t show );


//	Set M0 system Parameter 		------------------------------------------------
//	M0_SYS_PARAMETER_FRAM 	M0_Sys_Parameter
extern 	void 	uartA53M0_Set_M0_Sys_parameter( void );
extern 	void 	uartA53M0_Req_M0_Sys_parameter( void );


//	Chili2S 		----------------------------------------------------------------
extern 	void 	uartA53M0_Set_Chili2S_PAN_ADD( UINT16 panid, UINT16 sAddr, UINT8 rf_channel );



//	G-sensor 		----------------------------------------------------------------
extern 	void 	uartA53M0_REQM0_G_Sensor( void );

//extern 	void 	uartA53M0_Get_Radar_FWver( void );
//extern 	void 	uartA53M0_Set_Radar_Param( UINT8 A_B, UINT8 RW, M0_RADAR_SET_FRAME* radar_set_Ptr );


//	M0  EEPROM 		--------------------------------------------------------------
//	24AA64-I : 	512 Kbits
//	uint16_t addr,  must be n*0x10
//	uint16_t length,  MAX. 128 bytes
extern 	void 	uartA53M0_EEPROM_Save( uint16_t addr, uint16_t length, uint8_t* dataPtr );
extern 	void 	uartA53M0_EEPROM_Read( uint16_t addr, uint16_t length, uint8_t* dataPtr );


//	Power Source 		------------------------------------------------------------
extern 	void 	uartA53M0_Set_Bat_Source( UINT8 BatA_B );


//	Set Gesture Skip time 		--------------------------------------------------
extern 	void 	uartA53M0_Set_Gesture_SkipTime( UINT16 time );


//	ML22Q53x, Voice Out 		----------------------------------------------------
//	voice_phrase = 0 ~ 1024
//	voice_phrade = ML22_PLAY_PHRASE_NONE,  Not in playing voice
extern	void  	ml22_voice_Play_Start( int  voice_phrase );
extern 	void  	ml22_voice_Play_Stop( void );

//	Return Value	=0, Verify OK with  "/home/root/grids/bin/ml22_voice/ml22_voice.bin"
extern 	int 	ml22_Flash_Verify( UINT8* filePtr );

//	Return Value	=0, Write & Verify OK with  "/home/root/grids/bin/ml22_voice/ml22_voice.bin"
extern 	int 	ml22_Flash_Write( UINT8* filePtr );


//	TL-SAM Encryption 	--------------------------------------------------------
extern 	void 	uartA53M0_TLSAM_Encrypt( uint8_t *enc_file_name, uint8_t *enc_data, uint16_t enc_dataLength );


//	A53 linux Sleep 	----------------------------------------------------------
extern 	void  A53M0_gpio_Init( void );
extern 	void  A53M_Sleep( void );


//	A53 gpio H/L 	--------------------------------------------------------------
extern 	void  A53M_SleepState_gpio_H( void );
extern 	void  A53M_SleepState_gpio_L( void );

extern 	void  A53M_LCD_BackLight_ON( void );
extern 	void  A53M_LCD_BackLight_OFF( void );

extern 	void  A53M_USB_HUB_power_On( void );
extern 	void  A53M_USB_HUB_power_Off( void );



//==============================================================================
extern 	int  Str2Hex_2( unsigned char*, uint8_t* dataPtr );

extern 	void 	uartA53M0_Set_M0_A53Status_Awake( void );
extern 	void 	uartA53M0_Set_M0_A53Status_Sleep( void );


// 	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
extern 	void 	uartA53M0_Req_Dumming_Test( void );
//	check 	(UINT32)M0_Status_Update  to get New information of devices


#endif    //TA53M0_UART_H

