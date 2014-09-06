#!/bin/bash
g++ *.cpp -o model
test $? -eq 0 && clear
