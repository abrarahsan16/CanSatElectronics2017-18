function [] = setCOMPort(handles)
%setCOMPort sets available serial port of the arduino
%   Looks up all available ports and sets the proper port. If no port,
%   displays EMPTY PORTS.

% Returns serial prot HW information as object.
info = instrhwinfo('serial');
availPorts = info.SerialPorts; % Returns matrix

if (numel(availPorts) ~=0)
    set(handles.COMSelect, 'String', availPorts);
%     set(handles.COMSelect, 'Value', 1);
else
    set(handles.COMSelect, 'String', 'PORTS EMPTY');
    set(handles.COMSelect, 'Value', 1);    
   
end

end

