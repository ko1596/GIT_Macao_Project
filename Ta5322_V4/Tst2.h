

//	for 	Test		****************************************************

#ifndef _TEST_2_H
#define _TEST_2_H


//	TEST	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//********************************************************************
//	define
#define  		TST_AUTO_SLEEP   				1

//====================================================================
//14byte文件頭
typedef struct
{
	char cfType[2];//文件類型，"BM"(0x4D42)
	long cfSize;//文件大小（字節）
	long cfReserved;//保留，值爲0
	long cfoffBits;//數據區相對於文件頭的偏移量（字節）
}__attribute__((packed)) BITMAPFILEHEADER;
//__attribute__((packed))的作用是告訴編譯器取消結構在編譯過程中的優化對齊

//40byte信息頭
typedef struct
{
	char ciSize[4];//BITMAPFILEHEADER所佔的字節數
	long ciWidth;//寬度
	long ciHeight;//高度
	char ciPlanes[2];//目標設備的位平面數，值爲1
	int ciBitCount;//每個像素的位數
	char ciCompress[4];//壓縮說明
	char ciSizeImage[4];//用字節表示的圖像大小，該數據必須是4的倍數
	char ciXPelsPerMeter[4];//目標設備的水平像素數/米
	char ciYPelsPerMeter[4];//目標設備的垂直像素數/米
	char ciClrUsed[4]; //位圖使用調色板的顏色數
	char ciClrImportant[4]; //指定重要的顏色數，當該域的值等於顏色數時（或者等於0時），表示所有顏色都一樣重要
}__attribute__((packed)) BITMAPINFOHEADER;

typedef struct
{
	unsigned short blue;
	unsigned short green;
	unsigned short red;
	unsigned short reserved;
}__attribute__((packed)) PIXEL;//顏色模式RGB




//********************************************************************
//	Global
extern  	pthread_t thread_Test2;
extern  	pthread_t thread_FrameBuffer;


extern  	int 	LCD_Disp_No;


//====================================================================
pthread_t thread_tcp_Cmd;
pthread_t thread_auto_sleep;


//********************************************************************
//  Function
void  Test2_thread( void );
void  Framebuffer_Tst_thread( void );


//====================================================================
void  Tst_tcp_cmd_thread( void );

//====================================================================
struct timeb  	time_Tst_autu_sleep1;
struct timeb  	time_Tst_autu_sleep2;
int  		Tst_Auto_Sleep_Enable;
int  		Tst_Flg_Auto_Sleep;
void  Tst_auto_sleep_thread( void );

void 	Tst_Set_M0_Sys_parameterFile( void );


#endif    //_TEST_2_H

