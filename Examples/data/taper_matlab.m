clear all
close all
clc

delta=0.01;
npts=1000;

A=textread('taper_infile');
B=textread('taper_out');
C=textread('taper_out_sac');
t=(0:npts-1)*delta;

scatter(t,A,'bo');
hold on;
scatter(t,B,'*');
scatter(t,C,'go');
legend('Original','C','SAC');
