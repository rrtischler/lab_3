function [Y]=delaySF(X,FS,d, att)
    %   Y   = espectro do sinal de saída
    %   X   = espectro do sinal de entrada
    %   FS  = frequencia de amostragem
    %   att = atenuacao do eco, (0,1)
    %   d   = offset do eco em ms

del=round(d*FS/1000);
n = 1 : length(X)+del; 
R = zeros(del,1);
X = [X ; R];
Z = [R ; X];
%Z = [R ; att * X];
Y(n) = X(n) + Z(n);
%Y = Y * max(abs(X))/max(abs(Y));