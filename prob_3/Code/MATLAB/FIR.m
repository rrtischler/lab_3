f1 = 5000;
f2 = 2*f1;
f3 = 3*f1;
f4 = 4*f1;
fs = 44000; 
t = 0:(1/fs):1-(1/fs);
x = 1*cos(2*pi*f1*t) + 0.01*cos(2*pi*f2*t) + 0.005*cos(2*pi*f3*t) + 0.001*cos(2*pi*f4*t);
n = length(x);
plot(t, x)
fn = (fs/2);            %frequencia de nyquist 
fc = f1;                %frequencia de corte
%passa baixa
h = fir1(224,fc/fn);
freqz(h,1,50);
