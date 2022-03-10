

#include "m0All_Header.h"



//********************************************************************
//  Global
pthread_t thread_Test2;

pthread_t thread_FrameBuffer;


//====================================================================
pthread_t thread_tcp_Cmd;
pthread_t thread_auto_sleep;


//====================================================================
void  	uartA53M0_SetM0_TestRTC( M0_RTC_TIME_FRAME* rtc );
void  	Tst_M0_Sys_Parameter_Default( void  );



//********************************************************************
//
//********************************************************************
void  Test2_thread( void )
{
	char key;
	char StrCmd[16];
	char StrValue[16];
	int 	StrLen;
	int  cmdValue;

	printf( "********** **********  Thread Test2_thread Start  ********** ********** \n" );
	system( "date > /home/root/RadarOTAlog" );
	system( "echo \" ========== ========== ========== \" >> /home/root/RadarOTAlog" );


	//******************************************************************
	//
	//******************************************************************
	struct timeb  	time_T201;
	struct timeb  	time_T202;

	ftime( &time_T201 );
	ftime( &time_T202 );

	while( 1 )		{

		//==========================================================================
		//	Loop 1
		//if( ((time_T202.time*1000)+time_T202.millitm)-((time_T201.time*1000)+time_T201.millitm) >  (60000 *30) )		{  		//	1min * 30
		if( ((time_T202.time*1000)+time_T202.millitm)-((time_T201.time*1000)+time_T201.millitm) >  (60000 *10) )		{  		//	1min * 10
		//if( ((time_T202.time*1000)+time_T202.millitm)-((time_T201.time*1000)+time_T201.millitm) >  (60000 *5) )		{  		//	1min * 5
		//if( ((time_T202.time*1000)+time_T202.millitm)-((time_T201.time*1000)+time_T201.millitm) >  60000 )		{  		//	60sec
		//if( ((time_T202.time*1000)+time_T202.millitm)-((time_T201.time*1000)+time_T201.millitm) >  30000 )		{  		//	30sec
		//if( ((time_T202.time*1000)+time_T202.millitm)-((time_T201.time*1000)+time_T201.millitm) >  20000 )		{  		//	20sec
		//if( ((time_T202.time*1000)+time_T202.millitm)-((time_T201.time*1000)+time_T201.millitm) >  10000 )		{  		//	10sec
		//if( ((time_T202.time*1000)+time_T202.millitm)-((time_T201.time*1000)+time_T201.millitm) >  5000 )		{  		//	5sec
		//if( ((time_T202.time*1000)+time_T202.millitm)-((time_T201.time*1000)+time_T201.millitm) >  2000 )		{  		//	2sec
		//if( ((time_T202.time*1000)+time_T202.millitm)-((time_T201.time*1000)+time_T201.millitm) >  1000 )		{  		//	1sec
		//if( ((time_T202.time*1000)+time_T202.millitm)-((time_T201.time*1000)+time_T201.millitm) >  500 )		{  		//	0.5sec
			time_T201 = time_T202;

			if( OTA_Radar.cmd == RADAR_OTACMD_NOTHING )		{
				system( "date >> /home/root/RadarOTAlog" );

				OTA_Radar.cmd = RADAR_OTACMD_START;
			}  		//if( OTA_Radar.cmd == RADAR_OTACMD_NOTHING )		{

		}  		////if( ((time_T201.time*1000)+time_T201.millitm)-((time_T201.time*1000)+time_T201.millitm) >  (60000 *30) )		{  		//	1min * 30


		/*
		if( OTA_Radar.cmd == RADAR_OTACMD_NOTHING )		{
			sleep( 60*5 );		//	5min
			system( "date >> /home/root/RadarOTAlog" );
			OTA_Radar.cmd = RADAR_OTACMD_START;
			sleep( 10 );
		}  		//if( OTA_Radar.cmd == RADAR_OTACMD_NOTHING )		{
		*/



		//================================================================
		//printf( " ___________ sleep \n" );
		//usleep( 100000 );   //  100ms
		//usleep( 200000 );   //  200ms
		usleep( 500000 );   //  500ms
		//usleep( 1000000 );   //  1000ms
		//sleep( 1 );
		ftime( &time_T202 );
	} 		//while( 1 )		{
} 		//void  Keyboard_input_thread( void )



















