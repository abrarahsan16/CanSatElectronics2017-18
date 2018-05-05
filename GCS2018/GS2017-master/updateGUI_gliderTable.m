function [] = updateGUI_gliderTable(handles, dataMatrixGlider, pk)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

data = num2cell(dataMatrixGlider(1:pk,1:13));
%data = dataMatrixGlider(1:pk,1:12);
data(:,2) = cellstr('GLIDER');
set(handles.uitableGlider, 'Data', data);
end

