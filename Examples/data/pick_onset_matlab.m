close all
clear all
clc

A=textread('pick_onset_infile1');

plot(A(:,2));
line([12026,12026],[-1,1]);
