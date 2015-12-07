#!/bin/bash
for p in 1 2 4 8 16 32;
	do
	export OMP_NUM_THREADS=$p
	for i in `seq 1 $2`;
		do
			./$1 $3 $4
		done
	done