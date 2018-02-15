function [ y ] = funFir( file, x, t, fs )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

load(file)

y = filter(Num,1,x);

subplot(221); 
plot(t,x);
subplot(222);
plot(t,y);

subplot(223); 
periodogram(x, rectwin(length(x)), length(x), fs);
subplot(224); 
periodogram(y, rectwin(length(y)), length(y), fs);

figure;
freqz(Num,1);




end

