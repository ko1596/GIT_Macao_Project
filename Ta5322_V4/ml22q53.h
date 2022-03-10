

//********************************************************************
// 	ML22Q535
// 			16Mbit, 	2M byte
// 				20210706 			Daniel
//********************************************************************

/*
	cd /sys/class/gpio
	ls -l /sys/class/gpio

	//		SPI
	P43 	SPI0_CS0# 		GPIO5_IO13 	141		CSB
	P44 	SPI0_CK 			GPIO5_IO10 	138		SCK /	IRSCK
	P45 	SPI0_DIN 			GPIO5_IO12 	140		SO 	/	IRSO
	P46 	SPI0_DO 			GPIO5_IO11 	139		SI 	/	IRSI

	P113 	RESETB 		GPIO5 	133 	RESETB
	P114 	CBUSYB		GPIO6 	TCA9538PWR  P3 		507
	P115 	IRON 			GPIO7 	TCA9538PWR  P4 		508
	P116 	IRCSB 		GPIO8 	TCA9538PWR  P5 		509

	xx P115 	GPIO7 										500 	IRON
	xx P116 	GPIO8 										501 	IRCSB
	xx P113 	GPIO5 										133 	RESETB
	xx P114 	GPIO6 										499 	CBUSYB

CSB 		P43 	 SPI0_CS0# 			SPI	 SPI0_CS0# 		GPIO5_IO13(GPIO5,gpio_io,13)

	S116 	LCD1_VDD_EN 		STATUS1
	S122 	 LCD1_BKLT_PWM 	STATUS2
*/

/*
	//		GPIO
	# P113 	RESETB 		GPIO5 	133 	RESETB
		echo 133 > /sys/class/gpio/export 

	# P114 	CBUSYB		GPIO6 	TCA9538PWR  P3 		507
		echo 507 > /sys/class/gpio/export

	# P115 	IRON 			GPIO7 	TCA9538PWR  P4 		508
		echo 508 > /sys/class/gpio/export

	# P116 	IRCSB 		GPIO8 	TCA9538PWR  P5 		509
		echo 509 > /sys/class/gpio/export
*/

/*
	//		I2C
	S1 	I2C_CAM1_CK 		PCAM	 I2C_CAM1_CK 		TCA9545A
	S2 	I2C_CAM1_DAT 		PCAM	 I2C_CAM1_DAT 	TCA9545A

i2c TCA9545A
	/dev/i2c-4 		***
	/dev/i2c-5
	/dev/i2c-6
	/dev/i2c-7
*/




#ifndef _ML22Q53_H
#define _ML22Q53_H




//#define  	GPIO_ML22_CSB_ENABLE 				1
//#define  	GPIO_EXPORT_ENABLE 				1




//********************************************************************
//	define
#define SYSFS_GPIO_EXPORT  						"/sys/class/gpio/export"
#define SYSFS_GPIO_UNEXPORT 					"/sys/class/gpio/unexport"

#define SYSFS_GPIO_DIR1  							"/sys/class/gpio/gpio"
#define SYSFS_GPIO_DIR2  							"/direction"
#define SYSFS_GPIO_VALUE  						"/value"


//	ML22Q535 	========================================================
/*
#if 	GPIO_EXPORT_ENABLE
	//	................................................................
	#define  	GPIO_VALUE_ML22_CBUSYB 			"507"
	#define  	GPIO_VALUE_ML22_RESETB 			"133"
	#define  	GPIO_VALUE_ML22_IRCSB 			"509"
	#define  	GPIO_VALUE_ML22_IRON 				"508"

	#define  	GPIO_VALUE_ML22_CSB 				"141"

	#define  	GPIO_MAP_EXPORTNO_ML22_CBUSYB 				1
	#define  	GPIO_MAP_EXPORTNO_ML22_RESETB 				2
	#define  	GPIO_MAP_EXPORTNO_ML22_IRCSB 				3
	#define  	GPIO_MAP_EXPORTNO_ML22_IRON 					4

	#define  	GPIO_MAP_ML22_CSB 					5

#else
	//	gpio_export.sh  ................................................
	#define  	GPIO_MAP_ML22_CBUSYB 				6
	#define  	GPIO_MAP_ML22_RESETB 				7
	#define  	GPIO_MAP_ML22_IRCSB 				8
	#define  	GPIO_MAP_ML22_IRON 					9

#endif 		//#if 	GPIO_EXPORT_ENABLE
*/


//  I2C  -------------------------------------------------------------
//  	I2C  Slave Address :
//		SAD2 	SAD1 	SAD0 	0 1 0 1
//		1 		1 		1
//#define  ADDR_I2C_DEV_ML22  				0x75 				//  0b01110101

//		0 		0 		0
#define  ADDR_I2C_DEV_ML22  				0x05 				//  0b01110101


//--------------------------------------------------------------------
#define  ML22_PLAY_PHRASE_NONE  		0xFFFF  		//  ml22_voice_phrase




//********************************************************************
//	Global



//  GPIO 	============================================================
unsigned char 	str_gpio_value_CBUSYB[256];
unsigned char 	str_gpio_value_RESETB[256];
unsigned char 	str_gpio_value_IRCSB[256];
unsigned char 	str_gpio_value_IRON[256];
unsigned char 	str_gpio_value_CSB[256];


extern 	pthread_t thread_ml22_PlayStart;
extern 	pthread_t thread_ml22_CBUSYB_ck;
extern 	int  ml22_CBUSYB;

//  I2C 	============================================================
//extern 	unsigned char   dev_I2C_ML22[];
//extern 	int  fd_ml22_i2c;







//********************************************************************
//  Function
void 	ml22q53_gpio_Init( void );

void 	ml22q53_Close( void );

void 	ml22_CBUSYB_Read( int* cbusy );
void  ck_ml22_CBUSYB_thread( int* fdPtr );

int  ml22_PlayStart_thread( void );


//  Test  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void  ml22_PlayStart_thread_T01( void );



#endif    //_ML22Q53_H

