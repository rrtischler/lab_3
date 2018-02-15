f1 = 50;
f2 = 2*f1;
f3 = 3*f1;

fs = 1000; 

t = 0:(1/fs):1-(1/fs);

x = 1*cos(2*pi*f1*t) + 0.5*cos(2*pi*f2*t) + 0.2*cos(2*pi*f3*t);

%xfft = fft(x);
%fn = (fs/2);            %frequencia de nyquist 

%plot(t, x) 