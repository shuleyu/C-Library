#!/bin/bash

sac >/dev/null << EOF
fg seis
w alpha tmpfile.txt
interp npts 4996
w alpha tmpfile1.txt
q
EOF

awk 'NR>30 {print $1"\n"$2"\n"$3"\n"$4"\n"$5}' tmpfile.txt > tmpfile_$$
sed '/^\s*$/d' tmpfile_$$ > wiginterpd_infile

awk 'NR>30 {print $1"\n"$2"\n"$3"\n"$4"\n"$5}' tmpfile1.txt > tmpfile_$$
sed '/^\s*$/d' tmpfile_$$ > wiginterpd_out_SAC

rm -f tmpfile*

exit 0
