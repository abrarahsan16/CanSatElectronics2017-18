function [ard] = connectFunction(comport, handles)
%   This file is called when the connect button is clicked on main GUI
%   This file performs the following tasks:
%   1. Open Serial port from comportport input variable
%   2. Creates .CSV file and logs all recived telemetery into it at 1Hz
%   3. Outputs csvfile log name for reference
%   4. Also outputs timer object for reference
    GlobalDeclarations;
    % comportmand line display
    display('Connecting...');
    cla(handles.Graph1);

    % Initial arduino connection setup and variable clear
    delete(instrfind);
    ard = serial(comport);
    set(ard, 'DataBits', 8);
    set(ard, 'StopBits', 1);
    set(ard, 'BaudRate', 19200);
    set(ard, 'Parity', 'none');
    set(ard, 'InputBufferSize', 1000000);

    try %To stop and indicate that Radio is not connected
        fopen (ard); % Open comport
        error = false;
    catch %if there is an error in try
        error = true; 
        msgbox ('No Serial Device on selected comport.');
    end

    if (error == false)
        msgbox ('Serial successfully Connected!');  %Indicate connection ws a sucess  
        delete (timerfindall); %Delete all timer objects for initial setup.

        % Create CSV File name with the Date as the given name
        csvfilename = datestr(datetime); 
        csvfilename = strrep(csvfilename, ':', '_'); % Strip invalid characters : to _
        table_filename = csvfilename;
        csvfile =1;

        % Set up the timer class 
        onesecCSVlogger = timer('TimerFcn',{@LTimer_1s, ard, csvfile, csvfilename, handles,table_filename},... 
                                'ExecutionMode','fixedRate','Period', 1); 
        %Call csvlogger function every 1 sec period with ard(Serial port) and csvfilelog (name of csv file) as input 
        start (onesecCSVlogger);
    end
end


