function plotMap(lat_pos,lon_pos)

  % Takes lat/lon positions of glider and plots them on a map
  
    lat = [32.229248 32.271757]; % Converts lat/lon to pixels
    lon = [-98.227397 -98.172433];
    x_spacing = 1280/(lon(2) - lon(1)); % Pixels/deg lon
    y_spacing = 1196/(lat(2) - lat(1)); % Pixels/deg lat

    conv_lat = (lat_pos - lat(1))*y_spacing; % Converts given lat/lon values to pixels 
    conv_lon = (lon_pos - lon(1))*x_spacing;

    figure
    imshow('staticmap-1.jpeg')
    hold on
    plot(conv_lon,conv_lat,'y-') % Plots trajectory of glider
    hold off
end

