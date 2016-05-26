clear all
close all
clc

delta=0.025;
sigma=2;
gwidth=50;
NPTS=gwidth/delta;
df=1/gwidth;

A=textread('freq_amp_phase_in');
B=textread('freq_amp_phase_freq_AMP_Phase');
B(:,2)=B(:,2)/max(B(:,2));

L=length(B(:,1));

C=fft(A(:,2));
C=C/max(abs(C));

subplot(2,1,1);
scatter(B(:,1),B(:,2),'*');
hold on
scatter(B(:,1),abs(C(1:L)));
title('AMP');
legend('C','MATLAB');
xlim([0,1]);

subplot(2,1,2);
scatter(B(:,1),B(:,3),'*');
hold on
scatter(B(:,1),angle(C(1:L)));
title('Phase');
legend('C','MATLAB');
xlim([0,1]);
