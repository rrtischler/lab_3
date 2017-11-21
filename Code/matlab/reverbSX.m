function [Y]=reverbSX(X,FS, d, att)
    %   Y   = espectro do sinal de saída
    %   X   = espectro do sinal de entrada
    %   FS  = frequencia de amostragem
    %   att = atenuacao (0,1)
    %   d   = offset em ms

% criacao do filtro
d=d/1000;
del=round(d*FS);
b=zeros(1 , 4*del);
b(1)=1;
a=[1];
b(4*del)= att;
b(3*del)= att + 0.07;
b(2*del)= att + 0.07;
b(del)= att + 0.08;

% filtragem
Y=filter(b,a,X);