function [Y]=distortion(X,FS,d)
    %   Y   = espectro do sinal de saída
    %   X   = espectro do sinal de entrada
    %   FS  = frequencia de amostragem
    %   d   = offset do eco em ms
    
%distorcao
Y=(atan((0.1+2*d)*X));
%normalizacao
sx=sum(abs(X));
sy=sum(abs(Y));
sr=repmat(sx/sy,length(X),1);
Y=sr.*Y;

end