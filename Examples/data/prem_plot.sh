#!/bin/bash

# In Example directory, run the following first:
# ./Run.sh prem.c

awk 'NR>1 {print $1,$2}' prem_out > vpv.dat
awk 'NR>1 {print $1,$3}' prem_out > vph.dat
awk 'NR>1 {print $1,$4}' prem_out > vsv.dat
awk 'NR>1 {print $1,$5}' prem_out > vsh.dat
awk 'NR>1 {print $1,$6}' prem_out > rho.dat
awk 'NR>1 {print $1,$2}' prem_smoothed_out > vp_smoothed.dat
awk 'NR>1 {print $1,$3}' prem_smoothed_out > vs_smoothed.dat
awk 'NR>1 {print $1,$4}' prem_smoothed_out > rho_smoothed.dat

gmtset GRID_PEN_PRIMARY = 0.1p,200/200/200,-
gmtset ANNOT_FONT_PRIMARY = 12p

psbasemap -JX6i/-9.5i -R0/14/0/3000 -X1.4i -Y1i -P -Ba5f1:"Density purple (kg/m^3)":S -K > PREM.ps
psbasemap -J -R -Ba2f2g2:"Velocities (km/s)":/a500f500g250:"Depth (km)":WNe -O -K >> PREM.ps

psxy rho.dat -: -J -R -m -W2p,purple -O -K >> PREM.ps
psxy vsh.dat -: -J -R -m -W1p,red,. -O -K >> PREM.ps
psxy vph.dat -: -J -R -m -W1p,blue,. -O -K >> PREM.ps
psxy vsv.dat -: -J -R -m -W2p,red -O  -K >> PREM.ps
psxy vpv.dat -: -J -R -m -W2p,blue -O -K >> PREM.ps
psxy rho_smoothed.dat -: -J -R -m -W1p,black,- -O -K >> PREM.ps
psxy vp_smoothed.dat -: -J -R -m -W1p,black,- -O -K >> PREM.ps
psxy vs_smoothed.dat -: -J -R -m -W1p,black,- -O >> PREM.ps

ps2pdf PREM.ps PREM.pdf

rm -f PREM.ps rho.dat vpv.dat vph.dat vsv.dat vsh.dat rho_smoothed.dat vp_smoothed.dat vs_smoothed.dat

exit 0
