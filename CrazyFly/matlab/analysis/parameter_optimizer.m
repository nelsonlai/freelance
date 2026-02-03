% Parameter Optimizer for CrazyFly Quadrotor Control System
% ========================================================
%
% This script provides parameter optimization tools for the quadrotor
% control system, including:
% - PID parameter tuning
% - L1 adaptive control parameter optimization
% - MPC parameter optimization
% - Multi-objective optimization
% - Genetic algorithm optimization
% - Particle swarm optimization
% - Bayesian optimization
%
% Author: [Your Name]
% Date: [Current Date]
% License: MIT

classdef ParameterOptimizer < handle
    properties
        % Optimization parameters
        optimization_algorithm = 'genetic';  % 'genetic', 'particle_swarm', 'bayesian'
        objective_function = 'tracking_error';  % 'tracking_error', 'energy', 'multi_objective'
        parameter_bounds = struct();
        population_size = 50;
        max_iterations = 100;
        tolerance = 1e-6;
        
        % Controller parameters
        controller_type = 'pid';  % 'pid', 'l1_adaptive', 'mpc'
        current_parameters = struct();
        best_parameters = struct();
        
        % Optimization results
        optimization_history = [];
        convergence_data = [];
        performance_metrics = struct();
        
        % Simulation interface
        simulation_model = '';
        simulation_time = 10;
    end
    
    methods
        function obj = ParameterOptimizer()
            % Constructor - initialize parameter optimizer
            obj.initialize_parameter_bounds();
        end
        
        function initialize_parameter_bounds(obj)
            % Initialize parameter bounds for different controllers
            switch obj.controller_type
                case 'pid'
                    obj.parameter_bounds.position_kp = [0.1, 10.0];
                    obj.parameter_bounds.position_ki = [0.01, 2.0];
                    obj.parameter_bounds.position_kd = [0.1, 5.0];
                    obj.parameter_bounds.velocity_kp = [0.1, 8.0];
                    obj.parameter_bounds.velocity_ki = [0.01, 1.5];
                    obj.parameter_bounds.velocity_kd = [0.1, 4.0];
                    obj.parameter_bounds.attitude_kp = [0.5, 15.0];
                    obj.parameter_bounds.attitude_ki = [0.01, 3.0];
                    obj.parameter_bounds.attitude_kd = [0.1, 8.0];
                    
                case 'l1_adaptive'
                    obj.parameter_bounds.adaptation_rate = [1.0, 50.0];
                    obj.parameter_bounds.filter_bandwidth = [1.0, 20.0];
                    obj.parameter_bounds.prediction_horizon = [5, 50];
                    
                case 'mpc'
                    obj.parameter_bounds.horizon_length = [5, 30];
                    obj.parameter_bounds.position_weight = [0.1, 10.0];
                    obj.parameter_bounds.control_weight = [0.01, 5.0];
                    obj.parameter_bounds.max_iterations = [10, 100];
            end
        end
        
        function set_controller_type(obj, controller_type)
            % Set controller type and update parameter bounds
            obj.controller_type = controller_type;
            obj.initialize_parameter_bounds();
        end
        
        function set_optimization_algorithm(obj, algorithm)
            % Set optimization algorithm
            valid_algorithms = {'genetic', 'particle_swarm', 'bayesian', 'gradient_descent'};
            if ismember(algorithm, valid_algorithms)
                obj.optimization_algorithm = algorithm;
            else
                error('Invalid optimization algorithm. Choose from: %s', strjoin(valid_algorithms, ', '));
            end
        end
        
        function set_objective_function(obj, objective)
            % Set objective function type
            valid_objectives = {'tracking_error', 'energy', 'multi_objective', 'settling_time', 'overshoot'};
            if ismember(objective, valid_objectives)
                obj.objective_function = objective;
            else
                error('Invalid objective function. Choose from: %s', strjoin(valid_objectives, ', '));
            end
        end
        
        function cost = evaluate_parameters(obj, parameters)
            % Evaluate parameters using simulation
            try
                % Update simulation model with new parameters
                obj.update_simulation_parameters(parameters);
                
                % Run simulation
                simulation_results = obj.run_simulation();
                
                % Calculate cost based on objective function
                cost = obj.calculate_cost(simulation_results);
                
            catch ME
                fprintf('Error in parameter evaluation: %s\n', ME.message);
                cost = inf;  % Return high cost for invalid parameters
            end
        end
        
        function update_simulation_parameters(obj, parameters)
            % Update simulation model with new parameters
            switch obj.controller_type
                case 'pid'
                    % Update PID parameters in simulation
                    obj.current_parameters = parameters;
                    
                case 'l1_adaptive'
                    % Update L1 adaptive parameters
                    obj.current_parameters = parameters;
                    
                case 'mpc'
                    % Update MPC parameters
                    obj.current_parameters = parameters;
            end
        end
        
        function results = run_simulation(obj)
            % Run simulation with current parameters
            % This is a placeholder - replace with actual simulation call
            t = 0:0.01:obj.simulation_time;
            
            % Generate reference trajectory
            reference = ones(size(t));
            
            % Simulate system response (simplified)
            % In practice, this would call the actual simulation model
            response = reference + 0.1*sin(2*pi*0.5*t) + 0.05*randn(size(t));
            control = 0.5*ones(size(t)) + 0.1*randn(size(t));
            
            results = struct();
            results.time = t;
            results.reference = reference;
            results.response = response;
            results.control = control;
        end
        
        function cost = calculate_cost(obj, simulation_results)
            % Calculate cost based on objective function
            switch obj.objective_function
                case 'tracking_error'
                    error = simulation_results.reference - simulation_results.response;
                    cost = sqrt(mean(error.^2));  % RMSE
                    
                case 'energy'
                    cost = sum(simulation_results.control.^2);  % Total energy
                    
                case 'settling_time'
                    % Calculate settling time (simplified)
                    final_value = simulation_results.reference(end);
                    threshold = final_value * 0.05;
                    settled_indices = abs(simulation_results.response - final_value) <= threshold;
                    if any(settled_indices)
                        settling_time = find(settled_indices, 1) * 0.01;
                        cost = settling_time;
                    else
                        cost = inf;
                    end
                    
                case 'overshoot'
                    % Calculate overshoot
                    max_value = max(simulation_results.response);
                    final_value = simulation_results.reference(end);
                    if max_value > final_value
                        overshoot = (max_value - final_value) / final_value * 100;
                        cost = overshoot;
                    else
                        cost = 0;
                    end
                    
                case 'multi_objective'
                    % Multi-objective cost (weighted combination)
                    error = simulation_results.reference - simulation_results.response;
                    tracking_cost = sqrt(mean(error.^2));
                    energy_cost = sum(simulation_results.control.^2);
                    
                    % Weighted combination
                    cost = 0.7 * tracking_cost + 0.3 * energy_cost;
                    
                otherwise
                    cost = inf;
            end
        end
        
        function optimize_parameters(obj)
            % Main optimization function
            fprintf('Starting parameter optimization...\n');
            fprintf('Controller: %s\n', obj.controller_type);
            fprintf('Algorithm: %s\n', obj.optimization_algorithm);
            fprintf('Objective: %s\n', obj.objective_function);
            
            % Initialize optimization history
            obj.optimization_history = [];
            obj.convergence_data = [];
            
            switch obj.optimization_algorithm
                case 'genetic'
                    obj.genetic_algorithm_optimization();
                    
                case 'particle_swarm'
                    obj.particle_swarm_optimization();
                    
                case 'bayesian'
                    obj.bayesian_optimization();
                    
                case 'gradient_descent'
                    obj.gradient_descent_optimization();
            end
            
            fprintf('Optimization completed!\n');
            fprintf('Best cost: %.6f\n', min(obj.optimization_history));
        end
        
        function genetic_algorithm_optimization(obj)
            % Genetic algorithm optimization
            fprintf('Running Genetic Algorithm...\n');
            
            % Get parameter names and bounds
            param_names = fieldnames(obj.parameter_bounds);
            num_params = length(param_names);
            
            % Initialize population
            population = obj.initialize_population(num_params);
            best_cost = inf;
            best_individual = [];
            
            for generation = 1:obj.max_iterations
                % Evaluate population
                costs = zeros(obj.population_size, 1);
                for i = 1:obj.population_size
                    parameters = obj.individual_to_parameters(population(i, :), param_names);
                    costs(i) = obj.evaluate_parameters(parameters);
                end
                
                % Update best solution
                [min_cost, min_idx] = min(costs);
                if min_cost < best_cost
                    best_cost = min_cost;
                    best_individual = population(min_idx, :);
                end
                
                % Store history
                obj.optimization_history = [obj.optimization_history; min_cost];
                obj.convergence_data = [obj.convergence_data; generation, min_cost];
                
                % Selection
                parents = obj.tournament_selection(population, costs);
                
                % Crossover
                offspring = obj.crossover(parents);
                
                % Mutation
                offspring = obj.mutation(offspring);
                
                % Update population
                population = offspring;
                
                % Print progress
                if mod(generation, 10) == 0
                    fprintf('Generation %d: Best Cost = %.6f\n', generation, min_cost);
                end
                
                % Check convergence
                if generation > 10 && abs(obj.optimization_history(end) - obj.optimization_history(end-10)) < obj.tolerance
                    fprintf('Converged at generation %d\n', generation);
                    break;
                end
            end
            
            % Store best parameters
            obj.best_parameters = obj.individual_to_parameters(best_individual, param_names);
        end
        
        function population = initialize_population(obj, num_params)
            % Initialize random population
            population = zeros(obj.population_size, num_params);
            param_names = fieldnames(obj.parameter_bounds);
            
            for i = 1:obj.population_size
                for j = 1:num_params
                    param_name = param_names{j};
                    bounds = obj.parameter_bounds.(param_name);
                    population(i, j) = bounds(1) + (bounds(2) - bounds(1)) * rand();
                end
            end
        end
        
        function parameters = individual_to_parameters(obj, individual, param_names)
            % Convert individual to parameter structure
            parameters = struct();
            for i = 1:length(param_names)
                parameters.(param_names{i}) = individual(i);
            end
        end
        
        function parents = tournament_selection(obj, population, costs)
            % Tournament selection
            tournament_size = 3;
            parents = zeros(size(population));
            
            for i = 1:obj.population_size
                % Select tournament participants
                tournament_indices = randi(obj.population_size, tournament_size, 1);
                tournament_costs = costs(tournament_indices);
                
                % Select winner (lowest cost)
                [~, winner_idx] = min(tournament_costs);
                parents(i, :) = population(tournament_indices(winner_idx), :);
            end
        end
        
        function offspring = crossover(obj, parents)
            % Single-point crossover
            offspring = parents;
            crossover_rate = 0.8;
            
            for i = 1:2:obj.population_size
                if rand() < crossover_rate && i < obj.population_size
                    % Single-point crossover
                    crossover_point = randi(size(parents, 2) - 1);
                    offspring(i, crossover_point+1:end) = parents(i+1, crossover_point+1:end);
                    offspring(i+1, crossover_point+1:end) = parents(i, crossover_point+1:end);
                end
            end
        end
        
        function offspring = mutation(obj, offspring)
            % Gaussian mutation
            mutation_rate = 0.1;
            mutation_strength = 0.1;
            
            for i = 1:obj.population_size
                for j = 1:size(offspring, 2)
                    if rand() < mutation_rate
                        offspring(i, j) = offspring(i, j) + mutation_strength * randn();
                    end
                end
            end
        end
        
        function particle_swarm_optimization(obj)
            % Particle swarm optimization
            fprintf('Running Particle Swarm Optimization...\n');
            
            % Get parameter names and bounds
            param_names = fieldnames(obj.parameter_bounds);
            num_params = length(param_names);
            
            % Initialize particles
            particles = obj.initialize_population(num_params);
            velocities = zeros(size(particles));
            personal_best = particles;
            personal_best_costs = inf(obj.population_size, 1);
            global_best = [];
            global_best_cost = inf;
            
            % PSO parameters
            w = 0.7;  % Inertia weight
            c1 = 1.5; % Cognitive coefficient
            c2 = 1.5; % Social coefficient
            
            for iteration = 1:obj.max_iterations
                % Evaluate particles
                costs = zeros(obj.population_size, 1);
                for i = 1:obj.population_size
                    parameters = obj.individual_to_parameters(particles(i, :), param_names);
                    costs(i) = obj.evaluate_parameters(parameters);
                end
                
                % Update personal best
                for i = 1:obj.population_size
                    if costs(i) < personal_best_costs(i)
                        personal_best_costs(i) = costs(i);
                        personal_best(i, :) = particles(i, :);
                    end
                end
                
                % Update global best
                [min_cost, min_idx] = min(costs);
                if min_cost < global_best_cost
                    global_best_cost = min_cost;
                    global_best = particles(min_idx, :);
                end
                
                % Store history
                obj.optimization_history = [obj.optimization_history; min_cost];
                obj.convergence_data = [obj.convergence_data; iteration, min_cost];
                
                % Update velocities and positions
                for i = 1:obj.population_size
                    r1 = rand(1, num_params);
                    r2 = rand(1, num_params);
                    
                    velocities(i, :) = w * velocities(i, :) + ...
                                     c1 * r1 .* (personal_best(i, :) - particles(i, :)) + ...
                                     c2 * r2 .* (global_best - particles(i, :));
                    
                    particles(i, :) = particles(i, :) + velocities(i, :);
                end
                
                % Print progress
                if mod(iteration, 10) == 0
                    fprintf('Iteration %d: Best Cost = %.6f\n', iteration, min_cost);
                end
                
                % Check convergence
                if iteration > 10 && abs(obj.optimization_history(end) - obj.optimization_history(end-10)) < obj.tolerance
                    fprintf('Converged at iteration %d\n', iteration);
                    break;
                end
            end
            
            % Store best parameters
            obj.best_parameters = obj.individual_to_parameters(global_best, param_names);
        end
        
        function bayesian_optimization(obj)
            % Bayesian optimization (simplified implementation)
            fprintf('Running Bayesian Optimization...\n');
            
            % Get parameter names and bounds
            param_names = fieldnames(obj.parameter_bounds);
            num_params = length(param_names);
            
            % Initialize with random points
            n_init = 10;
            X = obj.initialize_population(n_init);
            y = zeros(n_init, 1);
            
            for i = 1:n_init
                parameters = obj.individual_to_parameters(X(i, :), param_names);
                y(i) = obj.evaluate_parameters(parameters);
            end
            
            % Bayesian optimization loop
            for iteration = 1:obj.max_iterations
                % Simple acquisition function (expected improvement)
                [~, best_idx] = min(y);
                best_cost = y(best_idx);
                
                % Generate new candidate
                candidate = obj.initialize_population(1);
                candidate_cost = obj.evaluate_parameters(obj.individual_to_parameters(candidate, param_names));
                
                % Update data
                X = [X; candidate];
                y = [y; candidate_cost];
                
                % Store history
                obj.optimization_history = [obj.optimization_history; best_cost];
                obj.convergence_data = [obj.convergence_data; iteration, best_cost];
                
                % Print progress
                if mod(iteration, 10) == 0
                    fprintf('Iteration %d: Best Cost = %.6f\n', iteration, best_cost);
                end
                
                % Check convergence
                if iteration > 10 && abs(obj.optimization_history(end) - obj.optimization_history(end-10)) < obj.tolerance
                    fprintf('Converged at iteration %d\n', iteration);
                    break;
                end
            end
            
            % Store best parameters
            [~, best_idx] = min(y);
            obj.best_parameters = obj.individual_to_parameters(X(best_idx, :), param_names);
        end
        
        function gradient_descent_optimization(obj)
            % Gradient descent optimization (simplified)
            fprintf('Running Gradient Descent...\n');
            
            % Get parameter names and bounds
            param_names = fieldnames(obj.parameter_bounds);
            num_params = length(param_names);
            
            % Initialize parameters
            current_params = obj.initialize_population(1);
            learning_rate = 0.01;
            
            for iteration = 1:obj.max_iterations
                % Evaluate current parameters
                parameters = obj.individual_to_parameters(current_params, param_names);
                current_cost = obj.evaluate_parameters(parameters);
                
                % Store history
                obj.optimization_history = [obj.optimization_history; current_cost];
                obj.convergence_data = [obj.convergence_data; iteration, current_cost];
                
                % Finite difference gradient
                gradient = zeros(1, num_params);
                h = 0.001;
                
                for i = 1:num_params
                    % Forward step
                    forward_params = current_params;
                    forward_params(i) = forward_params(i) + h;
                    forward_parameters = obj.individual_to_parameters(forward_params, param_names);
                    forward_cost = obj.evaluate_parameters(forward_parameters);
                    
                    % Backward step
                    backward_params = current_params;
                    backward_params(i) = backward_params(i) - h;
                    backward_parameters = obj.individual_to_parameters(backward_params, param_names);
                    backward_cost = obj.evaluate_parameters(backward_parameters);
                    
                    % Central difference
                    gradient(i) = (forward_cost - backward_cost) / (2 * h);
                end
                
                % Update parameters
                current_params = current_params - learning_rate * gradient;
                
                % Print progress
                if mod(iteration, 10) == 0
                    fprintf('Iteration %d: Cost = %.6f\n', iteration, current_cost);
                end
                
                % Check convergence
                if iteration > 10 && abs(obj.optimization_history(end) - obj.optimization_history(end-10)) < obj.tolerance
                    fprintf('Converged at iteration %d\n', iteration);
                    break;
                end
            end
            
            % Store best parameters
            obj.best_parameters = obj.individual_to_parameters(current_params, param_names);
        end
        
        function plot_optimization_results(obj)
            % Plot optimization results
            if isempty(obj.optimization_history)
                error('No optimization results to plot. Run optimize_parameters() first.');
            end
            
            figure('Position', [100, 100, 1200, 800]);
            
            % Plot convergence
            subplot(2, 2, 1);
            plot(obj.convergence_data(:, 1), obj.convergence_data(:, 2), 'b-', 'LineWidth', 2);
            title('Optimization Convergence');
            xlabel('Iteration');
            ylabel('Best Cost');
            grid on;
            
            % Plot parameter evolution (if available)
            subplot(2, 2, 2);
            if size(obj.convergence_data, 2) > 2
                param_names = fieldnames(obj.parameter_bounds);
                for i = 1:min(3, length(param_names))
                    plot(obj.convergence_data(:, 1), obj.convergence_data(:, i+2), 'LineWidth', 2);
                    hold on;
                end
                title('Parameter Evolution');
                xlabel('Iteration');
                ylabel('Parameter Value');
                legend(param_names(1:min(3, length(param_names))), 'Location', 'best');
                grid on;
            end
            
            % Plot cost distribution
            subplot(2, 2, 3);
            histogram(obj.optimization_history, 20, 'FaceColor', 'c', 'EdgeColor', 'k');
            title('Cost Distribution');
            xlabel('Cost');
            ylabel('Frequency');
            grid on;
            
            % Plot final parameters
            subplot(2, 2, 4);
            if ~isempty(obj.best_parameters)
                param_names = fieldnames(obj.best_parameters);
                param_values = zeros(length(param_names), 1);
                for i = 1:length(param_names)
                    param_values(i) = obj.best_parameters.(param_names{i});
                end
                bar(param_values, 'FaceColor', 'g');
                set(gca, 'XTickLabel', param_names);
                title('Best Parameters');
                ylabel('Parameter Value');
                grid on;
            end
            
            sgtitle(sprintf('Optimization Results - %s Algorithm', obj.optimization_algorithm), 'FontSize', 16);
        end
        
        function export_optimization_results(obj, filename)
            % Export optimization results
            if nargin < 2
                filename = 'optimization_results.mat';
            end
            
            results = struct();
            results.best_parameters = obj.best_parameters;
            results.optimization_history = obj.optimization_history;
            results.convergence_data = obj.convergence_data;
            results.performance_metrics = obj.performance_metrics;
            results.optimization_settings = struct('algorithm', obj.optimization_algorithm, ...
                                                 'objective', obj.objective_function, ...
                                                 'controller_type', obj.controller_type, ...
                                                 'population_size', obj.population_size, ...
                                                 'max_iterations', obj.max_iterations);
            
            save(filename, 'results');
            fprintf('Optimization results exported to: %s\n', filename);
        end
        
        function generate_optimization_report(obj, filename)
            % Generate optimization report
            if nargin < 2
                filename = 'optimization_report.txt';
            end
            
            fid = fopen(filename, 'w');
            
            % Write report header
            fprintf(fid, '=== CRAZYFLY PARAMETER OPTIMIZATION REPORT ===\n\n');
            fprintf(fid, 'Generated: %s\n', datestr(now));
            fprintf(fid, 'Controller Type: %s\n', obj.controller_type);
            fprintf(fid, 'Optimization Algorithm: %s\n', obj.optimization_algorithm);
            fprintf(fid, 'Objective Function: %s\n', obj.objective_function);
            fprintf(fid, 'Population Size: %d\n', obj.population_size);
            fprintf(fid, 'Max Iterations: %d\n\n', obj.max_iterations);
            
            % Write optimization results
            fprintf(fid, 'OPTIMIZATION RESULTS:\n');
            fprintf(fid, '===================\n');
            if ~isempty(obj.optimization_history)
                fprintf(fid, 'Final Best Cost: %.6f\n', min(obj.optimization_history));
                fprintf(fid, 'Initial Cost: %.6f\n', obj.optimization_history(1));
                fprintf(fid, 'Improvement: %.2f%%\n', (obj.optimization_history(1) - min(obj.optimization_history)) / obj.optimization_history(1) * 100);
                fprintf(fid, 'Convergence Iterations: %d\n\n', length(obj.optimization_history));
            end
            
            % Write best parameters
            fprintf(fid, 'BEST PARAMETERS:\n');
            fprintf(fid, '================\n');
            if ~isempty(obj.best_parameters)
                param_names = fieldnames(obj.best_parameters);
                for i = 1:length(param_names)
                    fprintf(fid, '%s: %.6f\n', param_names{i}, obj.best_parameters.(param_names{i}));
                end
            end
            fprintf(fid, '\n');
            
            % Write recommendations
            fprintf(fid, 'RECOMMENDATIONS:\n');
            fprintf(fid, '===============\n');
            if ~isempty(obj.optimization_history)
                final_cost = min(obj.optimization_history);
                if final_cost < 0.1
                    fprintf(fid, 'Excellent optimization results! The parameters are well-tuned.\n');
                elseif final_cost < 0.5
                    fprintf(fid, 'Good optimization results. Consider fine-tuning for better performance.\n');
                else
                    fprintf(fid, 'Optimization results need improvement. Consider different algorithms or constraints.\n');
                end
            end
            
            fclose(fid);
            fprintf('Optimization report generated: %s\n', filename);
        end
    end
