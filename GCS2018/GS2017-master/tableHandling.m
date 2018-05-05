function [] = tableHandling(packet, handles)
% After creating the csv file and writing to it from serial, this function
% is called. Takes RAW CSV file and checks each row of column 3 (see mission
% guideline for future use.
% 'glider'. Determines which table to fill on GUI.


%{
Container
---------------
1 - TeleTeamID
~ - CONTAINER
2 - TeleMissionTime
3 - TelePacketCount
4 - TeleAltSensor
5 - TeleTemp
6 - TeleVoltage
7 - TeleState
8 - TeleDeployed
9 - TeleLat
10 - TeleLong


Glider
-------------
1 - TeleTeamID
~ - GLIDER
2 - TeleMissionTime
3 - TelePacketCount
4 - TeleAltSensor
5 - TelePressure
6 - TeleSpeed
7 - TeleTemp
8 - TeleVoltage
9 - TeleHeading
10 - TeleState
11 - TeleNumPics

%}

global matrix;
global lastDevice;

tele = strsplit(packet, ',');
isDeployed = 0;


%packet count
pk = str2num(tele{4});

if pk == 0
    if (lastDevice == 'G')

        pk = matrix.glider(end,4);
        matrix.glider(pk+1, 1) = matrix.glider(pk, 1);
        matrix.glider(pk+1,2) = 0;
        matrix.glider(pk+1,3) = matrix.glider(pk,3)+1;
        matrix.glider(pk+1,4) = matrix.glider(pk,4)+1;
        for i = 5:13
            matrix.glider(pk+1, i) = packetLoss( matrix.glider(pk-1,i), matrix.glider(pk,i));
        end
        updateGUI_gliderTable(handles,matrix.glider, pk+1);
        set(0,'DefaultFigureVisible', 'off')
        plot_google_map('axis', handles.map)
        set(0,'DefaultFigureVisible', 'on')
        
        
    else
        pk = matrix.container(end,4);
        matrix.container(pk+1, 1) = matrix.container(pk, 1);
        matrix.container(pk+1,2) = 0;
        matrix.container(pk+1,3) = matrix.container(pk,3)+1;
        matrix.container(pk+1,4) = matrix.container(pk,4)+1;
        for i = 5:11
            matrix.container(pk+1, i) = packetLoss( matrix.container(pk-1,i), matrix.container(pk,i));
        end
        if (matrix.container(pk+1, 9) == 1 && isDeployed == 0)
            isDeployed = 1;
            set(handles.deploymentButton, 'BackgroundColor', [0.26 0.96 0.49]);
            set(handles.deploymentButton, 'String', 'Is Deployed: T');
            %         msgbox('Glider has been deployed!');
            
        else
            set(handles.deploymentButton, 'BackgroundColor','yellow');
        end
        updateGUI_containerTable(handles,matrix.container, pk+1);
    end
     
else

    if (ismember('GLIDER', tele{2}))
        matrix.glider(pk, 1) = str2num(tele{1});
        matrix.glider(pk,2) = 0;
        for i = 3:13
            matrix.glider(pk, i) = str2num(tele{i}) ;
        end
        updateGUI_gliderTable(handles,matrix.glider, pk);
%         set(0,'DefaultFigureVisible', 'off')
%         plot_google_map('axis', handles.map)
%         set(0,'DefaultFigureVisible', 'on')
        
        lastDevice = 'G';
        
    else
        matrix.container(pk, 1) = str2num(tele{1});
        matrix.container(pk,2) = 0;
        for i = 3:11
            matrix.container(pk, i) = str2num(tele{i});
        end
        
        if (matrix.container(pk, 9) == 1 && isDeployed == 0)
            isDeployed = 1;
            set(handles.deploymentButton, 'BackgroundColor', [0.26 0.96 0.49]);
            set(handles.deploymentButton, 'String', 'Is Deployed: T');
            %         msgbox('Glider has been deployed!');
            
        else
            set(handles.deploymentButton, 'BackgroundColor','yellow');
        end
        updateGUI_containerTable(handles,matrix.container, pk);
        lastDevice = 'C';
    end
end

end

