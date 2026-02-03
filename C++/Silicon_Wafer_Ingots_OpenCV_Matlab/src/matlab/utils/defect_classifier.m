function defect_classification = defect_classifier(detection_results, varargin)
%DEFECT_CLASSIFIER Rule-based classification of detected features
%
% Inputs:
%   detection_results - Structure containing all detection results
%   varargin - Optional parameters:
%     'classification_rules' - Custom classification rules
%     'severity_thresholds' - Thresholds for severity classification
%     'output_format' - Output format ('struct', 'table', 'json')
%
% Outputs:
%   defect_classification - Classification results

    % Parse input parameters
    p = inputParser;
    addParameter(p, 'classification_rules', 'default', @ischar);
    addParameter(p, 'severity_thresholds', struct('low', 0.3, 'medium', 0.6, 'high', 0.8), @isstruct);
    addParameter(p, 'output_format', 'struct', @ischar);
    parse(p, varargin{:});
    
    params = p.Results;
    
    fprintf('Classifying detected defects...\n');
    
    % Initialize classification structure
    defect_classification = struct();
    defect_classification.overall_quality = 'Unknown';
    defect_classification.defect_summary = struct();
    defect_classification.severity_levels = struct();
    defect_classification.recommendations = {};
    
    % Classify each defect type
    defect_classification.defect_summary.oxygen_precipitation = classifyOxygenPrecipitation(detection_results, params);
    defect_classification.defect_summary.dislocation = classifyDislocation(detection_results, params);
    defect_classification.defect_summary.swirl_defect = classifySwirlDefect(detection_results, params);
    defect_classification.defect_summary.void_cop = classifyVoidCOP(detection_results, params);
    defect_classification.defect_summary.crack = classifyCrack(detection_results, params);
    defect_classification.defect_summary.dopant_uniformity = classifyDopantUniformity(detection_results, params);
    
    % Determine overall quality
    defect_classification.overall_quality = determineOverallQuality(defect_classification.defect_summary, params);
    
    % Generate recommendations
    defect_classification.recommendations = generateClassificationRecommendations(defect_classification.defect_summary);
    
    % Display results
    fprintf('Overall quality: %s\n', defect_classification.overall_quality);
    
    % Visualization
    figure('Name', 'Defect Classification Results');
    
    % Create classification summary
    subplot(2, 2, 1);
    classification_data = getClassificationData(defect_classification.defect_summary);
    bar(classification_data);
    title('Defect Classification Summary');
    xlabel('Defect Type');
    ylabel('Severity Level');
    set(gca, 'XTickLabel', {'Oxygen', 'Dislocation', 'Swirl', 'Void/COP', 'Crack', 'Dopant'});
    set(gca, 'YTickLabel', {'Low', 'Medium', 'High'});
    
    % Overall quality pie chart
    subplot(2, 2, 2);
    quality_scores = getQualityScores(defect_classification.defect_summary);
    pie(quality_scores, {'Good', 'Acceptable', 'Poor'});
    title('Overall Quality Distribution');
    
    % Severity distribution
    subplot(2, 2, 3);
    severity_counts = getSeverityCounts(defect_classification.defect_summary);
    bar(severity_counts);
    title('Severity Level Distribution');
    xlabel('Severity Level');
    ylabel('Number of Defect Types');
    
    % Recommendations
    subplot(2, 2, 4);
    text(0.1, 0.9, 'Key Recommendations:', 'FontSize', 12, 'FontWeight', 'bold');
    if ~isempty(defect_classification.recommendations)
        for i = 1:min(5, length(defect_classification.recommendations))
            text(0.1, 0.8 - (i-1)*0.15, sprintf('%d. %s', i, defect_classification.recommendations{i}), ...
                 'FontSize', 10, 'VerticalAlignment', 'top');
        end
    end
    title('Recommendations');
    axis off;
    
    % Save results
    assignin('base', 'defect_classification', defect_classification);
    
end

function classification = classifyOxygenPrecipitation(detection_results, params)
    % Classify oxygen precipitation defects
    
    classification = struct();
    classification.type = 'Oxygen Precipitation';
    classification.severity = 'Low';
    classification.score = 0;
    classification.count = 0;
    classification.description = 'No significant oxygen precipitation detected';
    
    if isfield(detection_results, 'oxygen_precipitation')
        results = detection_results.oxygen_precipitation;
        count = length(results.precipitate_locations);
        classification.count = count;
        
        % Calculate severity score
        if count > 0
            avg_size = mean(results.size_distribution);
            severity_score = min(1.0, (count / 100) + (avg_size / 1000));
            classification.score = severity_score;
            
            % Classify severity
            if severity_score < params.severity_thresholds.low
                classification.severity = 'Low';
                classification.description = 'Minimal oxygen precipitation detected';
            elseif severity_score < params.severity_thresholds.medium
                classification.severity = 'Medium';
                classification.description = 'Moderate oxygen precipitation detected';
            else
                classification.severity = 'High';
                classification.description = 'Significant oxygen precipitation detected';
            end
        end
    end
    
