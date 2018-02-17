function [ maxdif ] = difFilters (f1, f2)
    
dif = f1 - f2;

maxdif = max(abs(dif));

plot(abs(dif));


end
