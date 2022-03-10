
//********************************************************************
// 	ML22Q535
// 			16Mbit, 	2M byte
// 				20210706 			Daniel
//********************************************************************

#include "m0All_Header.h"




//********************************************************************
//  Global

//	ml22_voice_phrase = 0 ~ 2048
//	ml22_voice_phrase = ML22_PLAY_PHRASE_NONE,  ML22  nothing, Not in playing voice
int 		ml22_voice_phrase;



//  I2C 	============================================================
#if  	Tst_ML22_I2C_S1S2
	//	S1 	 CSI1_TX+ 	 I2C_CAM1_CK
	//	S2 	 CSI1_TX-	   I2C_CAM1_DAT
	unsigned char   dev_I2C_ML22[] = "/dev/i2c-4";

#else
	//	S48 	 I2C_GP_CK 			D13	I2C4_SCL	I2C4_SCL(I2C4,i2c_scl)	GPIO5_IO20(GPIO5,gpio_io,20)
	//	S49 	 I2C_GP_DAT 		E13	I2C4_SDA	I2C4_SDA(I2C4,i2c_sda)	GPIO5_IO21(GPIO5,gpio_io,21)
	unsigned char   dev_I2C_ML22[] = "/dev/i2c-3";

#endif  	//#if  	Tst_ML22_I2C_S1S2





int  fd_ml22_i2c;


//  GPIO 	============================================================
unsigned char 	str_gpio_value_CBUSYB[256];
unsigned char 	str_gpio_value_RESETB[256];
unsigned char 	str_gpio_value_IRCSB[256];
unsigned char 	str_gpio_value_IRON[256];
unsigned char 	str_gpio_value_CSB[256];


pthread_t thread_ml22_PlayStart;
pthread_t thread_ml22_CBUSYB_ck;
int  ml22_CBUSYB;







