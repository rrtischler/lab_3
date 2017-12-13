function [  ] = playSound( filename )

    [y, Fs] = audioread(filename);
    
    player = audioplayer(y, Fs);
    
    play(player);
    


end

