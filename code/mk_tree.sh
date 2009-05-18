#!/bin/sh
# This script generates the missing dirs for the project

# OBJ_DIR is in Makefile
OBJ_DIR=$(grep "^ODIR" Makefile | cut -f 2 -d "=");

echo ">>> Making dirs";

for i in $OBJ_DIR
do
    if [[ -e $i ]]
    then
	echo ">>> $i is ready :P";
    else
	echo ">>> Creating $i";
	mkdir $i;
    fi
done;

echo ">>> End";

# EOF
