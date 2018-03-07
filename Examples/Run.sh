#!/bin/bash

set -e

if [ $# -ne 1 ] || ! [ -e $1 ]
then
    echo "Usage: input c code as \$1."
    exit 1;
fi

SRCDIR=${PWD}
CCODEDIR=${PWD}/..
INCLUDE="-I${CCODEDIR} -I${SACHOME}/include -I/opt/local/include -I/usr/include"
LIBDIR="-L${CCODEDIR} -L${SACHOME}/lib -L/opt/local/lib"
LIBs="-lASU_tools -lsac -lsacio -lgsl -lgslcblas -lfftw3 -lm "

cd ${CCODEDIR}
make
cd ${SRCDIR}

# ======== Compile c code ========

gcc -fPIC -Wall -Wimplicit $1 ${INCLUDE} ${LIBDIR} ${LIBs}
 
# ======== Run c code ========

time ./a.out
echo ""

rm -f a.out

exit 0
