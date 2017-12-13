function [Y]=delaySF(X,FS,d,att)
    %   Y   = espectro do sinal de saída (X,FS,d,att)
    %   X   = espectro do sinal de entrada
    %   FS  = frequencia de amostragem
    %   att = atenuacao do eco, (0,1)
    %   d   = offset do eco em ms
%d = 200;
%att = 0.5;

del=round(d*FS/1000);
n = 1 : length(X)+del; 
R = zeros(del,1);
X = [X ; R];
Z = [R ; att * X];
Y = zeros(length(n),1);

Y(n) = X(n) + Z(n);
    
Y = Y * max(abs(X))/max(abs(Y));
end