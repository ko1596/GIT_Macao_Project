
//********************************************************************
// 	ML22Q535-Flash
// 			16Mbit, 	2M byte
// 				20210706 			Daniel
//********************************************************************

#include "m0All_Header.h"


//#define 	TST_FLASH_PROGRAM_DISABLE 	1
//#define 	TST_FLASH_PROGRAM_SLEEP_WAIT 	1

#define 	FLASH_SPI_RE_PUP 			1


//********************************************************************
//  Global
unsigned char   dev_SPI_ML22[] = "/dev/spidev1.0";
//unsigned char   dev_SPI_ML22[] = "/dev/spidev1.1";

unsigned char   FILE_ML22_VERIFY[] = "/home/root/grids/EPM/firmware/ml22_voice/ml22_flash.bin";
//unsigned char   file_ML22_write[] = "/home/root/grids/EPM/firmware/ml22_voice/ml22_voice.bin";


//  SPI 	============================================================
int  				fd_ml22_spi;

//uint32_t  	spi_modeW = 0x00;
//uint32_t  	spi_modeR = 0x00;
//uint8_t  		spi_bits = 8;
//uint32_t  	ml22_spi_speed = ML22_SPI_SPEED;

//
uint8_t 	wBuf_flash[ML22_FLASH_SIZE + 0x20];
uint8_t 	rBuf_flash[ML22_FLASH_SIZE + 0x20];


//====================================================================
void  	ml22q53Flash_Reset_PUP( void );
void  	ml22q53Flash_PDWN( void );




//********************************************************************
//
//********************************************************************
//	Return Value =	0, Verify OK with  "/home/root/grids/bin/ml22_voice/ml22_voice.bin"
int 	ml22q53Flash_ReadVerify( UINT8* filePtr )
{
	uint8_t 	wBuf[256];
	uint8_t 	rBuf[256];
	int 	wRes;
	int 	rRes;


	printf( "\n" );
	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf(" ========== ml22q53Flash_ReadVerify ---------- ----------  %02d/%02d/%02d %02d:%02d:%02d \n",
				((a53m0API_current_tm->tm_year+1900)-2000),
				a53m0API_current_tm->tm_mon + 1,
				a53m0API_current_tm->tm_mday,
				a53m0API_current_tm->tm_hour,
				a53m0API_current_tm->tm_min,
				a53m0API_current_tm->tm_sec );



	//==================================================================
	//	PUP  	----------------------------------------------------------
	wBuf[0] = 0x00;
	wRes = write( fd_gpio_value_IRCSB, "0" ,sizeof("1"));
	wRes = write( fd_ml22_spi, wBuf, 1 );
	wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));
	printf( "    -----  wRes[%d]  -PUP \n", wRes );

	ml22_CBUSYB = 0;
	while( ml22_CBUSYB == 0) 		{
		ml22_CBUSYB_Read( &ml22_CBUSYB );
	}

	//	FDIRECT  	------------------------------------------------------
	wBuf[0] = 0x10;
	wBuf[1] = 0xFF;
	wRes = write( fd_gpio_value_IRCSB, "0" ,sizeof("1"));
	wRes = write( fd_ml22_spi, wBuf, 2 );
	wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));
	printf( "    -----  wRes[%d]  -FDIRECT \n", wRes );

	//------------------------------------------------------------------
	//	Read Flash  	--------------------------------------------------
	int  flash_read_bank = 0x00;
	int  i;

	wBuf[0] = 0x03;
	wBuf[1] = 0x00;
	wBuf[2] = 0x00;
	wBuf[3] = 0x00;
	wRes = write( fd_gpio_value_IRCSB, "0" ,sizeof("1"));
	wRes = write( fd_ml22_spi, wBuf, 4 );

	
	for( i=0 ; i<(ML22_FLASH_SIZE/256) ; i++ )		{
	//for( i=0 ; i<10 ; i++ )		{
		rRes = read( fd_ml22_spi, rBuf_flash+(i*256), 256 );
		//fwrite( rBuf_flash, 1, rRes, f_ml22 );
		//printf( "    -----  rRes[%d] -%04d   [", rRes, i );
		/*
		for( int j=0 ; j<rRes ; j++ )		{
			printf( " %02X", rBuf_flash[j + (i*256)] );
		}
		*/
		
		//printf( "] \n" );
		//usleep( 10 );
	}  		// for(   )
	wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));
	printf( "    -----            -Read Flash \n" );


	//usleep( 100000 );   //  100ms
	//close( fd_ml22_spi );
	
	wRes = write( fd_gpio_value_IRON, "0" ,sizeof("1"));


	//==================================================================
	//	file compare
	//==================================================================
	//		Write to file
	FILE 		*f_ml22 = fopen( FILE_ML22_VERIFY, "w+b" );
	if( f_ml22 )  		{
		printf( "    write flash data to [%s] \n", FILE_ML22_VERIFY );
		fwrite( rBuf_flash, 1, ML22_FLASH_SIZE, f_ml22 );
		fclose( f_ml22 );		
	}
	else 		{
		printf( "    XXXXX  Open [%s] fail !!! \n", FILE_ML22_VERIFY );
		return 1;
	}

	//==================================================================
	//		Read Write file
	f_ml22 = fopen( filePtr, "r+b" );  		
	if( f_ml22 )				{
		printf( "    read voice data from [%s] \n", filePtr );
		size_t res = fread( wBuf_flash, 1, ML22_FLASH_SIZE, f_ml22 );
		fclose( f_ml22 );
	}
	else {
		printf( "    XXXXX  Open [%s] fail !!! \n", filePtr );
		return 1;
	}


	//==================================================================
	//		Verify
	for ( i = 0; i<ML22_FLASH_SIZE ; ++i)			{
		if( rBuf_flash[i] != wBuf_flash[i] )				{
			printf( "    XXXXX XXXXX  Verify Error !!!  XXXXX XXXXX \n" );
			return 1;
		}
	}

	
	printf(" ========== ml22q53Flash_ReadVerify __________  Over \n" );
	return 0;
}  		//int 	ml22q53Flash_ReadVerify( UINT8* filePtr )













