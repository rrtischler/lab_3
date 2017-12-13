[y, fs] = audioread('out_MATLAB.wav');
[y1, fs1] = audioread('out_DSP.wav');

n = 1 : length(y1);
dif = zeros(length(y1),1);

dif(n) = y(n) - y1(n);

%Magnitude da resposta em frequencia
fvtool(y);
set(gcf,'NumberTitle','off'); 
set(gcf,'Name','Transformação em frequência: Sinal distorção gerado pelo MATLAB');
fvtool(y1);
set(gcf,'NumberTitle','off'); 
set(gcf,'Name','Transformação em frequência: Sinal distorção gerado em C');
fvtool(dif);
set(gcf,'NumberTitle','off'); 
set(gcf,'Name','Transformação em frequência: Diferença entre sinal gerado em MATLAB e C');
