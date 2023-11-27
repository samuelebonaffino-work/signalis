#!/bin/bash

# Set the compiler
CC=gcc

# Set compiler flags
CFLAGS="-std=c11 -Wall"

# Set the source folder
SRC_FOLDER=src

# Set the output folder
OUTPUT_FOLDER=build

# Create the output folder if it doesn't exist
mkdir -p $OUTPUT_FOLDER
rm -f $OUTPUT_FOLDER/*

# Compile the project using make
$CC $CFLAGS -I$SRC_FOLDER $SRC_FOLDER/*.c -o $OUTPUT_FOLDER/signalis -lm


echo
echo "*******************************************"
echo "** Build task completed (build/signalis) **"
echo "*******************************************"
echo
