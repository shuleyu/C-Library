clear all
close all
clc

A=textread('gaussblur_1d_infile');
B=textread('gaussblur_1d_out1');
C=textread('gaussblur_1d_out2');

subplot(2,1,1);
plot(A(:,1),B);

delta=0.025;
mu=0;
sigma=1;
gwidth=100;

NPTS=2*ceil(gwidth/2/delta)+1;
END=floor(NPTS/2);
for count=1:END
    x(count)=mu-delta*(END-count+1);
    x(NPTS+1-count)=2*mu-x(count);
end
x(ceil(NPTS/2))=mu;

gaussFilter=gaussmf(x,[sigma,0]);
D=conv(B(:,1),gaussFilter,'same');
D=D/max(abs(D));

subplot(2,1,2);
hold on
plot(A(:,1),C);
plot(A(:,1),D,'r');
legend('C','Matlab');
