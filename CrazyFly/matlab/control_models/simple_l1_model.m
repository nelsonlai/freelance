% Simple L1 Adaptive Control Model Generator
% =========================================
%
% This script creates a basic Simulink model with L1 adaptive control
% without complex string concatenation.

clear all;
close all;
clc;

fprintf('=== Simple L1 Adaptive Control Model Generator ===\n');
fprintf('Creating basic model with L1 adaptive control...\n\n');

% Create new Simulink model
model_name = 'simple_l1_model';
fprintf('Creating model: %s\n', model_name);

try
    % Create new system
    new_system(model_name);
    open_system(model_name);
    
    % Set model parameters
    set_param(model_name, 'Solver', 'ode45');
    set_param(model_name, 'StopTime', '10');
    set_param(model_name, 'FixedStep', '0.01');
    
    fprintf('Adding basic control blocks...\n');
    
    % Add basic blocks
    add_block('simulink/Sources/Step', [model_name '/Reference']);
    add_block('simulink/Continuous/PID Controller', [model_name '/PID_Controller']);
    add_block('simulink/Math Operations/Sum', [model_name '/Sum']);
    add_block('simulink/Continuous/Transfer Fcn', [model_name '/Plant']);
    add_block('simulink/Sinks/Scope', [model_name '/Output_Scope']);
    
    % Add L1 adaptive control blocks
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/L1_Controller']);
    add_block('simulink/Signal Routing/Multiplexer', [model_name '/Control_Switch']);
    add_block('simulink/Sources/Constant', [model_name '/Control_Mode']);
    
    % Configure PID controller
    set_param([model_name '/PID_Controller'], 'P', '2.0');
    set_param([model_name '/PID_Controller'], 'I', '0.1');
    set_param([model_name '/PID_Controller'], 'D', '1.0');
    
    % Configure plant (simple transfer function)
    set_param([model_name '/Plant'], 'Numerator', '[1]');
    set_param([model_name '/Plant'], 'Denominator', '[1 2 1]');
    
    % Configure reference signal
    set_param([model_name '/Reference'], 'Time', '1');
    set_param([model_name '/Reference'], 'After', '1.0');
    set_param([model_name '/Reference'], 'Before', '0.0');
    
    % Configure control mode (1=PID, 0=L1)
    set_param([model_name '/Control_Mode'], 'Value', '1');
    
    % Configure multiplexer
    set_param([model_name '/Control_Switch'], 'Inputs', '2');
    
    % Configure L1 controller with simple script
    l1_script = 'function u = fcn(r, y, dt) persistent x_hat; if isempty(x_hat), x_hat = 0; end; error = r - y; kp = 2.0; kd = 1.0; u = kp * error - kd * x_hat; x_hat = y; end';
    set_param([model_name '/L1_Controller'], 'Script', l1_script);
    
    fprintf('Connecting blocks...\n');
    
    % Connect blocks
    add_line(model_name, 'Reference/1', 'Sum/1');
    add_line(model_name, 'Sum/1', 'PID_Controller/1');
    add_line(model_name, 'PID_Controller/1', 'Control_Switch/1');
    add_line(model_name, 'Sum/1', 'L1_Controller/1');
    add_line(model_name, 'Reference/1', 'L1_Controller/2');
    add_line(model_name, 'L1_Controller/1', 'Control_Switch/2');
    add_line(model_name, 'Control_Switch/1', 'Plant/1');
    add_line(model_name, 'Plant/1', 'Sum/2', 'autorouting', 'on');
    add_line(model_name, 'Plant/1', 'Output_Scope/1');
    add_line(model_name, 'Control_Mode/1', 'Control_Switch/3');
    
    fprintf('Positioning blocks...\n');
    
    % Position blocks
    set_param([model_name '/Reference'], 'Position', [50, 50, 80, 80]);
    set_param([model_name '/Sum'], 'Position', [150, 50, 180, 80]);
    set_param([model_name '/PID_Controller'], 'Position', [250, 50, 300, 80]);
    set_param([model_name '/L1_Controller'], 'Position', [250, 150, 300, 180]);
    set_param([model_name '/Control_Switch'], 'Position', [350, 50, 380, 80]);
    set_param([model_name '/Plant'], 'Position', [450, 50, 500, 80]);
    set_param([model_name '/Output_Scope'], 'Position', [550, 50, 580, 80]);
    set_param([model_name '/Control_Mode'], 'Position', [350, 150, 380, 180]);
    
    fprintf('Saving model...\n');
    
    % Save the model
    save_system(model_name);
    
    fprintf('\n=== Model Generation Complete ===\n');
    fprintf('Simple L1 Adaptive Control model created: %s.slx\n', model_name);
    fprintf('Control Mode: 1=PID Control, 0=L1 Adaptive Control\n');
    fprintf('You can now run simulation or modify the model.\n\n');
    
    % Open the model
    open_system(model_name);
    
catch ME
    fprintf('Error occurred: %s\n', ME.message);
    fprintf('Stack trace:\n');
    for i = 1:length(ME.stack)
        fprintf('  %s (line %d)\n', ME.stack(i).name, ME.stack(i).line);
    end
end
