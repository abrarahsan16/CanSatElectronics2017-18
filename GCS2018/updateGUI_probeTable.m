function [] = updateGUI_probeTable(handles, dataMatrixProbe)
data = num2cell(dataMatrixProbe(1:16));
data = strsplit(data, ', ');
set(handles.uiTableProbe, 'Data', Data);
end