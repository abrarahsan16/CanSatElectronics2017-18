function [] = updateGUI_containerTable(handles, dataMatrixContainer, pk)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

data = num2cell(dataMatrixContainer(1:pk,1:11));
data(:,2) = cellstr('CONTAINER');
set(handles.uitableContainer, 'Data', data);
end

