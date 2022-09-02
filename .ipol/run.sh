#!/bin/bash
#/*
# * Copyright (c) 2020, Mariano Rodriguez <rdguez.mariano@gmail.com>
# * All rights reserved.
# *
# * This program is free software: you can use, modify and/or
# * redistribute it under the terms of the GNU General Public
# * License as published by the Free Software Foundation, either
# * version 3 of the License, or (at your option) any later
# * version. You should have received a copy of this license along
# * this program. If not, see <http://www.gnu.org/licenses/>.
# */

set -eu

binfolder=$1
input0="input_0.png"
input1="input_1.png"
gfilter=$2
aid_thres=$3
hardnet_thres=$4
detector=$5
descriptor=$6
ransac_iters=$7
precision=${8}
affmaps=${9}

python3 $binfolder/main.py --im1 $input0 --im2 $input1 --gfilter $gfilter --aid_thres $aid_thres --hardnet_thres $hardnet_thres --detector $detector --descriptor $descriptor --workdir "./" --bindir $binfolder --visual --ransac_iters $ransac_iters --precision $precision --affmaps $affmaps

