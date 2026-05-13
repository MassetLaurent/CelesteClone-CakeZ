#!/bin/bash

libs=-luser32
warnings=-Wno-writable-strings

clang++ -g src/main.cpp -oCeleste.exe $libs $warnings