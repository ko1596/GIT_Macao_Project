

#ifndef ALL_DEFINE_H
#define ALL_DEFINE_H


//********************************************************************
#define 	A53M0_UART_COMMAND						1




//********************************************************************
//====================================================================
//--------------------------------------------------------------------
//....................................................................
#define   UINT8       uint8_t
#define   UINT16      uint16_t
#define   UINT32      uint32_t

#define   FAILURE     0
#define   SUCCESS     1


//==============================================================================
//	Device Version
#define 	M0_RADAR_VER_30_210930  		1


//====================================================================
//  Device SubType of UART CMD
/*
	#define    uart_SET_DEV 						0x50
	#define    uart_RSP_DEV 						0xD0
	#define    uart_REQ_DEV_STATUS 			0x51
	#define    uart_RSP_DEV_STATUS 			0xD1
*/
//====================================================================
#define 	SUBTYPE_RTC								0x01
#define 	SUBTYPE_MGC3130						0x11
#define 	SUBTYPE_ADC								0x12
#define 	SUBTYPE_G_SENSOR					0x13
#define 	SUBTYPE_ALPS							0x14

#define 	SUBTYPE_RADAR_A						0x21
#define 	SUBTYPE_RADAR_B						0x22

#define 	SUBTYPE_LIDAR							0x28

#define 	SUBTYPE_TEMPERATURE				0x30

#define 	SUBTYPE_PW_METER0					0x38
#define 	SUBTYPE_PW_METER1					0x39
#define 	SUBTYPE_PW_METER2					0x3A
#define 	SUBTYPE_PW_METER3					0x3B

#define 	SUBTYPE_PW_BAT						0x40
#define 	SUBTYPE_PW_BAT_A					0x41
#define 	SUBTYPE_PW_BAT_B					0x42

#define 	SUBTYPE_M0_SYS						0x70
#define 	SUBTYPE_TLSAM							0x71
#define 	SUBTYPE_CHILI2S						0x72
#define 	SUBTYPE_SYS_PW						0x78
#define 	SUBTYPE_A53_AWAKESLEEP		0x79

#define 	SUBTYPE_SELFTEST					0xF0
#define 	SUBTYPE_ALL								0xFF



//====================================================================
//#define    uart_M0_WAKEUP_A53 			0x82
//	UINT32
//====================================================================
#define  	SUBTYPE_WAKEUP_NOTHING 								0x0000
#define  	SUBTYPE_WAKEUP_DEV_STATUS_UPDATE 			0x0001

#define  	SUBTYPE_WAKEUP_CHILI2S_BOOT 					0x0010


//==============================================================================
//	msg_TimeEvent.msg
//		#define    uart_M0_TIME_EVENT 			0x83
#define  	SUBTYPE_TIME_EVENT_FEE_TIME_PRE_START			0x0100
#define  	SUBTYPE_TIME_EVENT_FEE_TIME_START					0x0101
#define  	SUBTYPE_TIME_EVENT_FEE_TIME_END						0x0108

#define  	SUBTYPE_TIME_EVENT_HEARTBEAT							0x0110
#define  	SUBTYPE_TIME_EVENT_FEE_FREE_TIME_CK				0x0111

#define  	SUBTYPE_TIME_EVENT_RADAR_A_CC							0x0201
#define  	SUBTYPE_TIME_EVENT_RADAR_B_CC							0x0211



//====================================================================
// 	OTA  	------------------------------------------------------------
#define 	M0DEV_OTA_START						0x00
#define 	M0DEV_OTA_READ						0x02

#define 	M0DEV_OTA_PROGRAM					0x10
#define 	M0DEV_OTA_VERIFY					0x20

#define 	M0DEV_OTA_ADDR						0x10
#define 	M0DEV_OTA_DATA						0x11



//--------------------------------------------------------------------
//	flag of M0_Status_Update
//	M0_Status_Update
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
/*
	if( M0_DEV_UPDATE_TIME_EVENT )  	{
		check Msg_M0_TimeEvent
	}
*/

//--------------------------------------------------------------------
#define 	PW_EN_BAT_A			0x01		//	0001
#define 	PW_EN_BAT_B			0x02		//	0010
#define 	PW_EN_DC_IN			0x04		//	0100
#define 	PW_EN_SOLAR			0x08		//	1000




//********************************************************************
//	A53 - M0  UART
//********************************************************************
typedef struct _uart_fifo {
    UINT8*  buffer; // used as a ring buffer
    UINT16  front;          // Head index of queue
    UINT16  tail;         // next new index of queue
    UINT8   buffull;        // =1, queue full
    /*
    UINT8   NC1;          // No used
    UINT8   NC2;          // No used
    UINT8   NC3;          // No used
    */
    UINT8     STATE;
  	UINT16    PTR;
  	UINT16    LENGTH;
  	UINT16    CMD;
  	UINT16    CRC;
}M0_UART_FIFO;






