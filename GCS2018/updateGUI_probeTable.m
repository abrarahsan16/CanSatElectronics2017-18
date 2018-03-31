function [] = updateGUI_probeTable(handles, dataMatrixProbe,pk)

data = num2cell(dataMatrixProbe(1:pk,1:16));
set(handles.uiTableProbe, 'data', data);
end