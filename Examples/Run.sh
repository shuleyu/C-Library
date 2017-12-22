#!/bin/bash

if [ $# -ne 1 ] || ! [ -e $1 ]
then
    echo "Usage: input c code as \$1."
    exit 1;
fi

SRCDIR=${PWD}
CCODEDIR=${HOME}/Research/Fun.C.c002
INCLUDE="-I${CCODEDIR} -I${SACHOME}/include -I/opt/local/include -I/usr/include"
LIBDIR="-L${CCODEDIR} -L${SACHOME}/lib -L/opt/local/lib"
LIBs="-lASU_tools -lsac -lsacio -lgsl -lgslcblas -lfftw3 -lm "

cd ${CCODEDIR}
make
cd ${SRCDIR}

# ======== Compile c code ========

gcc -Wall -Wimplicit $1 ${INCLUDE} ${LIBDIR} ${LIBs}
 

# ======== Run c code ========
if [ $? -ne 0 ]
then
    echo "$1 compile failed ..."
    exit 1
fi

time ./a.out

exit 0
