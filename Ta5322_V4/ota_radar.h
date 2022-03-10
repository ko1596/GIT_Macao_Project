
//********************************************************************
// 	ota_radar.h
// 				20211108 			Daniel
//********************************************************************

#include "m0All_Header.h"


#ifndef _OTA_RADAR_H
#define _OTA_RADAR_H



/*

unsigned char   path_RadarOTA_HEX[128] = "/home/root/grids/EPM/firmware/radar";
unsigned char   file_RadarOTA_HEX[128] = "/home/root/grids/EPM/firmware/radar/radar_FW.hex";

unsigned char   file_RadarOTA_FW_BIN11[128] = "/home/root/grids/EPM/firmware/radar/radarFW11.bin";
unsigned char   file_RadarOTA_FW_BIN12[128] = "/home/root/grids/EPM/firmware/radar/radarFW12.bin";

unsigned char   file_RadarOTA_FW_BIN01[128] = "/home/root/grids/EPM/firmware/radar/radarFW01.bin";
unsigned char   file_RadarOTA_FW_BIN02[128] = "/home/root/grids/EPM/firmware/radar/radarFW02.bin";

unsigned char   file_RadarOTA_SAVEBIN1[128] = "/home/root/grids/EPM/firmware/radar/fwSave1.bin";
unsigned char   file_RadarOTA_SAVEBIN2[128] = "/home/root/grids/EPM/firmware/radar/fwSave2.bin";

*/

//********************************************************************
//	define


//	TEST  	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//#define  	TST_RADAR_OTA_STEP1		1
//#define  	TST_RADAR_OTA_STEP3		1

//#define  	TST_RADAR_OTA_SHOW_PRGDATA								1
//#define  	TST_RADAR_OTA_SHOW_PRGDATA2								1

//#define  	TST_RADAR_OTA_PRGDATA_TIMEOUT_DISABLE			1

#define  	TST_W_HEX_TABLE  			1






//********************************************************************
//	Global

//extern 	UINT8 	uartRadar_OTA_CmdState;
extern 	UINT8 	uartRadar_OTA_CmdRsp;

extern 	UINT8  	uartRadar_OTA_rBuf[];
extern 	UINT8  	uartRadar_OTA_TxBuf[];


//	OTA TEST  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
extern 	unsigned char   path_RadarOTA_HEX[];
extern 	unsigned char   file_RadarOTA_HEX[];

extern 	unsigned char   file_RadarOTA_FW_BIN11[];
extern 	unsigned char   file_RadarOTA_FW_BIN12[];


#if  	TST_W_HEX_TABLE
	extern  	FILE*  f_hexTable;
#endif  		//	#if  	TST_TxRx_COUNT



/*
//====================================================================
//	OTA Radar Cmd
unsigned char  Cmd_RadarOTA_Cmd_wBK1[] = 				{ 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4F };
unsigned char  Cmd_RadarOTA_Cmd_wBK2[] = 				{ 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4D };
unsigned char  Cmd_RadarOTA_Cmd_wOver[] = 			{ 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//unsigned char  Cmd_RadarOTA_Cmd_wOver = 			{ 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char  Cmd_RadarOTA_Cmd_wRUNflash[] = 	{ 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
*/

//********************************************************************
//	Function
int 	radar_set_param( void );

int  OTA_Radar_get_HEX( void );
//int  OTA_Radar_HEX_DownLoad( void );
int  RadarFW_HEX_BIN( unsigned char* f_ota_hex_Name );

void  Get_Radar_OTA_BinTxData( UINT8* InBuf, UINT8* OutBuf, int InLength );

void  RadarOTA_Rsp( UINT8* rx_payload, UINT16 length );

int  	OTA_Radar_Req_Init( void );
int  	OTA_Radar_Req_ErasePage( void );
int  	OTA_Radar_Req_ProgramData( void );


void 	OTA_Radar_Tx_Init( void );
void 	OTA_Radar_Tx_ErasePage( void );
void 	OTA_Radar_Tx_PrgCmdData( UINT8* txBuf, int length );


#endif    //_OTA_RADAR_H

