function [ val ] = packetLoss( nm1, nm2 )
xx = [1 2];
yy = [nm2 nm1];
x = 3;
val = interp1(xx, yy,x,'linear', 'extrap');

end

