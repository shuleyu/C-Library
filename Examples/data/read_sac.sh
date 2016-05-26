#!/bin/bash

# This script makes read_sac_out_SAC.

rm -f sac.macro
delta="0.01"

count=0
while read file
do
    count=$((count+1))
    cat >> sac.macro << EOF
cut off
r ${file}
interp delta ${delta}
w sac tmpfile.sac
cut t9 -200 50
r tmpfile.sac
rtr
taper type hanning width 0.02
bp butter co 0.02 0.3 n 2 p 2
lh b
w alpha tmpfile_${count}.txt
EOF


done << EOF
200608250044.CN.LMN.BHT.sac
200608250044.TA.X13A.BHT.sac
EOF

sac > sac.output << EOF
m sac.macro
q
EOF

rm -f read_sac_out_SAC
for count in 1 2
do
    B=`grep "b =" sac.output | awk -v C=${count} 'NR==C {printf "%.4lf",$3}'`
    awk 'NR>30 {print $1"\n"$2"\n"$3"\n"$4"\n"$5}' tmpfile_${count}.txt > tmpfile_$$
    if ! [ -e read_sac_out_SAC ]
    then
        sed '/^\s*$/d' tmpfile_$$ > read_sac_out_SAC

		NR=`wc -l < read_sac_out_SAC`
		E=`echo "${B} ${NR} ${delta}" | awk '{printf "%.4lf",$1+($2-1)*$3}'`
		seq ${B} ${delta} ${E} > tmpfile1_$$

		paste tmpfile1_$$ read_sac_out_SAC > tmpfile_$$
		mv tmpfile_$$ read_sac_out_SAC
    else
        sed '/^\s*$/d' tmpfile_$$ > tmpfile1_$$

		NR=`wc -l < tmpfile1_$$`
		E=`echo "${B} ${NR} ${delta}" | awk '{printf "%.4lf",$1+($2-1)*$3}'`
		seq ${B} ${delta} ${E} > tmpfile_$$

        paste read_sac_out_SAC tmpfile_$$ tmpfile1_$$ > tmpfile2_$$
        mv tmpfile2_$$ read_sac_out_SAC
    fi
done

cat sac.output

rm -f sac.macro sac.output tmpfile*

exit 0
