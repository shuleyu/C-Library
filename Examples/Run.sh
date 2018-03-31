#!/bin/bash

[ $# -ne 1 ] || ! [ -e $1 ] && echo "Usage: input c code as \$1." && exit 1;
CodeName=$1

SRCDIR=${PWD}
CCODEDIR=${PWD}/..
cd ${CCODEDIR}
make examples
[ $? -ne 0 ] && exit 1

cd ${SRCDIR}
time ./${CodeName%c}out

echo ""

exit 0
