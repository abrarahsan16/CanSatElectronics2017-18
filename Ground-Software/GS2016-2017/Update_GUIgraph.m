function [] = Update_GUIgraph(handles, table_filename)
% First fill the tables with appropriate columns.
% This function then takes the data in the table and plots it with
% specifications from the axis popup menus.
global matrix;

handles.gliderData = matrix.glider;
handles.containerData = matrix.container;
xAxis = get(handles.graphxAxis, 'Value');
yAxis = get(handles.graphyAxis, 'Value');

handles.xGlider = handles.gliderData(:,xAxis+2);
handles.yGlider = handles.gliderData(:,yAxis+2);
%-- Original Code
switch xAxis
    case 1
        handles.xContainer = handles.containerData(:,3);
    case 2
        handles.xContainer = handles.containerData(:,4);
    case 3
        handles.xContainer = handles.containerData(:,5);
    case 6
        handles.xContainer = handles.containerData(:,6);
    case 7
        handles.xContainer = handles.containerData(:,7);
    case 9
        handles.xGlider = 0;
        handles.xContainer = handles.containerData(:,10);
    case 10
        handles.xGlider = 0;
        handles.xContainer = handles.containerData(:,11);
    otherwise 
        handles.xContainer = 0;
end
switch yAxis
    case 1
        handles.yContainer = handles.containerData(:,3);
    case 2
        handles.yContainer = handles.containerData(:,4);
    case 3
        handles.yContainer = handles.containerData(:,5);
    case 6
        handles.yContainer = handles.containerData(:,6);
    case 7
        handles.yContainer = handles.containerData(:,7);
    case 9
        handles.yGlider = 0;
        handles.yContainer = handles.containerData(:,10);
    case 10
        handles.yGlider = 0;
        handles.yContainer = handles.containerData(:,11);
    otherwise 
        handles.yContainer = 0;
end
%-- End Original

%-- Potential Fix

%-- End Potential Fix

cla(handles.Graph1);
grid(handles.Graph1, 'on');
    

% To fix the plotting issue, try to change all rows to only the previous
% row in the switch statement above. 
if (handles.xGlider & handles.yGlider) ~= 0 % Old If
% if (matrix.glider(end,4) ~= 0) % New if
    plot(handles.xGlider, handles.yGlider, '.-b','Parent', handles.Graph1);
end
hold(handles.Graph1,'on');

if (handles.xContainer & handles.yContainer) ~= 0 % Old If
% if (matrix.container(end,4) ~= 0) % New if
    plot(handles.xContainer, handles.yContainer, '.-r','Parent', handles.Graph1);
end

end

