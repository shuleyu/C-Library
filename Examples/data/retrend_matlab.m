clear all
close all
clc

delta=0.01;
npts=1000;

A=textread('retrend_infile');
B=textread('retrend_out');
t=(0:npts-1)*delta;

subplot(2,1,1);
plot(t,A);
grid on
ylim([-2,2]);
legend('Input');

p=polyfit(t(:),A(:),1);
C=A(:)-p(1)*t(:)-p(2);

subplot(2,1,2);
hold on;
scatter(t,C,'b*');
scatter(t,C,'go');
grid on
ylim([-2,2]);
legend('C','Matlab');
