

//	# P119   -- export gpio13

int 	fd_gpio_epaper_backled_state;

void  A53M0_gpio_Init( void )
{
	char 	str_cmd[256];
	int  	fd_gpio_dir;
	int  	wRes;

	bzero( str_cmd, 256 );
	sprintf( str_cmd, "/sys/class/gpio/gpio%d/direction", GPIO_EPAPER_BACKLED_STATE );
	fd_gpio_dir = open( str_cmd, O_WRONLY );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}
	//write( fd_gpio_dir, "out", sizeof("out"));
	wRes = write( fd_gpio_dir, "out", sizeof("out"));
	close( fd_gpio_dir );

	bzero( str_cmd, 256 );
	sprintf( str_cmd, "/sys/class/gpio/gpio%d/value", GPIO_EPAPER_BACKLED_STATE );
	fd_gpio_epaper_backled_state = open( str_cmd, O_RDWR );
	if ( fd_gpio_dir == -1 )  		{
		printf("  XXXXX  ERR: Open [%s] error.\n", str_cmd);
	}
}



//********************************************************************
//
//********************************************************************
void  A53M_LCD_BackLight_ON( void )
{
	int wRes = write( fd_gpio_epaper_backled_state, "1" ,sizeof("1"));
}  		//void  A53M_LCD_BackLight_ON( void )

//********************************************************************
//
//********************************************************************
void  A53M_LCD_BackLight_OFF( void )
{
	int wRes = write( fd_gpio_epaper_backled_state, "0" ,sizeof("0"));
}  		//void  A53M_LCD_BackLight_OFF( void )
