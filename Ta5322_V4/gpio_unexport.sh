#!/bin/sh

T1=0.1
T2=1

# S41 4G POWER (GPIO4_IO02, ((4-1)*32)+2)=98) -- linux-98 -- export gpio1
echo "unexport gpio 98"
echo 98 > /sys/class/gpio/unexport
sleep $T1

# P108 Camera POWER -- linux-504 -- export gpio2
echo "unexport gpio 504"
echo 504 > /sys/class/gpio/unexport
sleep $T1

# P117 USB HUB Power -- linux-510 -- export gpio3 
echo "unexport gpio 510"
echo 510 > /sys/class/gpio/unexport
sleep $T1

# P126 RESET USB HUB (GPIO4_IO28, ((4-1)*32)+28)=124) -- linux-124 -- export gpio4
echo "unexport gpio 124"
echo 124 > /sys/class/gpio/unexport
sleep $T1

# S107 EPD POWER (GPIO4_IO27) -- linux-123 -- export gpio5
echo "unexport gpio 123"
echo 123 > /sys/class/gpio/unexport
sleep $T1

# P114 GPIO6 TCA9538PWR P3 -- linux-507 -- export gpio6
echo "unexport gpio 507"
echo 507 > /sys/class/gpio/unexport
sleep $T1

# P113 GPIO5_IO05 -- linux-133 -- export gpio7
echo "unexport gpio 133"
echo 133 > /sys/class/gpio/unexport
sleep $T1

# P116 GPIO8  TCA9538PWR P5 -- linux-509 -- export gpio8
echo "unexport gpio 509"
echo 509 > /sys/class/gpio/unexport
sleep $T1


# P115 GPIO7  TCA9538PWR P4 -- linux-508 -- export gpio9
echo "unexport gpio 508"
echo 508 > /sys/class/gpio/unexport
sleep $T1


# S40 GPIO4_IO12 -- Linux-108 -- export gpio10
echo "unexport gpio 108"
echo 108 > /sys/class/gpio/unexport
sleep $T1

# P119 GPIO11  e-paper back light -- linux-131 -- export gpio11
echo "unexport gpio 512"
echo 131 > /sys/class/gpio/unexport
sleep $T1


