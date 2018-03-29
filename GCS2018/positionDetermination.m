function [lat_pos, lon_pos] = positionDetermination(pk)
    global matrix;
    vel = matrix.glider(:,5); % Velocity from pitot tube
    heading = matrix.glider(:,8); % Direction from magnometer (degrees)
    pitch = matrix.glider(:,11); % Placeholder for pitch data (degrees)

    dx(pk) = round(vel(pk) * cosd(heading(pk)) * cosd(pitch(pk)),6); % Change in x,y,z position over 1 second update interval
    dy(pk) = round(vel(pk) * sind(heading(pk)) * cosd(pitch(pk)),6);
    dz(pk) = round(vel(pk) * sind(pitch(pk)),6);

    pos_x(pk) = cumsum(dx(pk)); % Summation of delta changes in x,y,z position
    pos_y(pk) = cumsum(dy(pk));
    pos_z(pk) = cumsum(dz(pk));
    
    lat_pos(pk) = round((pos_x(pk) / 111000) + matrix.container(end,10),6);
    lon_pos(pk) = round((pos_y(pk) / (111000 * cos(lat_pos(pk)))) + matrix.container(end,11),6);

end

