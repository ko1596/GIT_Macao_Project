#!/bin/sh

T1=1
T2=10


#**********************************
#          unexport
#**********************************
# S41 4G POWER (GPIO4_IO02, ((4-1)*32)+2)=98) -- linux-98 -- export gpio1
echo 98 > /sys/class/gpio/unexport
#echo -e ".\c"

# P108 Camera POWER -- linux-504 -- export gpio2
echo 504 > /sys/class/gpio/unexport

# P117 USB HUB Power -- linux-510 -- export gpio3 
echo 510 > /sys/class/gpio/unexport

# P126 RESET USB HUB (GPIO4_IO28, ((4-1)*32)+28)=124) -- linux-124 -- export gpio4
echo 124 > /sys/class/gpio/unexport

# S107 EPD POWER (GPIO4_IO27) -- linux-123 -- export gpio5
echo 123 > /sys/class/gpio/unexport

# P114 GPIO6 TCA9538PWR P3 -- linux-507 -- export gpio6
echo 507 > /sys/class/gpio/unexport

# P113 GPIO5_IO05 -- linux-133 -- export gpio7
echo 133 > /sys/class/gpio/unexport

# P116 GPIO8  TCA9538PWR P5 -- linux-509 -- export gpio8
echo 509 > /sys/class/gpio/unexport

# P115 GPIO7  TCA9538PWR P4 -- linux-508 -- export gpio9
echo 508 > /sys/class/gpio/unexport

# S40 GPIO4_IO12 -- Linux-108 -- export gpio10
echo 108 > /sys/class/gpio/unexport

# P110   -- export gpio11
echo 505 > /sys/class/gpio/unexport

# P111   -- export gpio12
echo 8 > /sys/class/gpio/unexport

# P119   -- export gpio13
echo 131 > /sys/class/gpio/unexport

# P109  Camera POWER -- linux-134 -- export gpio14
echo 134 > /sys/class/gpio/unexport

# P112  Card Reader -- linux-506 -- export gpio15
echo 506 > /sys/class/gpio/unexport

echo "unexport done"

#**********************************
#          export
#**********************************
# S41 4G POWER (GPIO4_IO02, ((4-1)*32)+2)=98)
#echo "export gpio 98"
echo 98 > /sys/class/gpio/export
#sleep $T1
echo out > /sys/class/gpio/gpio1/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio1/value
#sleep $T1

# P108 Camera POWER
#echo "export gpio 504"
echo 504 > /sys/class/gpio/export
#sleep $T1
echo out > /sys/class/gpio/gpio2/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio2/value
#sleep $T1

# P117 USB HUB Power 
#echo "export gpio 510"
echo 510 > /sys/class/gpio/export
#sleep $T1
echo out > /sys/class/gpio/gpio3/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio3/value
#sleep $T1

# P126 RESET USB HUB (GPIO4_IO28, ((4-1)*32)+28)=124)
#echo "export gpio 124"
echo 124 > /sys/class/gpio/export
#sleep $T1
echo out > /sys/class/gpio/gpio4/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio4/value
#sleep $T1

# S107 EPD POWER (GPIO4_IO27)
#echo "export gpio 123"
echo 123 > /sys/class/gpio/export
#sleep $T1
echo out > /sys/class/gpio/gpio5/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio5/value
#sleep $T1


# P114 GPIO6 TCA9538PWR P3 -- linux-507 -- export gpio6
#echo "export gpio 507"
echo 507 > /sys/class/gpio/export
#sleep $T1
#echo out > /sys/class/gpio/gpio6/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio6/value
#sleep $T1


# P113 GPIO5_IO05 -- linux-133 -- export gpio7
#echo "export gpio 133"
echo 133 > /sys/class/gpio/export
#sleep $T1
#echo out > /sys/class/gpio/gpio7/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio7/value
#sleep $T1

# P116 GPIO8  TCA9538PWR P5 -- linux-509 -- export gpio8
#echo "export gpio 509"
echo 509 > /sys/class/gpio/export
#sleep $T1
#echo out > /sys/class/gpio/gpio8/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio8/value
#sleep $T1


# P115 GPIO7  TCA9538PWR P4 -- linux-508 -- export gpio9
#echo "export gpio 508"
echo 508 > /sys/class/gpio/export
#sleep $T1
#echo out > /sys/class/gpio/gpio9/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio9/value
#sleep $T1

# S40 GPIO4_IO12 -- Linux-108 -- export gpio10
#echo "export gpio 108"
echo 108 > /sys/class/gpio/export
#sleep $T1
#echo out > /sys/class/gpio/gpio10/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio10/value
#sleep $T1

# P110
echo 505 > /sys/class/gpio/export
#sleep $T1
echo out > /sys/class/gpio/gpio11/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio11/value
#sleep $T1

# P111
echo 8 > /sys/class/gpio/export
#sleep $T1
echo out > /sys/class/gpio/gpio12/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio12/value
#sleep $T1

# P119 GPIO11 e-paper back light -- linux-131 -- export gpio13
echo 131 > /sys/class/gpio/export
#sleep $T1
echo out > /sys/class/gpio/gpio13/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio13/value
#sleep $T1

# P109  Camera POWER -- linux-134 -- export gpio14
echo 134 > /sys/class/gpio/export
#sleep $T1
echo out > /sys/class/gpio/gpio14/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio14/value
#sleep $T1

# P112  Card Reader -- linux-506 -- export gpio15
echo 506 > /sys/class/gpio/export
#sleep $T1
echo out > /sys/class/gpio/gpio15/direction
#sleep $T1
#echo 1 > /sys/class/gpio/gpio15/value
#sleep $T1



#**********************************
#          set value
#**********************************
# S41
echo 1 > /sys/class/gpio/gpio1/value
#sleep $T1

# P110
echo 1 > /sys/class/gpio/gpio11/value
#sleep $T1


# P108
echo 1 > /sys/class/gpio/gpio2/value
#sleep $T1

# P117
echo 1 > /sys/class/gpio/gpio3/value
#sleep $T1

# P126
echo 1 > /sys/class/gpio/gpio4/value
#sleep $T1

# S107
echo 1 > /sys/class/gpio/gpio5/value
#sleep $T1

# P111
echo 1 > /sys/class/gpio/gpio12/value
#sleep $T1

# P119
echo 1 > /sys/class/gpio/gpio13/value
#sleep $T1

# P109  Camera POWER -- linux-134 -- export gpio14
echo 1 > /sys/class/gpio/gpio14/value
#sleep $T1

# P112  Card Reader -- linux-506 -- export gpio15
echo 1 > /sys/class/gpio/gpio15/value
#sleep $T1


