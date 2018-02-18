%script para filtro FIR

firlowmat = funFir('firLow', x, t, fs);

firbandmat = funFir('firBand', x, t, fs);

firhighmat = funFir('firHigh', x, t, fs);
