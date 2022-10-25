#!/bin/sh

cd libs/RpkLib/src/core
qmake RpkCore.pro
make

cd ../../../../src/AdbServer/
qmake AdbServer.pro
make clean
make

cd ../../bin
./AdbServerUnix
