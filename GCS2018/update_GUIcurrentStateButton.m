%{
This function takes in the current software state and changes the button
and text of the state button in the GUI based on the current software state

State 1 --> red
State 2 --> blue
State 3 --> green
State 4 --> purple
State 5 --> orange
State 6 --> white (text --> black)
State 7 --> black (text --> white)
State 8 --> yellow (text --> black)


%}

function [] = update_GUIcurrentStateButton(handles, sS)
    switch(sS)
        case 1
            set(handles.currentStateButton, 'BackgroundColor',[1,0,0]);
            set(handles.currentStateButton, 'String','State: 1');
        case 2
            set(handles.currentStateButton, 'BackgroundColor',[0,0,1]);
            set(handles.currentStateButton, 'String','State: 2');
        case 3
            set(handles.currentStateButton, 'BackgroundColor',[0.4,1,0.4]);
            set(handles.currentStateButton, 'String','State: 3');
        case 4
            set(handles.currentStateButton, 'BackgroundColor',[0.8,0.4,1]);
            set(handles.currentStateButton, 'String','State: 4');
        case 5
            set(handles.currentStateButton, 'BackgroundColor',[0.99,0.6,0.4]);
            set(handles.currentStateButton, 'String','State: 5');
        case 6
            set(handles.currentStateButton, 'BackgroundColor',[1,1,1]);
            set(handles.currentStateButton, 'ForegroundColor',[0,0,0]);
            set(handles.currentStateButton, 'String','State: 6');
        case 7
            set(handles.currentStateButton, 'BackgroundColor',[0,0,0]);
            set(handles.currentStateButton, 'ForegroundColor',[1,1,1]);
            set(handles.currentStateButton, 'String','State: 7');
            set(handles.deploymentButton, 'String', 'Is Deployed: T');
            set(handles.deploymentButton, 'BackgroundColor','yellow');
        case 8
            set(handles.currentStateButton, 'BackgroundColor', [1,1,0.39]);
            set(handles.currentStateButton, 'ForegroundColor', [0,0,0]);
            set(handles.currentStateButton, 'String', 'State: 8');
    end
end

