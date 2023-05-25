#!/bin/sh

#cd ../src/AdbServer/
#qmake AdbServer.pro
#make clean
#make

cd bin/
./AdbServerUnix 6003 10.130.0.9 adbTest
