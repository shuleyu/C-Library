clear all
close all
clc

delta=0.01;
npts=1000;

A=textread('retrend_infile');
t=(0:npts-1)*delta;

p=polyfit(t(:),A(:),1);

format long
p(1)
p(2)
