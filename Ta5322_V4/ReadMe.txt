



//********************************************************************
//  SDK     -   Ta5322_V4
//********************************************************************
//  FileZillea :: 	==================================================
D:\Green_Project\Prj_Parking\iMX8mini-SDK\SDK-M0\
/home/user/yocto_imx8/SDK/d88sdk-M0


//	docker 		========================================================
//	git-u1664_M4-01 	================================================
docker ps -a

advt@git-u1664:~$ docker ps -a
CONTAINER ID        IMAGE                     COMMAND             CREATED             STATUS                     PORTS               NAMES
3742ca706c83        ubuntu:18.04              "/bin/bash"         13 days ago         Exited (0) 13 days ago                         hardcore_elbakyan
ded14a49880c        advrisc/u18.04-imx8lbv1   "/bin/bash"         6 weeks ago         Up 11 days                                     imx8mm-sdk
507bbace5351        advrisc/u18.04-imx8lbv1   "/bin/bash"         6 weeks ago         Up 2 weeks                                     imx8mm-image
1c25897e25d6        advrisc/u16.04-imx8lbv1   "/bin/bash"         12 months ago       Up 2 weeks                                     greenidea-imx8lbv1-sdk
3d37c0891304        advrisc/u16.04-imx8lbv1   "/bin/bash"         12 months ago       Exited (0) 12 months ago                       imx8mm02
advt@git-u1664:~$ 



//--------------------------------------------------------------------
//	20210531
//	 		SDK  Start 		imx8mm-sdk 			--------------------------------
//--------------------------------------------------------------------
docker start imx8mm-sdk
docker exec -it imx8mm-sdk /bin/bash

cd /home/adv/adv-release-bsp
##source /home/adv/adv-release-bsp/build_sdk/tmp/work/aarch64-poky-linux/meta-toolchain/1.0-r7/sdk/image/opt/fsl-imx-xwayland/4.14-sumo/environment-setup-aarch64-poky-linux
source /home/adv/adv-release-bsp/environment-setup-aarch64-poky-linux

##export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
##export ARCH=arm64
##export CROSS_COMPILE=/usr/bin/aarch64-linux-gnu-gcc
##export JSON_C_DIR=/usr/local/

cd /home/adv/adv-release-bsp/D88SDK-M0/Ta5322_V4

cd /home/adv/adv-release-bsp/D88SDK-M0/Ta5322_V4alps



//	Local PC 	========================================================
cd D:\Green_Project\Prj_Parking\iMX8mini-SDK\SDK-M0\Ta5322_V4
cd /home/user/yocto_imx8/sdk/D88SDK-M0/Ta5322_V4
//	linux
cd /home/user/yocto_imx8/sdk/D88SDK-M0/Ta5322_V4


//	${CC} 		********************************************************
##${CC} -o Ta5322_V4 Ta5322_V4.c Ta53M0.c m0Uart_rx.c m0Uart_tx.c getDcuParam.c TstA53M0.c -lpthread

make clean
make

scp ./Ta5322_V4 root@192.168.1.104://home/root/grids/bin
scp ./Ta5322_V4 root@192.168.1.104://home/root/D88


//====================================================================
//	folder  ==========================================================
/home/root/grids/bin
/home/root/grids/EPM/firmware/radar


//	Test function  	==================================================
/home/root/grids/bin/Ta5322_V4 1 2

sh /home/root/grids/bin/gpioLS.sh
sh /home/root/TEST/gpioLS.sh

/home/root/grids/bin/	


//====================================================================
//	4G Init
sh /home/root/grids/bin/pls62_setup.sh


ls -l /dev | grep ttyACM
sh /home/root/grids/bin/pls62_setup.sh
sh /home/root/grids/bin/pls62_setup2.sh

sh /home/root/grids/bin/pls62_disconnect.sh


ls -l /sys/class/gpio

sh /home/root/grids/bin/gpio_export.sh
sh /home/root/grids/bin/gpio_unexport.sh

ls -l --time-style='+%y-%m-%d %H:%M:%S'


ps -aux | grep Ta5322_V4
top p PID

//	Samuel RUN
ps -aux | grep grids_main






//		Old Ver. 		----------------------------------------------------
//	 SDK  Start 		--------------------------------------------------
//--------------------------------------------------------------------
docker start greenidea-imx8lbv1-sdk
docker exec -it imx8mm-sdk /bin/bash

cd /home/adv/adv-release-bsp/d88sdk-M0
source environment-setup-aarch-64-poky-linux
cd /home/adv/adv-release-bsp/d88sdk-M0/Ta5322_V4

//	Local PC 	========================================================
cd D:\Green_Project\Prj_Parking\iMX8mini-SDK\SDK-M0\Ta5322_V4
//	linux
cd /home/user/yocto_imx8/SDK/d88sdk-M0











//********************************************************************
//		API F/W Update :
//********************************************************************
//--------------------------------------------------------------------
API F/W Update :	Radar[FW03000105]
A53-API : [iMX8mm Ta5322_V4    20220225B3e]
M0 SAML22 : [Prj318_ALL       20220227-0318cD]

//--------------------------------------------------------------------
API F/W Update :	Radar[FW03000105]
A53-API : [iMX8mm Ta5322_V4    20220222B28b]
M0 SAML22 : [Prj318_ALL       20220224-0318b8]

