clear all
close all
clc

A=textread('envelope_hilbert_in');
B=textread('envelope_hilbert_out');
C=textread('envelope_hilbert_sac');
y=hilbert(A(:,2));
env=abs(y);

plot(A(:,1),env,'k','linewidth',2);
hold on;
plot(A(:,1),A(:,2),C(:,1),C(:,2),B(:,1),B(:,2));
legend('MATLAB_1','Original','SAC','C');
title('Comparison');
xlim([-5 5]);
