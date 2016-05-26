
npts=100;
sigma=0.5;
mu=0;
snr=1;
Nrecord=1000;

t=linspace(-2,2,npts);
y=gaussmf(t,[sigma,mu]);

z=zeros(Nrecord,length(y));
for i=1:Nrecord
    z(i,:)=awgn(y,snr);
end

save bootstrap_in z '-ascii' '-tabs'
save bootstrap_clean_signal y '-ascii' '-tabs'
