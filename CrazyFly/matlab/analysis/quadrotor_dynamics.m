% Quadrotor Dynamics Simulink Model Generator
% ============================================
%
% This script generates a Simulink model for quadrotor dynamics including:
% - 6-DOF rigid body dynamics
% - Motor dynamics and thrust generation
% - Aerodynamic effects (drag, ground effect)
% - Gravity and environmental forces
% - Sensor models (IMU, GPS, barometer)
%
% Author: [Your Name]
% Date: [Current Date]
% License: MIT

function create_quadrotor_dynamics_model()
    % Create new Simulink model
    model_name = 'quadrotor_dynamics';
    new_system(model_name);
    open_system(model_name);
    
    % Set model parameters
    set_param(model_name, 'Solver', 'ode45');
    set_param(model_name, 'StopTime', '50');
    set_param(model_name, 'FixedStep', '0.01');
    
    % Add motor control inputs
    add_block('simulink/Sources/Constant', [model_name '/Motor_1_Input']);
    add_block('simulink/Sources/Constant', [model_name '/Motor_2_Input']);
    add_block('simulink/Sources/Constant', [model_name '/Motor_3_Input']);
    add_block('simulink/Sources/Constant', [model_name '/Motor_4_Input']);
    
    % Configure motor inputs (normalized 0-1)
    set_param([model_name '/Motor_1_Input'], 'Value', '0.5');
    set_param([model_name '/Motor_2_Input'], 'Value', '0.5');
    set_param([model_name '/Motor_3_Input'], 'Value', '0.5');
    set_param([model_name '/Motor_4_Input'], 'Value', '0.5');
    
    % Add motor dynamics subsystem
    add_block('simulink/Ports & Subsystems/Subsystem', [model_name '/Motor_Dynamics']);
    create_motor_dynamics_subsystem([model_name '/Motor_Dynamics']);
    
    % Add thrust and moment calculation subsystem
    add_block('simulink/Ports & Subsystems/Subsystem', [model_name '/Thrust_Moment_Calc']);
    create_thrust_moment_subsystem([model_name '/Thrust_Moment_Calc']);
    
    % Add 6-DOF dynamics subsystem
    add_block('simulink/Ports & Subsystems/Subsystem', [model_name '/Six_DOF_Dynamics']);
    create_six_dof_dynamics_subsystem([model_name '/Six_DOF_Dynamics']);
    
    % Add aerodynamic effects subsystem
    add_block('simulink/Ports & Subsystems/Subsystem', [model_name '/Aerodynamic_Effects']);
    create_aerodynamic_effects_subsystem([model_name '/Aerodynamic_Effects']);
    
    % Add sensor models subsystem
    add_block('simulink/Ports & Subsystems/Subsystem', [model_name '/Sensor_Models']);
    create_sensor_models_subsystem([model_name '/Sensor_Models']);
    
    % Add environment forces subsystem
    add_block('simulink/Ports & Subsystems/Subsystem', [model_name '/Environment_Forces']);
    create_environment_forces_subsystem([model_name '/Environment_Forces']);
    
    % Add scopes for visualization
    add_block('simulink/Sinks/Scope', [model_name '/Position_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/Velocity_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/Attitude_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/Angular_Velocity_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/Motor_Speeds_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/Thrust_Scope']);
    add_block('simulink/Sinks/Scope', [model_name '/Sensor_Data_Scope']);
    
    % Add To Workspace blocks for data logging
    add_block('simulink/Sinks/To Workspace', [model_name '/Position_Data']);
    add_block('simulink/Sinks/To Workspace', [model_name '/Velocity_Data']);
    add_block('simulink/Sinks/To Workspace', [model_name '/Attitude_Data']);
    add_block('simulink/Sinks/To Workspace', [model_name '/Angular_Velocity_Data']);
    add_block('simulink/Sinks/To Workspace', [model_name '/Motor_Speeds_Data']);
    add_block('simulink/Sinks/To Workspace', [model_name '/Thrust_Data']);
    add_block('simulink/Sinks/To Workspace', [model_name '/Sensor_Data']);
    
    % Configure To Workspace blocks
    set_param([model_name '/Position_Data'], 'VariableName', 'position_data');
    set_param([model_name '/Velocity_Data'], 'VariableName', 'velocity_data');
    set_param([model_name '/Attitude_Data'], 'VariableName', 'attitude_data');
    set_param([model_name '/Angular_Velocity_Data'], 'VariableName', 'angular_velocity_data');
    set_param([model_name '/Motor_Speeds_Data'], 'VariableName', 'motor_speeds_data');
    set_param([model_name '/Thrust_Data'], 'VariableName', 'thrust_data');
    set_param([model_name '/Sensor_Data'], 'VariableName', 'sensor_data');
    
    % Connect blocks
    add_line(model_name, 'Motor_1_Input/1', 'Motor_Dynamics/1');
    add_line(model_name, 'Motor_2_Input/1', 'Motor_Dynamics/2');
    add_line(model_name, 'Motor_3_Input/1', 'Motor_Dynamics/3');
    add_line(model_name, 'Motor_4_Input/1', 'Motor_Dynamics/4');
    
    add_line(model_name, 'Motor_Dynamics/1', 'Thrust_Moment_Calc/1');
    add_line(model_name, 'Thrust_Moment_Calc/1', 'Six_DOF_Dynamics/1');
    add_line(model_name, 'Six_DOF_Dynamics/1', 'Aerodynamic_Effects/1');
    add_line(model_name, 'Aerodynamic_Effects/1', 'Six_DOF_Dynamics/2');
    add_line(model_name, 'Environment_Forces/1', 'Six_DOF_Dynamics/3');
    
    add_line(model_name, 'Six_DOF_Dynamics/1', 'Sensor_Models/1');
    
    % Connect to scopes
    add_line(model_name, 'Six_DOF_Dynamics/2', 'Position_Scope/1');
    add_line(model_name, 'Six_DOF_Dynamics/3', 'Velocity_Scope/1');
    add_line(model_name, 'Six_DOF_Dynamics/4', 'Attitude_Scope/1');
    add_line(model_name, 'Six_DOF_Dynamics/5', 'Angular_Velocity_Scope/1');
    add_line(model_name, 'Motor_Dynamics/1', 'Motor_Speeds_Scope/1');
    add_line(model_name, 'Thrust_Moment_Calc/1', 'Thrust_Scope/1');
    add_line(model_name, 'Sensor_Models/1', 'Sensor_Data_Scope/1');
    
    % Connect to data logging
    add_line(model_name, 'Six_DOF_Dynamics/2', 'Position_Data/1');
    add_line(model_name, 'Six_DOF_Dynamics/3', 'Velocity_Data/1');
    add_line(model_name, 'Six_DOF_Dynamics/4', 'Attitude_Data/1');
    add_line(model_name, 'Six_DOF_Dynamics/5', 'Angular_Velocity_Data/1');
    add_line(model_name, 'Motor_Dynamics/1', 'Motor_Speeds_Data/1');
    add_line(model_name, 'Thrust_Moment_Calc/1', 'Thrust_Data/1');
    add_line(model_name, 'Sensor_Models/1', 'Sensor_Data/1');
    
    % Position blocks
    pos_x = 50; pos_y = 50;
    set_param([model_name '/Motor_1_Input'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 50; pos_y = 100;
    set_param([model_name '/Motor_2_Input'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 50; pos_y = 150;
    set_param([model_name '/Motor_3_Input'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 50; pos_y = 200;
    set_param([model_name '/Motor_4_Input'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 150; pos_y = 125;
    set_param([model_name '/Motor_Dynamics'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+60]);
    
    pos_x = 300; pos_y = 125;
    set_param([model_name '/Thrust_Moment_Calc'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+60]);
    
    pos_x = 450; pos_y = 125;
    set_param([model_name '/Six_DOF_Dynamics'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+60]);
    
    pos_x = 600; pos_y = 125;
    set_param([model_name '/Aerodynamic_Effects'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+60]);
    
    pos_x = 450; pos_y = 250;
    set_param([model_name '/Environment_Forces'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+60]);
    
    pos_x = 600; pos_y = 250;
    set_param([model_name '/Sensor_Models'], 'Position', [pos_x, pos_y, pos_x+80, pos_y+60]);
    
    % Position scopes
    pos_x = 50; pos_y = 350;
    set_param([model_name '/Position_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 150; pos_y = 350;
    set_param([model_name '/Velocity_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 250; pos_y = 350;
    set_param([model_name '/Attitude_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 350; pos_y = 350;
    set_param([model_name '/Angular_Velocity_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 450; pos_y = 350;
    set_param([model_name '/Motor_Speeds_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 550; pos_y = 350;
    set_param([model_name '/Thrust_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 650; pos_y = 350;
    set_param([model_name '/Sensor_Data_Scope'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Position data logging blocks
    pos_x = 50; pos_y = 450;
    set_param([model_name '/Position_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 150; pos_y = 450;
    set_param([model_name '/Velocity_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 250; pos_y = 450;
    set_param([model_name '/Attitude_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 350; pos_y = 450;
    set_param([model_name '/Angular_Velocity_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 450; pos_y = 450;
    set_param([model_name '/Motor_Speeds_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 550; pos_y = 450;
    set_param([model_name '/Thrust_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    pos_x = 650; pos_y = 450;
    set_param([model_name '/Sensor_Data'], 'Position', [pos_x, pos_y, pos_x+30, pos_y+30]);
    
    % Save the model
    save_system(model_name);
    fprintf('Quadrotor Dynamics model created successfully: %s.slx\n', model_name);
end

function create_motor_dynamics_subsystem(subsystem_name)
    % Create motor dynamics subsystem
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Motor_1_Input']);
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Motor_2_Input']);
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Motor_3_Input']);
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Motor_4_Input']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Motor_Speeds']);
    
    % Add motor dynamics for each motor
    for i = 1:4
        motor_name = sprintf('Motor_%d', i);
        input_name = sprintf('Motor_%d_Input', i);
        
        % Add motor transfer function (first-order system)
        add_block('simulink/Continuous/Transfer Fcn', [subsystem_name '/' motor_name '_TF']);
        set_param([subsystem_name '/' motor_name '_TF'], 'Numerator', '[1]');
        set_param([subsystem_name '/' motor_name '_TF'], 'Denominator', '[0.1 1]');
        
        % Add saturation for motor limits
        add_block('simulink/Discontinuities/Saturation', [subsystem_name '/' motor_name '_Saturation']);
        set_param([subsystem_name '/' motor_name '_Saturation'], 'UpperLimit', '1.0');
        set_param([subsystem_name '/' motor_name '_Saturation'], 'LowerLimit', '0.0');
        
        % Connect motor dynamics
        add_line(subsystem_name, [input_name '/1'], [motor_name '_Saturation/1']);
        add_line(subsystem_name, [motor_name '_Saturation/1'], [motor_name '_TF/1']);
    end
    
    % Add multiplexer to combine motor speeds
    add_block('simulink/Signal Routing/Mux', [subsystem_name '/Motor_Mux']);
    set_param([subsystem_name '/Motor_Mux'], 'Inputs', '4');
    
    % Connect all motors to mux
    add_line(subsystem_name, 'Motor_1_TF/1', 'Motor_Mux/1');
    add_line(subsystem_name, 'Motor_2_TF/1', 'Motor_Mux/2');
    add_line(subsystem_name, 'Motor_3_TF/1', 'Motor_Mux/3');
    add_line(subsystem_name, 'Motor_4_TF/1', 'Motor_Mux/4');
    
    add_line(subsystem_name, 'Motor_Mux/1', 'Motor_Speeds/1');
end

function create_thrust_moment_subsystem(subsystem_name)
    % Create thrust and moment calculation subsystem
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Motor_Speeds']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Thrust_Moments']);
    
    % Add demultiplexer for motor speeds
    add_block('simulink/Signal Routing/Demux', [subsystem_name '/Motor_Demux']);
    set_param([subsystem_name '/Motor_Demux'], 'Outputs', '4');
    
    % Add thrust calculation blocks
    add_block('simulink/Math Operations/Sum', [subsystem_name '/Total_Thrust']);
    add_block('simulink/Continuous/Gain', [subsystem_name '/Thrust_Coefficient']);
    set_param([subsystem_name '/Thrust_Coefficient'], 'Gain', '0.1'); % N/(rad/s)^2
    
    % Add moment calculation blocks
    add_block('simulink/Math Operations/Sum', [subsystem_name '/Roll_Moment']);
    add_block('simulink/Math Operations/Sum', [subsystem_name '/Pitch_Moment']);
    add_block('simulink/Math Operations/Sum', [subsystem_name '/Yaw_Moment']);
    
    % Add moment coefficients
    add_block('simulink/Continuous/Gain', [subsystem_name '/Roll_Coefficient']);
    add_block('simulink/Continuous/Gain', [subsystem_name '/Pitch_Coefficient']);
    add_block('simulink/Continuous/Gain', [subsystem_name '/Yaw_Coefficient']);
    
    set_param([subsystem_name '/Roll_Coefficient'], 'Gain', '0.05');
    set_param([subsystem_name '/Pitch_Coefficient'], 'Gain', '0.05');
    set_param([subsystem_name '/Yaw_Coefficient'], 'Gain', '0.02');
    
    % Connect motor speeds to demux
    add_line(subsystem_name, 'Motor_Speeds/1', 'Motor_Demux/1');
    
    % Connect thrust calculation
    add_line(subsystem_name, 'Motor_Demux/1', 'Total_Thrust/1');
    add_line(subsystem_name, 'Motor_Demux/2', 'Total_Thrust/2');
    add_line(subsystem_name, 'Motor_Demux/3', 'Total_Thrust/3');
    add_line(subsystem_name, 'Motor_Demux/4', 'Total_Thrust/4');
    add_line(subsystem_name, 'Total_Thrust/1', 'Thrust_Coefficient/1');
    
    % Connect moment calculations
    add_line(subsystem_name, 'Motor_Demux/1', 'Roll_Moment/1');
    add_line(subsystem_name, 'Motor_Demux/3', 'Roll_Moment/2');
    add_line(subsystem_name, 'Roll_Moment/1', 'Roll_Coefficient/1');
    
    add_line(subsystem_name, 'Motor_Demux/2', 'Pitch_Moment/1');
    add_line(subsystem_name, 'Motor_Demux/4', 'Pitch_Moment/2');
    add_line(subsystem_name, 'Pitch_Moment/1', 'Pitch_Coefficient/1');
    
    add_line(subsystem_name, 'Motor_Demux/1', 'Yaw_Moment/1');
    add_line(subsystem_name, 'Motor_Demux/2', 'Yaw_Moment/2');
    add_line(subsystem_name, 'Motor_Demux/3', 'Yaw_Moment/3');
    add_line(subsystem_name, 'Motor_Demux/4', 'Yaw_Moment/4');
    add_line(subsystem_name, 'Yaw_Moment/1', 'Yaw_Coefficient/1');
end

function create_six_dof_dynamics_subsystem(subsystem_name)
    % Create 6-DOF dynamics subsystem
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Thrust_Moments']);
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Aerodynamic_Forces']);
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/Environment_Forces']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Position']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Velocity']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Attitude']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Angular_Velocity']);
    
    % Add integrators for position and velocity
    add_block('simulink/Continuous/Integrator', [subsystem_name '/Position_Integrator']);
    add_block('simulink/Continuous/Integrator', [subsystem_name '/Velocity_Integrator']);
    
    % Add integrators for attitude and angular velocity
    add_block('simulink/Continuous/Integrator', [subsystem_name '/Attitude_Integrator']);
    add_block('simulink/Continuous/Integrator', [subsystem_name '/Angular_Velocity_Integrator']);
    
    % Add mass and inertia gains
    add_block('simulink/Continuous/Gain', [subsystem_name '/Mass_Gain']);
    add_block('simulink/Continuous/Gain', [subsystem_name '/Inertia_Gain']);
    set_param([subsystem_name '/Mass_Gain'], 'Gain', '0.027'); % kg
    set_param([subsystem_name '/Inertia_Gain'], 'Gain', '1.4e-5'); % kg*m^2
    
    % Add force summation
    add_block('simulink/Math Operations/Sum', [subsystem_name '/Force_Sum']);
    add_block('simulink/Math Operations/Sum', [subsystem_name '/Moment_Sum']);
    
    % Connect forces and moments
    add_line(subsystem_name, 'Thrust_Moments/1', 'Force_Sum/1');
    add_line(subsystem_name, 'Aerodynamic_Forces/1', 'Force_Sum/2');
    add_line(subsystem_name, 'Environment_Forces/1', 'Force_Sum/3');
    
    add_line(subsystem_name, 'Thrust_Moments/2', 'Moment_Sum/1');
    add_line(subsystem_name, 'Aerodynamic_Forces/2', 'Moment_Sum/2');
    
    % Connect to dynamics
    add_line(subsystem_name, 'Force_Sum/1', 'Mass_Gain/1');
    add_line(subsystem_name, 'Mass_Gain/1', 'Velocity_Integrator/1');
    add_line(subsystem_name, 'Velocity_Integrator/1', 'Position_Integrator/1');
    
    add_line(subsystem_name, 'Moment_Sum/1', 'Inertia_Gain/1');
    add_line(subsystem_name, 'Inertia_Gain/1', 'Angular_Velocity_Integrator/1');
    add_line(subsystem_name, 'Angular_Velocity_Integrator/1', 'Attitude_Integrator/1');
    
    % Connect outputs
    add_line(subsystem_name, 'Position_Integrator/1', 'Position/1');
    add_line(subsystem_name, 'Velocity_Integrator/1', 'Velocity/1');
    add_line(subsystem_name, 'Attitude_Integrator/1', 'Attitude/1');
    add_line(subsystem_name, 'Angular_Velocity_Integrator/1', 'Angular_Velocity/1');
end

function create_aerodynamic_effects_subsystem(subsystem_name)
    % Create aerodynamic effects subsystem
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/State']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Aerodynamic_Forces']);
    
    % Add drag calculation
    add_block('simulink/Math Operations/Product', [subsystem_name '/Drag_Calculation']);
    add_block('simulink/Continuous/Gain', [subsystem_name '/Drag_Coefficient']);
    set_param([subsystem_name '/Drag_Coefficient'], 'Gain', '0.1');
    
    % Add ground effect
    add_block('simulink/Math Operations/Product', [subsystem_name '/Ground_Effect']);
    add_block('simulink/Continuous/Gain', [subsystem_name '/Ground_Effect_Coefficient']);
    set_param([subsystem_name '/Ground_Effect_Coefficient'], 'Gain', '0.05');
    
    % Connect aerodynamic calculations
    add_line(subsystem_name, 'State/1', 'Drag_Calculation/1');
    add_line(subsystem_name, 'Drag_Calculation/1', 'Drag_Coefficient/1');
    add_line(subsystem_name, 'State/1', 'Ground_Effect/1');
    add_line(subsystem_name, 'Ground_Effect/1', 'Ground_Effect_Coefficient/1');
    
    % Combine aerodynamic forces
    add_block('simulink/Math Operations/Sum', [subsystem_name '/Aero_Sum']);
    add_line(subsystem_name, 'Drag_Coefficient/1', 'Aero_Sum/1');
    add_line(subsystem_name, 'Ground_Effect_Coefficient/1', 'Aero_Sum/2');
    add_line(subsystem_name, 'Aero_Sum/1', 'Aerodynamic_Forces/1');
end

function create_sensor_models_subsystem(subsystem_name)
    % Create sensor models subsystem
    add_block('simulink/Ports & Subsystems/In1', [subsystem_name '/State']);
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Sensor_Data']);
    
    % Add sensor noise
    add_block('simulink/Sources/Constant', [subsystem_name '/IMU_Noise']);
    add_block('simulink/Sources/Constant', [subsystem_name '/GPS_Noise']);
    add_block('simulink/Sources/Constant', [subsystem_name '/Barometer_Noise']);
    
    set_param([subsystem_name '/IMU_Noise'], 'Value', '0.01');
    set_param([subsystem_name '/GPS_Noise'], 'Value', '0.1');
    set_param([subsystem_name '/Barometer_Noise'], 'Value', '0.05');
    
    % Add noise addition
    add_block('simulink/Math Operations/Add', [subsystem_name '/IMU_Noise_Add']);
    add_block('simulink/Math Operations/Add', [subsystem_name '/GPS_Noise_Add']);
    add_block('simulink/Math Operations/Add', [subsystem_name '/Barometer_Noise_Add']);
    
    % Connect sensor models
    add_line(subsystem_name, 'State/1', 'IMU_Noise_Add/1');
    add_line(subsystem_name, 'IMU_Noise/1', 'IMU_Noise_Add/2');
    add_line(subsystem_name, 'State/1', 'GPS_Noise_Add/1');
    add_line(subsystem_name, 'GPS_Noise/1', 'GPS_Noise_Add/2');
    add_line(subsystem_name, 'State/1', 'Barometer_Noise_Add/1');
    add_line(subsystem_name, 'Barometer_Noise/1', 'Barometer_Noise_Add/2');
    
    % Combine sensor data
    add_block('simulink/Signal Routing/Mux', [subsystem_name '/Sensor_Mux']);
    set_param([subsystem_name '/Sensor_Mux'], 'Inputs', '3');
    
    add_line(subsystem_name, 'IMU_Noise_Add/1', 'Sensor_Mux/1');
    add_line(subsystem_name, 'GPS_Noise_Add/1', 'Sensor_Mux/2');
    add_line(subsystem_name, 'Barometer_Noise_Add/1', 'Sensor_Mux/3');
    add_line(subsystem_name, 'Sensor_Mux/1', 'Sensor_Data/1');
end

function create_environment_forces_subsystem(subsystem_name)
    % Create environment forces subsystem
    add_block('simulink/Ports & Subsystems/Out1', [subsystem_name '/Environment_Forces']);
    
    % Add gravity
    add_block('simulink/Sources/Constant', [subsystem_name '/Gravity']);
    set_param([subsystem_name '/Gravity'], 'Value', '9.81');
    
    % Add wind disturbance
    add_block('simulink/Sources/Sine Wave', [subsystem_name '/Wind_Disturbance']);
    set_param([subsystem_name '/Wind_Disturbance'], 'Amplitude', '0.1');
    set_param([subsystem_name '/Wind_Disturbance'], 'Frequency', '0.5');
    
    % Add force summation
    add_block('simulink/Math Operations/Sum', [subsystem_name '/Environment_Sum']);
    
    % Connect environment forces
    add_line(subsystem_name, 'Gravity/1', 'Environment_Sum/1');
    add_line(subsystem_name, 'Wind_Disturbance/1', 'Environment_Sum/2');
    add_line(subsystem_name, 'Environment_Sum/1', 'Environment_Forces/1');
end

% Main execution
if ~bdIsLoaded('quadrotor_dynamics')
    create_quadrotor_dynamics_model();
else
    fprintf('Model already exists. Opening existing model.\n');
    open_system('quadrotor_dynamics');
end