//********************************************************************
//
//********************************************************************
BITMAPFILEHEADER FileHead;
BITMAPINFOHEADER InfoHead;

static char *fbp = 0;
static int xres = 0;
static int yres = 0;
static int bits_per_pixel = 0;


unsigned char		LCD_Tst01[] = "/home/root/TEST/T11.BMP";
unsigned char		LCD_Tst02[] = "/home/root/TEST/T02.BMP";
unsigned char		LCD_Tst03[] = "/home/root/TEST/T03.BMP";
unsigned char		LCD_Tst04[] = "/home/root/TEST/T04.BMP";
unsigned char		LCD_Tst05[] = "/home/root/TEST/T05.BMP";


int 	LCD_Disp_No;




//********************************************************************
//
//********************************************************************
int 	show_bmp( unsigned char* DispBMPPtr )
{
	FILE *fp;
	int rc;
	int line_x, line_y;
	long int location = 0, BytesPerLine = 0;
	char tmp[1024*10];

	printf( "==========  show_bmp : [%s]  \n", DispBMPPtr );

	//fp = fopen( "./niu.bmp", "rb" );
	fp = fopen( DispBMPPtr, "rb" );
	if (fp == NULL)			{
		return( -1 );
	}

	rc = fread( &FileHead, sizeof(BITMAPFILEHEADER),1, fp );
	if ( rc != 1)			{
		printf("read header error!\n");
		fclose( fp );
		return( -2 );
	}

	//檢測是否是bmp圖像
	if (memcmp(FileHead.cfType, "BM", 2) != 0)			{
		printf("it's not a BMP file\n");
		fclose( fp );
		return( -3 );
	}

	rc = fread( (char *)&InfoHead, sizeof(BITMAPINFOHEADER),1, fp );
	if ( rc != 1)			{
		printf("read infoheader error!\n");
		fclose( fp );
		return( -4 );
	}

	//跳轉的數據區
	fseek(fp, FileHead.cfoffBits, SEEK_SET);
	//每行字節數
	BytesPerLine = (InfoHead.ciWidth * InfoHead.ciBitCount + 31) / 32 * 4;

	line_x = line_y = 0;
	//向framebuffer中寫BMP圖片
	while(!feof(fp))
	{
		PIXEL pix;
		unsigned short int tmp;
		rc = fread( (char *)&pix, 1, sizeof(PIXEL), fp);
		if (rc != sizeof(PIXEL))
			break;
		location = line_x * bits_per_pixel / 8 + (InfoHead.ciHeight - line_y - 1) * xres * bits_per_pixel / 8;

		//顯示每一個像素
		*(fbp + location + 0)=pix.blue;
		*(fbp + location + 1)=pix.green;
		*(fbp + location + 2)=pix.red;
		*(fbp + location + 3)=pix.reserved;

		line_x++;
		if (line_x == InfoHead.ciWidth )
		{
			line_x = 0;
			line_y++;
			if(line_y == InfoHead.ciHeight)
				break;
		}
	}
	fclose( fp );

	printf( "__________  show_bmp End  __________ \n" );
	return( 0 );
}  		//int 	show_bmp( void )




