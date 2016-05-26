clear all
close all
clc

delta=0.01;
npts=1000;

A=textread('wiginterpd_infile');
B=textread('wiginterpd_out_C');
C=textread('wiginterpd_out_SAC');
t=(0:npts-1)*delta;

plot(t,A);
hold on;
scatter(B(:,1),B(:,2),'g*');
scatter(B(:,1),C,'ro');
legend('Original','C','SAC');
