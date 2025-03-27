#!/bin/sh

#cd ../src/AdbServer/
#qmake AdbServer.pro
#make clean
#make

cd bin/

killall AdbServerUnix

killall AdbApi

./AdbServerUnix 6003 172.104.117.7 adp &

./AdbApi 7001 127.0.0.1 6003 &