//********************************************************************
//
//********************************************************************
void  Framebuffer_Tst_thread( void )
{

	int fbfd = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long int screensize = 0;
	struct fb_bitfield red;
	struct fb_bitfield green;
	struct fb_bitfield blue;

	printf( "********** **********  Thread Framebuffer_Tst_thread Start  ********** ********** \n" );

	//打開顯示設備
	fbfd = open("/dev/fb0", O_RDWR);
	if (!fbfd)		{
		printf("Error: cannot open framebuffer device.\n");
		exit(1);
	}

	if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo))		{
		printf("Error：reading fixed information.\n");
		exit(2);
	}

	if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo))		{
		printf("Error: reading variable information.\n");
		exit(3);
	}
	printf("R:%d G:%d B:%d \n", vinfo.red, vinfo.green, vinfo.blue );

	/*
	if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo))		{
		printf("Error: Set variable information.\n");
		exit(3);
	}
	if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo))		{
		printf("Error: reading variable information.\n");
		exit(3);
	}
	printf("R:%d G:%d B:%d \n", vinfo.red, vinfo.green, vinfo.blue );
	*/

	printf("H:%d, W:%d \n", vinfo.height, vinfo.width );
	printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel );
	xres = vinfo.xres;
	yres = vinfo.yres;
	bits_per_pixel = vinfo.bits_per_pixel;

	//計算屏幕的總大小（字節）
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
	//screensize = vinfo.xres * vinfo.yres * (24 / 8);
	printf("screensize=%d byte\n",screensize);

	//對象映射
	fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	if ((int)fbp == -1)			{
		printf("Error: failed to map framebuffer device to memory.\n");
		exit(4);
	}

	printf("sizeof file header=%d\n", sizeof(BITMAPFILEHEADER));


	//==================================================================
	printf("into show_bmp function\n");
	//顯示圖像
	//show_bmp();
	while( 1 )		{
		switch( LCD_Disp_No )		{
			case 0:
				break;

			case 1:
				show_bmp( LCD_Tst01 );
				LCD_Disp_No = 0;
				break;
			case 2:
				show_bmp( LCD_Tst02 );
				LCD_Disp_No = 0;
				break;
			case 3:
				show_bmp( LCD_Tst03 );
				LCD_Disp_No = 0;
				break;
			case 4:
				show_bmp( LCD_Tst04 );
				LCD_Disp_No = 0;
				break;
			case 5:
				show_bmp( LCD_Tst05 );
				LCD_Disp_No = 0;
				break;
		}  		//switch( LCD_Disp_No )		{


		//================================================================
		usleep( 50000 );			//	50ms
	}  		//while( 1 )		{


	//刪除對象映射
	munmap(fbp, screensize);
	close(fbfd);
	//return 0;

	printf( "__________  Thread Framebuffer_Tst_thread End  __________ \n" );

}  		//void  Framebuffer_Tst_thread( void )














//********************************************************************
//
//********************************************************************
struct timeb  	time_Tst_autu_sleep1;
struct timeb  	time_Tst_autu_sleep2;
int  		Tst_Auto_Sleep_Enable;
int  		Tst_Flg_Auto_Sleep;