//--------------------------------------------------------------------
API F/W Update :	Radar[FW03000105]
A53-API : [iMX8mm Ta5322_V4    20220222B28b]
M0 SAML22 : [Prj318_ALL       20220222-0318b5]

//--------------------------------------------------------------------
API F/W Update :	Radar[FW03000105]
A53-API : [iMX8mm Ta5322_V4    20220217B27 0221T15]
M0 SAML22 : ["]Prj318_ALL       20220221-0318b1]
















//********************************************************************
//	ROM-5721  Image, 	I/O Ver2.0
//********************************************************************

//		eMMC Boot  	----------------------------------------------------
Switch :
	1 	BOOT_SEL2 	OFF
	2 	BOOT_SEL1 	OFF
	3 	BOOT_SEL0 	ON
	4 	SW2 				OFF
	5 	SW1 				OFF
	ls -l /run/media/mmcblk2p1

//		SD Boot  	------------------------------------------------------
Switch :
	1 	BOOT_SEL2 	ON
	2 	BOOT_SEL1 	ON
	3 	BOOT_SEL0 	OFF
	4 	SW2 				OFF
	5 	SW1 				OFF
	ls -l /run/media/mmcblk1p1


// SW1  	............................................................
	BOOT_SEL2		BOOT_SEL1		BOOT_SEL0
		GND					GND 				Float 				SD
		Float 			Float 			GND 					eMMC



//====================================================================
//		imx8m 燒錄image到emmc方法
//====================================================================
將檔案 5720A1AIM20LIV90022_iMX8M_flash_tool.tgz 拷貝到SD card 或是 usb disk
解壓縮檔案
$ tar zxvf 5720A1AIM20LIV90022_iMX8M_flash_tool.tgz
查找eMMC device name
$ fdisk -l
Device         Boot  Start      End  Sectors  Size Id Type
/dev/mmcblk2p1       16384   147455   131072   64M  c W95 FAT32 (LBA)
/dev/mmcblk2p2      147456 15273592 15126137  7.2G 83 Linux
將 fsl-image-validation-imx-imx8mmrom5721a1-20200520094113.rootfs.sdcard 放到 5721A1AIM20LIV90102_iMX8MM_flash_tool/image 目錄中
執行 5721A1AIM20LIV90102_iMX8MM_flash_tool/mk_inand/mksd-linux.sh
$ sudo ./mksd-linux.sh /dev/mmcblk2

連結為5720A1AIM20LIV90022_iMX8M_flash_tool.tgz下載點


------------------------------------------------------------------------------------------
目前Android下有OTA的方式可以透過網路下載image下來後再做更新的動作, 不過這個需要EMMC的容量夠大才能夠儲存要更新的image檔.

以下為目前我們使用的方式:

1.      燒錄到SD card的話都是直接在host PC上做, image要解壓縮並直接燒錄到SD card. 
		如果用網路將image傳到iMX8mm, 要有空間可以儲存image然後, 然後在解壓縮後在燒錄到SD card(使用eMMC開機).

2.      寫到eMMC的話, 會用已做好的SD card開機後, 將image檔放在SD card內或是其他儲存裝置上, 
		所以需要有儲存的地方來放置image檔, 然後再將image燒錄到eMMC, 如果要用網路傳送的話也須要有可以儲存的地方, 然後解壓縮後在燒錄到eMMC.

3.      如果是工廠要載入image的話可以使用OTG的方式來將image載入到eMMC.


======================================================================
root@imx8mmrom5721a1:~/image# pwd
/home/root/image
root@imx8mmrom5721a1:~/image# ls -l
total 452104
drwxrwxr-x 4 1000 tracing      4096 Apr  8  2020 5721A1AIM20LIV90102_iMX8MM_flash_tool
-rwxrwxrwx 1 root root    462943333 Jun 28 06:00 5721A1AIM20LIV90102_iMX8MM_flash_tool.tgz

cd /home/root/image/5721A1AIM20LIV90102_iMX8MM_flash_tool/mk_inand
root@imx8mmrom5721a1:~/image/5721A1AIM20LIV90102_iMX8MM_flash_tool/mk_inand# ls -l
total 4
-rwxr-xr-x 1 root root 1424 Apr  8  2020 mksd-linux.sh

----------------------------------------------------------------------
./mksd-linux.sh /dev/mmcblk2
root@imx8mmrom5721a1:~/image/5721A1AIM20LIV90102_iMX8MM_flash_tool/mk_inand# ./mksd-linux.sh /dev/mmcblk2

Transfer U-Boot & Linux to target device

All data on /dev/mmcblk2 now will be destroyed! Continue? [y/n]
y
[Unmounting all existing partitions on the device ]
[Partitioning /dev/mmcblk2...]
[Copy fsl-image-validation-imx-imx8mmrom5721a1-20200408092213.rootfs.sdcard image]
[Resize filesystems...]
[Done]
root@imx8mmrom5721a1:~/image/5721A1AIM20LIV90102_iMX8MM_flash_tool/mk_inand# 


======================================================================
root@imx8mmrom5721a1:~# lsb_release -a
LSB Version:	core-5.0-noarch:core-5.0-aarch64
Distributor ID:	fsl-imx-xwayland
Description:	NXP i.MX Release Distro 4.14-sumo
Release:	4.14-sumo
Codename:	sumo
root@imx8mmrom5721a1:~# uname -a
Linux imx8mmrom5721a1 4.14.98-imx_4.14.98_2.0.0_ga #1 SMP PREEMPT Wed Apr 14 11:34:34 UTC 2021 aarch64 aarch64 aarch64 GNU/Linux

root@imx8mmrom5721a1:~# lsb_release -a
LSB Version:	core-5.0-noarch:core-5.0-aarch64
Distributor ID:	fsl-imx-xwayland
Description:	NXP i.MX Release Distro 4.14-sumo
Release:	4.14-sumo
Codename:	sumo
root@imx8mmrom5721a1:~# uname -a
Linux imx8mmrom5721a1 4.14.98-5721A1AIM20LIV90102 #1 SMP PREEMPT Wed Apr 8 09:14:47 UTC 2020 aarch64 aarch64 aarch64 GNU/Linux
root@imx8mmrom5721a1:~# 





//********************************************************************
//	Write linux Image
//********************************************************************

//		Write Image to eMMC  		----------------------------------------
//		SD Boot
cd /home/root/image/5721A1AIM20LIV90102_iMX8MM_flash_tool/mk_inand
ls -l /home/root/image/5721A1AIM20LIV90102_iMX8MM_flash_tool/image
./mksd-linux.sh /dev/mmcblk2

//		Write Image to SDCard  		--------------------------------------
//		eMMC Boot
./mksd-linux.sh /dev/mmcblk2


//--------------------------------------------------------------------
//		fsl-image-validation-imx-imx8mmrom5721a1-20210526023343.rootfs.sdcard
root@imx8mmrom5721a1:~/image/5721A1AIM20LIV90102_iMX8MM_flash_tool/mk_inand# date 
Thu Sep 16 08:29:10 UTC 2021
root@imx8mmrom5721a1:~/image/5721A1AIM20LIV90102_iMX8MM_flash_tool/mk_inand# ./mksd-linux.sh /dev/mmcblk2

Transfer U-Boot & Linux to target device

All data on /dev/mmcblk2 now will be destroyed! Continue? [y/n]
y
[Unmounting all existing partitions on the device ]
[Partitioning /dev/mmcblk2...]
[Copy fsl-image-validation-imx-imx8mmrom5721a1-20210526023343.rootfs.sdcard image]
[Resize filesystems...]
[Done]
root@imx8mmrom5721a1:~/image/5721A1AIM20LIV90102_iMX8MM_flash_tool/mk_inand# 
root@imx8mmrom5721a1:~/image/5721A1AIM20LIV90102_iMX8MM_flash_tool/mk_inand# date
Thu Sep 16 08:32:04 UTC 2021
root@imx8mmrom5721a1:~/image/5721A1AIM20LIV90102_iMX8MM_flash_tool/mk_inand# 

root@imx8mmrom5721a1:~# uname -a
Linux imx8mmrom5721a1 4.14.98-imx_4.14.98_2.0.0_ga #1 SMP PREEMPT Wed Apr 14 11:34:34 UTC 2021 aarch64 aarch64 aarch64 GNU/Linux
root@imx8mmrom5721a1:~# lsb_release -a
LSB Version:	core-5.0-noarch:core-5.0-aarch64
Distributor ID:	fsl-imx-xwayland
Description:	NXP i.MX Release Distro 4.14-sumo
Release:	4.14-sumo
Codename:	sumo
root@imx8mmrom5721a1:~# 




//====================================================================
//	DTS
//		adv-imx8mm-rom5721-a1.dtb
//====================================================================
//		eMMC Boot  	----------------------------------------------------
/run/media/mmcblk2p1
ls -l /run/media/mmcblk2p1

root@imx8mmrom5721a1:~# ls -l /run/media/mmcblk2p1
total 24118
-rwxrwx--- 1 root disk 24185344 Feb 16 11:26 Image
-rwxrwx--- 1 root disk    45142 Feb 16 11:26 adv-imx8mm-rom5721-a1-adv7535.dtb
-rwxrwx--- 1 root disk    46636 Feb 16 11:26 adv-imx8mm-rom5721-a1-auog101uan02.dtb
-rwxrwx--- 1 root disk    45774 Feb 16 11:26 adv-imx8mm-rom5721-a1-dsi2dp.dtb
-rwxrwx--- 1 root disk    45680 Feb 16 11:26 adv-imx8mm-rom5721-a1-dsi2lvds-g150xgel05.dtb
-rwxrwx--- 1 root disk    45680 Feb 16 11:26 adv-imx8mm-rom5721-a1-dsi2lvds-g215hvn01.dtb
-rwxrwx--- 1 root disk    46472 Feb 16 11:26 adv-imx8mm-rom5721-a1-m2-i2s.dtb
-rwxrwx--- 1 root disk    46613 Feb 16 11:26 adv-imx8mm-rom5721-a1-m2-sdio.dtb
-rwxrwx--- 1 root disk    46606 Feb 16 11:26 adv-imx8mm-rom5721-a1-m4.dtb
-rwxrwx--- 1 root disk    46472 Feb 16 11:26 adv-imx8mm-rom5721-a1.dtb
-rwxrwx--- 1 root disk     6320 Feb 16 11:26 imx8mm_m4_TCM_hello_world.bin
-rwxrwx--- 1 root disk    16888 Feb 16 11:26 imx8mm_m4_TCM_rpmsg_lite_pingpong_rtos_linux_remote.bin
-rwxrwx--- 1 root disk    16520 Feb 16 11:26 imx8mm_m4_TCM_rpmsg_lite_str_echo_rtos.bin
-rwxrwx--- 1 root disk    40724 Feb 16 11:26 imx8mm_m4_TCM_sai_low_power_audio.bin


//		SDCARD Boot  	--------------------------------------------------
/run/media/mmcblk1p1
ls -l /run/media/mmcblk1p1


root@imx8mmrom5721a1:/usr/lib# ls -l /run/media/mmcblk2p1
total 23704
-rwxrwx--- 1 root disk 23763456 May 26 02:36 Image
-rwxrwx--- 1 root disk    45034 May 26 02:36 adv-imx8mm-rom5721-a1-adv7535.dtb
-rwxrwx--- 1 root disk    45736 May 26 02:36 adv-imx8mm-rom5721-a1-auog101uan02.dtb
-rwxrwx--- 1 root disk    45666 May 26 02:36 adv-imx8mm-rom5721-a1-dsi2dp.dtb
-rwxrwx--- 1 root disk    45572 May 26 02:36 adv-imx8mm-rom5721-a1-dsi2lvds-g150xgel05.dtb
-rwxrwx--- 1 root disk    45572 May 26 02:36 adv-imx8mm-rom5721-a1-dsi2lvds-g215hvn01.dtb
-rwxrwx--- 1 root disk    45572 May 26 02:36 adv-imx8mm-rom5721-a1-m2-i2s.dtb
-rwxrwx--- 1 root disk    45713 May 26 02:36 adv-imx8mm-rom5721-a1-m2-sdio.dtb
-rwxrwx--- 1 root disk    45710 May 26 02:36 adv-imx8mm-rom5721-a1-m4.dtb
-rwxrwx--- 1 root disk    45572 May 26 02:36 adv-imx8mm-rom5721-a1.dtb
-rwxrwx--- 1 root disk     6320 May 26 02:36 imx8mm_m4_TCM_hello_world.bin
-rwxrwx--- 1 root disk    16888 May 26 02:36 imx8mm_m4_TCM_rpmsg_lite_pingpong_rtos_linux_remote.bin
-rwxrwx--- 1 root disk    16520 May 26 02:36 imx8mm_m4_TCM_rpmsg_lite_str_echo_rtos.bin
-rwxrwx--- 1 root disk    40724 May 26 02:36 imx8mm_m4_TCM_sai_low_power_audio.bin


root@imx8mmrom5721a1:~# uname -a
Linux imx8mmrom5721a1 4.14.98-imx_4.14.98_2.0.0_ga #1 SMP PREEMPT Wed Apr 14 11:34:34 UTC 2021 aarch64 aarch64 aarch64 GNU/Linux
root@imx8mmrom5721a1:~# lsb_release -a
LSB Version:	core-5.0-noarch:core-5.0-aarch64
Distributor ID:	fsl-imx-xwayland
Description:	NXP i.MX Release Distro 4.14-sumo
Release:	4.14-sumo
Codename:	sumo
root@imx8mmrom5721a1:~# 


//====================================================================
//		Update  adv-imx8mm-rom5721-a1.dtb
//====================================================================
//		eMMC Boot  	----------------------------------------------------
ls -l /run/media/mmcblk2p1

//		SD Boot  	------------------------------------------------------
ls -l /run/media/mmcblk1p1






//********************************************************************
//	ROM-5721  ==>  json-c

root@imx8mmrom5721a1:~/a53m0# ls -l | grep libjson-c
-rwxr-xr-x 1 root root 619726 Jun 16 08:47 libjson-c.a
-rwxr-xr-x 1 root root 255800 Jun 16 08:47 libjson-c.so
-rwxr-xr-x 1 root root 255800 Jun 16 08:47 libjson-c.so.5
-rwxr-xr-x 1 root root 255800 Jun 16 08:47 libjson-c.so.5.1.0

//	Start Update  json  ----------------------------------------------
cp libjson-c.* /usr/lib/
cd /usr/lib/
====>
root@imx8mmrom5721a1:/usr/lib# ls -l | grep libjson
-rwxr-xr-x  1 root root   619726 Jun 16 08:50 libjson-c.a
-rwxr-xr-x  1 root root   255800 Jun 16 08:50 libjson-c.so
lrwxrwxrwx  1 root root       18 Apr 14 11:58 libjson-c.so.3 -> libjson-c.so.3.0.1
-rwxr-xr-x  1 root root    51616 Apr 14 11:59 libjson-c.so.3.0.1
-rwxr-xr-x  1 root root   255800 Jun 16 08:50 libjson-c.so.5
-rwxr-xr-x  1 root root   255800 Jun 16 08:50 libjson-c.so.5.1.0
lrwxrwxrwx  1 root root       27 Apr 14 11:55 libjson-glib-1.0.so.0 -> libjson-glib-1.0.so.0.400.2
-rwxr-xr-x  1 root root   145160 Apr 14 11:59 libjson-glib-1.0.so.0.400.2

***** 		rm libjson-c.so
***** 		ln -s libjson-c.so.5 libjson-c.so
root@imx8mmrom5721a1:/usr/lib# rm libjson-c.so

root@imx8mmrom5721a1:/usr/lib# ln -s libjson-c.so.5 libjson-c.so
root@imx8mmrom5721a1:/usr/lib# ls -l | grep libjson
-rwxr-xr-x  1 root root   619726 Jun 16 08:50 libjson-c.a
lrwxrwxrwx  1 root root       14 Jun 16 08:56 libjson-c.so -> libjson-c.so.5
lrwxrwxrwx  1 root root       18 Apr 14 11:58 libjson-c.so.3 -> libjson-c.so.3.0.1
-rwxr-xr-x  1 root root    51616 Apr 14 11:59 libjson-c.so.3.0.1
-rwxr-xr-x  1 root root   255800 Jun 16 08:50 libjson-c.so.5
-rwxr-xr-x  1 root root   255800 Jun 16 08:50 libjson-c.so.5.1.0
lrwxrwxrwx  1 root root       27 Apr 14 11:55 libjson-glib-1.0.so.0 -> libjson-glib-1.0.so.0.400.2
-rwxr-xr-x  1 root root   145160 Apr 14 11:59 libjson-glib-1.0.so.0.400.2






//********************************************************************
//	IP / MAC 
//********************************************************************
On	192.168.1.105	192.168.1.105	ADVANTECH CO., LTD.	74:FE:48:58:9F:07

eth0      Link encap:Ethernet  HWaddr 74:fe:48:58:9e:a6  
          inet addr:192.168.1.106  Bcast:192.168.1.255  Mask:255.255.255.0



//********************************************************************
//		TL-SAM
//********************************************************************

//		加密16 bytes. 總回應bytes數是 256+(16+16）+256 = 544 bytes


//	Test 	adlk00026 		==============================================
scp /home/root/TL_SAM/*.tlsam user@192.168.1.104://home/user/TL_SAM



//********************************************************************
//		Audio 		ML22Q53x 	TQFP48
//********************************************************************

I2C  Slave Address :
	SAD2 SAD1 SAD0  0 1 0 1



//********************************************************************
//
ttymxc0 	CN15 	下(SER2/UART1): /dev/ttymxc0
ttymxc1 	COM1 	(A53 debug/UART2): /dev/ttymxc1
ttymxc2 	CN15	上(SER0/UART3): /dev/ttymxc2
ttymxc3 	COM3 	(M4 debug/UART4): /dev/ttymxc3



//********************************************************************
//  UTC
//********************************************************************
#timedatectl list-timezones
Asia/Samarkand
Asia/Seoul
Asia/Shanghai
Asia/Singapore
Asia/Srednekolymsk
Asia/Taipei
Asia/Tashkent
Asia/Tbilisi
Asia/Tehran
Asia/Thimphu
Asia/Tokyo
Asia/Tomsk
Asia/Ulaanbaatar
Asia/Urumqi

#timedatectl set-timezone Asia/Taipei




//********************************************************************
//  A53 Sleep
//********************************************************************
root@imx8mmrom5721a1:~# cat /sys/power/state
freeze mem

echo mem > /sys/power/state
==> 	0.10A
[  174.984246] PM: suspend entry (deep)
[  174.987890] PM: Syncing filesystems ... done.
[  175.011427] Freezing user space processes ... (elapsed 0.054 seconds) done.
[  175.072664] OOM killer disabled.
[  175.075943] Freezing remaining freezable tasks ... (elapsed 0.001 seconds) done.
[  175.084672] Suspending console(s) (use no_console_suspend to debug)

echo freeze > /sys/power/state
==> 	0.24A
[  143.566466] PM: suspend entry (s2idle)
[  143.570279] PM: Syncing filesystems ... done.
[  143.640868] Freezing user space processes ... (elapsed 0.001 seconds) done.
[  143.649693] OOM killer disabled.
[  143.652954] Freezing remaining freezable tasks ... (elapsed 0.000 seconds) done.
[  143.661370] Suspending console(s) (use no_console_suspend to debug)


//====================================================================
//	Enter Sleep  -----------------------------------------------------
s
 StrCmd-[s] 
 **********  Set A53 to SLEEP MODE - mem  **********
    $$$$$$$$$$  [echo mem > /sys/[  362.937539] PM: suspend entry (deep)
power/state] 
[  362.941378] PM: Syncing filesystems ... done.
[  363.010543] Freezing user space processes ... (elapsed 0.001 seconds) done.
[  363.019283] OOM killer disabled.
[  363.022525] Freezing remaining freezable tasks ... (elapsed 0.001 seconds) done.
[  363.031291] Suspending console(s) (use no_console_suspend to debug)

//	Wake Up  ---------------------------------------------------------
[  363.038278] wlan: Stoping AP
[  363.048441] wlan: AP stopped
[  363.112601] vhci_hcd vhci_hcd.0: suspend vhci_hcd
[  363.115615] BT: suspend success! skip=0
[  363.228693] PM: suspend devices took 0.192 seconds
[  363.230993] Disabling non-boot CPUs ...
[  363.246508] IRQ 6: no longer affine to CPU1
[  363.246660] CPU1: shutdown
[  363.246664] psci: CPU1 killed.
[  363.270578] CPU2: shutdown
[  363.270583] psci: CPU2 killed.
[  363.294538] CPU3: shutdown
[  363.294541] psci: CPU3 killed.
[  363.294901] Enabling non-boot CPUs ...
[  363.295068] Detected VIPT I-cache on CPU1
[  363.295088] GICv3: CPU1: found redistributor 1 region 0:0x00000000388a0000
[  363.295118] CPU1: Booted secondary processor [410fd034]
[  363.295492]  cache: parent cpu1 should not be sleeping
[  363.295614] CPU1 is up
[  363.295726] Detected VIPT I-cache on CPU2
[  363.295739] GICv3: CPU2: found redistributor 2 region 0:0x00000000388c0000
[  363.295756] CPU2: Booted secondary processor [410fd034]
[  363.296001]  cache: parent cpu2 should not be sleeping
[  363.296105] CPU2 is up
[  363.296245] Detected VIPT I-cache on CPU3
[  363.296257] GICv3: CPU3: found redistributor 3 region 0:0x00000000388e0000
[  363.296274] CPU3: Booted secondary processor [410fd034]
[  363.296517]  cache: parent cpu3 should not be sleeping
[  363.296626] CPU3 is up
[  363.564711] imx-sgtl5000 sound: no-audmux specified, skipping audmux configuration
[  363.564777] imx-sgtl5000 sound: failed to find SSI platform device
[  363.564853] PM: resume devices took 0.264 seconds
[  363.702584] OOM killer enabled.
[  363.705723] Restarting tasks ... 
[  363.706493] done.
[  363.721319] PM: suspend entry (deep)
[  363.724975] PM: suspend exit
[  363.728496] PM: suspend exit
    ##########  WakeUp WiFi AP : [systemctl restart hostapd] 
[  364.019404] get_channel when AP is not started
[  364.024227] get_channel when AP is not started
[  364.029576] get_channel when AP is not started
[  364.035045] get_channel when AP is not started
[  364.041409] wlan: Starting AP
[  364.057298] wlan: AP started
[  364.061217] Set AC=3, txop=47 cwmin=3, cwmax=7 aifs=1
[  364.069221] Set AC=2, txop=94 cwmin=7, cwmax=15 aifs=1
[  364.076802] Set AC=0, txop=0 cwmin=15, cwmax=63 aifs=3
[  364.084327] Set AC=1, txop=0 cwmin=15, cwmax=1023 aifs=7
RxM0 MGC : [21-09-16 05:51:47]  M0_Status_Update[80001136] mgc[02]
21-09-16 05:51:48	80001136	0045	3193	0018	02	8151	507	0067
[  365.193117] IPv6: ADDRCONF(NETDEV_UP): eth0: link is not ready
[  365.335959] fec 30be0000.ethernet eth0: Link is Up - 100Mbps/Full - flow control rx/tx
[  365.343959] IPv6: ADDRCONF(NETDEV_CHANGE): eth0: link becomes ready
21-09-16 05:51:50	80001136	0045	3175	0018	02	8159	445	0068
21-09-16 05:51:52	80001136	0051	3175	0014	02	8154	461	0069
21-09-16 05:51:54	80001136	0051	3172	0026	02	8154	461	0070
21-09-16 05:51:56	80001136	0053	3177	0026	02	8156	461	0071
21-09-16 05:51:58	80001136	0046	3177	0019	02	8154	453	0072
21-09-16 05:52:00	80001136	0046	3175	0018	02	8152	445	0073
21-09-16 05:52:02	80001136	0046	3174	0018	02	8153	461	0074
21-09-16 05:52:04	80001136	0046	3174	0019	02	8155	445	0075
21-09-16 05:52:06	80001136	0046	3149	0019	02	8153	445	0076
21-09-16 05:52:08	80001136	0047	3151	0019	02	8155	445	0077
21-09-16 05:52:10	80001136	0046	3181	0019	02	8153	453	0078
21-09-16 05:52:12	80001136	0052	3181	0021	02	8154	445	0079
[  388.202860] wlan: EVENT: MICRO_AP_STA_ASSOC f4:XX:XX:XX:52:2a
21-09-16 05:52:14	80001136	0052	3178	0018	02	8154	445	0080
21-09-16 05:52:16	80001136	0047	3176	0018	02	8155	453	0081





















//********************************************************************
//  Radar Test
//********************************************************************
ftp.green-ideas.com.tw
[user]
[git54272485git]

//--------------------------------------------------------------------
ftp.green-ideas.com.tw
user: [parkmeter]
passwd:[gitpark]

ftp :		/home/ftp/parkmeter/Tst_radar
/home/ftp/parkmeter/Tst_radar


??? wput ./getParam.txt ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/
wget ftp://parkmeter:gitpark@ftp.green-ideas.com.tw/Tst_radar/getParam.txt





//********************************************************************
//  ADC Test
//********************************************************************
8.4V / 3 = 2.8V
33 / 28 = 4095 / 3474.545454545455		3474

84 / 3474  = 62 / 2564.142857142857



//********************************************************************
//  GPIO A53
//********************************************************************
P108  	 GPIO0		409
P109  	 GPIO1 		GPIO5_IO06 	(5-1)*32+6=134
P110  	 GPIO2		497
P111  	 GPIO3
P112  	 GPIO4		498
P113  	 GPIO5 		133
P114  	 GPIO6 		499
P115  	 GPIO7 		500
P116  	 GPIO8 		501
P117  	 GPIO9 		502
P118  	 GPIO10 	503
P119  	 GPIO11 	131
 
P109: GPIO1: MX8MM_IOMUXC_ECSPI1_SCLK_GPIO5_IO06: 134
P111: GPIO3: MX8MM_IOMUXC_GPIO1_IO08_GPIO1_IO08: 8

S107 		GPIO4_IO27	123
//	GPIO4_IO27 	......................................................
echo 123 > /sys/class/gpio/export


//	GPIO0 	496 	----------------------------------------------------
//	TEST.		P113  	 GPIO5 		133
root@imx8mmrom5721a1:~# echo 133 > /sys/class/gpio/export
root@imx8mmrom5721a1:~# echo in > /sys/class/gpio/gpio1/direction
root@imx8mmrom5721a1:~# cat /sys/class/gpio/gpio1/value
1
root@imx8mmrom5721a1:~# echo 133 > /sys/class/gpio/unexport

//	TEST.		P119  	 GPIO11 	131
root@imx8mmrom5721a1:~# echo 131 > /sys/class/gpio/export
root@imx8mmrom5721a1:~# echo in > /sys/class/gpio/gpio1/direction
root@imx8mmrom5721a1:~# cat /sys/class/gpio/gpio1/value
1
root@imx8mmrom5721a1:~# echo 131 > /sys/class/gpio/unexport


//	TEST.		P134 	GPIO5_IO29		157
echo 157 > /sys/class/gpio/export
0
//	TEST.		P135 	GPIO5_IO28		156
echo 156 > /sys/class/gpio/export
0

//	TEST.		P57 	GPIO5_IO23		151
//	TEST.		P58 	GPIO5_IO24		152




//********************************************************************
// 	systemD
//********************************************************************

/etc/systemd/system

k_parking.service

systemctl enable k_parking
systemctl status k_parking
systemctl disable k_parking

這個可以看到個服務啟動占用的時間
systemd-analyze blame

cat StartUp_Time.txt
cat /etc/systemd/system/k_parking.service




//********************************************************************
// 	iMx8 Dual
//********************************************************************
root@imx8mmrom5721a1:~# df -ha
Filesystem      Size  Used Avail Use% Mounted on
/dev/root       7.0G  2.9G  3.8G  43% /
devtmpfs        153M  4.0K  153M   1% /dev
sysfs              0     0     0    - /sys
proc               0     0     0    - /proc
securityfs         0     0     0    - /sys/kernel/security
tmpfs           474M     0  474M   0% /dev/shm
devpts             0     0     0    - /dev/pts
tmpfs           474M   25M  449M   6% /run
tmpfs           474M     0  474M   0% /sys/fs/cgroup
cgroup2            0     0     0    - /sys/fs/cgroup/unified
cgroup             0     0     0    - /sys/fs/cgroup/systemd
pstore             0     0     0    - /sys/fs/pstore
cgroup             0     0     0    - /sys/fs/cgroup/devices
cgroup             0     0     0    - /sys/fs/cgroup/cpu,cpuacct
cgroup             0     0     0    - /sys/fs/cgroup/memory
cgroup             0     0     0    - /sys/fs/cgroup/hugetlb
cgroup             0     0     0    - /sys/fs/cgroup/blkio
cgroup             0     0     0    - /sys/fs/cgroup/pids
cgroup             0     0     0    - /sys/fs/cgroup/cpuset
cgroup             0     0     0    - /sys/fs/cgroup/perf_event
hugetlbfs          0     0     0    - /dev/hugepages
mqueue             0     0     0    - /dev/mqueue
debugfs            0     0     0    - /sys/kernel/debug
tmpfs           474M     0  474M   0% /tmp
fusectl            0     0     0    - /sys/fs/fuse/connections
configfs           0     0     0    - /sys/kernel/config
tmpfs           474M  228K  474M   1% /var/volatile
tmpfs            95M  4.0K   95M   1% /run/user/0
/dev/mmcblk1p5  7.8M   45K  7.3M   1% /run/media/mmcblk1p5
/dev/mmcblk1p6  740M  776K  686M   1% /run/media/mmcblk1p6
/dev/mmcblk1p1   64M   24M   41M  37% /run/media/mmcblk1p1
/dev/mmcblk2p1   84M   30M   54M  36% /run/media/mmcblk2p1
/dev/mmcblk1p2   28G  5.2G   21G  20% /run/media/mmcblk1p2












回復來看看




//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

ifconfig uap0 down
ifconfig uap0 up

systemctl stop hostapd
systemctl restart hostapd


service network restart
service network stop

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	Samuel RUN
ps -aux | grep grids_main

scp ./Ta5321_ALL root@192.168.1.103://home/root/grids/bin
scp ./Ta5321_ALL root@192.168.1.103://home/root/D88


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
sh /home/root/grids/bin/gpio_export.sh
sh /home/root/gpioLS.sh

/home/root/grids/bin/Ta5321_ALL 1


ps -aux | grep k_main

echo mem > /sys/power/state
systemctl restart hostapd

											printf( "    ##########  WakeUp WiFi AP : [systemctl restart hostapd] \n" );
											system( "systemctl restart hostapd" );



ifconfig uap0 | grep "inet addr"
systemctl status hostapd | grep "running"
systemctl status hostapd

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
cat StartUp_Time.txt
cat /etc/systemd/system/k_parking.service

/etc/systemd/system

k_parking.service

systemctl enable k_parking
systemctl status k_parking
systemctl disable k_parking

這個可以看到個服務啟動占用的時間
systemd-analyze blame


ps -aux | grep Ta5321_ALL











//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	Radar OTA
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	typedef struct  {
		UINT8  		cmd;
		UINT8 		nc01;
		UINT16 		Status_RadarA;
		UINT16 		Status_RadarB;
		UINT32 		nc02;
		UINT8  		FileName_radarOTA[256];
	}M0_RADAR_OTA_FRAME;

M0_RADAR_OTA_FRAME  	OTA_Radar

//====================================================================
***** 		Start to used Radar OTA
1.
Set Radar HEX file to OTA_Radar.FileName_radarOTA
		bzero( OTA_Radar.FileName_radarOTA, 256 );
		sprint( OTA_Radar.FileName_radarOTA "%s", Radar HEX filename )

2.
save radar parameter value to  /home/root/grids/EPM/firmware/radar/radarparam30.txt

3.
check  OTA_Radar.cmd == RADAR_OTACMD_NOTHING
	if( OTA_Radar.cmd == RADAR_OTACMD_NOTHING )		{
		OTA_Radar.cmd == RADAR_OTACMD_START  		//	Start Radar OTA
			- 	RADAR_OTACMD_INIT
			- 	RADAR_OTACMD_ERASE_PAGE
			- 	RADAR_OTACMD_PROGRAM_DATA
			- 	RADAR_OTACMD_SET_PARAMETER

		if( OTA_Radar.cmd == RADAR_OTACMD_NOTHING ) 	{
			Radar OTA Over
			Check  OTA_Radar.Status_RadarA & OTA_Radar.Status_RadarB
		}
	}


//====================================================================
***** 		Set Radar parameter
1.
save radar parameter value to  /home/root/grids/EPM/firmware/radar/radarparam30.txt

2.
call  radar_set_param( );








//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	M0 All device Self-Test
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
M0_Status_Update
	#define  	M0_DEV_UPDATE_M0_SELFTEST		0x20000000  		//0010 0000  0000 0000  0000 0000  0000 0000

M0_DEV_SELF_TEST 	M0_Device_SelfTest;

	typedef struct  {
		UINT32 	Device_SelfCheck;
		M0_RTC_TIME_FRAME  		mcu_RTC;
	}M0_DEV_SELF_TEST;

	M0_Device_SelfTest.Device_SelfCheck  ::
			#define  	DEV_SELFTEST_ERR_RTC  											0x0001  		//	0000 0000  0000 0001
			#define  	DEV_SELFTEST_ERR_GESTURE  									0x0002  		//	0000 0000  0000 0010
			#define  	DEV_SELFTEST_ERR_G_SENSOR  									0x0004  		//	0000 0000  0000 0100

			#define  	DEV_SELFTEST_ERR_RADAR_A  									0x0008  		//	0000 0000  0000 1000
			#define  	DEV_SELFTEST_ERR_RADAR_B  									0x0010  		//	0000 0000  0001 0000

			#define  	DEV_SELFTEST_ERR_LTC2644  									0x0100  		//	0000 0001  0000 0000
			#define  	DEV_SELFTEST_ERR_LM75  											0x0200  		//	0000 0010  0000 0000
			#define  	DEV_SELFTEST_ERR_STK8BA53  									0x0400  		//	0000 0100  0000 0000
			#define  	DEV_SELFTEST_ERR_K60168  										0x0800  		//	0000 1000  0000 0000

			#define  	DEV_SELFTEST_ERR_EEPROM  										0x1000  		//	0001 0000  0000 0000

			#define  	DEV_SELFTEST_ERR_CHILI2S  									0x8000  		//	1000 0000  0000 0000


1.  M0 power On should auto Run devices Self-Test, about 20sec.

2.  Request uartA53M0_REQM0_SelfTest( ) function
		After 20sec should response :  "RxM0 Devices Self-Test  [22-01-17 17:18:43]  M0 devices Self-Test:[00000800]"








//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	M0 Gesture Skip Time
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/home/root/grids/bin/Ta5322_V4alps 1 600
/home/root/grids/bin/Ta5322_V4 1 600
systemctl start k_parking.service

/home/root/D88TEST/killPID Ta5322_V4
/home/root/D88TEST/killPID grids_pm_hk
systemctl stop k_parking.service


sh /home/root/grids/bin/gpioLS.sh
sh /home/root/D88TEST/gpioLS.sh


curl "http://127.0.0.1:8080/m0st"

curl "http://127.0.0.1:8080/sleep"

curl "http://127.0.0.1:8080/m0ss"
curl "http://127.0.0.1:8080/m0s1"
curl "http://127.0.0.1:8080/m0s2"

curl "http://127.0.0.1:8080/m0"
curl "http://127.0.0.1:8080/rs"

curl "http://127.0.0.1:8080/a53p0"  		//A53 Power Off
curl "http://127.0.0.1:8080/a53p1"

//	Tst_Auto_Sleep_Enable
curl "http://127.0.0.1:8080/as1"
curl "http://127.0.0.1:8080/as0"

//	TL-SAM Test
curl "http://127.0.0.1:8080/sam1"


cd /home/root/D88TEST/Ta5322_V4alps/
/home/root/D88TEST/Ta5322_V4alps/Ta5322_V4alps 1 600




/home/root/D88TEST/Ta5322_V4alps/image/
