function [Y]=distortion(X,d)
    %   Y   = espectro do sinal de saída
    %   X   = espectro do sinal de entrada
    %   FS  = frequencia de amostragem


    %fs = 16000;
    %distorcao
    Y=(atan((0.1+2*d)*X));
    %normalizacao
    sx=sum(abs(X));
    sy=sum(abs(Y));
    sr=repmat(sx/sy,length(X),1);
    Y=sr.*Y;

end