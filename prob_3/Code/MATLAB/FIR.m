f1 = 50;
f2 = 100;
f3 = 150;
f4 = 200;
fs = 2048; 
t = 0:(1/fs):1-(1/fs);
x = 1*cos(2*pi*f1*t) + 0.01*cos(2*pi*f2*t) + 0.005*cos(2*pi*f3*t) + 0.001*cos(2*pi*f4*t);
n = length(x);
plot(t, x)
fn = (fs/2);            %frequencia de nyquist 
fc = 50;                %frequencia de corte
%passa baixa
h = fir1(100,fc/fn);
freqz(h,1,50);
