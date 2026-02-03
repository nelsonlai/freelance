function visualize_results(original_image, detection_results, varargin)
%VISUALIZE_RESULTS Overlay detection results on original images
%
% Inputs:
%   original_image - Original image
%   detection_results - Structure containing detection results
%   varargin - Optional parameters:
%     'show_all' - Show all detection types (true/false)
%     'detection_types' - Cell array of detection types to show
%     'overlay_alpha' - Transparency for overlays (0-1)
%     'save_figure' - Save figure to file (true/false)
%     'output_dir' - Output directory for saved figures
%
% Outputs:
%   None (displays figure)

    % Parse input parameters
    p = inputParser;
    addParameter(p, 'show_all', true, @islogical);
    addParameter(p, 'detection_types', {'oxygen', 'dislocation', 'swirl', 'void', 'crack', 'dopant'}, @iscell);
    addParameter(p, 'overlay_alpha', 0.7, @isnumeric);
    addParameter(p, 'save_figure', false, @islogical);
    addParameter(p, 'output_dir', 'data/output/visualizations', @ischar);
    parse(p, varargin{:});
    
    params = p.Results;
    
    % Create figure
    figure('Name', 'Defect Detection Results Overlay', 'Position', [100, 100, 1200, 800]);
    
    % Display original image
    imshow(original_image, []);
    hold on;
    
    % Define colors for different defect types
    colors = struct();
    colors.oxygen = [1, 0, 0];      % Red
    colors.dislocation = [0, 1, 0]; % Green
    colors.swirl = [0, 0, 1];       % Blue
    colors.void = [1, 1, 0];        % Yellow
    colors.crack = [1, 0, 1];       % Magenta
    colors.dopant = [0, 1, 1];      % Cyan
    
    % Overlay detection results
    legend_entries = {};
    
    % Oxygen precipitation
    if params.show_all || ismember('oxygen', params.detection_types)
        if isfield(detection_results, 'oxygen_precipitation') && ...
           isfield(detection_results.oxygen_precipitation, 'precipitate_locations')
            locations = detection_results.oxygen_precipitation.precipitate_locations;
            if ~isempty(locations)
                plot(locations(:, 1), locations(:, 2), 'o', ...
                     'Color', colors.oxygen, 'MarkerSize', 8, 'MarkerFaceColor', colors.oxygen);
                legend_entries{end+1} = 'Oxygen Precipitates';
            end
        end
    end
    
    % Dislocations
    if params.show_all || ismember('dislocation', params.detection_types)
        if isfield(detection_results, 'dislocation') && ...
           isfield(detection_results.dislocation, 'dislocation_lines')
            lines = detection_results.dislocation.dislocation_lines;
            if ~isempty(lines)
                for k = 1:length(lines)
                    xy = [lines(k).point1; lines(k).point2];
                    plot(xy(:, 1), xy(:, 2), '-', ...
                         'Color', colors.dislocation, 'LineWidth', 2);
                end
                legend_entries{end+1} = 'Dislocation Lines';
            end
        end
    end
    
    % Swirl defects
    if params.show_all || ismember('swirl', params.detection_types)
        if isfield(detection_results, 'swirl_defect') && ...
           isfield(detection_results.swirl_defect, 'swirl_patterns')
            patterns = detection_results.swirl_defect.swirl_patterns;
            if ~isempty(patterns)
                % Create contour overlay
                contour(patterns, [0.5, 0.5], 'Color', colors.swirl, 'LineWidth', 2);
                legend_entries{end+1} = 'Swirl Defects';
            end
        end
    end
    
    % Voids and COPs
    if params.show_all || ismember('void', params.detection_types)
        if isfield(detection_results, 'void_cop') && ...
           isfield(detection_results.void_cop, 'void_locations')
            void_locations = detection_results.void_cop.void_locations;
            if ~isempty(void_locations)
                plot(void_locations(:, 1), void_locations(:, 2), 's', ...
                     'Color', colors.void, 'MarkerSize', 6, 'MarkerFaceColor', colors.void);
                legend_entries{end+1} = 'Voids';
            end
        end
        
        if isfield(detection_results, 'void_cop') && ...
           isfield(detection_results.void_cop, 'cop_locations')
            cop_locations = detection_results.void_cop.cop_locations;
            if ~isempty(cop_locations)
                plot(cop_locations(:, 1), cop_locations(:, 2), '^', ...
                     'Color', colors.void, 'MarkerSize', 6, 'MarkerFaceColor', colors.void);
                legend_entries{end+1} = 'COPs';
            end
        end
    end
    
    % Cracks
    if params.show_all || ismember('crack', params.detection_types)
        if isfield(detection_results, 'crack') && ...
           isfield(detection_results.crack, 'crack_lines')
            lines = detection_results.crack.crack_lines;
            if ~isempty(lines)
                for k = 1:length(lines)
                    xy = [lines(k).point1; lines(k).point2];
                    plot(xy(:, 1), xy(:, 2), '-', ...
                         'Color', colors.crack, 'LineWidth', 3);
                end
                legend_entries{end+1} = 'Cracks';
            end
        end
    end
    
    % Dopant variation
    if params.show_all || ismember('dopant', params.detection_types)
        if isfield(detection_results, 'dopant_uniformity') && ...
           isfield(detection_results.dopant_uniformity, 'variation_maps') && ...
           isfield(detection_results.dopant_uniformity.variation_maps, 'variation_map')
            variation_map = detection_results.dopant_uniformity.variation_maps.variation_map;
            if ~isempty(variation_map)
                % Create contour overlay for high variation regions
                contour(variation_map, [0.7, 0.7], 'Color', colors.dopant, 'LineWidth', 2);
                legend_entries{end+1} = 'High Dopant Variation';
            end
        end
    end
    
    % Add legend
    if ~isempty(legend_entries)
        legend(legend_entries, 'Location', 'best');
    end
    
    % Add title
    title('Silicon Wafer Defect Detection Results');
    
    hold off;
    
    % Save figure if requested
    if params.save_figure
        % Create output directory if it doesn't exist
        if ~exist(params.output_dir, 'dir')
            mkdir(params.output_dir);
        end
        
        % Generate filename
        timestamp = datestr(now, 'yyyymmdd_HHMMSS');
        filename = fullfile(params.output_dir, sprintf('defect_detection_%s.png', timestamp));
        
        % Save figure
        saveas(gcf, filename);
        fprintf('Figure saved to: %s\n', filename);
    end
    
end
