% calcula maxdiferenca maxima e media

[firlowmaxdif,  firlowrmse]  = difFilters(firlowmat,  firlowdsp, t) ;

[firhighmaxdif, firhighrmse] = difFilters(firhighmat, firhighdsp, t);

[firbandmaxdif, firbandrmse] = difFilters(firbandmat, firbanddsp, t);

[iirlowmaxdif,  iirlowrmse]  = difFilters(iirlowmat,  iirlowdsp, t) ;

[iirhighmaxdif, iirhighrmse] = difFilters(iirhighmat, iirhighdsp, t);

% [iirbandmaxdif, iirbandrmse] = maxdifFilters(iirbandmat, iirbanddsp);