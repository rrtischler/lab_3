fs = 2048; %1KHz

t = 0:1/fs:1-1/fs;
%t = t(1:512);
x = 1*cos(2*pi*50*t) + 0.01*cos(2*pi*100*t) + 0.005*cos(2*pi*150*t) + 0.001*cos(2*pi*200*t);
n = length(x);
plot(x)
thd_teorico = sqrt(.01^2+.005^2+.001^2)/sqrt(1);

q15data = dec2q15(x);

[r,harmpow,harmfreq] = thd(x, fs, 4);
thd_matlab = 10^(r/20);