%function [  ] = plotDFT( y, fs )
[y, fs] = audioread('out_MATLABreverb.wav');

ydft = fft(y);
% I'll assume y has even length
ydft = ydft(1:length(y)/2+1);
% create a frequency vector
freq = 0:fs/length(y):fs/2;

% plot magnitude
subplot(211);
plot(freq,abs(ydft));
title('Reverbenação');
xlabel('Frequencia (Hz)');
ylabel('Magnitude(db)');
% plot phase
subplot(212);
plot(freq,unwrap(angle(ydft))); 
title('Reverbenação');
xlabel('Frequencia (Hz)');
ylabel('Fase (Radianos)');

%end
