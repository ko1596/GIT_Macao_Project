#!/bin/bash

while true; do
	ls -l /sys/class/gpio
	echo "__________ __________ __________ __________"
	ifconfig uap0 | grep  "inet addr"
	ps -aux | grep Ta53
	#pidof -s Ta5321_ALL 
	
	date
	sleep 1
done

exit 0
