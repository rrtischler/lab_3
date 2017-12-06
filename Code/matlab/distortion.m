function [Y]=distortion(X,d)
    %   Y   = espectro do sinal de sa�da
    %   X   = espectro do sinal de entrada
    %   FS  = frequencia de amostragem

%X = [0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;-0.390625000000000;-0.414062500000000;-0.289062500000000;
%    -0.117187500000000;-0.0312500000000000;-0.0312500000000000;-0.0625000000000000;-0.0234375000000000;
%    0.0234375000000000;0.0703125000000000;0.109375000000000;0.156250000000000;0.203125000000000;
%    0.242187500000000;0.218750000000000;0;-0.164062500000000;-0.140625000000000;-0.0156250000000000;
%    0.195312500000000;0.320312500000000;0.320312500000000;0.242187500000000;0.242187500000000;
%    0.265625000000000;0.304687500000000;0.289062500000000;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0]; 
%d = 200;

%fs = 16000;
%distorcao
Y=(atan((0.1+2*d)*X));
%normalizacao
sx=sum(abs(X));
sy=sum(abs(Y));
sr=repmat(sx/sy,length(X),1);
Y=sr.*Y;

end
