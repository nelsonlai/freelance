function generate_report(detection_results, varargin)
%GENERATE_REPORT Create comprehensive defect detection report
%
% Inputs:
%   detection_results - Structure containing all detection results
%   varargin - Optional parameters:
%     'output_format' - Output format ('html', 'pdf', 'txt')
%     'output_dir' - Output directory
%     'include_images' - Include images in report (true/false)
%     'detailed_analysis' - Include detailed analysis (true/false)
%
% Outputs:
%   report_filename - Path to generated report file

    % Parse input parameters
    p = inputParser;
    addParameter(p, 'output_format', 'html', @ischar);
    addParameter(p, 'output_dir', 'data/output/reports', @ischar);
    addParameter(p, 'include_images', true, @islogical);
    addParameter(p, 'detailed_analysis', true, @islogical);
    parse(p, varargin{:});
    
    params = p.Results;
    
    % Create output directory if it doesn't exist
    if ~exist(params.output_dir, 'dir')
        mkdir(params.output_dir);
    end
    
    % Generate timestamp
    timestamp = datestr(now, 'yyyymmdd_HHMMSS');
    
    % Generate report based on format
    switch params.output_format
        case 'html'
            report_filename = generateHTMLReport(detection_results, params, timestamp);
        case 'pdf'
            report_filename = generatePDFReport(detection_results, params, timestamp);
        case 'txt'
            report_filename = generateTextReport(detection_results, params, timestamp);
        otherwise
            error('Unknown output format: %s', params.output_format);
    end
    
    fprintf('Report generated: %s\n', report_filename);
    
end

function report_filename = generateHTMLReport(detection_results, params, timestamp)
    % Generate HTML report
    
    report_filename = fullfile(params.output_dir, sprintf('defect_report_%s.html', timestamp));
    
    % Open file for writing
    fid = fopen(report_filename, 'w');
    
    % Write HTML header
    fprintf(fid, '<!DOCTYPE html>\n');
    fprintf(fid, '<html>\n<head>\n');
    fprintf(fid, '<title>Silicon Wafer Defect Detection Report</title>\n');
    fprintf(fid, '<style>\n');
    fprintf(fid, 'body { font-family: Arial, sans-serif; margin: 20px; }\n');
    fprintf(fid, 'h1 { color: #333; }\n');
    fprintf(fid, 'h2 { color: #666; }\n');
    fprintf(fid, 'table { border-collapse: collapse; width: 100%%; }\n');
    fprintf(fid, 'th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }\n');
    fprintf(fid, 'th { background-color: #f2f2f2; }\n');
    fprintf(fid, '.summary { background-color: #e7f3ff; padding: 15px; margin: 10px 0; }\n');
    fprintf(fid, '.defect-section { margin: 20px 0; }\n');
    fprintf(fid, '</style>\n');
    fprintf(fid, '</head>\n<body>\n');
    
    % Write report title
    fprintf(fid, '<h1>Silicon Wafer Defect Detection Report</h1>\n');
    fprintf(fid, '<p><strong>Generated:</strong> %s</p>\n', datestr(now, 'yyyy-mm-dd HH:MM:SS'));
    
    % Write summary
    writeSummarySection(fid, detection_results);
    
    % Write detailed sections for each defect type
    writeDefectSections(fid, detection_results, params);
    
    % Write HTML footer
    fprintf(fid, '</body>\n</html>\n');
    
    % Close file
    fclose(fid);
    
end