//********************************************************************
//
//********************************************************************
/*
	P115 	GPIO7 										500 	IRON
	P116 	GPIO8 										501 	IRCSB
	P113 	GPIO5 										133 	RESETB
	P114 	GPIO6 										499 	CBUSYB
*/
void 	ml22q53_gpio_Init( void )
{
	char 	str_cmd[256];
	int  	fd_gpio_export;
	int  	fd_gpio_dir;

	int wRes;


	//==================================================================

	//fd_gpio_export = open(SYSFS_GPIO_EXPORT, O_WRONLY);
	//if( fd_gpio_export == -1 )   {
  //  printf("  XXXXX  ERR: Open [%s] error.\n", SYSFS_GPIO_EXPORT);
  //  return;
	//}

	printf("  ml22q53_gpio_Init     Open [%s]  ========== ========== \n", SYSFS_GPIO_EXPORT);

	//  1, 		GPIO_VALUE_ML22_CBUSYB  ----------------------------------
	//printf( "    gpio - - - - -  GPIO_VALUE_ML22_CBUSYB \n" );

	bzero( str_cmd, 256 );
	sprintf( str_cmd, "%s%d%s", SYSFS_GPIO_DIR1, GPIO_MAP_EXPORTNO_ML22_CBUSYB, SYSFS_GPIO_DIR2 );
	//printf( "  ==[%s] \n", str_cmd );
	fd_gpio_dir = open( str_cmd, O_WRONLY );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}
	//write( fd_gpio_dir, "out", sizeof("out"));
	wRes = write( fd_gpio_dir, "in", sizeof("in"));
	close( fd_gpio_dir );


	//  2, 		GPIO_VALUE_ML22_RESETB  ----------------------------------
	//printf( "    gpio - - - - -  GPIO_VALUE_ML22_RESETB \n" );

	bzero( str_cmd, 256 );
	sprintf( str_cmd, "%s%d%s", SYSFS_GPIO_DIR1, GPIO_MAP_EXPORTNO_ML22_RESETB, SYSFS_GPIO_DIR2 );
	//printf( "  ==[%s] \n", str_cmd );
	fd_gpio_dir = open( str_cmd, O_WRONLY );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}
	wRes = write( fd_gpio_dir, "out", sizeof("out"));
	close( fd_gpio_dir );

	//  3, 		GPIO_VALUE_ML22_IRCSB  -----------------------------------
	//printf( "    gpio - - - - -  GPIO_VALUE_ML22_IRCSB \n" );

	bzero( str_cmd, 256 );
	sprintf( str_cmd, "%s%d%s", SYSFS_GPIO_DIR1, GPIO_MAP_EXPORTNO_ML22_IRCSB, SYSFS_GPIO_DIR2 );
	//printf( "  ==[%s] \n", str_cmd );
	fd_gpio_dir = open( str_cmd, O_WRONLY );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}
	wRes = write( fd_gpio_dir, "out", sizeof("out"));
	close( fd_gpio_dir );

	//  4, 		GPIO_VALUE_ML22_IRON  ------------------------------------
	//printf( "    gpio - - - - -  GPIO_VALUE_ML22_IRON \n" );

	bzero( str_cmd, 256 );
	sprintf( str_cmd, "%s%d%s", SYSFS_GPIO_DIR1, GPIO_MAP_EXPORTNO_ML22_IRON, SYSFS_GPIO_DIR2 );
	//printf( "  ==[%s] \n", str_cmd );
	fd_gpio_dir = open( str_cmd, O_WRONLY );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}
	wRes = write( fd_gpio_dir, "out", sizeof("out"));
	close( fd_gpio_dir );

	//  5, 		GPIO_VALUE_ML22_CSB  ------------------------------------
	#if 	GPIO_ML22_CSB_ENABLE
		//printf( "    gpio - - - - -  GPIO_VALUE_ML22_CSB \n" );

		bzero( str_cmd, 256 );
		sprintf( str_cmd, "%s%d%s", SYSFS_GPIO_DIR1, GPIO_MAP_ML22_CSB, SYSFS_GPIO_DIR2 );
		//printf( "  ==[%s] \n", str_cmd );
		fd_gpio_dir = open( str_cmd, O_WRONLY );
		if ( fd_gpio_dir == -1 )  		{
			printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
		}
		wRes = write( fd_gpio_dir, "out", sizeof("out"));
		close( fd_gpio_dir );
	#endif  	//#if 	GPIO_ML22_CSB_ENABLE

	//close( fd_gpio_export );




	//==================================================================
	// 	/sys/class/gpio/gpio1/value
	//	1, 		GPIO_VALUE_ML22_CBUSYB
	//		str_gpio_value_CBUSYB
	bzero( str_gpio_value_CBUSYB, 256 );
	sprintf( str_gpio_value_CBUSYB, "%s%d%s", SYSFS_GPIO_DIR1, GPIO_MAP_EXPORTNO_ML22_CBUSYB, SYSFS_GPIO_VALUE );
	//printf( "  ***[%s] \n", str_gpio_value_CBUSYB );
	//fd_gpio_value_CBUSYB = open( str_gpio_value_CBUSYB, O_RDWR );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}

	//	2, 		GPIO_VALUE_ML22_RESETB
	bzero( str_cmd, 256 );
	sprintf( str_cmd, "%s%d%s", SYSFS_GPIO_DIR1, GPIO_MAP_EXPORTNO_ML22_RESETB, SYSFS_GPIO_VALUE );
	//printf( "  ***[%s] \n", str_cmd );
	fd_gpio_value_RESETB = open( str_cmd, O_RDWR );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}

	//	3, 		GPIO_VALUE_ML22_IRCSB
	bzero( str_cmd, 256 );
	sprintf( str_cmd, "%s%d%s", SYSFS_GPIO_DIR1, GPIO_MAP_EXPORTNO_ML22_IRCSB, SYSFS_GPIO_VALUE );
	//printf( "  ***[%s] \n", str_cmd );
	fd_gpio_value_IRCSB = open( str_cmd, O_RDWR );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}

	//	4, 		GPIO_VALUE_ML22_IRON
	bzero( str_cmd, 256 );
	sprintf( str_cmd, "%s%d%s", SYSFS_GPIO_DIR1, GPIO_MAP_EXPORTNO_ML22_IRON, SYSFS_GPIO_VALUE );
	//printf( "  ***[%s] \n", str_cmd );
	fd_gpio_value_IRON = open( str_cmd, O_RDWR );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}

	//	5, 		GPIO_VALUE_ML22_CSB
	#if 	GPIO_ML22_CSB_ENABLE
		bzero( str_cmd, 256 );
		sprintf( str_cmd, "%s%d%s", SYSFS_GPIO_DIR1, 4, SYSFS_GPIO_VALUE );
		//printf( "  ***[%s] \n", str_cmd );
		fd_gpio_value_CSB = open( str_cmd, O_RDWR );
		if ( fd_gpio_dir == -1 )  		{
			printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
		}
	#endif  	//#if 	GPIO_ML22_CSB_ENABLE

	
	//==================================================================
	wRes = write( fd_gpio_value_RESETB, "1" ,sizeof("1"));
	wRes = write( fd_gpio_value_IRON, "1" ,sizeof("1"));
	wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));


	//  	TEST  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	printf( " __________ __________ __________ __________ \n" );
	//int sysRes = system( "ls -l /sys/class/gpio" );
	//printf( "\n" );

}  		//void 	ml22q53_gpio_Init( void )


