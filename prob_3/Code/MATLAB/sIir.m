%script para filtros iir

iirlowmat = funIir('iirLow', x, t, fs);

% iirbandmat = funIir('iirBand', x, t, fs);

iirhighmat = funIir('iirHigh', x, t, fs);
