function [  ] = playSFX( v1, v2 )

[y, fs] = audioread('dspafsx_mono.wav');

dist = distortion(y, fs, v1);
delay = delaySF(y, fs, v1, v2);
reverb = reverbSX(y, fs, v1, v2);

player1 = audioplayer(y,fs);
player2 = audioplayer(dist, fs);
player3 = audioplayer(delay, fs);
player4 = audioplayer(reverb, fs);

disp('Original')
playblocking(player1);
disp('Distorcao')
playblocking(player2);
disp('Delay')
playblocking(player3);
disp('Reverberacao')
playblocking(player4);
end

