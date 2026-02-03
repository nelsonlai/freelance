% Hybrid Controller Simulink Model Generator
% ==========================================
%
% This script generates a Simulink model for a hybrid control system
% that combines multiple control strategies for quadrotor flight control:
% - PID Controller
% - L1 Adaptive Controller
% - Model Predictive Controller
% - Intelligent switching logic
%
% Author: [Your Name]
% Date: [Current Date]
% License: MIT

function create_hybrid_controller_model()
    % Create new Simulink model
    model_name = 'hybrid_controller';
    new_system(model_name);
    open_system(model_name);
    
    % Set model parameters
    set_param(model_name, 'Solver', 'ode45');
    set_param(model_name, 'StopTime', '100');
    set_param(model_name, 'FixedStep', '0.01');
    
    % Add reference input
    add_block('simulink/Sources/Step', [model_name '/Reference_Input']);
    set_param([model_name '/Reference_Input'], 'Time', '1');
    set_param([model_name '/Reference_Input'], 'After', '1.0');
    set_param([model_name '/Reference_Input'], 'Before', '0.0');
    
    % Add PID controller subsystem
    add_block('simulink/Ports & Subsystems/Subsystem', [model_name '/PID_Controller']);
    create_pid_controller_subsystem([model_name '/PID_Controller']);
    
    % Add L1 Adaptive controller subsystem
    add_block('simulink/Ports & Subsystems/Subsystem', [model_name '/L1_Controller']);
    create_l1_controller_subsystem([model_name '/L1_Controller']);
    
    % Add MPC controller subsystem
    add_block('simulink/Ports & Subsystems/Subsystem', [model_name '/MPC_Controller']);
    create_mpc_controller_subsystem([model_name '/MPC_Controller']);
    
    % Add switching logic subsystem
    add_block('simulink/Ports & Subsystems/Subsystem', [model_name '/Switching_Logic']);
    create_switching_logic_subsystem([model_name '/Switching_Logic']);
    
    % Add multiplexer for control output selection
    add_block('simulink/Signal Routing/Multiport Switch', [model_name '/Control_Selector']);
    set_param([model_name '/Control_Selector'], 'Inputs', '3');
    set_param([model_name '/Control_Selector'], 'Criteria', 'Input port (default)');
    
    % Add plant model (quadrotor dynamics)
    add_block('simulink/Continuous/Transfer Fcn', [model_name '/Plant_Model']);
    set_param([model_name '/Plant_Model'], 'Numerator', '[1]');
    set_param([model_name '/Plant_Model'], 'Denominator', '[1 2 1]');
    
    % Add sensor noise
    add_block('simulink/Sources/Constant', [model_name '/Sensor_Noise']);
    set_param([model_name '/Sensor_Noise'], 'Value', '0.01');
    add_block('simulink/Math Operations/Add', [model_name '/Noise_Addition']);
    
    % Add performance evaluation subsystem
    add_block('simulink/Ports & Subsystems/Subsystem', [model_name '/Performance_Evaluator']);
    create_performance_evaluator_subsystem([model_name '/Performance_Evaluator']);
    
    % Add scopes for visualization
    add_block('simulink/Sinks/Scope', [model_name '/Reference_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/Output_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/Control_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/Controller_Selection_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/Performance_Scope']);
    
    % Add To Workspace blocks for data logging
    add_block('simulink/Sinks/To Workspace', [model_name '/Reference_Data']);
    add_block('simulink/Sinks/To Workspace', [model_name '/Output_Data']);
    add_block('simulink/Sinks/To Workspace', [model_name '/Control_Data']);
    add_block('simulink/Sinks/To Workspace', [model_name '/Controller_Selection_Data']);
    add_block('simulink/Sinks/To Workspace', [model_name '/Performance_Data']);
    
    % Configure To Workspace blocks
    set_param([model_name '/Reference_Data'], 'VariableName', 'reference_data');
    set_param([model_name '/Output_Data'], 'VariableName', 'output_data');
    set_param([model_name '/Control_Data'], 'VariableName', 'control_data');
    set_param([model_name '/Controller_Selection_Data'], 'VariableName', 'controller_selection_data');
    set_param([model_name '/Performance_Data'], 'VariableName', 'performance_data');
    
    % Connect blocks
    add_line(model_name, 'Reference_Input/1', 'PID_Controller/1');
    add_line(model_name, 'Reference_Input/1', 'L1_Controller/1');
    add_line(model_name, 'Reference_Input/1', 'MPC_Controller/1');
    add_line(model_name, 'Reference_Input/1', 'Switching_Logic/1');
    
    add_line(model_name, 'PID_Controller/1', 'Control_Selector/1');
    add_line(model_name, 'L1_Controller/1', 'Control_Selector/2');
    add_line(model_name, 'MPC_Controller/1', 'Control_Selector/3');
    add_line(model_name, 'Switching_Logic/1', 'Control_Selector/4');
    
    add_line(model_name, 'Control_Selector/1', 'Plant_Model/1');
    add_line(model_name, 'Plant_Model/1', 'Noise_Addition/1');
    add_line(model_name, 'Sensor_Noise/1', 'Noise_Addition/2');
    
    add_line(model_name, 'Noise_Addition/1', 'PID_Controller/2');
    add_line(model_name, 'Noise_Addition/1', 'L1_Controller/2');
    add_line(model_name, 'Noise_Addition/1', 'MPC_Controller/2');
    add_line(model_name, 'Noise_Addition/1', 'Switching_Logic/2');
    add_line(model_name, 'Noise_Addition/1', 'Performance_Evaluator/1');
    
    add_line(model_name, 'Reference_Input/1', 'Performance_Evaluator/2');
    add_line(model_name, 'Control_Selector/1', 'Performance_Evaluator/3');
    
    % Connect to scopes
    add_line(model_name, 'Reference_Input/1', 'Reference_Scope/1');
    add_line(model_name, 'Noise_Addition/1', 'Output_Scope/1');
    add_line(model_name, 'Control_Selector/1', 'Control_Scope/1');
    add_line(model_name, 'Switching_Logic/1', 'Controller_Selection_Scope/1');
    add_line(model_name, 'Performance_Evaluator/1', 'Performance_Scope/1');
    
    % Connect to data logging
    add_line(model_name, 'Reference_Input/1', 'Reference_Data/1');
    add_line(model_name, 'Noise_Addition/1', 'Output_Data/1');
    add_line(model_name, 'Control_Selector/1', 'Control_Data/1');
    add_line(model_name, 'Switching_Logic/1', 'Controller_Selection_Data/1');
    add_line(model_name, 'Performance_Evaluator/1', 'Performance_Data/1');
    
    % Position blocks
    pos_x = 50; pos_y = 50;
    set_param([model_name '/Reference_Input'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 150; pos_y = 30;
    set_param([model_name '/PID_Controller'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+60]);
    
    pos_x = 150; pos_y = 120;
    set_param([model_name '/L1_Controller'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+60]);
    
    pos_x = 150; pos_y = 210;
    set_param([model_name '/MPC_Controller'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+60]);
    
    pos_x = 150; pos_y = 300;
    set_param([model_name '/Switching_Logic'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+60]);
    
    pos_x = 300; pos_y = 150;
    set_param([model_name '/Control_Selector'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 400; pos_y = 150;
    set_param([model_name '/Plant_Model'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+30]);
    
    pos_x = 550; pos_y = 150;
    set_param([model_name '/Sensor_Noise'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 650; pos_y = 150;
    set_param([model_name '/Noise_Addition'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 400; pos_y = 300;
    set_param([model_name '/Performance_Evaluator'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+60]);
    
    % Position scopes
    pos_x = 50; pos_y = 400;
    set_param([model_name '/Reference_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 150; pos_y = 400;
    set_param([model_name '/Output_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 250; pos_y = 400;
    set_param([model_name '/Control_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 350; pos_y = 400;
    set_param([model_name '/Controller_Selection_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 450; pos_y = 400;
    set_param([model_name '/Performance_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Position data logging blocks
    pos_x = 50; pos_y = 500;
    set_param([model_name '/Reference_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 150; pos_y = 500;
    set_param([model_name '/Output_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 250; pos_y = 500;
    set_param([model_name '/Control_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 350; pos_y = 500;
    set_param([model_name '/Controller_Selection_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 450; pos_y = 500;
    set_param([model_name '/Performance_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Save the model
    save_system(model_name);
    fprintf('Hybrid Controller model created successfully: %s.slx\n', model_name);
end

function create_pid_controller_subsystem(subsystem_name)
    % Create PID controller subsystem
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Reference']);
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Measurement']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Control_Output']);
    
    % Add PID controller
    add_block('simulink/Continuous/PID Controller', [subsystem_name '/PID']);
    add_block('simulink/Math Operations/Sum', [subsystem_name '/Error_Sum']);
    
    % Configure PID gains
    set_param([subsystem_name '/PID'], 'P', '2.0');
    set_param([subsystem_name '/PID'], 'I', '0.1');
    set_param([subsystem_name '/PID'], 'D', '1.0');
    
    % Connect blocks
    add_line(subsystem_name, 'Reference/1', 'Error_Sum/1');
    add_line(subsystem_name, 'Measurement/1', 'Error_Sum/2');
    add_line(subsystem_name, 'Error_Sum/1', 'PID/1');
    add_line(subsystem_name, 'PID/1', 'Control_Output/1');
end

function create_l1_controller_subsystem(subsystem_name)
    % Create L1 adaptive controller subsystem
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Reference']);
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Measurement']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Control_Output']);
    
    % Add L1 adaptive components
    add_block('simulink/Continuous/Transfer Fcn', [subsystem_name '/L1_Filter']);
    add_block('simulink/Continuous/Integrator', [subsystem_name '/Adaptive_Parameter']);
    add_block('simulink/Math Operations/Sum', [subsystem_name '/Control_Sum']);
    
    % Configure L1 filter
    set_param([subsystem_name '/L1_Filter'], 'Numerator', '[10]');
    set_param([subsystem_name '/L1_Filter'], 'Denominator', '[1 10]');
    
    % Configure adaptive parameter
    set_param([subsystem_name '/Adaptive_Parameter'], 'InitialCondition', '0');
    
    % Connect blocks
    add_line(subsystem_name, 'Reference/1', 'L1_Filter/1');
    add_line(subsystem_name, 'Reference/1', 'Control_Sum/1');
    add_line(subsystem_name, 'L1_Filter/1', 'Adaptive_Parameter/1');
    add_line(subsystem_name, 'Adaptive_Parameter/1', 'Control_Sum/2');
    add_line(subsystem_name, 'Control_Sum/1', 'Control_Output/1');
end

function create_mpc_controller_subsystem(subsystem_name)
    % Create MPC controller subsystem
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Reference']);
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Measurement']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Control_Output']);
    
    % Add MPC components (simplified)
    add_block('simulink/Continuous/Transfer Fcn', [subsystem_name '/MPC_Predictor']);
    add_block('simulink/Math Operations/Sum', [subsystem_name '/MPC_Sum']);
    add_block('simulink/Continuous/Gain', [subsystem_name '/MPC_Gain']);
    
    % Configure MPC predictor
    set_param([subsystem_name '/MPC_Predictor'], 'Numerator', '[1]');
    set_param([subsystem_name '/MPC_Predictor'], 'Denominator', '[1 1]');
    
    % Configure MPC gain
    set_param([subsystem_name '/MPC_Gain'], 'Gain', '1.5');
    
    % Connect blocks
    add_line(subsystem_name, 'Reference/1', 'MPC_Predictor/1');
    add_line(subsystem_name, 'MPC_Predictor/1', 'MPC_Sum/1');
    add_line(subsystem_name, 'Measurement/1', 'MPC_Sum/2');
    add_line(subsystem_name, 'MPC_Sum/1', 'MPC_Gain/1');
    add_line(subsystem_name, 'MPC_Gain/1', 'Control_Output/1');
end

function create_switching_logic_subsystem(subsystem_name)
    % Create switching logic subsystem
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Reference']);
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Measurement']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Controller_Selection']);
    
    % Add switching logic components
    add_block('simulink/Math Operations/Abs', [subsystem_name '/Error_Abs']);
    add_block('simulink/Continuous/Transfer Fcn', [subsystem_name '/Error_Filter']);
    add_block('simulink/Logic and Bit Operations/Compare To Constant', [subsystem_name '/Threshold_Check']);
    add_block('simulink/Signal Routing/Switch', [subsystem_name '/Controller_Switch']);
    
    % Configure error filter
    set_param([subsystem_name '/Error_Filter'], 'Numerator', '[1]');
    set_param([subsystem_name '/Error_Filter'], 'Denominator', '[1 0.1]');
    
    % Configure threshold check
    set_param([subsystem_name '/Threshold_Check'], 'const', '0.1');
    set_param([subsystem_name '/Threshold_Check'], 'relop', '>=');
    
    % Configure controller switch
    set_param([subsystem_name '/Controller_Switch'], 'Criteria', 'u2 ~= 0');
    set_param([subsystem_name '/Controller_Switch'], 'Threshold', '0');
    
    % Connect blocks
    add_line(subsystem_name, 'Reference/1', 'Error_Abs/1');
    add_line(subsystem_name, 'Measurement/1', 'Error_Abs/1');
    add_line(subsystem_name, 'Error_Abs/1', 'Error_Filter/1');
    add_line(subsystem_name, 'Error_Filter/1', 'Threshold_Check/1');
    add_line(subsystem_name, 'Threshold_Check/1', 'Controller_Switch/1');
    add_line(subsystem_name, 'Controller_Switch/1', 'Controller_Selection/1');
end

function create_performance_evaluator_subsystem(subsystem_name)
    % Create performance evaluator subsystem
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Output']);
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Reference']);
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Control']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Performance_Metrics']);
    
    % Add performance evaluation components
    add_block('simulink/Math Operations/Sum', [subsystem_name '/Tracking_Error']);
    add_block('simulink/Math Operations/Abs', [subsystem_name '/Error_Abs']);
    add_block('simulink/Math Operations/Abs', [subsystem_name '/Control_Abs']);
    add_block('simulink/Continuous/Transfer Fcn', [subsystem_name '/Error_Filter']);
    add_block('simulink/Continuous/Transfer Fcn', [subsystem_name '/Control_Filter']);
    add_block('simulink/Math Operations/Sum', [subsystem_name '/Performance_Sum']);
    
    % Configure filters
    set_param([subsystem_name '/Error_Filter'], 'Numerator', '[1]');
    set_param([subsystem_name '/Error_Filter'], 'Denominator', '[1 0.1]');
    set_param([subsystem_name '/Control_Filter'], 'Numerator', '[1]');
    set_param([subsystem_name '/Control_Filter'], 'Denominator', '[1 0.1]');
    
    % Connect blocks
    add_line(subsystem_name, 'Reference/1', 'Tracking_Error/1');
    add_line(subsystem_name, 'Output/1', 'Tracking_Error/2');
    add_line(subsystem_name, 'Tracking_Error/1', 'Error_Abs/1');
    add_line(subsystem_name, 'Control/1', 'Control_Abs/1');
    add_line(subsystem_name, 'Error_Abs/1', 'Error_Filter/1');
    add_line(subsystem_name, 'Control_Abs/1', 'Control_Filter/1');
    add_line(subsystem_name, 'Error_Filter/1', 'Performance_Sum/1');
    add_line(subsystem_name, 'Control_Filter/1', 'Performance_Sum/2');
    add_line(subsystem_name, 'Performance_Sum/1', 'Performance_Metrics/1');
end

% Main execution
if ~bdIsLoaded('hybrid_controller')
    create_hybrid_controller_model();
else
    fprintf('Model already exists. Opening existing model.\n');
    open_system('hybrid_controller');
end
