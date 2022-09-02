#!/bin/bash

set -eu

binfolder=$1
method=$2
iters=$3
lmbda=$4
patchsz=$5
numscales=$6
coarsest_scale_factor=$7
confidence_decay=$8
confidence_asymptotic=$9 
initialization_type=${10}
offsets=${11}
pyr=${12}  
input=${13}
mask=${14}
output=${15}
input_mask=${16}

# merge the painted and the input mask

if [ -f "$input_mask" ]; then
   python3 $binfolder/merge_mask.py $input_mask $mask $mask
   echo "merging input mask with the drawn one"
fi

$binfolder/Inpainting -method $method -iters $iters -lambda $lmbda -patch $patchsz -scales $numscales -coarse $coarsest_scale_factor -conft $confidence_decay -confa $confidence_asymptotic -init $initialization_type -shownnf $offsets -showpyr $pyr   $input $mask $output 

