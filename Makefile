
CC = gcc
FLAGS = -Wall -Wimplicit
COMP = $(CC) $(FLAGS)

SACHOME = /opt/sac
INCLUDE = -I. -I$(SACHOME)/include -I/opt/local/include

all: libASU_tools.a
	@echo > /dev/null

libASU_tools.a: amplitude.fun.o binary_search.fun.o bootstrap.fun.o bottom_depth.fun.o bottom_location.fun.o cart2sph.fun.o cbin_update.fun.o cc.fun.o cmt2tp.fun.o complex_divide.fun.o confidence.fun.o convolve.fun.o ellipcor_kennett.fun.o envelope_hilbert.fun.o filenr.fun.o findjunction.fun.o findrayp.fun.o freq_amp_phase.fun.o gaussblur.fun.o gaussian.fun.o gcpdistance.fun.o interp_linear.fun.o ll2tp.fun.o mean.fun.o minmax.fun.o mixing.fun.o mollifier.fun.o normalize.fun.o combination.fun.o phase_shift.fun.o pick_onset.fun.o p_norm.fun.o prem.fun.o rad_pat.fun.o ramp_function.fun.o random.fun.o rayp2takeoff.fun.o ray_path.fun.o read_sac.fun.o retrend.fun.o reverse_array.fun.o shift_array.fun.o shift_stack.fun.o simpsonx.fun.o snr.fun.o sort_quick.fun.o sph2cart.fun.o sphdist.fun.o std.fun.o std_weight.fun.o taper.fun.o tp2ll.fun.o tpangle.fun.o union_sets.fun.o waterlevel_decon.fun.o waypoint.fun.o wiginterp.fun.o sum.fun.o butterworth.fun.o graycode.fun.o crossproduct.fun.o points_in_polygon.fun.o meshing.fun.o redirection.fun.o gmttrans.fun.o lon2360.fun.o lon2180.fun.o print_2d_array.fun.o tstar.fun.o findpeak.fun.o StretchTrace.fun.o SignalCompare.fun.o derivative.fun.o
	ar cr libASU_tools.a amplitude.fun.o binary_search.fun.o bootstrap.fun.o bottom_depth.fun.o bottom_location.fun.o cart2sph.fun.o cbin_update.fun.o cc.fun.o cmt2tp.fun.o complex_divide.fun.o confidence.fun.o convolve.fun.o ellipcor_kennett.fun.o envelope_hilbert.fun.o filenr.fun.o findjunction.fun.o findrayp.fun.o freq_amp_phase.fun.o gaussblur.fun.o gaussian.fun.o gcpdistance.fun.o interp_linear.fun.o ll2tp.fun.o mean.fun.o minmax.fun.o mixing.fun.o mollifier.fun.o normalize.fun.o combination.fun.o phase_shift.fun.o pick_onset.fun.o p_norm.fun.o prem.fun.o rad_pat.fun.o ramp_function.fun.o random.fun.o rayp2takeoff.fun.o ray_path.fun.o read_sac.fun.o retrend.fun.o reverse_array.fun.o shift_array.fun.o shift_stack.fun.o simpsonx.fun.o snr.fun.o sort_quick.fun.o sph2cart.fun.o sphdist.fun.o std.fun.o std_weight.fun.o taper.fun.o tp2ll.fun.o tpangle.fun.o union_sets.fun.o waterlevel_decon.fun.o waypoint.fun.o wiginterp.fun.o sum.fun.o butterworth.fun.o graycode.fun.o crossproduct.fun.o points_in_polygon.fun.o meshing.fun.o redirection.fun.o gmttrans.fun.o lon2360.fun.o lon2180.fun.o print_2d_array.fun.o tstar.fun.o findpeak.fun.o StretchTrace.fun.o SignalCompare.fun.o derivative.fun.o

amplitude.fun.o: amplitude.fun.c ASU_tools.h
	$(COMP) -c amplitude.fun.c $(INCLUDE)
binary_search.fun.o: binary_search.fun.c ASU_tools.h
	$(COMP) -c binary_search.fun.c $(INCLUDE)
bootstrap.fun.o: bootstrap.fun.c ASU_tools.h
	$(COMP) -c bootstrap.fun.c $(INCLUDE)
bottom_depth.fun.o: bottom_depth.fun.c ASU_tools.h
	$(COMP) -c bottom_depth.fun.c $(INCLUDE)
bottom_location.fun.o: bottom_location.fun.c ASU_tools.h
	$(COMP) -c bottom_location.fun.c $(INCLUDE)
cart2sph.fun.o: cart2sph.fun.c ASU_tools.h
	$(COMP) -c cart2sph.fun.c $(INCLUDE)
cbin_update.fun.o: cbin_update.fun.c ASU_tools.h
	$(COMP) -c cbin_update.fun.c $(INCLUDE)
