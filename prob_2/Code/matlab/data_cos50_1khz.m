fs = 1000; %1KHz

t = 0:1/fs:1-1/fs;
x = 1*cos(2*pi*50*t) + 0.01*cos(2*pi*100*t) + 0.005*cos(2*pi*150*t) + 0.001*cos(2*pi*200*t);

q15data = dec2q15(x);


%[r,harmpow,harmfreq] = thd(x, fs);