//********************************************************************
//
//********************************************************************
//	Return Value =	0, Verify OK with  "/home/root/grids/bin/ml22_voice/ml22_voice.bin"
int 	ml22q53Flash_Write( UINT8* filePtr )
{
	uint8_t 	wBuf[256];
	uint8_t 	rBuf[256];
	int 	wRes;
	int 	rRes;


	printf( "\n" );
	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf(" ========== ml22q53Flash_Write ---------- ----------  %02d/%02d/%02d %02d:%02d:%02d \n",
				((a53m0API_current_tm->tm_year+1900)-2000),
				a53m0API_current_tm->tm_mon + 1,
				a53m0API_current_tm->tm_mday,
				a53m0API_current_tm->tm_hour,
				a53m0API_current_tm->tm_min,
				a53m0API_current_tm->tm_sec );



	//******************************************************************
	//		Flash Erase
	//******************************************************************
	printf("\n    ******* Flash Erase ----------  %02d/%02d/%02d %02d:%02d:%02d \n",
				((a53m0API_current_tm->tm_year+1900)-2000),
				a53m0API_current_tm->tm_mon + 1,
				a53m0API_current_tm->tm_mday,
				a53m0API_current_tm->tm_hour,
				a53m0API_current_tm->tm_min,
				a53m0API_current_tm->tm_sec );


	//==================================================================
	//	PUP  	----------------------------------------------------------
	wBuf[0] = 0x00;
	wRes = write( fd_gpio_value_IRCSB, "0" ,sizeof("1"));
	wRes = write( fd_ml22_spi, wBuf, 1 );
	wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));
	printf( "    -----  wRes[%d]  PUP \n", wRes );

	ml22_CBUSYB = 0;
	while( ml22_CBUSYB == 0) 		{
		ml22_CBUSYB_Read( &ml22_CBUSYB );
	}

	//	FDIRECT  	------------------------------------------------------
	wBuf[0] = 0x10;
	wBuf[1] = 0xFF;
	wRes = write( fd_gpio_value_IRCSB, "0" ,sizeof("1"));
	wRes = write( fd_ml22_spi, wBuf, 2 );
	wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));
	printf( "    -----  wRes[%d]  FDIRECT \n", wRes );


	//------------------------------------------------------------------
	//	Erase Flash  	--------------------------------------------------
	printf( "      erasing .......... .......... \n" );

	int  flash_read_bank = 0x00;
	int  i;

	while( flash_read_bank < ML22_FLASH_SIZE ) 		{
		wBuf[0] = 0x06;
		wRes = write( fd_gpio_value_IRCSB, "0" ,sizeof("1"));
		wRes = write( fd_ml22_spi, wBuf, 1 );
		wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));

		wBuf[0] = 0xD8;
		wBuf[1] = (flash_read_bank >> 16)& 0x00FF;
		wBuf[2] = (flash_read_bank >> 8)& 0x00FF;
		wBuf[3] = (flash_read_bank )& 0x00FF;
		wRes = write( fd_gpio_value_IRCSB, "0" ,sizeof("1"));
		wRes = write( fd_ml22_spi, wBuf, 4 );
		wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));
		

		//	Wait Ready 	....................................................
		rBuf[0] = 0xFF;
		while( rBuf[0] != 0x00 )	{
			wBuf[0] = 0x05;
			wRes = write( fd_gpio_value_IRCSB, "0" ,sizeof("1"));
			wRes = write( fd_ml22_spi, wBuf, 1 );
			rRes = read( fd_ml22_spi, rBuf, 1 );
			wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));
		}  		//while( rBuf[0] != 0x00 )	{
		//printf( "      rRes[%d]-[%02X]  Status  FlashBank[%06X]\n", rRes, rBuf[0], flash_read_bank );
		printf( "      Erasing  rRes[%d]-[%02X]  Status  FlashBank[%06X]\n", rRes, rBuf[0], flash_read_bank );

		flash_read_bank += ML22_FLASH_ERASE_BANKSIZE;
	}  		//while( flash_read_bank < ML22_FLASH_SIZE ) 		{
	
	//close( fd_ml22_spi );



	//******************************************************************
	//		Flash Program
	//******************************************************************
	printf("\n    ******* Flash Program ----------  %02d/%02d/%02d %02d:%02d:%02d \n",
				((a53m0API_current_tm->tm_year+1900)-2000),
				a53m0API_current_tm->tm_mon + 1,
				a53m0API_current_tm->tm_mday,
				a53m0API_current_tm->tm_hour,
				a53m0API_current_tm->tm_min,
				a53m0API_current_tm->tm_sec );

	FILE 		*f_ml22 = fopen( filePtr, "r+b" );
	if( f_ml22 )  		{
		printf( "    read voice data from [%s] \n", filePtr );
		size_t res = fread( rBuf_flash, 1, ML22_FLASH_SIZE, f_ml22 );
		fclose( f_ml22 );		
	}
	else 		{
		printf( "    XXXXX  Open [%s] fail !!! \n", filePtr );
		return 1;
	}

	//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	printf ( "\n    [%s] :[", filePtr );
	for ( i=0; i<256 ; ++i)		{
		printf( " %02X", rBuf_flash[i] );
	}
	printf( "] \n\n" );
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#if  !TST_FLASH_PROGRAM_DISABLE
	// 	Program Flash 	------------------------------------------------
	printf( "      programing .......... .......... \n" );
	flash_read_bank = 0x00;

	//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if 	TST_FLASH_PROGRAM_SLEEP_WAIT
	sleep( 5 );
