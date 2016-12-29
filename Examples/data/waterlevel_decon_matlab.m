clear all
close all
clc

delta=0.025;

A=textread('waterlevel_decon_out_structure');
B=textread('waterlevel_decon_out_source');
C=textread('waterlevel_decon_out_signal');
D=textread('waterlevel_decon_out_decon');

figure;
h1=subplot(4,1,1);
plot(A(:,1),A(:,2));
ylabel('amp.','FontSize',15);
title('Structure','FontSize',20);
ylim([-0.2,1.1]);
grid on

h2=subplot(4,1,2);
plot(B(:,1),B(:,2));
ylabel('amp.','FontSize',15);
title('Source','FontSize',20);
ylim([-0.1,1.1]);
grid on

h3=subplot(4,1,3);
plot(C(:,1),C(:,2));
ylabel('amp.','FontSize',15);
title('Signal','FontSize',20);
ylim([-0.5,1.1]);
grid on

h4=subplot(4,1,4);
plot(D(:,1),D(:,2));
xlabel('Time (sec.)','FontSize',15);
ylabel('amp.','FontSize',15);
title('Decon','FontSize',20);
ylim([-0.4,1.0]);
grid on

linkaxes([h1,h2,h3,h4],'x');
xlim([-100,100]);

[~,I_Signal]=max(abs(C(:,2)));
[~,I_Decon]=max(abs(D(:,2)));

figure;
XT=int16(2*max(A(:,1)));

E=C(I_Signal:I_Signal+XT/delta,2)-C(I_Signal:-1:I_Signal-XT/delta,2);
F=D(I_Decon:I_Decon+XT/delta,2)-D(I_Decon:-1:I_Decon-XT/delta,2);

h1=subplot(2,1,1);
plot(delta*(1:length(E)),E);
title('Signal FRS','FontSize',20);
ylim([-0.2,0.5]);
grid on;

h2=subplot(2,1,2);
plot(delta*(1:length(F)),F);
xlabel('Time (sec.)','FontSize',15);
ylabel('amp.','FontSize',15);
title('Decon FRS','FontSize',20);
ylim([-0.2,0.5]);
grid on;
linkaxes([h1,h2],'x');
xlim([0,XT]);
