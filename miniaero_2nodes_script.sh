#!/bin/bash

echo "GHC"

mpirun -np 2 -H n0000,n0001 --bind-to none -x LD_LIBRARY_PATH miniaero_GHC -ll:cpu 4 -ll:gpu 2 -ll:csize 15000 -ll:fsize 6000 -ll:zsize 15000 -ll:rsize 0 -nblocks 8 -mesh 8x32x1000 -x_length 1 -y_length 0.2 -z_length 2 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 5 -output_frequency 5

#echo "BEAM"

#mpirun -np 2 -H n0000,n0001 --bind-to none -x LD_LIBRARY_PATH miniaero_BM -ll:cpu 4 -ll:gpu 2 -ll:csize 15000 -ll:fsize 6000 -ll:zsize 15000 -ll:rsize 0 -nblocks 8 -mesh 8x32x1000 -x_length 1 -y_length 0.2 -z_length 2 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 5 -output_frequency 5

echo "GSM GOOD"

mpirun -np 2 -H n0000,n0001 --bind-to none -x LD_LIBRARY_PATH miniaero_GSM -ll:cpu 4 -ll:gpu 2 -ll:csize 15000 -ll:fsize 6000 -ll:zsize 15000 -ll:rsize 0 -nblocks 8 -mesh 8x32x1000 -x_length 1 -y_length 0.2 -z_length 2 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 5 -output_frequency 5 -gsm:max_batch_size 100

echo "GSM BAD"

mpirun -np 2 -H n0000,n0001 --bind-to none -x LD_LIBRARY_PATH miniaero_GSM -ll:cpu 4 -ll:gpu 2 -ll:csize 15000 -ll:fsize 6000 -ll:zsize 15000 -ll:rsize 0 -nblocks 8 -mesh 8x32x1000 -x_length 1 -y_length 0.2 -z_length 2 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 5 -output_frequency 5 -gsm:bad -gsm:max_batch_size 100

echo "SAMPLE"

mpirun -np 2 -H n0000,n0001 --bind-to none -x LD_LIBRARY_PATH miniaero_SAMPLE -ll:cpu 4 -ll:gpu 2 -ll:csize 15000 -ll:fsize 6000 -ll:zsize 15000 -ll:rsize 0 -nblocks 8 -mesh 8x32x1000 -x_length 1 -y_length 0.2 -z_length 2 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 5 -output_frequency 5 -sm:samples 100

echo "VBS"

mpirun -np 2 -H n0000,n0001 --bind-to none -x LD_LIBRARY_PATH miniaero_VBS -vm:bad -ll:cpu 4 -ll:gpu 2 -ll:csize 15000 -ll:fsize 6000 -ll:zsize 15000 -ll:rsize 0 -nblocks 8 -mesh 8x32x1000 -x_length 1 -y_length 0.2 -z_length 2 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 5 -output_frequency 5

echo "VARIANCE"

mpirun -np 2 -H n0000,n0001 --bind-to none -x LD_LIBRARY_PATH miniaero_VBS -ll:cpu 4 -ll:gpu 2 -ll:csize 15000 -ll:fsize 6000 -ll:zsize 15000 -ll:rsize 0 -nblocks 8 -mesh 8x32x1000 -x_length 1 -y_length 0.2 -z_length 2 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 5 -output_frequency 5
