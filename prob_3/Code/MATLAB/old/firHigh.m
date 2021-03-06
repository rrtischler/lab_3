


%NAO UTILIZADO



function Hd = firHigh
%FIRHIGH Returns a discrete-time filter object.

% MATLAB Code
% Generated by MATLAB(R) 9.0 and the DSP System Toolbox 9.2.
% Generated on: 15-Feb-2018 10:08:47

% Equiripple Highpass filter designed using the FIRPM function.

% All frequency values are in Hz.
Fs = 1000;  % Sampling Frequency

Fstop = 140;             % Stopband Frequency
Fpass = 150;             % Passband Frequency
Dstop = 0.001;           % Stopband Attenuation
Dpass = 0.057501127785;  % Passband Ripple
dens  = 20;              % Density Factor

% Calculate the order from the parameters using FIRPMORD.
[N, Fo, Ao, W] = firpmord([Fstop, Fpass]/(Fs/2), [0 1], [Dstop, Dpass]);

% Calculate the coefficients using the FIRPM function.
b  = firpm(N, Fo, Ao, W, {dens});
Hd = dfilt.dffir(b);

% [EOF]
