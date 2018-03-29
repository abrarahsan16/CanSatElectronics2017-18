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
12 - GPS Sets
13 - GPS Sats
14 - Tilt X
15 - Tilt Y
16 - Tilt Z
17 - Software State

%}

global matrix;

tele = strsplit(packet, ',');
isDeployed = 0;



updateGUI_probeTable(handles, matrix.probe);



end

