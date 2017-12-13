%function [  ] = ThdF()

    [y, fs] = audioread('dspafsx_mono.wav');
    [y1, fs1] = audioread('outGuitar.wav');
    r = thd(y)
    r1 = thd(y1)
%end

