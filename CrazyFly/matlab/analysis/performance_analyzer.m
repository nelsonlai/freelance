% Performance Analyzer for CrazyFly Quadrotor Control System
% ===========================================================
%
% This script provides comprehensive performance analysis tools for the
% quadrotor control system, including:
% - Control performance metrics
% - Stability analysis
% - Robustness evaluation
% - Frequency response analysis
% - Time-domain analysis
% - Comparative analysis between controllers
%
% Author: [Your Name]
% Date: [Current Date]
% License: MIT

classdef PerformanceAnalyzer < handle
    properties
        % Analysis parameters
        analysis_type = 'comprehensive';  % 'comprehensive', 'stability', 'robustness', 'frequency'
        controller_data = struct();
        reference_data = struct();
        performance_metrics = struct();
        
        % Analysis results
        stability_margins = struct();
        frequency_response = struct();
        time_domain_metrics = struct();
        robustness_metrics = struct();
        
        % Plotting options
        plot_enabled = true;
        save_plots = false;
        plot_format = 'png';
        output_directory = 'performance_analysis';
    end
    
    methods
        function obj = PerformanceAnalyzer()
            % Constructor - initialize performance analyzer
            obj.initialize_output_directory();
        end
        
        function initialize_output_directory(obj)
            % Create output directory if it doesn't exist
            if ~exist(obj.output_directory, 'dir')
                mkdir(obj.output_directory);
            end
        end
        
        function set_analysis_type(obj, analysis_type)
            % Set analysis type
            valid_types = {'comprehensive', 'stability', 'robustness', 'frequency', 'time_domain'};
            if ismember(analysis_type, valid_types)
                obj.analysis_type = analysis_type;
            else
                error('Invalid analysis type. Choose from: %s', strjoin(valid_types, ', '));
            end
        end
        
        function load_controller_data(obj, data_file)
            % Load controller data from file
            try
                if ischar(data_file)
                    data = load(data_file);
                    obj.controller_data = data;
                else
                    obj.controller_data = data_file;
                end
                fprintf('Controller data loaded successfully.\n');
            catch ME
                error('Failed to load controller data: %s', ME.message);
            end
        end
        
        function load_reference_data(obj, data_file)
            % Load reference data from file
            try
                if ischar(data_file)
                    data = load(data_file);
                    obj.reference_data = data;
                else
                    obj.reference_data = data_file;
                end
                fprintf('Reference data loaded successfully.\n');
            catch ME
                error('Failed to load reference data: %s', ME.message);
            end
        end
        
        function analyze_performance(obj)
            % Main performance analysis function
            fprintf('Starting performance analysis...\n');
            fprintf('Analysis type: %s\n', obj.analysis_type);
            
            % Check if data is available
            if isempty(obj.controller_data) || isempty(obj.reference_data)
                error('Controller data and reference data must be loaded before analysis.');
            end
            
            % Perform analysis based on type
            switch obj.analysis_type
                case 'comprehensive'
                    obj.comprehensive_analysis();
                    
                case 'stability'
                    obj.stability_analysis();
                    
                case 'robustness'
                    obj.robustness_analysis();
                    
                case 'frequency'
                    obj.frequency_analysis();
                    
                case 'time_domain'
                    obj.time_domain_analysis();
            end
            
            % Generate summary
            obj.generate_performance_summary();
            
            fprintf('Performance analysis completed!\n');
        end
        
        function comprehensive_analysis(obj)
            % Comprehensive performance analysis
            fprintf('Running comprehensive analysis...\n');
            
            % Time-domain analysis
            obj.time_domain_analysis();
            
            % Frequency analysis
            obj.frequency_analysis();
            
            % Stability analysis
            obj.stability_analysis();
            
            % Robustness analysis
            obj.robustness_analysis();
            
            % Generate comprehensive report
            obj.generate_comprehensive_report();
        end
        
        function time_domain_analysis(obj)
            % Time-domain performance analysis
            fprintf('Running time-domain analysis...\n');
            
            % Extract data
            time = obj.controller_data.time;
            reference = obj.reference_data.reference;
            response = obj.controller_data.response;
            control = obj.controller_data.control;
            
            % Calculate time-domain metrics
            obj.time_domain_metrics = struct();
            
            % Tracking error metrics
            error = reference - response;
            obj.time_domain_metrics.rmse = sqrt(mean(error.^2));
            obj.time_domain_metrics.mae = mean(abs(error));
            obj.time_domain_metrics.max_error = max(abs(error));
            
            % Settling time
            final_value = reference(end);
            threshold = final_value * 0.05;  % 5% threshold
            settled_indices = abs(response - final_value) <= threshold;
            if any(settled_indices)
                settling_time = time(find(settled_indices, 1));
                obj.time_domain_metrics.settling_time = settling_time;
            else
                obj.time_domain_metrics.settling_time = inf;
            end
            
            % Rise time
            initial_value = response(1);
            target_value = final_value;
            rise_threshold = initial_value + 0.9 * (target_value - initial_value);
            rise_indices = response >= rise_threshold;
            if any(rise_indices)
                rise_time = time(find(rise_indices, 1)) - time(1);
                obj.time_domain_metrics.rise_time = rise_time;
            else
                obj.time_domain_metrics.rise_time = inf;
            end
            
            % Overshoot
            max_value = max(response);
            if max_value > final_value
                overshoot = (max_value - final_value) / final_value * 100;
                obj.time_domain_metrics.overshoot = overshoot;
            else
                obj.time_domain_metrics.overshoot = 0;
            end
            
            % Control effort
            obj.time_domain_metrics.total_energy = sum(control.^2);
            obj.time_domain_metrics.max_control = max(abs(control));
            obj.time_domain_metrics.control_variance = var(control);
            
            % Steady-state error
            steady_state_start = round(0.8 * length(response));
            steady_state_error = mean(abs(error(steady_state_start:end)));
            obj.time_domain_metrics.steady_state_error = steady_state_error;
            
            fprintf('Time-domain analysis completed.\n');
        end
        
        function frequency_analysis(obj)
            % Frequency response analysis
            fprintf('Running frequency analysis...\n');
            
            % Extract data
            time = obj.controller_data.time;
            reference = obj.reference_data.reference;
            response = obj.controller_data.response;
            
            % Calculate frequency response
            dt = time(2) - time(1);
            fs = 1/dt;
            
            % FFT analysis
            n = length(time);
            f = (0:n-1) * fs / n;
            
            % Calculate transfer function magnitude
            ref_fft = fft(reference);
            resp_fft = fft(response);
            
            % Avoid division by zero
            ref_fft_mag = abs(ref_fft);
            ref_fft_mag(ref_fft_mag < 1e-10) = 1e-10;
            
            tf_mag = abs(resp_fft) ./ ref_fft_mag;
            tf_phase = angle(resp_fft) - angle(ref_fft);
            
            % Store frequency response data
            obj.frequency_response = struct();
            obj.frequency_response.frequency = f(1:round(n/2));
            obj.frequency_response.magnitude = tf_mag(1:round(n/2));
            obj.frequency_response.phase = tf_phase(1:round(n/2));
            
            % Calculate frequency domain metrics
            % Bandwidth (frequency where magnitude drops to 0.707)
            bandwidth_idx = find(tf_mag(1:round(n/2)) <= 0.707, 1);
            if ~isempty(bandwidth_idx)
                obj.frequency_response.bandwidth = f(bandwidth_idx);
            else
                obj.frequency_response.bandwidth = f(end);
            end
            
            % Peak magnitude
            obj.frequency_response.peak_magnitude = max(tf_mag(1:round(n/2)));
            
            % Phase margin (simplified)
            phase_cross_idx = find(tf_phase(1:round(n/2)) <= -pi, 1);
            if ~isempty(phase_cross_idx)
                obj.frequency_response.phase_margin = abs(tf_phase(phase_cross_idx)) - pi;
            else
                obj.frequency_response.phase_margin = inf;
            end
            
            fprintf('Frequency analysis completed.\n');
        end
        
        function stability_analysis(obj)
            % Stability analysis
            fprintf('Running stability analysis...\n');
            
            % Extract data
            time = obj.controller_data.time;
            response = obj.controller_data.response;
            
            % Calculate stability metrics
            obj.stability_margins = struct();
            
            % Lyapunov stability (simplified)
            % Check if response is bounded
            max_response = max(abs(response));
            if max_response < inf
                obj.stability_margins.lyapunov_stable = true;
            else
                obj.stability_margins.lyapunov_stable = false;
            end
            
            % BIBO stability (Bounded Input, Bounded Output)
            % Check if output remains bounded for bounded input
            if max_response < 1000  % Arbitrary threshold
                obj.stability_margins.bibo_stable = true;
            else
                obj.stability_margins.bibo_stable = false;
            end
            
            % Asymptotic stability
            % Check if response converges to steady state
            final_value = response(end);
            steady_state_start = round(0.8 * length(response));
            steady_state_variance = var(response(steady_state_start:end));
            
            if steady_state_variance < 0.01  % Small variance threshold
                obj.stability_margins.asymptotically_stable = true;
            else
                obj.stability_margins.asymptotically_stable = false;
            end
            
            % Stability margin (distance from instability)
            % Simplified calculation based on response characteristics
            response_derivative = diff(response);
            max_derivative = max(abs(response_derivative));
            
            if max_derivative < 10  % Arbitrary threshold
                obj.stability_margins.stability_margin = 1.0;  % High stability
            elseif max_derivative < 50
                obj.stability_margins.stability_margin = 0.5;  % Medium stability
            else
                obj.stability_margins.stability_margin = 0.1;  % Low stability
            end
            
            fprintf('Stability analysis completed.\n');
        end
        
        function robustness_analysis(obj)
            % Robustness analysis
            fprintf('Running robustness analysis...\n');
            
            % Extract data
            time = obj.controller_data.time;
            reference = obj.reference_data.reference;
            response = obj.controller_data.response;
            
            % Calculate robustness metrics
            obj.robustness_metrics = struct();
            
            % Sensitivity to parameter variations
            % Simulate parameter variations and analyze response
            base_error = sqrt(mean((reference - response).^2));
            
            % Test robustness with different parameter variations
            variations = [0.8, 0.9, 1.1, 1.2];  % ±20% variations
            robustness_scores = zeros(length(variations), 1);
            
            for i = 1:length(variations)
                % Simulate response with parameter variation
                varied_response = response * variations(i) + 0.1 * randn(size(response));
                varied_error = sqrt(mean((reference - varied_response).^2));
                
                % Calculate robustness score
                robustness_scores(i) = base_error / varied_error;
            end
            
            % Overall robustness metric
            obj.robustness_metrics.parameter_robustness = mean(robustness_scores);
            obj.robustness_metrics.robustness_variance = var(robustness_scores);
            
            % Disturbance rejection
            % Add disturbances and analyze response
            disturbance_magnitude = 0.1;
            disturbed_response = response + disturbance_magnitude * sin(2*pi*0.5*time);
            disturbance_error = sqrt(mean((reference - disturbed_response).^2));
            
            obj.robustness_metrics.disturbance_rejection = base_error / disturbance_error;
            
            % Noise sensitivity
            noise_levels = [0.01, 0.05, 0.1, 0.2];
            noise_sensitivity = zeros(length(noise_levels), 1);
            
            for i = 1:length(noise_levels)
                noisy_response = response + noise_levels(i) * randn(size(response));
                noisy_error = sqrt(mean((reference - noisy_response).^2));
                noise_sensitivity(i) = base_error / noisy_error;
            end
            
            obj.robustness_metrics.noise_sensitivity = mean(noise_sensitivity);
            
            % Overall robustness score
            obj.robustness_metrics.overall_robustness = (obj.robustness_metrics.parameter_robustness + ...
                                                      obj.robustness_metrics.disturbance_rejection + ...
                                                      obj.robustness_metrics.noise_sensitivity) / 3;
            
            fprintf('Robustness analysis completed.\n');
        end
        
        function generate_performance_summary(obj)
            % Generate performance summary
            fprintf('\n=== PERFORMANCE SUMMARY ===\n');
            
            % Time-domain summary
            if isfield(obj.time_domain_metrics, 'rmse')
                fprintf('Time-Domain Metrics:\n');
                fprintf('  RMSE: %.6f\n', obj.time_domain_metrics.rmse);
                fprintf('  MAE: %.6f\n', obj.time_domain_metrics.mae);
                fprintf('  Settling Time: %.3f s\n', obj.time_domain_metrics.settling_time);
                fprintf('  Rise Time: %.3f s\n', obj.time_domain_metrics.rise_time);
                fprintf('  Overshoot: %.2f%%\n', obj.time_domain_metrics.overshoot);
                fprintf('  Steady-State Error: %.6f\n', obj.time_domain_metrics.steady_state_error);
            end
            
            % Stability summary
            if isfield(obj.stability_margins, 'lyapunov_stable')
                fprintf('\nStability Analysis:\n');
                fprintf('  Lyapunov Stable: %s\n', mat2str(obj.stability_margins.lyapunov_stable));
                fprintf('  BIBO Stable: %s\n', mat2str(obj.stability_margins.bibo_stable));
                fprintf('  Asymptotically Stable: %s\n', mat2str(obj.stability_margins.asymptotically_stable));
                fprintf('  Stability Margin: %.3f\n', obj.stability_margins.stability_margin);
            end
            
            % Frequency summary
            if isfield(obj.frequency_response, 'bandwidth')
                fprintf('\nFrequency Analysis:\n');
                fprintf('  Bandwidth: %.3f Hz\n', obj.frequency_response.bandwidth);
                fprintf('  Peak Magnitude: %.3f\n', obj.frequency_response.peak_magnitude);
                fprintf('  Phase Margin: %.3f rad\n', obj.frequency_response.phase_margin);
            end
            
            % Robustness summary
            if isfield(obj.robustness_metrics, 'overall_robustness')
                fprintf('\nRobustness Analysis:\n');
                fprintf('  Parameter Robustness: %.3f\n', obj.robustness_metrics.parameter_robustness);
                fprintf('  Disturbance Rejection: %.3f\n', obj.robustness_metrics.disturbance_rejection);
                fprintf('  Noise Sensitivity: %.3f\n', obj.robustness_metrics.noise_sensitivity);
                fprintf('  Overall Robustness: %.3f\n', obj.robustness_metrics.overall_robustness);
            end
        end
        
        function generate_comprehensive_report(obj)
            % Generate comprehensive performance report
            report_filename = fullfile(obj.output_directory, 'comprehensive_performance_report.txt');
            
            fid = fopen(report_filename, 'w');
            
            % Write report header
            fprintf(fid, '=== CRAZYFLY COMPREHENSIVE PERFORMANCE REPORT ===\n\n');
            fprintf(fid, 'Generated: %s\n', datestr(now));
            fprintf(fid, 'Analysis Type: %s\n\n', obj.analysis_type);
            
            % Time-domain metrics
            fprintf(fid, 'TIME-DOMAIN METRICS:\n');
            fprintf(fid, '===================\n');
            if isfield(obj.time_domain_metrics, 'rmse')
                fprintf(fid, 'Root Mean Square Error (RMSE): %.6f\n', obj.time_domain_metrics.rmse);
                fprintf(fid, 'Mean Absolute Error (MAE): %.6f\n', obj.time_domain_metrics.mae);
                fprintf(fid, 'Maximum Error: %.6f\n', obj.time_domain_metrics.max_error);
                fprintf(fid, 'Settling Time: %.3f seconds\n', obj.time_domain_metrics.settling_time);
                fprintf(fid, 'Rise Time: %.3f seconds\n', obj.time_domain_metrics.rise_time);
                fprintf(fid, 'Overshoot: %.2f%%\n', obj.time_domain_metrics.overshoot);
                fprintf(fid, 'Steady-State Error: %.6f\n', obj.time_domain_metrics.steady_state_error);
                fprintf(fid, 'Total Control Energy: %.6f\n', obj.time_domain_metrics.total_energy);
                fprintf(fid, 'Maximum Control Effort: %.6f\n', obj.time_domain_metrics.max_control);
                fprintf(fid, 'Control Variance: %.6f\n\n', obj.time_domain_metrics.control_variance);
            end
            
            % Stability analysis
            fprintf(fid, 'STABILITY ANALYSIS:\n');
            fprintf(fid, '==================\n');
            if isfield(obj.stability_margins, 'lyapunov_stable')
                fprintf(fid, 'Lyapunov Stability: %s\n', mat2str(obj.stability_margins.lyapunov_stable));
                fprintf(fid, 'BIBO Stability: %s\n', mat2str(obj.stability_margins.bibo_stable));
                fprintf(fid, 'Asymptotic Stability: %s\n', mat2str(obj.stability_margins.asymptotically_stable));
                fprintf(fid, 'Stability Margin: %.3f\n\n', obj.stability_margins.stability_margin);
            end
            
            % Frequency analysis
            fprintf(fid, 'FREQUENCY ANALYSIS:\n');
            fprintf(fid, '===================\n');
            if isfield(obj.frequency_response, 'bandwidth')
                fprintf(fid, 'System Bandwidth: %.3f Hz\n', obj.frequency_response.bandwidth);
                fprintf(fid, 'Peak Magnitude: %.3f\n', obj.frequency_response.peak_magnitude);
                fprintf(fid, 'Phase Margin: %.3f radians\n\n', obj.frequency_response.phase_margin);
            end
            
            % Robustness analysis
            fprintf(fid, 'ROBUSTNESS ANALYSIS:\n');
            fprintf(fid, '====================\n');
            if isfield(obj.robustness_metrics, 'overall_robustness')
                fprintf(fid, 'Parameter Robustness: %.3f\n', obj.robustness_metrics.parameter_robustness);
                fprintf(fid, 'Disturbance Rejection: %.3f\n', obj.robustness_metrics.disturbance_rejection);
                fprintf(fid, 'Noise Sensitivity: %.3f\n', obj.robustness_metrics.noise_sensitivity);
                fprintf(fid, 'Overall Robustness Score: %.3f\n\n', obj.robustness_metrics.overall_robustness);
            end
            
            % Performance assessment
            fprintf(fid, 'PERFORMANCE ASSESSMENT:\n');
            fprintf(fid, '======================\n');
            
            % Overall performance score
            overall_score = 0;
            max_score = 0;
            
            if isfield(obj.time_domain_metrics, 'rmse')
                % Time-domain score (0-40 points)
                rmse_score = max(0, 40 - obj.time_domain_metrics.rmse * 100);
                settling_score = max(0, 20 - obj.time_domain_metrics.settling_time * 10);
                overshoot_score = max(0, 20 - obj.time_domain_metrics.overshoot * 2);
                overall_score = overall_score + rmse_score + settling_score + overshoot_score;
                max_score = max_score + 80;
            end
            
            if isfield(obj.stability_margins, 'stability_margin')
                % Stability score (0-20 points)
                stability_score = obj.stability_margins.stability_margin * 20;
                overall_score = overall_score + stability_score;
                max_score = max_score + 20;
            end
            
            if isfield(obj.robustness_metrics, 'overall_robustness')
                % Robustness score (0-20 points)
                robustness_score = obj.robustness_metrics.overall_robustness * 20;
                overall_score = overall_score + robustness_score;
                max_score = max_score + 20;
            end
            
            if max_score > 0
                performance_percentage = (overall_score / max_score) * 100;
                fprintf(fid, 'Overall Performance Score: %.1f%% (%.1f/%.1f)\n', ...
                        performance_percentage, overall_score, max_score);
                
                if performance_percentage >= 90
                    fprintf(fid, 'Performance Rating: EXCELLENT\n');
                elseif performance_percentage >= 80
                    fprintf(fid, 'Performance Rating: GOOD\n');
                elseif performance_percentage >= 70
                    fprintf(fid, 'Performance Rating: SATISFACTORY\n');
                elseif performance_percentage >= 60
                    fprintf(fid, 'Performance Rating: NEEDS IMPROVEMENT\n');
                else
                    fprintf(fid, 'Performance Rating: POOR\n');
                end
            end
            
            fclose(fid);
            fprintf('Comprehensive report generated: %s\n', report_filename);
        end
        
        function plot_performance_analysis(obj)
            % Plot performance analysis results
            if ~obj.plot_enabled
                return;
            end
            
            fprintf('Generating performance analysis plots...\n');
            
            % Create figure with subplots
            figure('Position', [100, 100, 1400, 1000]);
            
            % Time-domain plots
            if isfield(obj.controller_data, 'time')
                % Time response
                subplot(3, 3, 1);
                plot(obj.controller_data.time, obj.reference_data.reference, 'b--', 'LineWidth', 2);
                hold on;
                plot(obj.controller_data.time, obj.controller_data.response, 'r-', 'LineWidth', 2);
                title('Time Response');
                xlabel('Time (s)');
                ylabel('Amplitude');
                legend('Reference', 'Response', 'Location', 'best');
                grid on;
                
                % Error
                subplot(3, 3, 2);
                error = obj.reference_data.reference - obj.controller_data.response;
                plot(obj.controller_data.time, error, 'g-', 'LineWidth', 2);
                title('Tracking Error');
                xlabel('Time (s)');
                ylabel('Error');
                grid on;
                
                % Control effort
                subplot(3, 3, 3);
                plot(obj.controller_data.time, obj.controller_data.control, 'm-', 'LineWidth', 2);
                title('Control Effort');
                xlabel('Time (s)');
                ylabel('Control Signal');
                grid on;
            end
            
            % Frequency response plots
            if isfield(obj.frequency_response, 'frequency')
                % Magnitude response
                subplot(3, 3, 4);
                semilogx(obj.frequency_response.frequency, 20*log10(obj.frequency_response.magnitude), 'b-', 'LineWidth', 2);
                title('Frequency Response - Magnitude');
                xlabel('Frequency (Hz)');
                ylabel('Magnitude (dB)');
                grid on;
                
                % Phase response
                subplot(3, 3, 5);
                semilogx(obj.frequency_response.frequency, obj.frequency_response.phase * 180/pi, 'r-', 'LineWidth', 2);
                title('Frequency Response - Phase');
                xlabel('Frequency (Hz)');
                ylabel('Phase (degrees)');
                grid on;
                
                % Bode plot
                subplot(3, 3, 6);
                yyaxis left;
                semilogx(obj.frequency_response.frequency, 20*log10(obj.frequency_response.magnitude), 'b-', 'LineWidth', 2);
                ylabel('Magnitude (dB)');
                yyaxis right;
                semilogx(obj.frequency_response.frequency, obj.frequency_response.phase * 180/pi, 'r-', 'LineWidth', 2);
                ylabel('Phase (degrees)');
                xlabel('Frequency (Hz)');
                title('Bode Plot');
                grid on;
            end
            
            % Performance metrics plots
            if isfield(obj.time_domain_metrics, 'rmse')
                % Metrics comparison
                subplot(3, 3, 7);
                metrics_names = {'RMSE', 'MAE', 'Max Error', 'SS Error'};
                metrics_values = [obj.time_domain_metrics.rmse, obj.time_domain_metrics.mae, ...
                                 obj.time_domain_metrics.max_error, obj.time_domain_metrics.steady_state_error];
                bar(metrics_values, 'FaceColor', 'c');
                set(gca, 'XTickLabel', metrics_names);
                title('Error Metrics');
                ylabel('Error Value');
                grid on;
                
                % Time metrics
                subplot(3, 3, 8);
                time_metrics_names = {'Settling Time', 'Rise Time'};
                time_metrics_values = [obj.time_domain_metrics.settling_time, obj.time_domain_metrics.rise_time];
                bar(time_metrics_values, 'FaceColor', 'g');
                set(gca, 'XTickLabel', time_metrics_names);
                title('Time Metrics');
                ylabel('Time (s)');
                grid on;
            end
            
            % Robustness metrics
            if isfield(obj.robustness_metrics, 'overall_robustness')
                subplot(3, 3, 9);
                robustness_names = {'Param Robust', 'Disturb Reject', 'Noise Sens', 'Overall'};
                robustness_values = [obj.robustness_metrics.parameter_robustness, ...
                                   obj.robustness_metrics.disturbance_rejection, ...
                                   obj.robustness_metrics.noise_sensitivity, ...
                                   obj.robustness_metrics.overall_robustness];
                bar(robustness_values, 'FaceColor', 'y');
                set(gca, 'XTickLabel', robustness_names);
                title('Robustness Metrics');
                ylabel('Robustness Score');
                grid on;
            end
            
            sgtitle('CrazyFly Performance Analysis Results', 'FontSize', 16);
            
            % Save plot if requested
            if obj.save_plots
                plot_filename = fullfile(obj.output_directory, sprintf('performance_analysis.%s', obj.plot_format));
                saveas(gcf, plot_filename, obj.plot_format);
                fprintf('Performance analysis plot saved: %s\n', plot_filename);
            end
        end
        
        function export_analysis_results(obj, filename)
            % Export analysis results
            if nargin < 2
                filename = fullfile(obj.output_directory, 'analysis_results.mat');
            end
            
            results = struct();
            results.time_domain_metrics = obj.time_domain_metrics;
            results.stability_margins = obj.stability_margins;
            results.frequency_response = obj.frequency_response;
            results.robustness_metrics = obj.robustness_metrics;
            results.analysis_settings = struct('analysis_type', obj.analysis_type, ...
                                             'plot_enabled', obj.plot_enabled, ...
                                             'save_plots', obj.save_plots);
            
            save(filename, 'results');
            fprintf('Analysis results exported to: %s\n', filename);
        end
    end
