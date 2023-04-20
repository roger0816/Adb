#!/bin/sh

#cd ../src/AdbServer/
#qmake AdbServer.pro
#make clean
#make

cd bin/
./AdbServerUnix 6000 10.130.0.8 adp
