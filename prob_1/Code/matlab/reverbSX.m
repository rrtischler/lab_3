function [Y]=reverbSX(X,FS,d, att)
    %   Y   = espectro do sinal de sa�da
%>>>>>>> 3d60e344a8f2313716c44434dd42e20017e87010
    %   X   = espectro do sinal de entrada
    %   FS  = frequencia de amostragem
    %   att = atenuacao (0,1)
    %   d   = offset em ms

%<<<<<<< HEAD
%d = 200;
%att = 0.5;
%FS = 16000;

%>>>>>>> 3d60e344a8f2313716c44434dd42e20017e87010

% criacao do filtro
d = d/1000;
del = round(d*FS);
b = zeros(1 , 4*del);
b(1) = 1;
a = 1;
b(4*del) = att;
b(3*del) = att + 0.07;
b(2*del) = att + 0.07;
b(del) = att + 0.08;

%<<<<<<< HEAD
%sys = tf(b,a);

%end
%=======
% filtragem 'b' é o numerador e 'a' é o demonimador da função de transferencia
% filtro sem realimentação
Y=filter(b,a,X);
end
%>>>>>>> 3d60e344a8f2313716c44434dd42e20017e87010
