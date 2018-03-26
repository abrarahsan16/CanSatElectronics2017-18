function [] = LTimer_1s(src, evt, ard, csvfile, csvfilename, handles,table_filename)
%   Function performs the following tasks:
%   1. If No new serial data is avilable function does nothing
%   2. if serial data is avilable adds the new data to the .csv file log
%   display ('csvlogger');
    global matrix;
    csvExt = strcat(csvfilename,'.csv');
    if (ard.BytesAvailable <= 0) % If no new data
        disp ('No New data in Serial port');
    else 
        % Open file for reading or writing
        csvfile = fopen(csvExt, 'a+'); 
        % Get new data to string variable from Arduino
        StringFromSerial = fscanf(ard, '%s');
        fprintf ('%s\n',StringFromSerial);
        % Append string variable to file
        fprintf(csvfile, strcat(StringFromSerial, '\r\n')); 
        fclose (csvfile);% CLOSE file to allow ather app access file

        % Update Functions must be below to minimize timer objects
        % This section is called every 1 sec, Therefore plots are updates 1sec
        % 'StringFromSeriald' variable contains new lines of serial string from radio
            
        % This function updates table depending on packet 
        % Condition: Glider or Container column 2.
        tableHandling(StringFromSerial, handles);
        Update_GUIDateTimeDisplay(handles);
       Update_GUIgraph(handles);
    end 
end
