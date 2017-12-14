[y, fs] = audioread('delayC.wav');
[y1, fs1] = audioread('out_DSP.wav');

n = 1 : length(y1);
dif = zeros(length(y1),1);

dif(n) = y(n) - y1(n);

%Magnitude da resposta em frequencia
fvtool(y,'Analysis','freq')
set(gcf,'NumberTitle','off'); 
set(gcf,'Name','Transforma��o em frequ�ncia: Sinal distor��o gerado em C');

fvtool(y1,'Analysis','freq')
set(gcf,'NumberTitle','off'); 
set(gcf,'Name','Transforma��o em frequ�ncia: Sinal distor��o gerado em DSP');

fvtool(dif,'Analysis','freq')
set(gcf,'NumberTitle','off'); 
set(gcf,'Name','Transforma��o em frequ�ncia: Diferen�a entre sinal gerado em C e DSP');