cc.fun.o: cc.fun.c ASU_tools.h
	$(COMP) -c cc.fun.c $(INCLUDE)
cmt2tp.fun.o: cmt2tp.fun.c ASU_tools.h
	$(COMP) -c cmt2tp.fun.c $(INCLUDE)
complex_divide.fun.o: complex_divide.fun.c ASU_tools.h
	$(COMP) -c complex_divide.fun.c $(INCLUDE)
confidence.fun.o: confidence.fun.c ASU_tools.h
	$(COMP) -c confidence.fun.c $(INCLUDE)
convolve.fun.o: convolve.fun.c ASU_tools.h
	$(COMP) -c convolve.fun.c $(INCLUDE)
ellipcor_kennett.fun.o: ellipcor_kennett.fun.c ASU_tools.h
	$(COMP) -c ellipcor_kennett.fun.c $(INCLUDE)
envelope_hilbert.fun.o: envelope_hilbert.fun.c ASU_tools.h
	$(COMP) -c envelope_hilbert.fun.c $(INCLUDE)
filenr.fun.o: filenr.fun.c ASU_tools.h
	$(COMP) -c filenr.fun.c $(INCLUDE)
findjunction.fun.o: findjunction.fun.c ASU_tools.h
	$(COMP) -c findjunction.fun.c $(INCLUDE)
findrayp.fun.o: findrayp.fun.c ASU_tools.h
	$(COMP) -c findrayp.fun.c $(INCLUDE)
freq_amp_phase.fun.o: freq_amp_phase.fun.c ASU_tools.h
	$(COMP) -c freq_amp_phase.fun.c $(INCLUDE)
gaussblur.fun.o: gaussblur.fun.c ASU_tools.h
	$(COMP) -c gaussblur.fun.c $(INCLUDE)
gaussian.fun.o: gaussian.fun.c ASU_tools.h
	$(COMP) -c gaussian.fun.c $(INCLUDE)
gcpdistance.fun.o: gcpdistance.fun.c ASU_tools.h
	$(COMP) -c gcpdistance.fun.c $(INCLUDE)
interp_linear.fun.o: interp_linear.fun.c ASU_tools.h
	$(COMP) -c interp_linear.fun.c $(INCLUDE)
ll2tp.fun.o: ll2tp.fun.c ASU_tools.h
	$(COMP) -c ll2tp.fun.c $(INCLUDE)
mean.fun.o: mean.fun.c ASU_tools.h
	$(COMP) -c mean.fun.c $(INCLUDE)
minmax.fun.o: minmax.fun.c ASU_tools.h
	$(COMP) -c minmax.fun.c $(INCLUDE)
mixing.fun.o: mixing.fun.c ASU_tools.h
	$(COMP) -c mixing.fun.c $(INCLUDE)
mollifier.fun.o: mollifier.fun.c ASU_tools.h
	$(COMP) -c mollifier.fun.c $(INCLUDE)
normalize.fun.o: normalize.fun.c ASU_tools.h
	$(COMP) -c normalize.fun.c $(INCLUDE)
combination.fun.o: combination.fun.c ASU_tools.h
	$(COMP) -c combination.fun.c $(INCLUDE)
phase_shift.fun.o: phase_shift.fun.c ASU_tools.h
	$(COMP) -c phase_shift.fun.c $(INCLUDE)
pick_onset.fun.o: pick_onset.fun.c ASU_tools.h
	$(COMP) -c pick_onset.fun.c $(INCLUDE)
p_norm.fun.o: p_norm.fun.c ASU_tools.h
	$(COMP) -c p_norm.fun.c $(INCLUDE)
prem.fun.o: prem.fun.c ASU_tools.h
	$(COMP) -c prem.fun.c $(INCLUDE)
rad_pat.fun.o: rad_pat.fun.c ASU_tools.h
	$(COMP) -c rad_pat.fun.c $(INCLUDE)
ramp_function.fun.o: ramp_function.fun.c ASU_tools.h
	$(COMP) -c ramp_function.fun.c $(INCLUDE)
random.fun.o: random.fun.c ASU_tools.h
	$(COMP) -c random.fun.c $(INCLUDE)
rayp2takeoff.fun.o: rayp2takeoff.fun.c ASU_tools.h
	$(COMP) -c rayp2takeoff.fun.c $(INCLUDE)
ray_path.fun.o: ray_path.fun.c ASU_tools.h
	$(COMP) -c ray_path.fun.c $(INCLUDE)
read_sac.fun.o: read_sac.fun.c ASU_tools.h
	$(COMP) -c read_sac.fun.c $(INCLUDE)
retrend.fun.o: retrend.fun.c ASU_tools.h
	$(COMP) -c retrend.fun.c $(INCLUDE)
