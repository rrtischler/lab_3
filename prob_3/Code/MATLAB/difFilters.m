function [ maxdif, m ] = difFilters (f1, f2, t)
    
dif = f1 - f2;

%maximo da diferenca absoluta
maxdif = max(abs(dif));

% RMSE root mean squared error
m = sqrt(immse(f1, f2));

figure;
plot(t, (dif));


end
