% Four Layer PID Controller Simulink Model Generator
% ================================================
%
% This script generates a Simulink model for a 4-layer PID control system
% for quadrotor flight control. The model includes:
% - Position control layer
% - Velocity control layer  
% - Attitude control layer
% - Attitude rate control layer
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
    
    % Configure quadrotor dynamics (simplified transfer function)
    set_param([model_name '/Quadrotor_Dynamics'], 'Numerator', '[1]');
    set_param([model_name '/Quadrotor_Dynamics'], 'Denominator', '[1 2 1]');
    
    % Configure sensor noise
    set_param([model_name '/Sensor_Noise'], 'Value', '0.01');
    
    % Position reference configuration
    set_param([model_name '/Position_Reference'], 'Time', '1');
    set_param([model_name '/Position_Reference'], 'After', '1.0');
    set_param([model_name '/Position_Reference'], 'Before', '0.0');
    
    % Connect blocks
    add_line(model_name, 'Position_Reference/1', 'Position_Sum/1');
    add_line(model_name, 'Position_Sum/1', 'Position_PID/1');
    add_line(model_name, 'Position_PID/1', 'Velocity_Sum/1');
    add_line(model_name, 'Velocity_Sum/1', 'Velocity_PID/1');
    add_line(model_name, 'Velocity_PID/1', 'Attitude_Sum/1');
    add_line(model_name, 'Attitude_Sum/1', 'Attitude_PID/1');
    add_line(model_name, 'Attitude_PID/1', 'Attitude_Rate_Sum/1');
    add_line(model_name, 'Attitude_Rate_Sum/1', 'Attitude_Rate_PID/1');
    add_line(model_name, 'Attitude_Rate_PID/1', 'Quadrotor_Dynamics/1');
    
    % Feedback connections
    add_line(model_name, 'Quadrotor_Dynamics/1', 'Noise_Addition/1');
    add_line(model_name, 'Sensor_Noise/1', 'Noise_Addition/2');
    add_line(model_name, 'Noise_Addition/1', 'Position_Sum/2', 'autorouting', 'on');
    add_line(model_name, 'Noise_Addition/1', 'Velocity_Sum/2', 'autorouting', 'on');
    add_line(model_name, 'Noise_Addition/1', 'Attitude_Sum/2', 'autorouting', 'on');
    add_line(model_name, 'Noise_Addition/1', 'Attitude_Rate_Sum/2', 'autorouting', 'on');
    
    % Connect to scopes
    add_line(model_name, 'Position_Reference/1', 'Position_Scope/1');
    add_line(model_name, 'Position_PID/1', 'Position_Scope/2');
    add_line(model_name, 'Velocity_PID/1', 'Velocity_Scope/1');
    add_line(model_name, 'Attitude_PID/1', 'Attitude_Scope/1');
    add_line(model_name, 'Attitude_Rate_PID/1', 'Attitude_Rate_Scope/1');
    
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
    
    % Save the model
    save_system(model_name);
    fprintf('Four Layer PID Controller model created successfully: %s.slx\n', model_name);
end

% Main execution
if ~bdIsLoaded('four_layer_pid')
    create_four_layer_pid_model();
else
    fprintf('Model already exists. Opening existing model.\n');
    open_system('four_layer_pid');
end