//********************************************************************
//
//********************************************************************
void 	ml22q53_Close( void )
{
	close( fd_gpio_value_CBUSYB );

	close( fd_gpio_value_IRON );
	close( fd_gpio_value_IRCSB );
	close( fd_gpio_value_RESETB );

	close( fd_ml22_i2c );
	close( fd_ml22_spi );
}  		//void 	ml22q53_Close( void )








//********************************************************************
//
//********************************************************************
void  	ml22_CBUSYB_Read( int* cbusy )
{
	char  CBUSYB_value[4];
	char  pre_CBUSY = 'A';
	int  res;

	bzero( CBUSYB_value, 4 );
	fd_gpio_value_CBUSYB = open( str_gpio_value_CBUSYB, O_RDWR );
	res = read( fd_gpio_value_CBUSYB, CBUSYB_value, sizeof( CBUSYB_value ) );
	close( fd_gpio_value_CBUSYB );

	if( CBUSYB_value[0] == '0' )  	{
		*cbusy = 0;
	}
	else 	{
		*cbusy = 1;
	}
}  		//void  	ml22_CBUSYB_Read( int* cbusy )


//********************************************************************
//
//********************************************************************
void  ck_ml22_CBUSYB_thread( int* cbusy )
{
	char  CBUSYB_value[4];
	char  pre_CBUSY = 'A';
	int  res;


	while( 1 )		{
		bzero( CBUSYB_value, 4 );
		fd_gpio_value_CBUSYB = open( str_gpio_value_CBUSYB, O_RDWR );
		res = read( fd_gpio_value_CBUSYB, CBUSYB_value, sizeof( CBUSYB_value ) );
		close( fd_gpio_value_CBUSYB );

		if( CBUSYB_value[0] == '0' )  	{
			*cbusy = 0;
		}
		else 	{
			*cbusy = 1;
		}

		if( CBUSYB_value[0] != pre_CBUSY ) 	{
			printf( "  res[%02d] CBUSYB = [%c] - [%d] \n", res, CBUSYB_value[0], *cbusy );
		}
		pre_CBUSY = CBUSYB_value[0];

		usleep( 5000 );   //  5ms
	}  //		while( 1 )		{

}  		//void  ck_ml22_CBUSYB_thread( int* fdPtr )






