end

function classification = classifyDislocation(detection_results, params)
    % Classify dislocation defects
    
    classification = struct();
    classification.type = 'Dislocation';
    classification.severity = 'Low';
    classification.score = 0;
    classification.count = 0;
    classification.description = 'No significant dislocations detected';
    
    if isfield(detection_results, 'dislocation')
        results = detection_results.dislocation;
        count = length(results.dislocation_lines);
        classification.count = count;
        
        % Calculate severity score
        if count > 0
            avg_density = mean(results.dislocation_density(:));
            severity_score = min(1.0, avg_density * 1000);
            classification.score = severity_score;
            
            % Classify severity
            if severity_score < params.severity_thresholds.low
                classification.severity = 'Low';
                classification.description = 'Minimal dislocation density detected';
            elseif severity_score < params.severity_thresholds.medium
                classification.severity = 'Medium';
                classification.description = 'Moderate dislocation density detected';
            else
                classification.severity = 'High';
                classification.description = 'High dislocation density detected';
            end
        end
    end
    
end

function classification = classifySwirlDefect(detection_results, params)
    % Classify swirl defects
    
    classification = struct();
    classification.type = 'Swirl Defect';
    classification.severity = 'Low';
    classification.score = 0;
    classification.count = 0;
    classification.description = 'No significant swirl defects detected';
    
    if isfield(detection_results, 'swirl_defect')
        results = detection_results.swirl_defect;
        count = results.swirl_properties.num_regions;
        classification.count = count;
        classification.score = results.severity_score;
        
        % Classify severity
        if results.severity_score < params.severity_thresholds.low
            classification.severity = 'Low';
            classification.description = 'Minimal swirl defects detected';
        elseif results.severity_score < params.severity_thresholds.medium
            classification.severity = 'Medium';
            classification.description = 'Moderate swirl defects detected';
        else
            classification.severity = 'High';
            classification.description = 'Significant swirl defects detected';
        end
    end
    
end

function classification = classifyVoidCOP(detection_results, params)
    % Classify void and COP defects
    
    classification = struct();
    classification.type = 'Void/COP';
    classification.severity = 'Low';
    classification.score = 0;
    classification.count = 0;
    classification.description = 'No significant voids or COPs detected';
    
    if isfield(detection_results, 'void_cop')
        results = detection_results.void_cop;
        void_count = length(results.void_locations);
        cop_count = length(results.cop_locations);
        total_count = void_count + cop_count;
        classification.count = total_count;
        
        % Calculate severity score
        if total_count > 0
            avg_void_size = mean(results.void_sizes);
            avg_cop_size = mean(results.cop_sizes);
            severity_score = min(1.0, (total_count / 50) + (avg_void_size / 100) + (avg_cop_size / 20));
            classification.score = severity_score;
            
            % Classify severity
            if severity_score < params.severity_thresholds.low
                classification.severity = 'Low';
                classification.description = 'Minimal voids and COPs detected';
            elseif severity_score < params.severity_thresholds.medium
                classification.severity = 'Medium';
                classification.description = 'Moderate voids and COPs detected';
            else
                classification.severity = 'High';
                classification.description = 'Significant voids and COPs detected';
            end
        end
    end
    
end

function classification = classifyCrack(detection_results, params)
    % Classify crack defects
    
    classification = struct();
    classification.type = 'Crack';
    classification.severity = 'Low';
    classification.score = 0;
    classification.count = 0;
    classification.description = 'No significant cracks detected';
    
    if isfield(detection_results, 'crack')
        results = detection_results.crack;
        count = length(results.crack_lengths);
        classification.count = count;
        classification.score = results.crack_properties.severity_score;
        
        % Classify severity
        if results.crack_properties.severity_score < params.severity_thresholds.low
            classification.severity = 'Low';
            classification.description = 'Minimal cracks detected';
        elseif results.crack_properties.severity_score < params.severity_thresholds.medium
            classification.severity = 'Medium';
            classification.description = 'Moderate cracks detected';
        else
            classification.severity = 'High';
            classification.description = 'Significant cracks detected';
        end
    end
    
end

function classification = classifyDopantUniformity(detection_results, params)
    % Classify dopant uniformity
    
    classification = struct();
    classification.type = 'Dopant Uniformity';
    classification.severity = 'Low';
    classification.score = 0;
    classification.count = 0;
    classification.description = 'Good dopant uniformity';
    
    if isfield(detection_results, 'dopant_uniformity')
        results = detection_results.dopant_uniformity;
        uniformity_score = results.uniformity_score;
        classification.score = 1 - uniformity_score; % Invert for severity
        
        % Classify severity
        if uniformity_score > 0.8
            classification.severity = 'Low';
            classification.description = 'Excellent dopant uniformity';
        elseif uniformity_score > 0.6
            classification.severity = 'Medium';
            classification.description = 'Acceptable dopant uniformity';
        else
            classification.severity = 'High';
            classification.description = 'Poor dopant uniformity';
        end
    end
    
