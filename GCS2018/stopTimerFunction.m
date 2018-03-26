function [ ] = stopTimerFunction()
% This function stops aall incoming serial logs and timer updates
%   Executed when stopTimer button is pushed.

    display('Stop Timer button clicked!');

    % Look for all available timer logs
    if (numel(timerfindall) ~= 0)
        stop(timerfindall); % Stop all timers
        delete(timerfindall); % Delete all timer objects
    end

    if (numel(instrfind) ~= 0) % Read all serial ports and returns as array
        delete(instrfind) % Delete serial objects
        instrreset; % And reset
    end

    fclose('all'); % Close current open files
end

