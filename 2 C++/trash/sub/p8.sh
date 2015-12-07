#!/bin/csh
#PBS -l nodes=1:ppn=15
#  nodes must be 1, will fail if it is not
#  ppn must be a multiple of 15, because Greenfield processors each contain 15 cores
#PBS -l walltime=1:00
#  Combine standard output and error into one file
#PBS -j oe
#PBS -q batch
cd $HOME/parallel
#run my executable
setenv OMP_NUM_THREADS 8

set i = 0
while ($i < 15)
    ./naive 129 11
    ./lookahead 129 11
end
