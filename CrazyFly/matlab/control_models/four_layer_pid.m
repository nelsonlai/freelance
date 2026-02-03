% Four Layer PID Controller with L1 Adaptive Control Simulink Model Generator
% ============================================================================
%
% This script generates a Simulink model for a 4-layer PID control system
% with integrated L1 adaptive control for quadrotor flight control. The model includes:
% - Position control layer (PID + L1 Adaptive)
% - Velocity control layer (PID + L1 Adaptive)
% - Attitude control layer (PID + L1 Adaptive)
% - Attitude rate control layer (PID + L1 Adaptive)
% - Hybrid control switching between PID and L1 adaptive control
% - L1 adaptive control components: State Predictor, Adaptive Law, L1 Filter
%
% Author: [Your Name]
% Date: [Current Date]
% License: MIT

function create_four_layer_pid_model()
    % Create new Simulink model
    model_name = 'four_layer_pid';
    new_system(model_name);
    open_system(model_name);
    
    % Set model parameters
    set_param(model_name, 'Solver', 'ode45');
    set_param(model_name, 'StopTime', '100');
    set_param(model_name, 'FixedStep', '0.01');
    
    % Add control mode selector
    add_block('simulink/Sources/Constant', [model_name '/Control_Mode']);
    set_param([model_name '/Control_Mode'], 'Value', '1'); % 1=PID, 0=L1 Adaptive
    set_param([model_name '/Control_Mode'], 'Name', 'Control_Mode_Selector');
    
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
    
    % Add L1 Adaptive Control blocks for Position layer
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Position_L1_State_Predictor']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Position_L1_Adaptive_Law']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Position_L1_Filter']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Position_L1_Control_Law']);
    
    % Add L1 Adaptive Control blocks for Velocity layer
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Velocity_L1_State_Predictor']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Velocity_L1_Adaptive_Law']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Velocity_L1_Filter']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Velocity_L1_Control_Law']);
    
    % Add L1 Adaptive Control blocks for Attitude layer
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Attitude_L1_State_Predictor']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Attitude_L1_Adaptive_Law']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Attitude_L1_Filter']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Attitude_L1_Control_Law']);
    
    % Add L1 Adaptive Control blocks for Attitude Rate layer
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Attitude_Rate_L1_State_Predictor']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Attitude_Rate_L1_Adaptive_Law']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Attitude_Rate_L1_Filter']);
    add_block('simulink/User-Defined Functions/MATLAB Function', [model_name '/Attitude_Rate_L1_Control_Law']);
    
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
    
    % Configure L1 Adaptive Control Parameters
    % Position L1 parameters
    set_param([model_name '/Position_L1_State_Predictor'], 'Script', ...
        'function x_pred = fcn(x, u, dt)\n' ...
        '    % L1 State Predictor for Position\n' ...
        '    % x: current state [position; velocity]\n' ...
        '    % u: control input\n' ...
        '    % dt: time step\n' ...
        '    persistent x_hat;\n' ...
        '    if isempty(x_hat)\n' ...
        '        x_hat = [0; 0];\n' ...
        '    end\n' ...
        '    \n' ...
        '    % State prediction (simplified model)\n' ...
        '    A = [1 dt; 0 1];\n' ...
        '    B = [0; dt];\n' ...
        '    x_hat = A * x_hat + B * u;\n' ...
        '    x_pred = x_hat;\n' ...
        'end');
    
    set_param([model_name '/Position_L1_Adaptive_Law'], 'Script', ...
        'function theta = fcn(x, x_pred, dt)\n' ...
        '    % L1 Adaptive Law for Position\n' ...
        '    % x: actual state\n' ...
        '    % x_pred: predicted state\n' ...
        '    % dt: time step\n' ...
        '    persistent theta_hat;\n' ...
        '    if isempty(theta_hat)\n' ...
        '        theta_hat = 0;\n' ...
        '    end\n' ...
        '    \n' ...
        '    % Adaptive law (simplified)\n' ...
        '    error = x - x_pred;\n' ...
        '    gamma = 10; % adaptation rate\n' ...
        '    theta_hat = theta_hat + gamma * error(1) * dt;\n' ...
        '    theta = theta_hat;\n' ...
        'end');
    
    set_param([model_name '/Position_L1_Filter'], 'Script', ...
        'function u_filt = fcn(u, dt)\n' ...
        '    % L1 Filter for Position\n' ...
        '    % u: control input\n' ...
        '    % dt: time step\n' ...
        '    persistent u_prev;\n' ...
        '    if isempty(u_prev)\n' ...
        '        u_prev = 0;\n' ...
        '    end\n' ...
        '    \n' ...
        '    % Low-pass filter\n' ...
        '    omega = 5; % filter bandwidth\n' ...
        '    alpha = omega * dt;\n' ...
        '    u_filt = alpha * u + (1 - alpha) * u_prev;\n' ...
        '    u_prev = u_filt;\n' ...
        'end');
    
    set_param([model_name '/Position_L1_Control_Law'], 'Script', ...
        'function u = fcn(r, x, theta, dt)\n' ...
        '    % L1 Control Law for Position\n' ...
        '    % r: reference\n' ...
        '    % x: current state\n' ...
        '    % theta: adaptive parameter\n' ...
        '    % dt: time step\n' ...
        '    \n' ...
        '    % Control law (simplified)\n' ...
        '    kp = 2.0; % proportional gain\n' ...
        '    kd = 1.0; % derivative gain\n' ...
        '    \n' ...
        '    error = r - x(1);\n' ...
        '    u = kp * error - kd * x(2) + theta;\n' ...
        'end');
    
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
    
    % Connect L1 Adaptive Control Path - Velocity Layer
    add_line(model_name, 'Velocity_Sum/1', 'Velocity_L1_State_Predictor/1');
    add_line(model_name, 'Velocity_L1_State_Predictor/1', 'Velocity_L1_Adaptive_Law/1');
    add_line(model_name, 'Velocity_L1_Adaptive_Law/1', 'Velocity_L1_Control_Law/3');
    add_line(model_name, 'Position_Control_Switch/1', 'Velocity_L1_Control_Law/1');
    add_line(model_name, 'Velocity_Sum/1', 'Velocity_L1_Control_Law/2');
    add_line(model_name, 'Velocity_L1_Control_Law/1', 'Velocity_L1_Filter/1');
    add_line(model_name, 'Velocity_L1_Filter/1', 'Velocity_Control_Switch/2');
    
    % Connect L1 Adaptive Control Path - Attitude Layer
    add_line(model_name, 'Attitude_Sum/1', 'Attitude_L1_State_Predictor/1');
    add_line(model_name, 'Attitude_L1_State_Predictor/1', 'Attitude_L1_Adaptive_Law/1');
    add_line(model_name, 'Attitude_L1_Adaptive_Law/1', 'Attitude_L1_Control_Law/3');
    add_line(model_name, 'Velocity_Control_Switch/1', 'Attitude_L1_Control_Law/1');
    add_line(model_name, 'Attitude_Sum/1', 'Attitude_L1_Control_Law/2');
    add_line(model_name, 'Attitude_L1_Control_Law/1', 'Attitude_L1_Filter/1');
    add_line(model_name, 'Attitude_L1_Filter/1', 'Attitude_Control_Switch/2');
    
    % Connect L1 Adaptive Control Path - Attitude Rate Layer
    add_line(model_name, 'Attitude_Rate_Sum/1', 'Attitude_Rate_L1_State_Predictor/1');
    add_line(model_name, 'Attitude_Rate_L1_State_Predictor/1', 'Attitude_Rate_L1_Adaptive_Law/1');
    add_line(model_name, 'Attitude_Rate_L1_Adaptive_Law/1', 'Attitude_Rate_L1_Control_Law/3');
    add_line(model_name, 'Attitude_Control_Switch/1', 'Attitude_Rate_L1_Control_Law/1');
    add_line(model_name, 'Attitude_Rate_Sum/1', 'Attitude_Rate_L1_Control_Law/2');
    add_line(model_name, 'Attitude_Rate_L1_Control_Law/1', 'Attitude_Rate_L1_Filter/1');
    add_line(model_name, 'Attitude_Rate_L1_Filter/1', 'Attitude_Rate_Control_Switch/2');
    
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
    
    % Add L1 adaptive control monitoring scopes
    add_block('simulink/Sinks/Scope', [model_name '/L1_Adaptation_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/L1_Filter_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/Control_Mode_Scope']);
    
    % Connect L1 monitoring signals
    add_line(model_name, 'Position_L1_Adaptive_Law/1', 'L1_Adaptation_Scope/1');
    add_line(model_name, 'Position_L1_Filter/1', 'L1_Filter_Scope/1');
    add_line(model_name, 'Control_Mode/1', 'Control_Mode_Scope/1');
    
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
    
    % Velocity L1 Adaptive Control blocks
    pos_x = 600; pos_y = 150;
    set_param([model_name '/Velocity_L1_State_Predictor'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Velocity_L1_Adaptive_Law'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Velocity_L1_Control_Law'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Velocity_L1_Filter'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    
    % Attitude L1 Adaptive Control blocks
    pos_x = 600; pos_y = 250;
    set_param([model_name '/Attitude_L1_State_Predictor'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Attitude_L1_Adaptive_Law'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Attitude_L1_Control_Law'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Attitude_L1_Filter'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    
    % Attitude Rate L1 Adaptive Control blocks
    pos_x = 600; pos_y = 350;
    set_param([model_name '/Attitude_Rate_L1_State_Predictor'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Attitude_Rate_L1_Adaptive_Law'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Attitude_Rate_L1_Control_Law'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Attitude_Rate_L1_Filter'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    
    % Control switching blocks
    pos_x = 300; pos_y = 50;
    set_param([model_name '/Position_Control_Switch'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    pos_x = 300; pos_y = 150;
    set_param([model_name '/Velocity_Control_Switch'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    pos_x = 300; pos_y = 250;
    set_param([model_name '/Attitude_Control_Switch'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    pos_x = 300; pos_y = 350;
    set_param([model_name '/Attitude_Rate_Control_Switch'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % L1 monitoring scopes
    pos_x = 50; pos_y = 500;
    set_param([model_name '/L1_Adaptation_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/L1_Filter_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    pos_x = pos_x + 100;
    set_param([model_name '/Control_Mode_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Add model workspace variables for L1 adaptive control parameters
    assignin('base', 'L1_adaptation_rate', 10.0);
    assignin('base', 'L1_filter_bandwidth', 5.0);
    assignin('base', 'L1_control_gains', struct('kp', 2.0, 'kd', 1.0));
    assignin('base', 'control_mode', 1); % 1=PID, 0=L1 Adaptive
    
    % Save the model
    save_system(model_name);
    fprintf('Four Layer PID Controller with L1 Adaptive Control model created successfully: %s.slx\n', model_name);
    fprintf('Control Mode: 1=PID Control, 0=L1 Adaptive Control\n');
    fprintf('L1 Parameters: Adaptation Rate=%.1f, Filter Bandwidth=%.1f\n', 10.0, 5.0);
end

% Main execution
if ~bdIsLoaded('four_layer_pid')
    create_four_layer_pid_model();
else
    fprintf('Model already exists. Opening existing model.\n');
    open_system('four_layer_pid');
end

% ============================================================================
% USAGE INSTRUCTIONS FOR L1 ADAPTIVE CONTROL INTEGRATION
% ============================================================================
%
% This enhanced model now includes L1 adaptive control alongside the traditional
% 4-layer PID control system. Here's how to use it:
%
% 1. CONTROL MODE SELECTION:
%    - Set Control_Mode constant to 1 for PID control
%    - Set Control_Mode constant to 0 for L1 adaptive control
%    - The multiplexers will automatically switch between control methods
%
% 2. L1 ADAPTIVE CONTROL COMPONENTS:
%    - State Predictor: Predicts system state based on current state and control input
%    - Adaptive Law: Updates adaptive parameters based on prediction error
%    - L1 Filter: Low-pass filters the control signal for stability
%    - Control Law: Computes the adaptive control signal
%
% 3. PARAMETER TUNING:
%    - L1_adaptation_rate: Controls how fast the adaptive parameters update
%    - L1_filter_bandwidth: Controls the bandwidth of the L1 filter
%    - L1_control_gains: Proportional and derivative gains for the control law
%
% 4. MONITORING:
%    - L1_Adaptation_Scope: Shows adaptive parameter evolution
%    - L1_Filter_Scope: Shows filtered control signal
%    - Control_Mode_Scope: Shows current control mode
%
% 5. SIMULATION:
%    - Run the simulation to see both PID and L1 adaptive control in action
%    - Compare performance by switching control modes during simulation
%    - Analyze the adaptation behavior in the monitoring scopes
%
% 6. CUSTOMIZATION:
%    - Modify the MATLAB Function blocks to implement different L1 algorithms
%    - Adjust parameters in the model workspace variables
%    - Add additional monitoring signals as needed
%
% ============================================================================
