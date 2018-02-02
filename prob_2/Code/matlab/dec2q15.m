function [y]=dec2q15(x)

option = {'mode' , 'roundmode', 'overflowmode', 'format'}; 
value  = {'fixed', 'ceil'     , 'saturate'    ,  [16 15]}; 
q = quantizer( option, value ) ;

y=num2bin(q,x);
%y=num2hex(q,x);
end