end

% Example usage and demonstration
function demo_parameter_optimizer()
    % Demonstration of the ParameterOptimizer class
    
    fprintf('=== CrazyFly Parameter Optimizer Demo ===\n\n');
    
    % Create optimizer instance
    optimizer = ParameterOptimizer();
    
    % Configure optimizer
    optimizer.set_controller_type('pid');
    optimizer.set_optimization_algorithm('genetic');
    optimizer.set_objective_function('multi_objective');
    optimizer.population_size = 30;
    optimizer.max_iterations = 50;
    
    % Run optimization
    fprintf('Starting parameter optimization...\n');
    optimizer.optimize_parameters();
    
    % Display results
    fprintf('\nOptimization Results:\n');
    fprintf('Best Cost: %.6f\n', min(optimizer.optimization_history));
    fprintf('Best Parameters:\n');
    param_names = fieldnames(optimizer.best_parameters);
    for i = 1:length(param_names)
        fprintf('  %s: %.6f\n', param_names{i}, optimizer.best_parameters.(param_names{i}));
    end
    
    % Create plots
    fprintf('\nGenerating optimization plots...\n');
    optimizer.plot_optimization_results();
    
    % Export results
    optimizer.export_optimization_results('demo_optimization_results.mat');
    optimizer.generate_optimization_report('demo_optimization_report.txt');
    
    fprintf('\nDemo completed successfully!\n');
    fprintf('Check the generated plots and files for results.\n');
end

% Run demo if this file is executed directly
if ~exist('OCTAVE_VERSION', 'builtin') && ~exist('matlab', 'builtin')
    % This is not MATLAB/Octave, so just define the class
    return;
end

% Check if this is being run as a script
if ~exist('OCTAVE_VERSION', 'builtin')
    % MATLAB
    if ~exist('OCTAVE_VERSION', 'builtin') && exist('matlab', 'builtin')
        demo_parameter_optimizer();
    end
else
    % Octave
    if exist('OCTAVE_VERSION', 'builtin')
        demo_parameter_optimizer();
    end
end
