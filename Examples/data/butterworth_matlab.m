clear all
close all
clc

delta=0.01;
npts=1000;
t=(0:npts-1)*delta;

A=textread('butterworth_infile');

SAC_LP=textread('butterworth_lp_SAC');
SAC_BP=textread('butterworth_bp_SAC');
SAC_HP=textread('butterworth_hp_SAC');

C_LP=textread('butterworth_lp_C');
C_HP=textread('butterworth_hp_C');
C_BP=textread('butterworth_bp_C');

subplot(3,1,1);
scatter(t,SAC_LP,'bo');
hold on;
scatter(t,C_LP,'g*');
legend('LP, SAC','LP, C');

subplot(3,1,2);
scatter(t,SAC_BP,'bo');
hold on;
scatter(t,C_BP,'g*');
legend('BP, SAC','BP, C');

subplot(3,1,3);
scatter(t,SAC_HP,'bo');
hold on;
scatter(t,C_HP,'g*');
legend('HP, SAC','HP, C');
