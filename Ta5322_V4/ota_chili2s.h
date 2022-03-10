

//********************************************************************
// 	ota_chili2s.h
// 				20220127 			Daniel
//********************************************************************

#include "m0All_Header.h"


#ifndef _OTA_CHILI2S_H
#define _OTA_CHILI2S_H





//********************************************************************
//	define
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


#define  	OTA_CHILI2S_PROGRAMDATA_SIZE  		97
//#define  	OTA_CHILI2S_PROGRAMDATA_SIZE  		80

//********************************************************************
//	Global



//********************************************************************
//	Function

int  	OTA_Chili2s_get_BIN( void );
int  	OTA_Chili2s_Req_Init( void );
int  	OTA_Chili2s_Req_ProgramData( void );
int  	OTA_Chili2s_CK_ReBoot( void );

void  Chili2SOTA_Rsp( UINT8* rx_payload, UINT16 length );


#endif    //_OTA_CHILI2S_H

/*
//		PKmeter_025a2_DL.bin
2022/01/26 15:37:10.290  [Tx]: CC 17 7C 00 00 00 00 62 02 4D 32 33 2D 73 4C 45 44 20 E7 00 00 15 78 94 5D
2022/01/26 15:37:10.315  [Rx]: CC 17 FC 00 00 00 00 62 02 4D 32 33 2D 73 4C 45 44 20 E7 00 00 15 78 94 5D

2022/01/26 15:37:10.347  [Tx]: CC 6C 7C 00 00 01 00 01 00 62 02 4D 32 33 2D 73 4C 45 44 FF FF FF FF FF FF FF FF 03 00 00 00 18 00 00 00 50 00 00 00 00 00 00 00 48 02 00 00 FF FF FF FF B0 02 00 00 80 08 00 00 B4 04 00 00 FF FF FF FF 70 07 00 00 00 20 00 00 A4 DF 00 00 FF FF FF FF FF FF FF FF FF FF FF FF 38 60 00 20 01 20 00 00 09 20 00 00 0B 20 00 00 00 AC 25
2022/01/26 15:37:10.348  [Rx]: CC 0F FC 00 00 01 00 01 00 62 02 00 00 00 00 AC 25
2022/01/26 15:37:10.378  [Tx]: CC 6C 7C 00 00 01 00 02 00 62 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 1D 20 00 00 00 00 00 00 00 00 00 00 1F 20 00 00 55 9D 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 F4 2D
2022/01/26 15:37:10.393  [Rx]: CC 0F FC 00 00 01 00 02 00 62 02 00 00 00 00 F4 2D
2022/01/26 15:37:10.415  [Tx]: CC 6C 7C 00 00 01 00 03 00 62 02 00 00 23 20 00 00 23 20 00 00 23 20 00 00 B5 3F 00 00 23 20 00 00 F9 3F 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 23 20 00 00 29 B0 00 0B 74
2022/01/26 15:37:10.430  [Rx]: CC 0F FC 00 00 01 00 03 00 62 02 00 00 00 00 0B 74
......
2022/01/26 15:37:47.504  [Tx]: CC 6C 7C 00 00 01 00 60 02 62 02 45 33 32 43 43 20 20 32 30 32 32 30 31 32 30 2D 30 32 35 61 32 43 68 69 6C 69 73 20 50 61 72 6B 4D 65 74 65 72 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 47 69 74 4E 65 74 2D 43 41 20 20 20 20 20 20 20 4E 77 30 37 32 30 47 49 54 2D 7A 62 4E 45 54 20 00 00 00 00 04 00 00 00 08 00 00 00 27 44
2022/01/26 15:37:47.537  [Rx]: CC 0F FC 00 00 01 00 60 02 62 02 00 00 00 00 27 44
2022/01/26 15:37:47.565  [Tx]: CC 6C 7C 00 00 01 00 61 02 62 02 0C 00 00 00 00 00 00 00 04 00 00 00 08 00 00 00 10 00 00 00 00 00 00 00 04 00 00 00 08 00 00 00 0C 00 00 00 00 00 00 00 04 00 00 00 08 00 00 00 10 00 00 00 00 1B B7 00 00 00 00 00 00 80 00 00 00 1B B7 00 00 1B B7 00 00 00 00 00 00 80 00 00 00 1B B7 00 00 1B B7 00 00 00 00 00 00 80 00 00 00 05 CB
2022/01/26 15:37:47.596  [Rx]: CC 0F FC 00 00 01 00 61 02 62 02 00 00 00 00 05 CB
2022/01/26 15:37:47.635  [Tx]: CC 6A 7C 00 00 01 00 62 02 62 02 1B B7 00 00 1B B7 00 00 80 00 00 00 00 00 00 10 27 00 00 00 00 00 00 00 6C DC 02 00 00 00 00 00 1B B7 00 30 02 00 00 00 20 00 20 18 00 00 00 10 02 00 00 48 02 00 00 18 20 00 20 20 40 00 00 20 02 00 00 34 0D 00 00 00 00 00 20 EC 18 00 00 20 02 00 00 FF FF FF FF FF FF FF FF FF FF FF FF 3B BA
2022/01/26 15:37:48.055  [Rx]: CC 0F FC 00 00 01 00 62 02 62 02 00 00 00 00 3B BA


2022/01/26 15:37:55.397  [Rx]: CC 15 0F 55 55 55 55 55 55 55 55 55 55 00 00 77 77 77 4E 62 7A 22 22





CC 17 7C 00 00 00 00 62 02 4D 32 33 2D 73 4C 45 44 20 E7 00 00 15 78 94 5D
*/

