
%n = pow2(nextpow2(length(x)));
%n = 1000;

Y = fft(x, n)/n;

f = fs/2*linspace(0,1,n/2+1);

plot(f,abs(Y(1:n/2+1)))   
xlabel('Frequency (Hz)') 
ylabel('|Y|') 
title('{\bf Periodogram}')

%The bin is computed taking into account that the frequency range is divided in n bins. 
%Then computation of the width of a bin will give us information, 
%where the interesting DFT at frequencies (50/
bin=fs/n; 

% Finally the computatio is: 
thd_fft = sqrt(abs(Y(ceil((4*50)/bin+1)))^2+abs(Y(ceil((3*50)/bin+1)))^2+abs(Y(ceil((2*50)/bin+1)))^2)/sqrt(abs(Y(ceil(50/bin+1)))^2) ;
%THD = sqrt(abs(Y(floor((4*50)/bin+1)))^2+abs(Y(floor((3*50)/bin+1)))^2+abs(Y(floor((2*50)/bin+1)))^2)/sqrt(abs(Y(floor(50/bin+1)))^2) ;
