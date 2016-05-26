clear all
close all
clc

delta=0.025;

A=textread('waterlevel_decon_out_structure');
B=textread('waterlevel_decon_out_source');
C=textread('waterlevel_decon_out_signal');
D=textread('waterlevel_decon_out_decon');

h1=subplot(4,1,1);
plot(A(:,1),A(:,2));
title('Structure','FontSize',20);
h2=subplot(4,1,2);
plot(B(:,1),B(:,2));
title('Source','FontSize',20);
h3=subplot(4,1,3);
plot(C(:,1),C(:,2));
title('Signal','FontSize',20);
ylim([-0.5,1.1]);
h4=subplot(4,1,4);
plot(D(:,1),D(:,2));
xlabel('Time (sec.)','FontSize',15);
ylabel('amp.','FontSize',15);
title('Decon','FontSize',20);

linkaxes([h1,h2,h3,h4],'x');
xlim([0,200]);

[~,I_Signal]=max(abs(C));
[~,I_Decon]=max(abs(D));

figure;
E=C(I_Signal:I_Signal+20/delta)-C(I_Signal:-1:I_Signal-20/delta);
F=D(I_Decon:I_Decon+20/delta)-D(I_Decon:-1:I_Decon-20/delta);
subplot(2,1,1);
plot(t(1:length(E)),E);
title('Signal FRS','FontSize',20);
ylim([0,0.5]);
grid on;

subplot(2,1,2);
plot(t(1:length(F)),F);
xlabel('Time (sec.)','FontSize',15);
ylabel('amp.','FontSize',15);
title('Decon FRS','FontSize',20);
ylim([-0.2,0.5]);
grid on;