//********************************************************************
//	M0 device 
//********************************************************************

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




//==============================================================================
//  Chili2S
//==============================================================================
typedef struct {
	M0_RTC_TIME_FRAME  	rtc;

	UINT16  	panid;
	UINT16  	sAddr;

	UINT8  		rf_channel;
	UINT8  		nc01;
	UINT8  		nc11;

	UINT8 		fw_ver[48];
}CHILI2S_INFO_FRAME;


//==============================================================================
//  M0
typedef struct  {
  UINT8           FW_ver[32];
  M0_RTC_TIME_FRAME  mcu_RTC;

  //  TEST !!!
  UINT32 	sysTick;
  UINT32  TstCnt;   //  TEST
  UINT32  TstBuf_t; 
  UINT32  uartM0_RxCnt;

  CHILI2S_INFO_FRAME  	Chili2S_info;
}M0_SYSTEM_INFO;








//==============================================================================
//  device status
//==============================================================================

//  M0 ALarm A53  	------------------------------------------------------------
typedef struct  {
	UINT32 	alarm;
	M0_RTC_TIME_FRAME  	mcu_RTC;
}M0_ALARM_A53_FRAME;


//------------------------------------------------------------------------------
//  M0 WakeUp A53  	------------------------------------------------------------
typedef struct  {
	UINT32 	msg;
	M0_RTC_TIME_FRAME  	mcu_RTC;
}M0_WAKEUP_A53_FRAME;

typedef struct  {
	UINT32 	msg;
	M0_RTC_TIME_FRAME  	mcu_RTC;
}M0_TIME_EVENT_FRAME;


//  DC Power Meter 		----------------------------------------------------------
//	LTC2944
typedef struct  {
	UINT32 								bat_v;
	UINT32 								bat_i;
	UINT32 								temp;	
}M0_PW_METER_DATA_FRAME;

//  ADC   ----------------------------------------------------------------------


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

//  LM75-Sensor   --------------------------------------------------------------
typedef struct  {
	UINT32 alarm_temp_H;
	UINT32 alarm_temp_L;
}M0_TEMP_ALARMM_FRAME;

typedef struct  {
	UINT32 								temp0; 		//	xxx.xx;  negative : 0x80000000 true
	M0_TEMP_ALARMM_FRAME	alarm;
	M0_RTC_TIME_FRAME  		mcu_RTC;
}M0_TEMP_DATA_FRAME;


//  MGC3130   ------------------------------------------------------------------
typedef struct  {
  UINT32 mgc;
  M0_RTC_TIME_FRAME  mcu_RTC;
}M0_MGC_DATA_FRAME;










//  Radar   	------------------------------------------------------------------
#if 	M0_RADAR_VER_30_210930

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


	typedef struct  {
		UINT8  		cmd;
		UINT8 		nc01;
		UINT16 		Status_RadarA;
		UINT16 		Status_RadarB;
		UINT32 		nc02;
		UINT8  		FileName_radarOTA[256];
	}M0_RADAR_OTA_FRAME;

#else 	//#if 	M0_RADAR_VER_30_210930
#endif 	//#if 	M0_RADAR_VER_30_210930


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







//  Lidar  from Chili2S 	------------------------------------------------------
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
	UINT8  	shoot;
	UINT8  	pre_shoot;

	UINT8  	parking_fee_status;
	UINT8  	nc01;
	UINT8  	nc02;
	UINT8  	nc03;
	
	M0_RTC_TIME_FRAME 	mcu_RTC;
}PARKMETER_VOS_MSG_FRAME;


//  G-Sensor   -----------------------------------------------------------------
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


//  ALPS   ---------------------------------------------------------------------
typedef struct  {
	UINT16  	key;
	UINT16  	pre_key;
	M0_RTC_TIME_FRAME  		mcu_RTC;
}M0_ALPS_FRAME;


//  All Devices Self-Test   ----------------------------------------------------
typedef struct  {
	UINT32 	Device_SelfCheck;
	M0_RTC_TIME_FRAME  		mcu_RTC;
}M0_DEV_SELF_TEST;


//------------------------------------------------------------------------------
//	Fee Free Period  	----------------------------------------------------------
typedef struct  {
	UINT32  	Free_time1;
	UINT32  	Free_time2;
	UINT32  	period_FeeFree_CKcar;  		//	for  TIMER*
}M0_FEE_FREE_FRAME;


//  TL-SAM   	------------------------------------------------------------------
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








//==============================================================================
//  	M0 Parameter
//==============================================================================

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
	UINT8  								nc1;
	UINT8  								nc2;
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







//	TEST 		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//#define 	TST_SHOW_UART_TxData 		1
//#define 	TST_SHOW_UART_RxData 		1
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#endif    //ALL_DEFINE_H

