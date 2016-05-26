clear all
close all
clc

A=textread('read_sac_out_C');
B=textread('read_sac_out_SAC');

subplot(2,1,1);
hold on;
scatter(A(:,1),A(:,2),'bo');
scatter(B(:,1),B(:,2),'g*');
legend('C','SAC');

subplot(2,1,2);
hold on;
scatter(A(:,3),A(:,4),'bo');
scatter(B(:,3),B(:,4),'g*');
legend('C','SAC');