reverse_array.fun.o: reverse_array.fun.c ASU_tools.h
	$(COMP) -c reverse_array.fun.c $(INCLUDE)
shift_array.fun.o: shift_array.fun.c ASU_tools.h
	$(COMP) -c shift_array.fun.c $(INCLUDE)
shift_stack.fun.o: shift_stack.fun.c ASU_tools.h
	$(COMP) -c shift_stack.fun.c $(INCLUDE)
simpsonx.fun.o: simpsonx.fun.c ASU_tools.h
	$(COMP) -c simpsonx.fun.c $(INCLUDE)
snr.fun.o: snr.fun.c ASU_tools.h
	$(COMP) -c snr.fun.c $(INCLUDE)
sort_quick.fun.o: sort_quick.fun.c ASU_tools.h
	$(COMP) -c sort_quick.fun.c $(INCLUDE)
sph2cart.fun.o: sph2cart.fun.c ASU_tools.h
	$(COMP) -c sph2cart.fun.c $(INCLUDE)
sphdist.fun.o: sphdist.fun.c ASU_tools.h
	$(COMP) -c sphdist.fun.c $(INCLUDE)
std.fun.o: std.fun.c ASU_tools.h
	$(COMP) -c std.fun.c $(INCLUDE)
std_weight.fun.o: std_weight.fun.c ASU_tools.h
	$(COMP) -c std_weight.fun.c $(INCLUDE)
taper.fun.o: taper.fun.c ASU_tools.h
	$(COMP) -c taper.fun.c $(INCLUDE)
tp2ll.fun.o: tp2ll.fun.c ASU_tools.h
	$(COMP) -c tp2ll.fun.c $(INCLUDE)
tpangle.fun.o: tpangle.fun.c ASU_tools.h
	$(COMP) -c tpangle.fun.c $(INCLUDE)
union_sets.fun.o: union_sets.fun.c ASU_tools.h
	$(COMP) -c union_sets.fun.c $(INCLUDE)
waterlevel_decon.fun.o: waterlevel_decon.fun.c ASU_tools.h
	$(COMP) -c waterlevel_decon.fun.c $(INCLUDE)
waypoint.fun.o: waypoint.fun.c ASU_tools.h
	$(COMP) -c waypoint.fun.c $(INCLUDE)
wiginterp.fun.o: wiginterp.fun.c ASU_tools.h
	$(COMP) -c wiginterp.fun.c $(INCLUDE)
sum.fun.o: sum.fun.c ASU_tools.h
	$(COMP) -c sum.fun.c $(INCLUDE)
butterworth.fun.o: butterworth.fun.c ASU_tools.h
	$(COMP) -c butterworth.fun.c $(INCLUDE)
graycode.fun.o: graycode.fun.c ASU_tools.h
	$(COMP) -c graycode.fun.c $(INCLUDE)
crossproduct.fun.o: crossproduct.fun.c ASU_tools.h
	$(COMP) -c crossproduct.fun.c $(INCLUDE)
points_in_polygon.fun.o: points_in_polygon.fun.c ASU_tools.h
	$(COMP) -c points_in_polygon.fun.c $(INCLUDE)
meshing.fun.o: meshing.fun.c ASU_tools.h
	$(COMP) -c meshing.fun.c $(INCLUDE)
redirection.fun.o: redirection.fun.c ASU_tools.h
	$(COMP) -c redirection.fun.c $(INCLUDE)
gmttrans.fun.o: gmttrans.fun.c ASU_tools.h
	$(COMP) -c gmttrans.fun.c $(INCLUDE)
lon2360.fun.o: lon2360.fun.c ASU_tools.h
	$(COMP) -c lon2360.fun.c $(INCLUDE)
lon2180.fun.o: lon2180.fun.c ASU_tools.h
	$(COMP) -c lon2180.fun.c $(INCLUDE)
print_2d_array.fun.o: print_2d_array.fun.c ASU_tools.h
	$(COMP) -c print_2d_array.fun.c $(INCLUDE)
tstar.fun.o: tstar.fun.c ASU_tools.h
	$(COMP) -c tstar.fun.c $(INCLUDE)
findpeak.fun.o: findpeak.fun.c ASU_tools.h
	$(COMP) -c findpeak.fun.c $(INCLUDE)
StretchTrace.fun.o: StretchTrace.fun.c ASU_tools.h
	$(COMP) -c StretchTrace.fun.c $(INCLUDE)
SignalCompare.fun.o: SignalCompare.fun.c ASU_tools.h
	$(COMP) -c SignalCompare.fun.c $(INCLUDE)
derivative.fun.o: derivative.fun.c ASU_tools.h
	$(COMP) -c derivative.fun.c $(INCLUDE)

clean:
	rm -f *.fun.o libASU_tools.a