//********************************************************************
//
//********************************************************************
void  	ml22_voice_Play_Start( int  voice_phrase )
{
	printf( "\n" );
	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf(" ========== ml22_voice_Play_Start ---------- ----------  %02d/%02d/%02d %02d:%02d:%02d - [%d] \n",
				((a53m0API_current_tm->tm_year+1900)-2000),
				a53m0API_current_tm->tm_mon + 1,
				a53m0API_current_tm->tm_mday,
				a53m0API_current_tm->tm_hour,
				a53m0API_current_tm->tm_min,
				a53m0API_current_tm->tm_sec,
				voice_phrase  );

	ml22_voice_phrase = voice_phrase;

	printf(" ========== ml22_voice_Play_Start End ___________ ___________ \n");
}  		//void  	ml22_voice_Play_Start( int  voice_phrase )


//********************************************************************
//
//********************************************************************
void  	ml22_voice_Play_Stop( void )
{
	int wRes;

	ml22_voice_phrase = ML22_PLAY_PHRASE_NONE;

	//	Reset ML22Q53
	wRes = write( fd_gpio_value_RESETB, "1" ,sizeof("1"));
	usleep( 1000 );
	wRes = write( fd_gpio_value_RESETB, "0" ,sizeof("1"));
	usleep( 1000 );
	wRes = write( fd_gpio_value_RESETB, "1" ,sizeof("1"));
}  		//void  	ml22_voice_Play_Stop( void )