end

% Example usage and demonstration
function demo_performance_analyzer()
    % Demonstration of the PerformanceAnalyzer class
    
    fprintf('=== CrazyFly Performance Analyzer Demo ===\n\n');
    
    % Create analyzer instance
    analyzer = PerformanceAnalyzer();
    
    % Generate sample data
    t = 0:0.01:10;
    reference = ones(size(t));
    response = reference + 0.1*exp(-t) + 0.05*sin(2*pi*0.5*t) + 0.02*randn(size(t));
    control = 0.5*ones(size(t)) + 0.1*exp(-t) + 0.05*randn(size(t));
    
    % Create sample data structure
    sample_data = struct();
    sample_data.time = t;
    sample_data.response = response;
    sample_data.control = control;
    
    reference_data = struct();
    reference_data.reference = reference;
    
    % Load data
    analyzer.load_controller_data(sample_data);
    analyzer.load_reference_data(reference_data);
    
    % Configure analyzer
    analyzer.set_analysis_type('comprehensive');
    analyzer.plot_enabled = true;
    analyzer.save_plots = true;
    
    % Run analysis
    fprintf('Starting performance analysis...\n');
    analyzer.analyze_performance();
    
    % Generate plots
    analyzer.plot_performance_analysis();
    
    % Export results
    analyzer.export_analysis_results();
    
    fprintf('\nDemo completed successfully!\n');
    fprintf('Check the generated plots and reports for results.\n');
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
        demo_performance_analyzer();
    end
else
    % Octave
    if exist('OCTAVE_VERSION', 'builtin')
        demo_performance_analyzer();
    end
end
