%script para transformar o filtro IIR para coeficientes usados no DSP

[b,a] = sos2tf(SOS, G);
a = a(2:3);
a = double2intq15(a);
b = double2intq15(b);

fileID = fopen('iirHigh.txt','w');

fprintf(fileID, '%d, ', b);
fprintf(fileID, '%d, ', a);