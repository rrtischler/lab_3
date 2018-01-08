%function [  ] = ThdF()

    [y, fs] = audioread('out_DSPdelay.wav');
    m = length(y);          % original sample length 
    n = pow2(nextpow2(m));  % transform length
    x = fft(y, n);          % DFT of signal
    f = (0:n-1)*(fs/n)/10;  % frequency range
    power = abs(x).^2/n;    % power of the DFT
    %plot(f, power)

    %plot(y);
    %xlabel('Sample number')
    %ylabel('Amplitude')

    %plot(f(1:floor(n/2)), power(1:floor(n/2)))
    %xlabel('Frequency')
    %ylabel('Power')
    plot(abs(x));
    %periodogram(y)
    [r,harmpow,harmfreq] = thd(y, fs)
%end