void  Tst_auto_sleep_thread( void )
{
	ftime( &time_Tst_autu_sleep1 );
	ftime( &time_Tst_autu_sleep2 );

	while( 1 )		{
		
		ftime( &time_Tst_autu_sleep2 );

		//if( ((time_Tst_autu_sleep2.time*1000)+time_Tst_autu_sleep2.millitm) - ((time_Tst_autu_sleep1.time*1000)+time_Tst_autu_sleep1.millitm) >  (60000 * 5) )		{  		//	5ms
		//if( ((time_Tst_autu_sleep2.time*1000)+time_Tst_autu_sleep2.millitm) - ((time_Tst_autu_sleep1.time*1000)+time_Tst_autu_sleep1.millitm) >  (60000 * 3) )		{  		//	3ms
		//if( ((time_Tst_autu_sleep2.time*1000)+time_Tst_autu_sleep2.millitm) - ((time_Tst_autu_sleep1.time*1000)+time_Tst_autu_sleep1.millitm) >  (60000 * 2) )		{  		//	2ms
		//if( ((time_Tst_autu_sleep2.time*1000)+time_Tst_autu_sleep2.millitm) - ((time_Tst_autu_sleep1.time*1000)+time_Tst_autu_sleep1.millitm) >  (60000 * 1.5) )		{  		//	90sec
		if( ((time_Tst_autu_sleep2.time*1000)+time_Tst_autu_sleep2.millitm) - ((time_Tst_autu_sleep1.time*1000)+time_Tst_autu_sleep1.millitm) >  60000 )		{  		//	60sec
		//if( ((time_Tst_autu_sleep2.time*1000)+time_Tst_autu_sleep2.millitm) - ((time_Tst_autu_sleep1.time*1000)+time_Tst_autu_sleep1.millitm) >  50000 )		{  		//	50sec

			ftime( &time_Tst_autu_sleep1 );
			ftime( &time_Tst_autu_sleep2 );

			if( (Tst_Auto_Sleep_Enable == 1) && (Tst_Flg_Auto_Sleep == 1) )		{
				usleep( 500 );
				A53M_Sleep( );
			}

			usleep( 100000 );
		}

		sleep( 1 );
	}  		//while( 1 )		{
}  		//void  Tst_auto_sleep_thread( void )
















//********************************************************************
//
//********************************************************************
#define  	SERV_PORT 						8080

#define  	INET_ADDRSTRLEN 			16 			// for IPv4 dotted-decimal
#define  	MAXLINE 							256

