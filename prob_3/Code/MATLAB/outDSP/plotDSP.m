function [ outfirDSP ] = plotDSP(t, fs)
%=========================================
% outfirDSP = importdata('dspFirLow.txt');

% outfirDSP = importdata('dspFirBand.txt');

% outfirDSP = importdata('dspFirHigh.txt');

% outfirDSP = importdata('dspIirLow.txt');

outfirDSP = importdata('dspIirHigh.txt');

%=========================================

outfirDSP = outfirDSP / ( 2^15 );

figure
subplot(211);
plot(t, outfirDSP);
subplot(212); 
periodogram(outfirDSP, rectwin(length(outfirDSP)), length(outfirDSP), fs);

end
