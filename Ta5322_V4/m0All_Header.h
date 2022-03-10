

//********************************************************************
//  m0All_Header.h
//********************************************************************

#ifndef ALL_HEADER_H
#define ALL_HEADER_H


//====================================================================
#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

#include <time.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/mman.h>


#include <sys/time.h>
#include <sys/timeb.h>//timeb

//#include <asm/page.h>
#include <netinet/in.h>

#include <signal.h>

#include <linux/input.h>
//#include <linux/conio.h>		//	linux/conio.h: No such file or directory


//--------------------------------------------------------------------
#include <linux/kernel.h>
#include <linux/module.h>
//#include <linux/virtio.h>
#include <linux/virtio_ids.h>
#include <linux/virtio_config.h>
//#include <linux/scatterlist.h>
//#include <linux/dma-mapping.h>
//#include <linux/slab.h>
//#include <linux/idr.h>
//#include <linux/jiffies.h>
#include <linux/sched.h>
//#include <linux/wait.h>
#include <linux/rpmsg.h>
//#include <linux/mutex.h>
//#include <linux/of_device.h>

//#include "rpmsg_internal.h"

#include <json-c/json.h>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <linux/ioctl.h>
#include <sys/stat.h>
#include <linux/types.h>
//#include <linux/spi/spi.h>
#include <linux/spi/spidev.h>

//	FrameBuffer  Test
#include <linux/fb.h>
#include <arpa/inet.h>

#include <gtk/gtk.h>

//====================================================================
//	Ta5320I_ALL
#include 	"m0All_define.h"
#include 	"Ta53M0.h"

#include 	"ml22q53.h"
#include 	"ml22q53Flash.h"
#include 	"ota_radar.h"
#include 	"ota_chili2s.h"

#include 	"getDcuParam.h"

#include 	"gtkService.h"

//	TEST  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include 	"TstA53M0.h"
#include 	"Tst2.h"


#endif    //ALL_HEADER_H