function report_filename = generatePDFReport(detection_results, params, timestamp)
    % Generate PDF report (simplified - would need additional tools)
    
    report_filename = fullfile(params.output_dir, sprintf('defect_report_%s.pdf', timestamp));
    
    % Create a figure for the report
    figure('Position', [100, 100, 800, 600], 'Visible', 'off');
    
    % Create report content
    subplot(2, 2, 1);
    text(0.1, 0.9, 'Silicon Wafer Defect Detection Report', 'FontSize', 16, 'FontWeight', 'bold');
    text(0.1, 0.8, sprintf('Generated: %s', datestr(now, 'yyyy-mm-dd HH:MM:SS')), 'FontSize', 12);
    
    % Add summary information
    summary_text = generateSummaryText(detection_results);
    text(0.1, 0.6, summary_text, 'FontSize', 10, 'VerticalAlignment', 'top');
    
    % Add defect statistics
    subplot(2, 2, 2);
    defect_counts = getDefectCounts(detection_results);
    bar(defect_counts);
    title('Defect Counts by Type');
    xlabel('Defect Type');
    ylabel('Count');
    
    % Add severity scores
    subplot(2, 2, 3);
    severity_scores = getSeverityScores(detection_results);
    bar(severity_scores);
    title('Severity Scores');
    xlabel('Defect Type');
    ylabel('Severity (0-1)');
    
    % Add recommendations
    subplot(2, 2, 4);
    recommendations = generateRecommendations(detection_results);
    text(0.1, 0.9, 'Recommendations:', 'FontSize', 12, 'FontWeight', 'bold');
    text(0.1, 0.7, recommendations, 'FontSize', 10, 'VerticalAlignment', 'top');
    
    % Save as PDF
    print(report_filename, '-dpdf', '-r300');
    close(gcf);
    
end

function report_filename = generateTextReport(detection_results, params, timestamp)
    % Generate text report
    
    report_filename = fullfile(params.output_dir, sprintf('defect_report_%s.txt', timestamp));
    
    % Open file for writing
    fid = fopen(report_filename, 'w');
    
    % Write header
    fprintf(fid, 'SILICON WAFER DEFECT DETECTION REPORT\n');
    fprintf(fid, '=====================================\n\n');
    fprintf(fid, 'Generated: %s\n\n', datestr(now, 'yyyy-mm-dd HH:MM:SS'));
    
    % Write summary
    writeSummarySection(fid, detection_results);
    
    % Write detailed sections
    writeDefectSections(fid, detection_results, params);
    
    % Write recommendations
    writeRecommendationsSection(fid, detection_results);
    
    % Close file
    fclose(fid);
    
end

function writeSummarySection(fid, detection_results)
    % Write summary section
    
    fprintf(fid, '<div class="summary">\n');
    fprintf(fid, '<h2>Summary</h2>\n');
    
    % Count defects
    defect_counts = getDefectCounts(detection_results);
    severity_scores = getSeverityScores(detection_results);
    
    fprintf(fid, '<table>\n');
    fprintf(fid, '<tr><th>Defect Type</th><th>Count</th><th>Severity Score</th></tr>\n');
    
    defect_types = {'Oxygen Precipitates', 'Dislocations', 'Swirl Defects', 'Voids/COPs', 'Cracks', 'Dopant Variation'};
    
    for i = 1:length(defect_types)
        fprintf(fid, '<tr><td>%s</td><td>%d</td><td>%.3f</td></tr>\n', ...
                defect_types{i}, defect_counts(i), severity_scores(i));
    end
    
    fprintf(fid, '</table>\n');
    fprintf(fid, '</div>\n\n');
    
end

