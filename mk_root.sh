#!/bin/csh
set key=${1}

./bin/AC_ana1 -f replay_rootfiles/hkstest_ac2_ch$key.root -w rootfiles/ac2_ch$key.root -p param/AC2_seg$key.param 