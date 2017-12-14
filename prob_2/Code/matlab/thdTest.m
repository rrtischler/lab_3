%function [  ] = ThdF()

    [y, fs] = audioread('dspafsx_mono.wav');
    [y1, fs1] = audioread('out_DSPdelay.wav');
    r = thd(y)
    r1 = thd(y1)
%end

