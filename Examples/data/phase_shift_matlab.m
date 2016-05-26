clear all
close all
clc

delta=0.0025;

A=textread('phase_shift_in');
B=textread('phase_shift_out');
C=hilbert(A(:,2));

subplot(2,1,1);
plot(A(:,1),A(:,2));
title('Original');

subplot(2,1,2);
hold on;
%plot(B(:,1),B(:,2),B(:,1),imag(C)/max(imag(C)));
plot(B(:,1),B(:,2));
scatter(B(:,1),imag(C));
legend('C','MATLAB');
title('Hilbert');
