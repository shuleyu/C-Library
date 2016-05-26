clear all
close all
clc

bootN=5000;
nptsx=1000;
nptsy=100;

A=textread('bootstrap_in');
Clean=textread('bootstrap_clean_signal');
A=A(:,1:end-1);
Clean=Clean(:,1:end-1);

B_C=textread('bootstrap_out');
STD_C=textread('bootstrap_out_std');

B_M=bootstrp(bootN,@mean,A);
for i=1:nptsy
    STD_M(i)=std(B_M(:,i));
end

Mean_C=mean(B_C);
Mean_M=mean(B_M);

ax1=subplot(4,1,1);
plot(Mean_C,'k');
hold on
plot(Mean_C+STD_C);
plot(Mean_C-STD_C);


ax2=subplot(4,1,2);
plot(Mean_M,'k');
hold on
plot(Mean_M+STD_M);
plot(Mean_M-STD_M);

ax3=subplot(4,1,3);
plot(mean(A),'k');
hold on
plot(mean(A)+std(A));
plot(mean(A)-std(A));

ax4=subplot(4,1,4);
plot(Clean,'k');

linkaxes([ax1,ax2,ax3,ax4],'xy');
