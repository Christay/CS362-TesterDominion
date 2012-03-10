#!/bin/bash

make clean
make all
./playdom 44 > test1
./playdom 33 > test2
./playdom 22 > test3 