void  Tst_tcp_cmd_thread( void )
{
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cliaddr_len;
	int listenfd, connfd;
	char buf[MAXLINE];	
	char buf2[MAXLINE];
	char StrCmd[MAXLINE];
	char str[INET_ADDRSTRLEN];

	char wBuf[MAXLINE];
	int i, n;


	printf( "********** **********  Thread Tst_tcp_cmd_thread Start  ********** ********** \n" );

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(listenfd, 20);

	printf("Accepting connections ...\n");

	//==================================================================
	//
	//==================================================================
	while(1) {
		cliaddr_len = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);

		bzero( buf, MAXLINE );
		bzero( buf2, MAXLINE );
		bzero( StrCmd, MAXLINE );
		n = read(connfd, buf, MAXLINE);

		a53m0API_currentTime = time( NULL);
		a53m0API_current_tm = localtime (&a53m0API_currentTime);

		printf("\n TCP8080 : [%02d/%02d/%02d %02d:%02d:%02d]  received from %s at PORT %d\n", 
				((a53m0API_current_tm->tm_year+1900)-2000),
				a53m0API_current_tm->tm_mon + 1,
				a53m0API_current_tm->tm_mday,
				a53m0API_current_tm->tm_hour,
				a53m0API_current_tm->tm_min,
				a53m0API_current_tm->tm_sec,
				inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), 
				ntohs(cliaddr.sin_port)
				);
		

		//printf( " TCP8080: [[");
		for(i = 0; i < n; i++)  	{
			buf2[i] = buf[i];
			//printf( "%c", buf2[i] );

			//buf[i] = toupper(buf[i]);
		}
		//printf( "]]\n");

		for(i = 0; i < n; i++)  	{
			if( i >= 5 )	{
				if( buf2[i] == 0x20 )	{
					break;
				}
				StrCmd[i-5] = buf2[i];
			}
		}  		//for(i = 0; i < n; i++)  	{
		printf( "  :::: Socket StrCmd[%s]  from %s at PORT %d  \n", StrCmd, inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port) );


		//write(connfd, buf, n);
		bzero( wBuf, MAXLINE );
		sprintf( wBuf,"command received.  [%02d/%02d/%02d %02d:%02d:%02d]  \n",
				((a53m0API_current_tm->tm_year+1900)-2000),
				a53m0API_current_tm->tm_mon + 1,
				a53m0API_current_tm->tm_mday,
				a53m0API_current_tm->tm_hour,
				a53m0API_current_tm->tm_min,
				a53m0API_current_tm->tm_sec );

		write(connfd, wBuf, strlen(wBuf) );
		close(connfd);




		//****************************************************************
		//	Socket Cmd
		//****************************************************************
		int  StrLen = strlen( StrCmd );
		//printf( "  StrLen=[%d] \n", StrLen );

		switch( StrLen ) 		{
			//==============================================================
			//
			case 2:
				if( strcmp( StrCmd, "m0") == 0 )			{
					uartA53M0_REQM0_SystemInfo( );
				}
				else if( strcmp( StrCmd, "rs") == 0 )			{
					system( "wget -c -T30 -t3 -P /home/root/grids/EPM/firmware/radar ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/radarparam30.txt" );
					sleep( 2 );
					radar_set_param( );
				}
				else if( strcmp( StrCmd, "r1") == 0 )			{
					uartA53M0_Req_Radar_Status( );
				}
				break;

			//==============================================================
			//
			case 3:
				if( strcmp( StrCmd, "rs0") == 0 )			{
					uartA53M0_Set_Radar_ShowAllData( 0 );
				}
				else if( strcmp( StrCmd, "rs1") == 0 )			{
					uartA53M0_Set_Radar_ShowAllData( 1 );
				}

				else if( strcmp( StrCmd, "rtc") == 0 )			{
					uartA53M0_SetM0_currentRTC( );
				}

				//	Tst_Auto_Sleep_Enable  -----------------------------------
				else if( strcmp( StrCmd, "as0") == 0 )			{
					Tst_Auto_Sleep_Enable = 0;
				}
				else if( strcmp( StrCmd, "as1") == 0 )			{
					Tst_Auto_Sleep_Enable = 1;
				}
				break;

			//==============================================================
			//
			case 4:
				if( strcmp( StrCmd, "m0ss") == 0 )			{
					uartA53M0_Req_M0_Sys_parameter( );
				}

				else if( strcmp( StrCmd, "m0s0") == 0 )			{
					//	default  	----------------------------------------------
					Tst_M0_Sys_Parameter_Default( );
				  uartA53M0_Set_M0_Sys_parameter( );
				}
				else if( strcmp( StrCmd, "m0s1") == 0 )			{
					//	default  	----------------------------------------------
					Tst_M0_Sys_Parameter_Default( );

					M0_Sys_Parameter.period_heartbeat.Hour = 0;
					M0_Sys_Parameter.period_heartbeat.Minute = 2;
					M0_Sys_Parameter.period_heartbeat.Second = 22;

					M0_Sys_Parameter.fee_time.Fee_Start.Hour = 8;
					M0_Sys_Parameter.fee_time.Fee_Start.Minute = 00;
					M0_Sys_Parameter.fee_time.Fee_Start.Second = 0;
					M0_Sys_Parameter.fee_time.Fee_End.Hour = 20;
					M0_Sys_Parameter.fee_time.Fee_End.Minute = 00;
					M0_Sys_Parameter.fee_time.Fee_End.Second = 0;

					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Hour = 0;
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Minute = 15;
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Second = 22;

					M0_Sys_Parameter.radarA.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarA.car_car_ck.Minute = 10;
					M0_Sys_Parameter.radarA.car_car_ck.Second = 11;
					M0_Sys_Parameter.radarB.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarB.car_car_ck.Minute = 10;
					M0_Sys_Parameter.radarB.car_car_ck.Second = 11;
				  uartA53M0_Set_M0_Sys_parameter( );
				}
				else if( strcmp( StrCmd, "m0s2") == 0 )			{
					//	default  	----------------------------------------------
					Tst_M0_Sys_Parameter_Default( );

					M0_Sys_Parameter.period_heartbeat.Hour = 0;
					M0_Sys_Parameter.period_heartbeat.Minute = 2;
					M0_Sys_Parameter.period_heartbeat.Second = 22;

					M0_Sys_Parameter.fee_time.Fee_Start.Hour = 8;
					M0_Sys_Parameter.fee_time.Fee_Start.Minute = 00;
					M0_Sys_Parameter.fee_time.Fee_Start.Second = 0;
					M0_Sys_Parameter.fee_time.Fee_End.Hour = 9;
					M0_Sys_Parameter.fee_time.Fee_End.Minute = 40;
					M0_Sys_Parameter.fee_time.Fee_End.Second = 0;

					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Hour = 0;
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Minute = 15;
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Second = 22;

					M0_Sys_Parameter.radarA.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarA.car_car_ck.Minute = 10;
					M0_Sys_Parameter.radarA.car_car_ck.Second = 11;
					M0_Sys_Parameter.radarB.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarB.car_car_ck.Minute = 10;
					M0_Sys_Parameter.radarB.car_car_ck.Second = 11;
				  uartA53M0_Set_M0_Sys_parameter( );
				}
				else if( strcmp( StrCmd, "m0s3") == 0 )			{
					//	default  	----------------------------------------------
					Tst_M0_Sys_Parameter_Default( );

					M0_Sys_Parameter.fee_time.Fee_Start.Hour = 11;
					M0_Sys_Parameter.fee_time.Fee_Start.Minute = 20;
					M0_Sys_Parameter.fee_time.Fee_Start.Second = 0;
					M0_Sys_Parameter.fee_time.Fee_End.Hour = 11;
					M0_Sys_Parameter.fee_time.Fee_End.Minute = 40;
					M0_Sys_Parameter.fee_time.Fee_End.Second = 0;

					M0_Sys_Parameter.period_heartbeat.Hour = 0;
					M0_Sys_Parameter.period_heartbeat.Minute = 4;
					M0_Sys_Parameter.period_heartbeat.Second = 0;

					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Hour = 0;
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Minute = 5;
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Second = 00;

					M0_Sys_Parameter.radarA.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarA.car_car_ck.Minute = 5;
					M0_Sys_Parameter.radarA.car_car_ck.Second = 00;
					M0_Sys_Parameter.radarB.car_car_ck.Hour = 0;
					M0_Sys_Parameter.radarB.car_car_ck.Minute = 5;
					M0_Sys_Parameter.radarB.car_car_ck.Second = 00;
				  uartA53M0_Set_M0_Sys_parameter( );
				}
				else if( strcmp( StrCmd, "m0st") == 0 )			{
					//	default  	----------------------------------------------
					Tst_M0_Sys_Parameter_Default( );
					Tst_Set_M0_Sys_parameterFile( );
					uartA53M0_Set_M0_Sys_parameter( );
				}


				//	TL-SAM Test  	--------------------------------------------
				else if( strcmp( StrCmd, "sam1") == 0 )			{
					uint8_t 	dcu_fName[64];
					uint8_t 	dcu_Data[1024];

				  a53m0API_currentTime = time( NULL);
				  a53m0API_current_tm = localtime (&a53m0API_currentTime);
				  sprintf( dcu_fName, "/home/root/grids/EPM/firmware/tl_sam/Enc%02d%02d%02d%02d%02d%02d",
								((a53m0API_current_tm->tm_year+1900)-2000),
								a53m0API_current_tm->tm_mon + 1,
								a53m0API_current_tm->tm_mday,
								a53m0API_current_tm->tm_hour,
								a53m0API_current_tm->tm_min,
								a53m0API_current_tm->tm_sec );

				  for( int i=0 ; i<1000 ; i++ )		{
				  	dcu_Data[i] = i+0x11;
				  }
				  uartA53M0_TLSAM_Encrypt( (uint8_t*)dcu_fName, (uint8_t*)dcu_Data, 16 );
				}
				//	TL-SAM Test  	--------------------------------------------
				else if( strcmp( StrCmd, "sam2") == 0 )			{
					uint8_t 	dcu_fName[64];
					uint8_t 	dcu_Data[1024];

				  a53m0API_currentTime = time( NULL);
				  a53m0API_current_tm = localtime (&a53m0API_currentTime);
				  sprintf( dcu_fName, "/home/root/grids/EPM/firmware/tl_sam/Enc%02d%02d%02d%02d%02d%02d",
								((a53m0API_current_tm->tm_year+1900)-2000),
								a53m0API_current_tm->tm_mon + 1,
								a53m0API_current_tm->tm_mday,
								a53m0API_current_tm->tm_hour,
								a53m0API_current_tm->tm_min,
								a53m0API_current_tm->tm_sec );

				  for( int i=0 ; i<1000 ; i++ )		{
				  	dcu_Data[i] = i+0x11;
				  }
				  uartA53M0_TLSAM_Encrypt( (uint8_t*)dcu_fName, (uint8_t*)dcu_Data, 500 );
				}
				//	TL-SAM Test  	--------------------------------------------
				else if( strcmp( StrCmd, "sam3") == 0 )			{
					uint8_t 	dcu_fName[64];
					uint8_t 	dcu_Data[1024];

				  a53m0API_currentTime = time( NULL);
				  a53m0API_current_tm = localtime (&a53m0API_currentTime);
				  sprintf( dcu_fName, "/home/root/grids/EPM/firmware/tl_sam/Enc%02d%02d%02d%02d%02d%02d",
								((a53m0API_current_tm->tm_year+1900)-2000),
								a53m0API_current_tm->tm_mon + 1,
								a53m0API_current_tm->tm_mday,
								a53m0API_current_tm->tm_hour,
								a53m0API_current_tm->tm_min,
								a53m0API_current_tm->tm_sec );

				  for( int i=0 ; i<1000 ; i++ )		{
				  	dcu_Data[i] = i+0x11;
				  }
				  //uartA53M0_TLSAM_Encrypt( (uint8_t*)dcu_fName, (uint8_t*)dcu_Data, 900 );  		//	OK
				  uartA53M0_TLSAM_Encrypt( (uint8_t*)dcu_fName, (uint8_t*)dcu_Data, 950 );  		//	OK
				  //uartA53M0_TLSAM_Encrypt( (uint8_t*)dcu_fName, (uint8_t*)dcu_Data, 970 );  		//	XX
				  //uartA53M0_TLSAM_Encrypt( (uint8_t*)dcu_fName, (uint8_t*)dcu_Data, 960 );  		//	XX
				}
				break;


			//==============================================================
			case 5:
				if( strcmp( StrCmd, "sleep") == 0 )			{
					printf( " StrCmd-[%s] \n", StrCmd );
					printf( "  tcp CMD: [sleep] ::\n");
					A53M_Sleep( );
				}

				if( strcmp( StrCmd, "a53p0") == 0 )			{
					uartA53M0_Set_SysPower( 0x01, 0 );
				}
				if( strcmp( StrCmd, "a53p1") == 0 )			{
					uartA53M0_Set_SysPower( 0x01, 1 );
				}
				break;
		}  		//switch( StrLen ) 		{

		usleep( 5000 );		//	5ms
	}

	usleep( 100000 );		//	100ms
	printf( "__________  Thread Tst_tcp_cmd_thread End  __________ \n" );
}  		//void  Tst_tcp_cmd_thread( void )


