end

function overall_quality = determineOverallQuality(defect_summary, params)
    % Determine overall quality based on all defect classifications
    
    % Count severity levels
    severity_counts = struct('Low', 0, 'Medium', 0, 'High', 0);
    
    fields = fieldnames(defect_summary);
    for i = 1:length(fields)
        field = fields{i};
        if isfield(defect_summary.(field), 'severity')
            severity = defect_summary.(field).severity;
            if isfield(severity_counts, severity)
                severity_counts.(severity) = severity_counts.(severity) + 1;
            end
        end
    end
    
    % Determine overall quality
    if severity_counts.High > 0
        overall_quality = 'Poor';
    elseif severity_counts.Medium > 2
        overall_quality = 'Acceptable';
    elseif severity_counts.Medium > 0
        overall_quality = 'Good';
    else
        overall_quality = 'Excellent';
    end
    
end

function recommendations = generateClassificationRecommendations(defect_summary)
    % Generate recommendations based on classification results
    
    recommendations = {};
    
    fields = fieldnames(defect_summary);
    for i = 1:length(fields)
        field = fields{i};
        if isfield(defect_summary.(field), 'severity')
            severity = defect_summary.(field).severity;
            type = defect_summary.(field).type;
            
            if strcmp(severity, 'High')
                switch type
                    case 'Oxygen Precipitation'
                        recommendations{end+1} = 'Urgent: Address oxygen contamination in crucible and growth process';
                    case 'Dislocation'
                        recommendations{end+1} = 'Urgent: Review thermal stress management and cooling procedures';
                    case 'Swirl Defect'
                        recommendations{end+1} = 'Urgent: Optimize rotation parameters and temperature gradients';
                    case 'Void/COP'
                        recommendations{end+1} = 'Urgent: Review pulling rate and temperature control';
                    case 'Crack'
                        recommendations{end+1} = 'Urgent: Improve cooling procedures and handling protocols';
                    case 'Dopant Uniformity'
                        recommendations{end+1} = 'Urgent: Optimize doping process and melt convection';
                end
            elseif strcmp(severity, 'Medium')
                switch type
                    case 'Oxygen Precipitation'
                        recommendations{end+1} = 'Monitor oxygen levels and consider crucible improvements';
                    case 'Dislocation'
                        recommendations{end+1} = 'Monitor thermal stress and consider process optimization';
                    case 'Swirl Defect'
                        recommendations{end+1} = 'Monitor rotation parameters and temperature control';
                    case 'Void/COP'
                        recommendations{end+1} = 'Monitor pulling rate and temperature stability';
                    case 'Crack'
                        recommendations{end+1} = 'Monitor cooling procedures and handling practices';
                    case 'Dopant Uniformity'
                        recommendations{end+1} = 'Monitor doping process and consider optimization';
                end
            end
        end
    end
    
    if isempty(recommendations)
        recommendations{end+1} = 'Continue current process parameters - no significant issues detected';
    end
    
end

function classification_data = getClassificationData(defect_summary)
    % Get classification data for visualization
    
    classification_data = zeros(6, 3); % 6 defect types, 3 severity levels
    
    fields = fieldnames(defect_summary);
    for i = 1:length(fields)
        field = fields{i};
        if isfield(defect_summary.(field), 'severity')
            severity = defect_summary.(field).severity;
            switch severity
                case 'Low'
                    classification_data(i, 1) = 1;
                case 'Medium'
                    classification_data(i, 2) = 1;
                case 'High'
                    classification_data(i, 3) = 1;
            end
        end
    end
    
end

function quality_scores = getQualityScores(defect_summary)
    % Get quality scores for pie chart
    
    quality_scores = [0, 0, 0]; % Good, Acceptable, Poor
    
    fields = fieldnames(defect_summary);
    for i = 1:length(fields)
        field = fields{i};
        if isfield(defect_summary.(field), 'severity')
            severity = defect_summary.(field).severity;
            switch severity
                case 'Low'
                    quality_scores(1) = quality_scores(1) + 1;
                case 'Medium'
                    quality_scores(2) = quality_scores(2) + 1;
                case 'High'
                    quality_scores(3) = quality_scores(3) + 1;
            end
        end
    end
    
    % Normalize
    total = sum(quality_scores);
    if total > 0
        quality_scores = quality_scores / total;
    end
    
end

function severity_counts = getSeverityCounts(defect_summary)
    % Get severity level counts
    
    severity_counts = [0, 0, 0]; % Low, Medium, High
    
    fields = fieldnames(defect_summary);
    for i = 1:length(fields)
        field = fields{i};
        if isfield(defect_summary.(field), 'severity')
            severity = defect_summary.(field).severity;
            switch severity
                case 'Low'
                    severity_counts(1) = severity_counts(1) + 1;
                case 'Medium'
                    severity_counts(2) = severity_counts(2) + 1;
                case 'High'
                    severity_counts(3) = severity_counts(3) + 1;
            end
        end
    end
    
end