#endif 		//#if 	TST_FLASH_PROGRAM_SLEEP_WAIT
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	while( flash_read_bank < ML22_FLASH_SIZE ) 		{
		wBuf[0] = 0x06;
		wRes = write( fd_gpio_value_IRCSB, "0" ,sizeof("1"));
		wRes = write( fd_ml22_spi, wBuf, 1 );
		wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));

		wBuf[0] = 0x02;
		wBuf[1] = (flash_read_bank >> 16)& 0x00FF;
		wBuf[2] = (flash_read_bank >> 8)& 0x00FF;
		wBuf[3] = (flash_read_bank )& 0x00FF;
		wRes = write( fd_gpio_value_IRCSB, "0" ,sizeof("1"));
		wRes = write( fd_ml22_spi, wBuf, 4 );
		wRes = write( fd_ml22_spi, (rBuf_flash+flash_read_bank), ML22_FLASH_PROGRAM_BANKSIZE );
		wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));

		//	Wait Ready 	....................................................
		rBuf[0] = 0xFF;
		while( rBuf[0] != 0x00 )	{
			wBuf[0] = 0x05;
			wRes = write( fd_gpio_value_IRCSB, "0" ,sizeof("1"));
			wRes = write( fd_ml22_spi, wBuf, 1 );
			rRes = read( fd_ml22_spi, rBuf, 1 );
			wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));
		}  		//while( rBuf[0] != 0x00 )	{

		//printf( "      rRes[%d]-[%02X]  Status  FlashBank[%06X]\n", rRes, rBuf[0], flash_read_bank );
		if( (flash_read_bank % ML22_FLASH_ERASE_BANKSIZE) == 0 )	{			
			printf( "      Programing  rRes[%d]-[%02X]  Status  FlashBank[%06X]\n", rRes, rBuf[0], flash_read_bank );
		}

		flash_read_bank += ML22_FLASH_PROGRAM_BANKSIZE;
	}  		//while( flash_read_bank < ML22_FLASH_SIZE ) 		{

#endif 		//#if  !TST_FLASH_PROGRAM_DISABLE

	//close( fd_ml22_spi );
}  				//int 	ml22q53Flash_Write( void )













