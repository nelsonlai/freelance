% Generate L1 Adaptive Control Model - Standalone Script
% =====================================================
%
% This script generates a Simulink model with L1 adaptive control
% without requiring function definitions.
%
% Usage: Simply run this script in MATLAB

clear all;
close all;
clc;

fprintf('=== L1 Adaptive Control Model Generator ===\n');
fprintf('Generating Four Layer PID Controller with L1 Adaptive Control...\n\n');

% Create new Simulink model
model_name = 'four_layer_pid_l1_adapter';
fprintf('Creating model: %s\n', model_name);

try
    % Create new system
    new_system(model_name);
    open_system(model_name);
    
    % Set model parameters
    set_param(model_name, 'Solver', 'ode45');
    set_param(model_name, 'StopTime', '100');
    set_param(model_name, 'FixedStep', '0.01');
    
    fprintf('Adding control blocks...\n');
    
    % Add control mode selector
    add_block('simulink/Sources/Constant', [model_name '/Control_Mode']);
    set_param([model_name '/Control_Mode'], 'Value', '1'); % 1=PID, 0=L1 Adaptive
    
    % Add blocks for position control layer
    add_block('simulink/Sources/Step', [model_name '/Position_Reference']);
    add_block('simulink/Continuous/PID Controller', [model_name '/Position_PID']);
    add_block('simulink/Math Operations/Sum', [model_name '/Position_Sum']);
    add_block('simulink/Sinks/Scope', [model_name '/Position_Scope']);
    
    % Add blocks for velocity control layer
    add_block('simulink/Continuous/PID Controller', [model_name '/Velocity_PID']);
    add_block('simulink/Math Operations/Sum', [model_name '/Velocity_Sum']);
    add_block('simulink/Sinks/Scope', [model_name '/Velocity_Scope']);
    
    % Add blocks for attitude control layer
    add_block('simulink/Continuous/PID Controller', [model_name '/Attitude_PID']);
    add_block('simulink/Math Operations/Sum', [model_name '/Attitude_Sum']);
    add_block('simulink/Sinks/Scope', [model_name '/Attitude_Scope']);
    
    % Add blocks for attitude rate control layer
    add_block('simulink/Continuous/PID Controller', [model_name '/Attitude_Rate_PID']);
    add_block('simulink/Math Operations/Sum', [model_name '/Attitude_Rate_Sum']);
    add_block('simulink/Sinks/Scope', [model_name '/Attitude_Rate_Scope']);
    
    fprintf('Adding L1 adaptive control blocks...\n');
    
    % Add L1 Adaptive Control blocks for Position layer
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Position_L1_State_Predictor']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Position_L1_Adaptive_Law']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Position_L1_Filter']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Position_L1_Control_Law']);
    
    % Add control switching blocks (Multiplexers)
    add_block('simulink/Signal Routing/Multiplexer', [model_name '/Position_Control_Switch']);
    add_block('simulink/Signal Routing/Multiplexer', [model_name '/Velocity_Control_Switch']);
    add_block('simulink/Signal Routing/Multiplexer', [model_name '/Attitude_Control_Switch']);
    add_block('simulink/Signal Routing/Multiplexer', [model_name '/Attitude_Rate_Control_Switch']);
    
    % Add quadrotor dynamics model
    add_block('simulink/Continuous/Transfer Fcn', [model_name '/Quadrotor_Dynamics']);
    
    % Add sensor blocks
    add_block('simulink/Sources/Constant', [model_name '/Sensor_Noise']);
    add_block('simulink/Math Operations/Add', [model_name '/Noise_Addition']);
    
    fprintf('Configuring PID parameters...\n');
    
    % Configure position PID
    set_param([model_name '/Position_PID'], 'P', '2.0');
    set_param([model_name '/Position_PID'], 'I', '0.1');
    set_param([model_name '/Position_PID'], 'D', '1.0');
    
    % Configure velocity PID
    set_param([model_name '/Velocity_PID'], 'P', '1.5');
    set_param([model_name '/Velocity_PID'], 'I', '0.05');
    set_param([model_name '/Velocity_PID'], 'D', '0.8');
    
    % Configure attitude PID
    set_param([model_name '/Attitude_PID'], 'P', '3.0');
    set_param([model_name '/Attitude_PID'], 'I', '0.2');
    set_param([model_name '/Attitude_PID'], 'D', '1.5');
    
    % Configure attitude rate PID
    set_param([model_name '/Attitude_Rate_PID'], 'P', '4.0');
    set_param([model_name '/Attitude_Rate_PID'], 'I', '0.3');
    set_param([model_name '/Attitude_Rate_PID'], 'D', '2.0');
    
    fprintf('Configuring L1 adaptive control...\n');
    
    % Configure L1 Adaptive Control Parameters - Position L1 parameters
    script1 = sprintf(['function x_pred = fcn(x, u, dt)\n' ...
        '    persistent x_hat;\n' ...
        '    if isempty(x_hat)\n' ...
        '        x_hat = [0; 0];\n' ...
        '    end\n' ...
        '    A = [1 dt; 0 1];\n' ...
        '    B = [0; dt];\n' ...
        '    x_hat = A * x_hat + B * u;\n' ...
        '    x_pred = x_hat;\n' ...
        'end']);
    set_param([model_name '/Position_L1_State_Predictor'], 'Script', script1);
    
    script2 = sprintf(['function theta = fcn(x, x_pred, dt)\n' ...
        '    persistent theta_hat;\n' ...
        '    if isempty(theta_hat)\n' ...
        '        theta_hat = 0;\n' ...
        '    end\n' ...
        '    error = x - x_pred;\n' ...
        '    gamma = 10;\n' ...
        '    theta_hat = theta_hat + gamma * error(1) * dt;\n' ...
        '    theta = theta_hat;\n' ...
        'end']);
    set_param([model_name '/Position_L1_Adaptive_Law'], 'Script', script2);
    
    script3 = sprintf(['function u_filt = fcn(u, dt)\n' ...
        '    persistent u_prev;\n' ...
        '    if isempty(u_prev)\n' ...
        '        u_prev = 0;\n' ...
        '    end\n' ...
        '    omega = 5;\n' ...
        '    alpha = omega * dt;\n' ...
        '    u_filt = alpha * u + (1 - alpha) * u_prev;\n' ...
        '    u_prev = u_filt;\n' ...
        'end']);
    set_param([model_name '/Position_L1_Filter'], 'Script', script3);
    
    script4 = sprintf(['function u = fcn(r, x, theta, dt)\n' ...
        '    kp = 2.0;\n' ...
        '    kd = 1.0;\n' ...
        '    error = r - x(1);\n' ...
        '    u = kp * error - kd * x(2) + theta;\n' ...
        'end']);
    set_param([model_name '/Position_L1_Control_Law'], 'Script', script4);
    
    % Configure multiplexers for control switching
    set_param([model_name '/Position_Control_Switch'], 'Inputs', '2');
    set_param([model_name '/Velocity_Control_Switch'], 'Inputs', '2');
    set_param([model_name '/Attitude_Control_Switch'], 'Inputs', '2');
    set_param([model_name '/Attitude_Rate_Control_Switch'], 'Inputs', '2');
    
    % Configure quadrotor dynamics (simplified transfer function)
    set_param([model_name '/Quadrotor_Dynamics'], 'Numerator', '[1]');
    set_param([model_name '/Quadrotor_Dynamics'], 'Denominator', '[1 2 1]');
    
    % Configure sensor noise
    set_param([model_name '/Sensor_Noise'], 'Value', '0.01');
    
    % Position reference configuration
    set_param([model_name '/Position_Reference'], 'Time', '1');
    set_param([model_name '/Position_Reference'], 'After', '1.0');
    set_param([model_name '/Position_Reference'], 'Before', '0.0');
    
    fprintf('Connecting blocks...\n');
    
    % Connect blocks - PID Control Path
    add_line(model_name, 'Position_Reference/1', 'Position_Sum/1');
    add_line(model_name, 'Position_Sum/1', 'Position_PID/1');
    add_line(model_name, 'Position_PID/1', 'Position_Control_Switch/1');
    
    add_line(model_name, 'Position_Control_Switch/1', 'Velocity_Sum/1');
    add_line(model_name, 'Velocity_Sum/1', 'Velocity_PID/1');
    add_line(model_name, 'Velocity_PID/1', 'Velocity_Control_Switch/1');
    
    add_line(model_name, 'Velocity_Control_Switch/1', 'Attitude_Sum/1');
    add_line(model_name, 'Attitude_Sum/1', 'Attitude_PID/1');
    add_line(model_name, 'Attitude_PID/1', 'Attitude_Control_Switch/1');
    
    add_line(model_name, 'Attitude_Control_Switch/1', 'Attitude_Rate_Sum/1');
    add_line(model_name, 'Attitude_Rate_Sum/1', 'Attitude_Rate_PID/1');
    add_line(model_name, 'Attitude_Rate_PID/1', 'Attitude_Rate_Control_Switch/1');
    add_line(model_name, 'Attitude_Rate_Control_Switch/1', 'Quadrotor_Dynamics/1');
    
    % Connect L1 Adaptive Control Path - Position Layer
    add_line(model_name, 'Position_Sum/1', 'Position_L1_State_Predictor/1');
    add_line(model_name, 'Position_L1_State_Predictor/1', 'Position_L1_Adaptive_Law/1');
    add_line(model_name, 'Position_L1_Adaptive_Law/1', 'Position_L1_Control_Law/3');
    add_line(model_name, 'Position_Reference/1', 'Position_L1_Control_Law/1');
    add_line(model_name, 'Position_Sum/1', 'Position_L1_Control_Law/2');
    add_line(model_name, 'Position_L1_Control_Law/1', 'Position_L1_Filter/1');
    add_line(model_name, 'Position_L1_Filter/1', 'Position_Control_Switch/2');
    
    % Connect control mode selector to all switches
    add_line(model_name, 'Control_Mode/1', 'Position_Control_Switch/3');
    add_line(model_name, 'Control_Mode/1', 'Velocity_Control_Switch/3');
    add_line(model_name, 'Control_Mode/1', 'Attitude_Control_Switch/3');
    add_line(model_name, 'Control_Mode/1', 'Attitude_Rate_Control_Switch/3');
    
    % Feedback connections
    add_line(model_name, 'Quadrotor_Dynamics/1', 'Noise_Addition/1');
    add_line(model_name, 'Sensor_Noise/1', 'Noise_Addition/2');
    add_line(model_name, 'Noise_Addition/1', 'Position_Sum/2', 'autorouting', 'on');
    add_line(model_name, 'Noise_Addition/1', 'Velocity_Sum/2', 'autorouting', 'on');
    add_line(model_name, 'Noise_Addition/1', 'Attitude_Sum/2', 'autorouting', 'on');
    add_line(model_name, 'Noise_Addition/1', 'Attitude_Rate_Sum/2', 'autorouting', 'on');
    
    % Connect to scopes
    add_line(model_name, 'Position_Reference/1', 'Position_Scope/1');
    add_line(model_name, 'Position_Control_Switch/1', 'Position_Scope/2');
    add_line(model_name, 'Velocity_Control_Switch/1', 'Velocity_Scope/1');
    add_line(model_name, 'Attitude_Control_Switch/1', 'Attitude_Scope/1');
    add_line(model_name, 'Attitude_Rate_Control_Switch/1', 'Attitude_Rate_Scope/1');
    
    fprintf('Positioning blocks...\n');
    
    % Position blocks
    pos_x = 50; pos_y = 50;
    set_param([model_name '/Position_Reference'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Position_Sum'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Position_PID'], 'Position', [pos_x, pos_y, pos_x+50, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Position_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Velocity blocks
    pos_x = 50; pos_y = 150;
    set_param([model_name '/Velocity_Sum'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Velocity_PID'], 'Position', [pos_x, pos_y, pos_x+50, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Velocity_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Attitude blocks
    pos_x = 50; pos_y = 250;
    set_param([model_name '/Attitude_Sum'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Attitude_PID'], 'Position', [pos_x, pos_y, pos_x+50, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Attitude_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Attitude rate blocks
    pos_x = 50; pos_y = 350;
    set_param([model_name '/Attitude_Rate_Sum'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Attitude_Rate_PID'], 'Position', [pos_x, pos_y, pos_x+50, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Attitude_Rate_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Quadrotor dynamics and sensor blocks
    pos_x = 400; pos_y = 200;
    set_param([model_name '/Quadrotor_Dynamics'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Sensor_Noise'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Noise_Addition'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Control mode selector
    pos_x = 50; pos_y = 450;
    set_param([model_name '/Control_Mode'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Position L1 Adaptive Control blocks
    pos_x = 600; pos_y = 50;
    set_param([model_name '/Position_L1_State_Predictor'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Position_L1_Adaptive_Law'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Position_L1_Control_Law'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Position_L1_Filter'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    
    % Control switching blocks
    pos_x = 300; pos_y = 50;
    set_param([model_name '/Position_Control_Switch'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    pos_x = 300; pos_y = 150;
    set_param([model_name '/Velocity_Control_Switch'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    pos_x = 300; pos_y = 250;
    set_param([model_name '/Attitude_Control_Switch'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    pos_x = 300; pos_y = 350;
    set_param([model_name '/Attitude_Rate_Control_Switch'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Add model workspace variables for L1 adaptive control parameters
    assignin('base', 'L1_adaptation_rate', 10.0);
    assignin('base', 'L1_filter_bandwidth', 5.0);
    assignin('base', 'L1_control_gains', struct('kp', 2.0, 'kd', 1.0));
    assignin('base', 'control_mode', 1); % 1=PID, 0=L1 Adaptive
    
    fprintf('Saving model...\n');
    
    % Save the model
    save_system(model_name);
    
    fprintf('\n=== Model Generation Complete ===\n');
    fprintf('Four Layer PID Controller with L1 Adaptive Control model created successfully: %s.slx\n', model_name);
    fprintf('Control Mode: 1=PID Control, 0=L1 Adaptive Control\n');
    fprintf('L1 Parameters: Adaptation Rate=%.1f, Filter Bandwidth=%.1f\n', 10.0, 5.0);
    
    fprintf('\nYou can now:\n');
    fprintf('1. Open the model: open_system(''%s'')\n', model_name);
    fprintf('2. Run simulation: sim(''%s'')\n', model_name);
    fprintf('3. Switch control modes by changing the Control_Mode constant\n');
    fprintf('4. Monitor L1 adaptation in the scopes\n\n');
    
    % Open the model
    open_system(model_name);
    
catch ME
    fprintf('Error occurred: %s\n', ME.message);
    fprintf('Please check the MATLAB command window for more details.\n');
    fprintf('Stack trace:\n');
    for i = 1:length(ME.stack)
        fprintf('  %s (line %d)\n', ME.stack(i).name, ME.stack(i).line);
    end
end