function writeDefectSections(fid, detection_results, params)
    % Write detailed sections for each defect type
    
    % Oxygen precipitation
    if isfield(detection_results, 'oxygen_precipitation')
        fprintf(fid, '<div class="defect-section">\n');
        fprintf(fid, '<h2>Oxygen Precipitation Analysis</h2>\n');
        
        results = detection_results.oxygen_precipitation;
        fprintf(fid, '<p><strong>Precipitates detected:</strong> %d</p>\n', length(results.precipitate_locations));
        fprintf(fid, '<p><strong>Average size:</strong> %.2f pixels</p>\n', mean(results.size_distribution));
        fprintf(fid, '<p><strong>Stacking faults:</strong> %d</p>\n', length(results.stacking_fault_lines));
        
        fprintf(fid, '</div>\n\n');
    end
    
    % Dislocations
    if isfield(detection_results, 'dislocation')
        fprintf(fid, '<div class="defect-section">\n');
        fprintf(fid, '<h2>Dislocation Analysis</h2>\n');
        
        results = detection_results.dislocation;
        fprintf(fid, '<p><strong>Dislocation lines:</strong> %d</p>\n', length(results.dislocation_lines));
        fprintf(fid, '<p><strong>Average density:</strong> %.4f lines/pixel²</p>\n', mean(results.dislocation_density(:)));
        
        fprintf(fid, '</div>\n\n');
    end
    
    % Swirl defects
    if isfield(detection_results, 'swirl_defect')
        fprintf(fid, '<div class="defect-section">\n');
        fprintf(fid, '<h2>Swirl Defect Analysis</h2>\n');
        
        results = detection_results.swirl_defect;
        fprintf(fid, '<p><strong>Severity score:</strong> %.3f</p>\n', results.severity_score);
        fprintf(fid, '<p><strong>Swirl regions:</strong> %d</p>\n', results.swirl_properties.num_regions);
        
        fprintf(fid, '</div>\n\n');
    end
    
    % Voids and COPs
    if isfield(detection_results, 'void_cop')
        fprintf(fid, '<div class="defect-section">\n');
        fprintf(fid, '<h2>Void and COP Analysis</h2>\n');
        
        results = detection_results.void_cop;
        fprintf(fid, '<p><strong>Voids detected:</strong> %d</p>\n', length(results.void_locations));
        fprintf(fid, '<p><strong>COPs detected:</strong> %d</p>\n', length(results.cop_locations));
        fprintf(fid, '<p><strong>Average void size:</strong> %.2f pixels</p>\n', mean(results.void_sizes));
        fprintf(fid, '<p><strong>Average COP size:</strong> %.2f pixels</p>\n', mean(results.cop_sizes));
        
        fprintf(fid, '</div>\n\n');
    end
    
    % Cracks
    if isfield(detection_results, 'crack')
        fprintf(fid, '<div class="defect-section">\n');
        fprintf(fid, '<h2>Crack Analysis</h2>\n');
        
        results = detection_results.crack;
        fprintf(fid, '<p><strong>Crack segments:</strong> %d</p>\n', length(results.crack_lengths));
        fprintf(fid, '<p><strong>Average width:</strong> %.2f pixels</p>\n', mean(results.crack_widths));
        fprintf(fid, '<p><strong>Average length:</strong> %.2f pixels</p>\n', mean(results.crack_lengths));
        fprintf(fid, '<p><strong>Junctions:</strong> %d</p>\n', results.crack_topology.num_junctions);
        
        fprintf(fid, '</div>\n\n');
    end
    
    % Dopant uniformity
    if isfield(detection_results, 'dopant_uniformity')
        fprintf(fid, '<div class="defect-section">\n');
        fprintf(fid, '<h2>Dopant Uniformity Analysis</h2>\n');
        
        results = detection_results.dopant_uniformity;
        fprintf(fid, '<p><strong>Uniformity score:</strong> %.3f</p>\n', results.uniformity_score);
        fprintf(fid, '<p><strong>Coefficient of variation:</strong> %.2f%%</p>\n', ...
                results.variation_analysis.coefficient_variation * 100);
        
        fprintf(fid, '</div>\n\n');
    end
    
end

function writeRecommendationsSection(fid, detection_results)
    % Write recommendations section
    
    fprintf(fid, '<h2>Recommendations</h2>\n');
    
    recommendations = generateRecommendations(detection_results);
    
    fprintf(fid, '<ul>\n');
    for i = 1:length(recommendations)
        fprintf(fid, '<li>%s</li>\n', recommendations{i});
    end
    fprintf(fid, '</ul>\n\n');
    
end

function defect_counts = getDefectCounts(detection_results)
    % Get defect counts for each type
    
    defect_counts = zeros(6, 1);
    
    % Oxygen precipitates
    if isfield(detection_results, 'oxygen_precipitation')
        defect_counts(1) = length(detection_results.oxygen_precipitation.precipitate_locations);
    end
    
    % Dislocations
    if isfield(detection_results, 'dislocation')
        defect_counts(2) = length(detection_results.dislocation.dislocation_lines);
    end
    
    % Swirl defects
    if isfield(detection_results, 'swirl_defect')
        defect_counts(3) = detection_results.swirl_defect.swirl_properties.num_regions;
    end
    
    % Voids and COPs
    if isfield(detection_results, 'void_cop')
        defect_counts(4) = length(detection_results.void_cop.void_locations) + ...
                           length(detection_results.void_cop.cop_locations);
    end
    
    % Cracks
    if isfield(detection_results, 'crack')
        defect_counts(5) = length(detection_results.crack.crack_lengths);
    end
    
    % Dopant variation (use uniformity score as indicator)
    if isfield(detection_results, 'dopant_uniformity')
        defect_counts(6) = round((1 - detection_results.dopant_uniformity.uniformity_score) * 100);
    end
    
