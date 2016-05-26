close all;
clear all;
clc;

npts=1000;
snr=[10,20,30,40];
t=linspace(-3,1,npts);
y=gaussmf(t,[0.1,0]);

z=zeros(4,length(y));

for i=1:4
    z(i,:)=awgn(y,snr(i));
end

figure;
hold on;
plot(t,z(1,:),t,z(2,:),t,z(3,:),t,z(4,:));
ylim([-0.5,1.2]);

% Signal window.
line([-0.5 -0.5],[-1 1],'color','k');
line([0.5 0.5],[-1 1],'color','k');

% Noise window.
line([-2.5 -2.5],[-1 1],'color','r');
line([-1 -1],[-1 1],'color','r');

legend('SNR 10','SNR 20','SNR 30','SNR 40');

fp=fopen('snr_envelope_infile','w');
for j=1:1000
    fprintf(fp,'%.5e\t',t(j));
    for i=1:4
        fprintf(fp,'%.5e\t',z(i,j));
    end
    fprintf(fp,'\n');
end
fclose(fp);
