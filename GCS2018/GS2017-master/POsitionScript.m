%Take into account 3D height change effects

    %global matrix
    vel = matrix.glider(:,6);

    dir = matrix.glider(:,9);
    f= 1;
    vx = vel .* cosd(dir)*f;
    vy = vel .* sind(dir)*f;
    
    px = 0;
    py = 0;
    
    px = cumsum(vx);
    py = cumsum(vy);
    
    figure
    hold on
    plot(px, py+100, 'r');
    plot(xx, yy, 'b');
    hold off
    axis equal