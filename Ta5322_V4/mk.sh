#!/bin/bash

  make clean
  make

  echo "__________ __________ __________ __________"
  ##scp ./Ta5322_V4 root@192.168.1.122://home/root/grids/bin
  ##scp ./Ta5321_ALL root@192.168.1.167://home/root/grids/bin
  ls -l ./Ta5322_V4

	#scp ./gpio_export.sh root@192.168.1.117://home/root/grids/bin
	#scp ./gpio_unexport.sh root@192.168.1.117://home/root/grids/bin
	#scp ./gpioLS.sh root@192.168.1.117://home/root/grids/bin
	scp ./Ta5322_V4 root@192.168.1.102://home/root/grids/bin

  #echo ""
  date

exit 0
