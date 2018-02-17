function [Numq15 ] = double2intq15 ( Num )

Numq15 = round(Num * 2^15);

end
