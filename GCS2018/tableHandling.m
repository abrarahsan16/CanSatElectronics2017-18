function [] = tableHandling(packet, handles)
% After creating the csv file and writing to it from serial, this function
% is called. Takes RAW CSV file and checks each row of column 3 (see mission
% guideline for future use.
% 'glider'. Determines which table to fill on GUI.


%{
Probe
---------------
1 - Team ID
2 - Mission Time
3 - Packet Count
4 - Altitude
5 - Pressure
6 - Temperature
7 - Voltage
8 - GPS Time
9 - GPS Latitude
10 - GPS Longitude
11 - GPS Altitude
12 - GPS Sats
13 - Tilt X
14 - Tilt Y
15 - Tilt Z
16 - Software State

%}

global matrix;

tele = strsplit(packet, ',');
disp(tele);
disp(class(tele));
pk = str2num(tele{3});

for i= 1:16
    matrix.probe(pk, i) = str2num(tele{i});
end
updateGUI_probeTable(handles, matrix.probe, pk);

disp(tele);




end

