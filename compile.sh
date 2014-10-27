#!/bin/bash

g++ *.cpp -DBUILDSCENARIO2 -DACTIVITYSCENARIO1 -fpermissive -lgraph -L/usr/local/lib -lX11 -o model
#g++ *.cpp -DBUILDSCENARIO1 -DTRACE -fpermissive -DTEST -g -pedantic -Wall -Wextra -lgraph -L/usr/local/lib -lX11 -o model
test $? -eq 0 && clear
echo "Don\`t forget to create \"outputFolder\" as an output folder in directory where you run program\n"

#define BUILDSCENARIO1
#define BUILDSCENARIO2
#define ACTIVITYSCENARIO1
#define TRACE
#define TEST
