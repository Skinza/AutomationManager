on device connected to smartmeter: 
    stty -F /dev/ttyAMA0 9600 -parodd cs7 -cstopb igncr
    cat /dev/ttyAMA0 | nc -l -p 5252

on receiving device start nullmodem and nc data to it
    socat -d -d pty,raw,echo=0 pty,raw,echo=0
    nc 192.168.127.202 5252 > /dev/pts/2