//********************************************************************
//
//********************************************************************
void  	ml22q53Flash_Reset_PUP( void )
{
	uint8_t 	wBuf[256];
	uint8_t 	rBuf[256];
	int 	wRes;
	int 	rRes;


	printf( "\n" );
	a53m0API_currentTime = time( NULL);
	a53m0API_current_tm = localtime (&a53m0API_currentTime);
	printf(" ========== ml22q53Flash_Reset_PUP ---------- ----------  %02d/%02d/%02d %02d:%02d:%02d \n",
				((a53m0API_current_tm->tm_year+1900)-2000),
				a53m0API_current_tm->tm_mon + 1,
				a53m0API_current_tm->tm_mday,
				a53m0API_current_tm->tm_hour,
				a53m0API_current_tm->tm_min,
				a53m0API_current_tm->tm_sec );

	wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));

	//	reset ML22Q53
	//	RESETB - -------------------------------------------------
	printf( "    Reset ML22 ==========  \n" );
	wRes = write( fd_gpio_value_RESETB, "1" ,sizeof("1"));
	usleep( 200 );
	wRes = write( fd_gpio_value_RESETB, "0" ,sizeof("1"));
	usleep( 50 );
	wRes = write( fd_gpio_value_RESETB, "1" ,sizeof("1"));
	usleep( 1000 );
	
	wRes = write( fd_gpio_value_IRON, "1" ,sizeof("1"));


#if 	FLASH_SPI_RE_PUP
	for( int pwCnt=0 ; pwCnt<2 ; pwCnt++ ) 		{
		//	PUP  	----------------------------------------------------------
		wBuf[0] = 0x00;
		wRes = write( fd_gpio_value_IRCSB, "0" ,sizeof("1"));
		wRes = write( fd_ml22_spi, wBuf, 1 );
		wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));
		printf( "    -----  wRes[%d]  -PUP \n", wRes );

		ml22_CBUSYB = 0;
		while( ml22_CBUSYB == 0) 		{
			ml22_CBUSYB_Read( &ml22_CBUSYB );
		}
		usleep( 10000 );

		//	PDWN  	--------------------------------------------------------
		wBuf[0] = 0x20;
		wRes = write( fd_gpio_value_IRCSB, "0" ,sizeof("1"));
		wRes = write( fd_ml22_spi, wBuf, 1 );
		wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));
		printf( "    -----  wRes[%d]  -PDWN \n", wRes );

		ml22_CBUSYB = 0;
		while( ml22_CBUSYB == 0) 		{
			ml22_CBUSYB_Read( &ml22_CBUSYB );
		}
		usleep( 10000 );
	}  		//for( int pwCnt=0 ; pwCnt<4 ; pwCnt++ ) 		{
#endif  //#if 	FLASH_SPI_RE_PUP

}  		//void  	ml22q53Flash_Reset_PUP( void )


//********************************************************************
//
//********************************************************************
void  	ml22q53Flash_PDWN( void )
{
	uint8_t 	wBuf[256];
	uint8_t 	rBuf[256];
	int 	wRes;
	int 	rRes;

	//	PDWN  	--------------------------------------------------------
	wBuf[0] = 0x20;
	wRes = write( fd_gpio_value_IRCSB, "0" ,sizeof("1"));
	wRes = write( fd_ml22_spi, wBuf, 1 );
	wRes = write( fd_gpio_value_IRCSB, "1" ,sizeof("1"));
	printf( "    -----  wRes[%d]  -PDWN \n", wRes );

	ml22_CBUSYB = 0;
	while( ml22_CBUSYB == 0) 		{
		ml22_CBUSYB_Read( &ml22_CBUSYB );
	}
}  		//void  	ml22q53Flash_PDWN( void )










//********************************************************************
//
//********************************************************************
//	Return Value =	0, Verify OK with  "/home/root/grids/bin/ml22_voice/ml22_voice.bin"
int 	ml22_Flash_Verify( UINT8* filePtr )
{
	int  ml22_verify = 0;

	ml22q53Flash_Reset_PUP( );

	ml22_verify = ml22q53Flash_ReadVerify( filePtr );

	ml22q53Flash_PDWN( );

	return ml22_verify;
}  		//int 	ml22_Flash_Verify( UINT8* filePtr )


//********************************************************************
//
//********************************************************************
//	Return Value	=0, Write & Verify OK with  "/home/root/grids/bin/ml22_voice/ml22_voice.bin"
int 	ml22_Flash_Write( UINT8* filePtr )
{
	int  ml22_verify = 0;

	ml22q53Flash_Reset_PUP( );

	ml22q53Flash_Write( filePtr );

	ml22_verify = ml22q53Flash_ReadVerify( filePtr );

	ml22q53Flash_PDWN( );

	return ml22_verify;
}  		//int 	ml22_Flash_Write( UINT8* filePtr )