//******************************************************************************
//
//******************************************************************************
//	/home/root/grids/bin/radarparam.txt
//	M0_radarA_set		M0_radarB_set
void 	Tst_Set_M0_Sys_parameterFile( void )
{
	FILE*	f_m0sysfile;
	unsigned char  R_lineBuf[256];

	int 	scan_interval;

	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf( "\n========== Tst_Set_M0_Sys_parameterFile Start  ==========  [%02d/%02d/%02d %02d:%02d:%02d] \n\n",
			((a53m0API_current_tm->tm_year+1900)-2000),
						a53m0API_current_tm->tm_mon + 1,
						a53m0API_current_tm->tm_mday,
						a53m0API_current_tm->tm_hour,
						a53m0API_current_tm->tm_min,
						a53m0API_current_tm->tm_sec	 );

	f_m0sysfile = fopen( "/home/root/Tst_M0Sys.txt" , "r+b" ) ;
	if( f_m0sysfile )  	{

		//	Read line 	--------------------------------------------------
		int rLength;
		int paramCnt = 0;

		while( !feof( f_m0sysfile ) )		{
			bzero( R_lineBuf, 256 );

			rLength = fscanf( f_m0sysfile, "%s", R_lineBuf );
			if( rLength <= 0 )		{				break;				}

			switch( paramCnt )		{
				case 0:
					printf( "  --%02d  [%02d] \n", paramCnt, atoi( R_lineBuf ) );
					M0_Sys_Parameter.fee_time.Fee_Start.Hour = atoi( R_lineBuf );
					break;
				case 1:
					printf( "  --%02d  [%02d] \n", paramCnt, atoi( R_lineBuf ) );
					M0_Sys_Parameter.fee_time.Fee_Start.Minute = atoi( R_lineBuf );
					break;
				case 2:
					printf( "  --%02d  [%02d] \n", paramCnt, atoi( R_lineBuf ) );
					M0_Sys_Parameter.fee_time.Fee_Start.Second = atoi( R_lineBuf );
					break;
				case 3:
					printf( "  --%02d  [%02d] \n", paramCnt, atoi( R_lineBuf ) );
					M0_Sys_Parameter.fee_time.Fee_End.Hour = atoi( R_lineBuf );
					break;
				case 4:
					printf( "  --%02d  [%02d] \n", paramCnt, atoi( R_lineBuf ) );
					M0_Sys_Parameter.fee_time.Fee_End.Minute = atoi( R_lineBuf );
					break;
				case 5:
					printf( "  --%02d  [%02d] \n", paramCnt, atoi( R_lineBuf ) );
					M0_Sys_Parameter.fee_time.Fee_End.Second = atoi( R_lineBuf );
					break;
				case 6:
					M0_Sys_Parameter.period_heartbeat.Hour = atoi( R_lineBuf );
					break;
				case 7:
					M0_Sys_Parameter.period_heartbeat.Minute = atoi( R_lineBuf );
					break;
				case 8:
					M0_Sys_Parameter.period_heartbeat.Second = atoi( R_lineBuf );
					break;
				case 9:
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Hour = atoi( R_lineBuf );
					break;
				case 10:
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Minute = atoi( R_lineBuf );
					break;
				case 11:
					M0_Sys_Parameter.fee_time.period_FeeFree_CKcar.Second = atoi( R_lineBuf );
					break;
				case 12:
					M0_Sys_Parameter.radarA.car_car_ck.Hour = atoi( R_lineBuf );
					break;
				case 13:
					M0_Sys_Parameter.radarA.car_car_ck.Minute = atoi( R_lineBuf );
					break;
				case 14:
					M0_Sys_Parameter.radarA.car_car_ck.Second = atoi( R_lineBuf );
					break;
				case 15:
					M0_Sys_Parameter.radarB.car_car_ck.Hour = atoi( R_lineBuf );
					break;
				case 16:
					M0_Sys_Parameter.radarB.car_car_ck.Minute = atoi( R_lineBuf );
					break;
				case 17:
					M0_Sys_Parameter.radarB.car_car_ck.Second = atoi( R_lineBuf );
					break;
			} 		//switch( paramCnt )		{
			paramCnt++;
		} 		//while( !feof()f_m0sysfile )		{

		fclose( f_m0sysfile );
	}  		//if( f_m0sysfile )  	{


}  		//void 	Tst_Set_M0_Sys_parameterFile( void )