//********************************************************************
//
//********************************************************************
int  ml22_PlayStart_thread( void )
{
  a53m0API_currentTime = time( NULL);
  a53m0API_current_tm = localtime (&a53m0API_currentTime);


	uint8_t 	wBuf[256];
	uint8_t 	rBuf[256];
	int 	wRes;
	int 	rRes;

	int  		ml22_state;  		//	=0, 	Nothing
													// 	=1, 	Playing Voice

	int  		voice_phrase_play;  		//	== ml22_voice_phrase


	printf( "********** **********  Thread ml22_PlayStart_thread Start  ********** ********** \n" );

	//  	I2C Init  ----------------------------------------------------
	fd_ml22_i2c = open( dev_I2C_ML22, O_RDWR );
	if( fd_ml22_i2c < 0 ) 		{
		printf("    XXXXX XXXXX  ERR: Open [%s] error.\n", dev_I2C_ML22);
		return -1;
	}

	if( ioctl( fd_ml22_i2c, I2C_TIMEOUT, 1) < 0 )		{
		printf("    XXXXX ERR: I2C_TIMEOUT error.\n" );
		close( fd_ml22_i2c );
		return -1;
	}

	if( ioctl( fd_ml22_i2c, I2C_RETRIES, 1) < 0 ) 	{
		printf("    XXXXX ERR: I2C_RETRIES error.\n" );
		close( fd_ml22_i2c );
		return -1;
	}
	
	if( ioctl( fd_ml22_i2c, I2C_SLAVE_FORCE, ADDR_I2C_DEV_ML22 ) < 0 ) 	{
		printf("    XXXXX ERR: I2C_SLAVE_FORCE error.\n" );
		close( fd_ml22_i2c );
		return -1;
	}

	//	SPI port Open 	------------------------------------------------
	fd_ml22_spi = open( dev_SPI_ML22, O_RDWR );
	if( fd_ml22_spi < 0 ) 		{
		printf("    XXXXX XXXXX  ERR: Open [%s] error.\n", dev_SPI_ML22);
		return -1;
	}
	printf( "    [%s] Open success  ========== \n", dev_SPI_ML22 );


	uint32_t  	spi_modeW = 0x00;
	spi_modeW |= SPI_MODE_3;
	if( ioctl( fd_ml22_spi, SPI_IOC_WR_MODE, &spi_modeW) < 0 )		{
		printf("    XXXXX ERR: SPI_IOC_WR_MODE error.\n" );
		close( fd_ml22_spi );
		return -1;
	}


	//==================================================================
	ml22q53_gpio_Init( );

	wRes = write( fd_gpio_value_RESETB, "1" ,sizeof("1"));
	wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));
	wRes = write( fd_gpio_value_IRON, "1" ,sizeof("1"));


	ml22_state = ml22_voice_phrase = ML22_PLAY_PHRASE_NONE;



	//==================================================================
	//  while loop - ml22_PlayStart_thread
	//==================================================================
	while( 1 )  	{
		switch( ml22_state )		{

			//--------------------------------------------------------------
			case 0:
				//	reset ML22Q53
				//	RESETB - -------------------------------------------------
				printf( "    Reset ML22 ==========  [%d] \n", voice_phrase_play );
				wRes = write( fd_gpio_value_RESETB, "1" ,sizeof("1"));
				usleep( 1000 );
				wRes = write( fd_gpio_value_RESETB, "0" ,sizeof("1"));
				usleep( 1000 );
				wRes = write( fd_gpio_value_RESETB, "1" ,sizeof("1"));

				if ( voice_phrase_play > 1024 )			{
					ml22_state = ML22_PLAY_PHRASE_NONE;
					ml22_voice_phrase = ML22_PLAY_PHRASE_NONE;
					break;
				}

				//	IRON - Low   ---------------------------------------------------
				wRes = write( fd_gpio_value_IRON, "0" ,sizeof("1"));

				voice_phrase_play = ml22_voice_phrase;

				ml22_state = 1;
				break;

			//--------------------------------------------------------------
			case 1:
				usleep( 5000 );
				ml22_state = 2;
				break;

			//--------------------------------------------------------------
			case 2:
				//	PUP
				printf( "    ML22 PUP \n" );
				wBuf[0] = 0x00;
				wRes = write( fd_ml22_i2c, wBuf, 1 );
				//printf( "    wRes[%d]  PUP \n", wRes );
				usleep( 39000 );  		// 39ms

				ml22_state = 3;
				break;

			//--------------------------------------------------------------
			case 3:
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}

				// 	I2C, 	AMODE  .............................................
				wBuf[0] = 0x04;
				wBuf[1] = 0xC3;
				wRes = write( fd_ml22_i2c, wBuf, 2 );
				printf( "    wRes[%d]  AMODE \n", wRes );
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}
				// 	I2C, 	FADE  ..............................................
				wBuf[0] = 0x0C;
				wBuf[1] = 0x01;
				wRes = write( fd_ml22_i2c, wBuf, 2 );
				printf( "    wRes[%d]  FADE \n", wRes );
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}
				// 	I2C, 	AVOL  ..............................................
				//		9 = +0.0dB
				wBuf[0] = 0x08;
				wBuf[1] = 0x24;
				wRes = write( fd_ml22_i2c, wBuf, 2 );
				printf( "    wRes[%d]  AVOL \n", wRes );
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}
				// 	I2C, 	CVOL - CH1  ........................................
				//		0.00dB
				wBuf[0] = 0xA1;
				wBuf[1] = 0x00;
				wRes = write( fd_ml22_i2c, wBuf, 2 );
				printf( "    wRes[%d]  CVOL - CH1 \n", wRes );
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}
				// 	I2C, 	CVOL - CH2  ........................................
				//		0.00dB
				wBuf[0] = 0xA2;
				wBuf[1] = 0x00;
				wRes = write( fd_ml22_i2c, wBuf, 2 );
				printf( "    wRes[%d]  CVOL - CH2 \n", wRes );
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}
				// 	I2C, 	CVOL - CH3  ........................................
				//		0.00dB
				wBuf[0] = 0xA4;
				wBuf[1] = 0x00;
				wRes = write( fd_ml22_i2c, wBuf, 2 );
				printf( "    wRes[%d]  CVOL - CH3 \n", wRes );
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}
				// 	I2C, 	CVOL - CH4  ........................................
				//		0.00dB
				wBuf[0] = 0xA8;
				wBuf[1] = 0x00;
				wRes = write( fd_ml22_i2c, wBuf, 2 );
				printf( "    wRes[%d]  CVOL - CH4 \n", wRes );
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}

				// 	I2C, 	FADR - CH0  ........................................
				wBuf[0] = 0x30;
				wBuf[1] = voice_phrase_play;
				wRes = write( fd_ml22_i2c, wBuf, 2 );
				printf( "    wRes[%d]  FADR - CH0 [%d]\n", wRes, voice_phrase_play );
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}
				// 	I2C, 	FADR - CH1  ........................................
				wBuf[0] = 0x31;
				wBuf[1] = voice_phrase_play;
				wRes = write( fd_ml22_i2c, wBuf, 2 );
				printf( "    wRes[%d]  FADR - CH1 \n", wRes );
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}
				// 	I2C, 	FADR - CH2  ........................................
				wBuf[0] = 0x32;
				wBuf[1] = voice_phrase_play;
				wRes = write( fd_ml22_i2c, wBuf, 2 );
				printf( "    wRes[%d]  FADR - CH2 \n", wRes );
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}
				// 	I2C, 	FADR - CH3  ........................................
				wBuf[0] = 0x33;
				wBuf[1] = voice_phrase_play;
				wRes = write( fd_ml22_i2c, wBuf, 2 );
				printf( "    wRes[%d]  FADR - CH3 \n", wRes );

				//	CK ml22_voice_phrase play or Stop
				if( ml22_voice_phrase == ML22_PLAY_PHRASE_NONE )		{
					ml22_state = ML22_PLAY_PHRASE_NONE;
				}
				else if( voice_phrase_play !=  ml22_voice_phrase ) 		{
					ml22_state = 0;
				}
				else 	{
					ml22_state = 4;
				}
				break;

			//--------------------------------------------------------------
			case 4:
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}

				// 	I2C, 	RDSTAT  ............................................
				wBuf[0] = 0xB0;
				rBuf[0] = 0x00;
				wRes = write( fd_ml22_i2c, wBuf, 1 );
				printf( "    wRes[%d]  RDSTAT \n", wRes );
				if( wRes == 1 )		{
					rRes = read( fd_ml22_i2c, rBuf, 1 );
					if( rRes >= 1 ) 	{
						printf( "      Read [%02X] \n", rBuf[0] );
					}
				}

				if( rBuf[0] == 0xFF )		{
					ml22_state = 5;
				}  		//if( rBuf[0] == 0xFF )		{
				else 	{
					ml22_state = 4;
				}
				break;


			//--------------------------------------------------------------
			//	Play Voice  			******************************************
			case 5:
				//	CK ml22_voice_phrase play or Stop
				if( ml22_voice_phrase == ML22_PLAY_PHRASE_NONE )		{
					ml22_state = ML22_PLAY_PHRASE_NONE;
				}
				else if( voice_phrase_play !=  ml22_voice_phrase ) 		{
					ml22_state = 0;
				}

				// 	I2C, 	START 	 Start to play voice  **********************
				wBuf[0] = 0x5F;
				wRes = write( fd_ml22_i2c, wBuf, 1 );
				printf( "    wRes[%d]  START - play voice  **********  [%d] \n", wRes, voice_phrase_play );

				ml22_state = 6;
				break;


			//--------------------------------------------------------------
			// 	I2C, 	RDSTAT
			case 6:
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}

				//	CK ml22_voice_phrase play or Stop
				if( ml22_voice_phrase == ML22_PLAY_PHRASE_NONE )		{
					ml22_state = ML22_PLAY_PHRASE_NONE;
					break;
				}
				else if( voice_phrase_play !=  ml22_voice_phrase ) 		{
					//printf( "    !!!!!  ml22_state=[%d]  [%02d]-[%02d]  !!!!! \n",  ml22_state, voice_phrase_play, ml22_voice_phrase );
					a53m0API_currentTime = time( NULL);
					a53m0API_current_tm = localtime (&a53m0API_currentTime);
					printf("    !!!!!  ml22_state=[%d]  [%02d] ==>> [%02d]  !!!!!  %02d/%02d/%02d %02d:%02d:%02d \n",
								ml22_state, voice_phrase_play, ml22_voice_phrase,
								((a53m0API_current_tm->tm_year+1900)-2000),
								a53m0API_current_tm->tm_mon + 1,
								a53m0API_current_tm->tm_mday,
								a53m0API_current_tm->tm_hour,
								a53m0API_current_tm->tm_min,
								a53m0API_current_tm->tm_sec  );


					if( ml22_voice_phrase < 1024 )	{
						voice_phrase_play = ml22_voice_phrase;
						ml22_state = 0;
						//printf( "    !!!!!  ml22_state=[%d] \n", ml22_state );
						break;
					}
					else {
						ml22_state = ML22_PLAY_PHRASE_NONE;
						ml22_voice_phrase = ML22_PLAY_PHRASE_NONE;
						break;
					}
					break;
				}

				usleep( 50000 );  		// 50ms
				// 	I2C, 	RDSTAT  ............................................
				//printf( "-" );
				wBuf[0] = 0xB0;
				rBuf[0] = 0x00;
				wRes = write( fd_ml22_i2c, wBuf, 1 );
				//printf( "    wRes[%d]  RDSTAT \n", wRes );
				if( wRes == 1 )		{
					rRes = read( fd_ml22_i2c, rBuf, 1 );
					if( rRes >= 1 ) 	{
						//printf( "      Read [%02X] \n", rBuf[0] );						
					}
				}

				if( rBuf[0] == 0xFF )		{
					printf( "      -- RDSTAT = FF \n" );
					ml22_state = 7;
				}  		//if( rBuf[0] == 0xFF )		{
				else 	{
					ml22_state = 6;
				}
				break;

			//--------------------------------------------------------------
			case 7:
				// 	I2C, 	AMODE  .............................................
				wBuf[0] = 0x04;
				wBuf[1] = 0xC1;
				wRes = write( fd_ml22_i2c, wBuf, 2 );
				printf( "    wRes[%d]  AMODE \n", wRes );
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}

				// 	I2C, 	PDWN  ..............................................
				wBuf[0] = 0x20;
				wRes = write( fd_ml22_i2c, wBuf, 1 );
				printf( "    wRes[%d]  PDWN  __________ __________ [%d] \n", wRes, voice_phrase_play );
				printf( "\n" );
				ml22_CBUSYB = 0;
				while( ml22_CBUSYB == 0) 		{
					ml22_CBUSYB_Read( &ml22_CBUSYB );
				}

				ml22_state = ml22_voice_phrase = ML22_PLAY_PHRASE_NONE;
				break;


			//--------------------------------------------------------------
			//--------------------------------------------------------------
			case ML22_PLAY_PHRASE_NONE:
			default :
				if( ml22_voice_phrase < 1024 )	{
					voice_phrase_play = ml22_voice_phrase;
					ml22_state = 0;
					break;
				}

				//voice_phrase_play = ml22_voice_phrase = ML22_PLAY_PHRASE_NONE;
			  usleep( 100000 );  		// 100ms
				break;
		}  		//switch( ml22_state )		{
	}  		//while( 1 )  	{


	//==================================================================
	//close( fd_ml22_i2c );

	//	IRON - Low   ---------------------------------------------------
	wRes = write( fd_gpio_value_IRON, "1" ,sizeof("1"));	
	usleep( 5000 );

	//sleep( 1 );
	printf( "    ml22_PlayStart_thread  __________ __________  End \n" );
}  		//void  ml22_PlayStart_thread( void )

