#!/usr/bin/env bash
g++ -g p10.cpp p10_func.cpp -o main
sleep .1s
./main P10_input2.txt out2.txt
./main P10_input1.txt out1.txt
