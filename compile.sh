#!/bin/bash

g++ *.cpp -o model
#g++ *.cpp -DTRACE -o model
test $? -eq 0 && clear
