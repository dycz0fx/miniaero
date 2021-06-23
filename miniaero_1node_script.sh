#!/bin/bash

#echo "GHC"

#./regent.py examples/miniaero.rg -ll:cpu 8 -ll:gpu 2 -nblocks 10 -mesh 8x8x3000 -x_length 2 -y_length 0.2 -z_length 1 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 3 -output_frequency 3 -ll:rsize 0 -ll:zsize 15000 -ll:csize 15000 -ll:fsize 6000

#echo "BEAM"

#./regent.py examples/miniaero_beam.rg -ll:cpu 8 -ll:gpu 2 -nblocks 10 -mesh 8x8x3000 -x_length 2 -y_length 0.2 -z_length 1 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 3 -output_frequency 4 -ll:rsize 0 -ll:zsize 15000 -ll:csize 15000 -ll:fsize 6000

echo "BEAM constrained"

./regent.py examples/miniaero_beam.rg -ll:cpu 8 -ll:gpu 2 -nblocks 10 -mesh 8x8x3000 -x_length 2 -y_length 0.2 -z_length 1 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 3 -output_frequency 4 -ll:rsize 0 -ll:zsize 15000 -ll:csize 15000 -ll:fsize 6000 -bm:constrained

#echo "GSM GOOD"

#./regent.py examples/miniaero_gsm.rg -gsm:max_batch_size 100 -ll:cpu 8 -ll:gpu 2 -nblocks 10 -mesh 8x8x3000 -x_length 2 -y_length 0.2 -z_length 1 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 3 -output_frequency 4 -ll:rsize 0 -ll:zsize 15000 -ll:csize 15000 -ll:fsize 6000

#echo "GSM BAD"

#./regent.py examples/miniaero_gsm.rg -gsm:bad -gsm:max_batch_size 100 -ll:cpu 8 -ll:gpu 2 -nblocks 10 -mesh 8x8x3000 -x_length 2 -y_length 0.2 -z_length 1 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 3 -output_frequency 4 -ll:rsize 0 -ll:zsize 15000 -ll:csize 15000 -ll:fsize 6000

#echo "SAMPLE"

#./regent.py examples/miniaero_sample.rg -sm:samples 100 -ll:cpu 8 -ll:gpu 2 -nblocks 10 -mesh 8x8x3000 -x_length 2 -y_length 0.2 -z_length 1 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 3 -output_frequency 4 -ll:rsize 0 -ll:zsize 15000 -ll:csize 15000 -ll:fsize 6000

echo "VBS"

./regent.py examples/miniaero_vbs.rg -vm:bad -ll:cpu 8 -ll:gpu 2 -nblocks 10 -mesh 8x8x3000 -x_length 2 -y_length 0.2 -z_length 1 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 3 -output_frequency 4 -ll:rsize 0 -ll:zsize 15000 -ll:csize 15000 -ll:fsize 6000

#echo "VARIANCE"

#./regent.py examples/miniaero_vbs.rg --ll:cpu 8 -ll:gpu 2 -nblocks 10 -mesh 8x8x3000 -x_length 2 -y_length 0.2 -z_length 1 -ramp 0 -dt 1e-8 -viscous -second_order -time_steps 3 -output_frequency 3 -ll:rsize 0 -ll:zsize 15000 -ll:csize 15000 -ll:fsize 6000
