% Run L1 Adaptive Control Model Generator
% ======================================
%
% This script runs the four_layer_pid_l1_adapter.m script to generate
% the Simulink model with L1 adaptive control integration.
%
% Usage:
% 1. Run this script in MATLAB
% 2. The script will generate and open the Simulink model
% 3. You can then simulate and modify the model as needed

clear all;
close all;
clc;

fprintf('=== L1 Adaptive Control Model Generator ===\n');
fprintf('Generating Four Layer PID Controller with L1 Adaptive Control...\n\n');

% Add current directory to path
addpath(pwd);

% Run the model generator
try
    % Run the main script directly
    fprintf('Running four_layer_pid_l1_adapter.m...\n');
    run('four_layer_pid_l1_adapter.m');
    
    fprintf('\n=== Model Generation Complete ===\n');
    fprintf('The Simulink model "four_layer_pid_l1_adapter.slx" has been created.\n');
    fprintf('You can now:\n');
    fprintf('1. Open the model: open_system(''four_layer_pid_l1_adapter'')\n');
    fprintf('2. Run simulation: sim(''four_layer_pid_l1_adapter'')\n');
    fprintf('3. Switch control modes by changing the Control_Mode constant\n');
    fprintf('4. Monitor L1 adaptation in the scopes\n\n');
    
    % Check if model was created and open it
    if exist('four_layer_pid_l1_adapter.slx', 'file')
        fprintf('Opening the generated Simulink model...\n');
        open_system('four_layer_pid_l1_adapter');
    else
        fprintf('Warning: Simulink model file not found. Please check for errors.\n');
    end
    
catch ME
    fprintf('Error occurred: %s\n', ME.message);
    fprintf('Please check the MATLAB command window for more details.\n');
    fprintf('Stack trace:\n');
    for i = 1:length(ME.stack)
        fprintf('  %s (line %d)\n', ME.stack(i).name, ME.stack(i).line);
    end
end
