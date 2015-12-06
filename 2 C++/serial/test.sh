#!/bin/bash

for i in `seq 1 $1`;
	do
		./serial $2 $3
	done
