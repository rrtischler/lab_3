function [ y ] = funIir( file, x, t, fs )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

load(file)

[b, a] = sos2tf(SOS, G);

y = filter(b,a,x);

% subplot(221); 
% plot(t,x);
% subplot(222);
% plot(y);
% 
% subplot(223); 
% periodogram(x, rectwin(length(x)), length(x), fs);
% subplot(224); 
% periodogram(y, rectwin(length(y)), length(y), fs);

figure
subplot(211); 
plot(t,y);
subplot(212); 
periodogram(y, rectwin(length(y)), length(y), fs);

figure;
freqz(b, a);
end
