function [ outfirDSP ] = plotDSP(t, fs)

% outfirDSP = importdata('dspFirLow.txt');

outfirDSP = importdata('dspFirBand.txt');

% outfirDSP = importdata('dspFirHigh.txt');

outfirDSP = outfirDSP / ( 2^15 );

len = length(outfirDSP);

%completar com zeros
if len < fs
    outfirDSP(len:fs) = 0;    
end

subplot(211);
plot(t, outfirDSP);
subplot(212); 
periodogram(outfirDSP, rectwin(length(outfirDSP)), length(outfirDSP), fs);
end