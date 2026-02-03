% L1 Adaptive Controller Simulink Model Generator
% ===============================================
%
% This script generates a Simulink model for L1 adaptive control system
% for quadrotor flight control. The model includes:
% - State predictor
% - Adaptive law
% - L1 filter
% - Control law
% - Plant model
%
% Author: [Your Name]
% Date: [Current Date]
% License: MIT

function create_l1_adaptive_model()
    % Create new Simulink model
    model_name = 'l1_adaptive_model';
    new_system(model_name);
    open_system(model_name);
    
    % Set model parameters
    set_param(model_name, 'Solver', 'ode45');
    set_param(model_name, 'StopTime', '50');
    set_param(model_name, 'FixedStep', '0.01');
    
    % Add reference input
    add_block('simulink/Sources/Step', [model_name '/Reference_Input']);
    set_param([model_name '/Reference_Input'], 'Time', '1');
    set_param([model_name '/Reference_Input'], 'After', '1.0');
    set_param([model_name '/Reference_Input'], 'Before', '0.0');
    
    % Add state predictor subsystem
    add_block('simulink/Ports & Subsystems/Subsystem', [model_name '/State_Predictor']);
    create_state_predictor_subsystem([model_name '/State_Predictor']);
    
    % Add adaptive law subsystem
    add_block('simulink/Ports & Subsystems/Subsystem', [model_name '/Adaptive_Law']);
    create_adaptive_law_subsystem([model_name '/Adaptive_Law']);
    
    % Add L1 filter subsystem
    add_block('simulink/Ports & Subsystems/Subsystem', [model_name '/L1_Filter']);
    create_l1_filter_subsystem([model_name '/L1_Filter']);
    
    % Add control law
    add_block('simulink/Math Operations/Sum', [model_name '/Control_Law']);
    add_block('simulink/Continuous/Gain', [model_name '/Control_Gain']);
    set_param([model_name '/Control_Gain'], 'Gain', '1.0');
    
    % Add plant model (quadrotor dynamics)
    add_block('simulink/Continuous/Transfer Fcn', [model_name '/Plant_Model']);
    set_param([model_name '/Plant_Model'], 'Numerator', '[1]');
    set_param([model_name '/Plant_Model'], 'Denominator', '[1 2 1]');
    
    % Add sensor noise
    add_block('simulink/Sources/Constant', [model_name '/Sensor_Noise']);
    set_param([model_name '/Sensor_Noise'], 'Value', '0.01');
    add_block('simulink/Math Operations/Add', [model_name '/Noise_Addition']);
    
    % Add scopes for visualization
    add_block('simulink/Sinks/Scope', [model_name '/Reference_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/Output_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/Control_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/Adaptive_Parameter_Scope']);
    
    % Add To Workspace blocks for data logging
    add_block('simulink/Sinks/To Workspace', [model_name '/Reference_Data']);
    add_block('simulink/Sinks/To Workspace', [model_name '/Output_Data']);
    add_block('simulink/Sinks/To Workspace', [model_name '/Control_Data']);
    add_block('simulink/Sinks/To Workspace', [model_name '/Adaptive_Parameter_Data']);
    
    % Configure To Workspace blocks
    set_param([model_name '/Reference_Data'], 'VariableName', 'reference_data');
    set_param([model_name '/Output_Data'], 'VariableName', 'output_data');
    set_param([model_name '/Control_Data'], 'VariableName', 'control_data');
    set_param([model_name '/Adaptive_Parameter_Data'], 'VariableName', 'adaptive_param_data');
    
    % Connect blocks
    add_line(model_name, 'Reference_Input/1', 'State_Predictor/1');
    add_line(model_name, 'Reference_Input/1', 'L1_Filter/1');
    add_line(model_name, 'State_Predictor/1', 'Adaptive_Law/1');
    add_line(model_name, 'Adaptive_Law/1', 'L1_Filter/2');
    add_line(model_name, 'L1_Filter/1', 'Control_Law/1');
    add_line(model_name, 'Reference_Input/1', 'Control_Law/2');
    add_line(model_name, 'Control_Law/1', 'Control_Gain/1');
    add_line(model_name, 'Control_Gain/1', 'Plant_Model/1');
    add_line(model_name, 'Plant_Model/1', 'Noise_Addition/1');
    add_line(model_name, 'Sensor_Noise/1', 'Noise_Addition/2');
    add_line(model_name, 'Noise_Addition/1', 'State_Predictor/2');
    
    % Connect to scopes
    add_line(model_name, 'Reference_Input/1', 'Reference_Scope/1');
    add_line(model_name, 'Noise_Addition/1', 'Output_Scope/1');
    add_line(model_name, 'Control_Gain/1', 'Control_Scope/1');
    add_line(model_name, 'Adaptive_Law/1', 'Adaptive_Parameter_Scope/1');
    
    % Connect to data logging
    add_line(model_name, 'Reference_Input/1', 'Reference_Data/1');
    add_line(model_name, 'Noise_Addition/1', 'Output_Data/1');
    add_line(model_name, 'Control_Gain/1', 'Control_Data/1');
    add_line(model_name, 'Adaptive_Law/1', 'Adaptive_Parameter_Data/1');
    
    % Position blocks
    pos_x = 50; pos_y = 50;
    set_param([model_name '/Reference_Input'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 150; pos_y = 50;
    set_param([model_name '/State_Predictor'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+60]);
    
    pos_x = 300; pos_y = 50;
    set_param([model_name '/Adaptive_Law'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+60]);
    
    pos_x = 450; pos_y = 50;
    set_param([model_name '/L1_Filter'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+60]);
    
    pos_x = 600; pos_y = 50;
    set_param([model_name '/Control_Law'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 700; pos_y = 50;
    set_param([model_name '/Control_Gain'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 800; pos_y = 50;
    set_param([model_name '/Plant_Model'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    
    pos_x = 950; pos_y = 50;
    set_param([model_name '/Sensor_Noise'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 1100; pos_y = 50;
    set_param([model_name '/Noise_Addition'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Position scopes
    pos_x = 50; pos_y = 200;
    set_param([model_name '/Reference_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 150; pos_y = 200;
    set_param([model_name '/Output_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 250; pos_y = 200;
    set_param([model_name '/Control_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 350; pos_y = 200;
    set_param([model_name '/Adaptive_Parameter_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Position data logging blocks
    pos_x = 50; pos_y = 300;
    set_param([model_name '/Reference_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 150; pos_y = 300;
    set_param([model_name '/Output_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 250; pos_y = 300;
    set_param([model_name '/Control_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 350; pos_y = 300;
    set_param([model_name '/Adaptive_Parameter_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Save the model
    save_system(model_name);
    fprintf('L1 Adaptive Controller model created successfully: %s.slx\n', model_name);
end

function create_state_predictor_subsystem(subsystem_name)
    % Create state predictor subsystem
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Reference']);
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Measurement']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Predicted_State']);
    
    % Add state predictor dynamics
    add_block('simulink/Continuous/Integrator', [subsystem_name '/Integrator']);
    add_block('simulink/Continuous/Gain', [subsystem_name '/Am_Gain']);
    add_block('simulink/Continuous/Gain', [subsystem_name '/Bm_Gain']);
    add_block('simulink/Math Operations/Sum', [subsystem_name '/State_Sum']);
    
    % Configure gains
    set_param([subsystem_name '/Am_Gain'], 'Gain', '-2.0');  % State matrix
    set_param([subsystem_name '/Bm_Gain'], 'Gain', '1.0');   % Input matrix
    
    % Connect blocks
    add_line(subsystem_name, 'Reference/1', 'Bm_Gain/1');
    add_line(subsystem_name, 'Measurement/1', 'State_Sum/1');
    add_line(subsystem_name, 'Integrator/1', 'Am_Gain/1');
    add_line(subsystem_name, 'Am_Gain/1', 'State_Sum/2');
    add_line(subsystem_name, 'Bm_Gain/1', 'State_Sum/3');
    add_line(subsystem_name, 'State_Sum/1', 'Integrator/1');
    add_line(subsystem_name, 'Integrator/1', 'Predicted_State/1');
end

function create_adaptive_law_subsystem(subsystem_name)
    % Create adaptive law subsystem
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Prediction_Error']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Adaptive_Parameter']);
    
    % Add adaptive law components
    add_block('simulink/Continuous/Integrator', [subsystem_name '/Parameter_Integrator']);
    add_block('simulink/Continuous/Gain', [subsystem_name '/Adaptation_Gain']);
    
    % Configure adaptation gain
    set_param([subsystem_name '/Adaptation_Gain'], 'Gain', '10.0');
    
    % Connect blocks
    add_line(subsystem_name, 'Prediction_Error/1', 'Adaptation_Gain/1');
    add_line(subsystem_name, 'Adaptation_Gain/1', 'Parameter_Integrator/1');
    add_line(subsystem_name, 'Parameter_Integrator/1', 'Adaptive_Parameter/1');
end

function create_l1_filter_subsystem(subsystem_name)
    % Create L1 filter subsystem
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Reference']);
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Adaptive_Parameter']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Filtered_Output']);
    
    % Add L1 filter components
    add_block('simulink/Continuous/Transfer Fcn', [subsystem_name '/L1_Filter_TF']);
    add_block('simulink/Math Operations/Sum', [subsystem_name '/Filter_Sum']);
    
    % Configure L1 filter transfer function
    % L1 filter: D(s) = k / (s + k)
    set_param([subsystem_name '/L1_Filter_TF'], 'Numerator', '[10]');
    set_param([subsystem_name '/L1_Filter_TF'], 'Denominator', '[1 10]');
    
    % Connect blocks
    add_line(subsystem_name, 'Reference/1', 'Filter_Sum/1');
    add_line(subsystem_name, 'Adaptive_Parameter/1', 'L1_Filter_TF/1');
    add_line(subsystem_name, 'L1_Filter_TF/1', 'Filter_Sum/2');
    add_line(subsystem_name, 'Filter_Sum/1', 'Filtered_Output/1');
end

% Main execution
if ~bdIsLoaded('l1_adaptive_model')
    create_l1_adaptive_model();
else
    fprintf('Model already exists. Opening existing model.\n');
    open_system('l1_adaptive_model');
end