end

function severity_scores = getSeverityScores(detection_results)
    % Get severity scores for each defect type
    
    severity_scores = zeros(6, 1);
    
    % Oxygen precipitates
    if isfield(detection_results, 'oxygen_precipitation')
        severity_scores(1) = min(1.0, length(detection_results.oxygen_precipitation.precipitate_locations) / 100);
    end
    
    % Dislocations
    if isfield(detection_results, 'dislocation')
        severity_scores(2) = min(1.0, mean(detection_results.dislocation.dislocation_density(:)) * 1000);
    end
    
    % Swirl defects
    if isfield(detection_results, 'swirl_defect')
        severity_scores(3) = detection_results.swirl_defect.severity_score;
    end
    
    % Voids and COPs
    if isfield(detection_results, 'void_cop')
        total_defects = length(detection_results.void_cop.void_locations) + ...
                       length(detection_results.void_cop.cop_locations);
        severity_scores(4) = min(1.0, total_defects / 50);
    end
    
    % Cracks
    if isfield(detection_results, 'crack')
        severity_scores(5) = detection_results.crack.crack_properties.severity_score;
    end
    
    % Dopant variation
    if isfield(detection_results, 'dopant_uniformity')
        severity_scores(6) = 1 - detection_results.dopant_uniformity.uniformity_score;
    end
    
end

function recommendations = generateRecommendations(detection_results)
    % Generate recommendations based on detected defects
    
    recommendations = {};
    
    % Check for high oxygen precipitation
    if isfield(detection_results, 'oxygen_precipitation') && ...
       length(detection_results.oxygen_precipitation.precipitate_locations) > 50
        recommendations{end+1} = 'High oxygen precipitation detected. Consider improving crucible quality and reducing oxygen contamination.';
    end
    
    % Check for high dislocation density
    if isfield(detection_results, 'dislocation') && ...
       mean(detection_results.dislocation.dislocation_density(:)) > 0.01
        recommendations{end+1} = 'High dislocation density detected. Review thermal stress management during crystal growth.';
    end
    
    % Check for swirl defects
    if isfield(detection_results, 'swirl_defect') && ...
       detection_results.swirl_defect.severity_score > 0.5
        recommendations{end+1} = 'Significant swirl defects detected. Optimize rotation parameters and temperature gradients.';
    end
    
    % Check for voids and COPs
    if isfield(detection_results, 'void_cop') && ...
       (length(detection_results.void_cop.void_locations) + length(detection_results.void_cop.cop_locations)) > 20
        recommendations{end+1} = 'High void/COP density detected. Review pulling rate and temperature control.';
    end
    
    % Check for cracks
    if isfield(detection_results, 'crack') && ...
       detection_results.crack.crack_properties.severity_score > 0.3
        recommendations{end+1} = 'Cracks detected. Improve cooling procedures and handling protocols.';
    end
    
    % Check for dopant nonuniformity
    if isfield(detection_results, 'dopant_uniformity') && ...
       detection_results.dopant_uniformity.uniformity_score < 0.7
        recommendations{end+1} = 'Poor dopant uniformity detected. Optimize doping process and melt convection.';
    end
    
    % General recommendations
    if isempty(recommendations)
        recommendations{end+1} = 'No significant defects detected. Continue current process parameters.';
    end
    
end

function summary_text = generateSummaryText(detection_results)
    % Generate summary text for PDF report
    
    defect_counts = getDefectCounts(detection_results);
    severity_scores = getSeverityScores(detection_results);
    
    summary_text = sprintf('Defect Summary:\n');
    summary_text = [summary_text sprintf('Oxygen Precipitates: %d\n', defect_counts(1))];
    summary_text = [summary_text sprintf('Dislocations: %d\n', defect_counts(2))];
    summary_text = [summary_text sprintf('Swirl Defects: %d\n', defect_counts(3))];
    summary_text = [summary_text sprintf('Voids/COPs: %d\n', defect_counts(4))];
    summary_text = [summary_text sprintf('Cracks: %d\n', defect_counts(5))];
    summary_text = [summary_text sprintf('Dopant Variation: %d\n', defect_counts(6))];
    
end
