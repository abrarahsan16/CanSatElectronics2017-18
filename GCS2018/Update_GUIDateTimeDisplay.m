function [] = Update_GUIDateTimeDisplay(handles)
% Updates Date Time dispalay in main GUI
% Notice I passed the handles object from Main GUI
% This Function is called every 1 sec from csv logger.

time = datestr(datetime); % Get the current date and time as String
%time = strrep(spacetime,':', '_'); % Remove all unn
% set(handles.DateTimeDisplay, 'String', time);
set(handles.DateTimeDisplay, 'String', time);
end

