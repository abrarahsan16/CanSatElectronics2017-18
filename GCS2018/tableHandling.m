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

tele = strsplit(packet, ','); %Split the telemtry into seperate cells
pk = str2num(tele{3}); %Get the packet count from the telemetry
sS = str2num(tele{16});

update_GUIcurrentStateButton(handles, sS); %Update the current state button in GUI
 

%{
assign current telemtry to a new row of the global matrix "probe"
its done this way because in order to continually update a ui table in
matlab with new information and have all the old information you need to
add new rows to your global matrix.
%}


for i= 1:16
    matrix.probe(pk, i) = str2num(tele{i}); %
end

updateGUI_probeTable(handles, matrix.probe, pk); %Update the ui Table





end

