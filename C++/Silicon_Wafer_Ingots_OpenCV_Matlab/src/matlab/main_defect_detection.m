function main_defect_detection(varargin)
%MAIN_DEFECT_DETECTION Master orchestration script for silicon wafer defect detection
%
% This script coordinates all defect detection modules and generates comprehensive reports
%
% Inputs:
%   varargin - Optional parameters:
%     'input_dir' - Directory containing input images
%     'output_dir' - Directory for output results
%     'image_types' - Cell array of image types to process
%     'detection_modules' - Cell array of detection modules to run
%     'generate_report' - Generate comprehensive report (true/false)
%     'save_results' - Save all results to files (true/false)
%     'visualize_results' - Display visualization results (true/false)
%
% Outputs:
%   None (saves results to workspace and files)

    % Parse input parameters
    p = inputParser;
    addParameter(p, 'input_dir', 'data/output/processed', @ischar);
    addParameter(p, 'output_dir', 'data/output/results', @ischar);
    addParameter(p, 'image_types', {'optical', 'infrared'}, @iscell);
    addParameter(p, 'detection_modules', {'oxygen', 'dislocation', 'swirl', 'void', 'crack', 'dopant'}, @iscell);
    addParameter(p, 'generate_report', true, @islogical);
    addParameter(p, 'save_results', true, @islogical);
    addParameter(p, 'visualize_results', true, @islogical);
    parse(p, varargin{:});
    
    params = p.Results;
    
    fprintf('Silicon Wafer Defect Detection System\n');
    fprintf('=====================================\n\n');
    
    % Create output directory if it doesn't exist
    if ~exist(params.output_dir, 'dir')
        mkdir(params.output_dir);
    end
    
    % Initialize results structure
    detection_results = struct();
    detection_results.timestamp = datestr(now, 'yyyy-mm-dd HH:MM:SS');
    detection_results.parameters = params;
    detection_results.images_processed = {};
    detection_results.detection_summary = struct();
    
    % Load and process images
    fprintf('Loading images from: %s\n', params.input_dir);
    images = loadImages(params.input_dir, params.image_types);
    
    if isempty(images)
        fprintf('No images found in input directory. Exiting.\n');
        return;
    end
    
    fprintf('Found %d images to process\n\n', length(images));
    
    % Process each image
    for i = 1:length(images)
        fprintf('Processing image %d/%d: %s\n', i, length(images), images(i).filename);
        
        % Load image
        image_data = imread(images(i).fullpath);
        if size(image_data, 3) == 3
            image_data = rgb2gray(image_data);
        end
        
        % Preprocess image
        processed_image = preprocess_image(image_data);
        
        % Run detection modules
        image_results = runDetectionModules(processed_image, images(i), params);
        
        % Store results
        detection_results.images_processed{end+1} = images(i).filename;
        detection_results.(sprintf('image_%d', i)) = image_results;
        
        % Visualize results if requested
        if params.visualize_results
            visualize_results(processed_image, image_results, 'save_figure', true, ...
                            'output_dir', fullfile(params.output_dir, 'visualizations'));
        end
        
        fprintf('Completed processing image %d\n\n', i);
    end
    
    % Aggregate results across all images
    detection_results.detection_summary = aggregateResults(detection_results);
    
    % Classify defects
    fprintf('Classifying detected defects...\n');
    defect_classification = defect_classifier(detection_results.detection_summary);
    detection_results.defect_classification = defect_classification;
    
    % Generate comprehensive report
    if params.generate_report
        fprintf('Generating comprehensive report...\n');
        report_filename = generate_report(detection_results, 'output_dir', params.output_dir);
        detection_results.report_filename = report_filename;
    end
    
    % Save results
    if params.save_results
        fprintf('Saving results...\n');
        results_filename = fullfile(params.output_dir, sprintf('detection_results_%s.mat', ...
                              datestr(now, 'yyyymmdd_HHMMSS')));
        save(results_filename, 'detection_results');
        fprintf('Results saved to: %s\n', results_filename);
    end
    
    % Display summary
    displaySummary(detection_results);
    
    % Save to workspace
    assignin('base', 'detection_results', detection_results);
    assignin('base', 'defect_classification', defect_classification);
    
    fprintf('\nDefect detection analysis completed successfully!\n');
    
end

function images = loadImages(input_dir, image_types)
    % Load images from input directory
    
    images = [];
    
    % Get all image files
    image_extensions = {'*.png', '*.jpg', '*.jpeg', '*.tiff', '*.tif', '*.bmp'};
    
    for i = 1:length(image_extensions)
        files = dir(fullfile(input_dir, image_extensions{i}));
        for j = 1:length(files)
            filename = files(j).name;
            fullpath = fullfile(input_dir, filename);
            
            % Determine image type from filename
            image_type = determineImageType(filename, image_types);
            
            if ~isempty(image_type)
                images(end+1).filename = filename;
                images(end).fullpath = fullpath;
                images(end).type = image_type;
                images(end).size = files(j).bytes;
            end
        end
    end
    
end

function image_type = determineImageType(filename, image_types)
    % Determine image type from filename
    
    image_type = '';
    filename_lower = lower(filename);
    
    for i = 1:length(image_types)
        type = image_types{i};
        if contains(filename_lower, type)
            image_type = type;
            break;
        end
    end
    
    % Default to first type if no match
    if isempty(image_type) && ~isempty(image_types)
        image_type = image_types{1};
    end
    
end

function image_results = runDetectionModules(image, image_info, params)
    % Run all detection modules on the image
    
    image_results = struct();
    image_results.image_info = image_info;
    image_results.detection_modules = params.detection_modules;
    
    % Run each detection module
    for i = 1:length(params.detection_modules)
        module = params.detection_modules{i};
        
        fprintf('  Running %s detection...\n', module);
        
        try
            switch module
                case 'oxygen'
                    if strcmp(image_info.type, 'infrared')
                        [precipitate_locations, size_distribution, density_map] = ...
                            detect_oxygen_precipitation(image);
                        image_results.oxygen_precipitation = struct();
                        image_results.oxygen_precipitation.precipitate_locations = precipitate_locations;
                        image_results.oxygen_precipitation.size_distribution = size_distribution;
                        image_results.oxygen_precipitation.density_map = density_map;
                    else
                        fprintf('    Skipping oxygen detection (not IR image)\n');
                    end
                    
                case 'dislocation'
                    [dislocation_lines, dislocation_density, slip_patterns] = ...
                        detect_dislocations(image);
                    image_results.dislocation = struct();
                    image_results.dislocation.dislocation_lines = dislocation_lines;
                    image_results.dislocation.dislocation_density = dislocation_density;
                    image_results.dislocation.slip_patterns = slip_patterns;
                    
                case 'swirl'
                    if strcmp(image_info.type, 'infrared')
                        [swirl_patterns, severity_score, orientation_field] = ...
                            detect_swirl_defects(image);
                        image_results.swirl_defect = struct();
                        image_results.swirl_defect.swirl_patterns = swirl_patterns;
                        image_results.swirl_defect.severity_score = severity_score;
                        image_results.swirl_defect.orientation_field = orientation_field;
                    else
                        fprintf('    Skipping swirl detection (not IR image)\n');
                    end
                    
                case 'void'
                    [void_locations, void_sizes, cop_locations, cop_sizes] = ...
                        detect_voids_cops(image);
                    image_results.void_cop = struct();
                    image_results.void_cop.void_locations = void_locations;
                    image_results.void_cop.void_sizes = void_sizes;
                    image_results.void_cop.cop_locations = cop_locations;
                    image_results.void_cop.cop_sizes = cop_sizes;
                    
                case 'crack'
                    [crack_topology, crack_widths, crack_lengths] = ...
                        detect_cracks(image);
                    image_results.crack = struct();
                    image_results.crack.crack_topology = crack_topology;
                    image_results.crack.crack_widths = crack_widths;
                    image_results.crack.crack_lengths = crack_lengths;
                    
                case 'dopant'
                    [uniformity_score, variation_maps, resistivity_profiles] = ...
                        detect_dopant_variation(image);
                    image_results.dopant_uniformity = struct();
                    image_results.dopant_uniformity.uniformity_score = uniformity_score;
                    image_results.dopant_uniformity.variation_maps = variation_maps;
                    image_results.dopant_uniformity.resistivity_profiles = resistivity_profiles;
                    
                otherwise
                    fprintf('    Unknown detection module: %s\n', module);
            end
            
        catch ME
            fprintf('    Error in %s detection: %s\n', module, ME.message);
            image_results.(module) = struct('error', ME.message);
        end
    end
    
end

function summary = aggregateResults(detection_results)
    % Aggregate results across all images
    
    summary = struct();
    summary.total_images = length(detection_results.images_processed);
    summary.detection_modules = detection_results.parameters.detection_modules;
    
    % Initialize counters
    summary.oxygen_precipitation = struct('total_precipitates', 0, 'total_stacking_faults', 0);
    summary.dislocation = struct('total_lines', 0, 'avg_density', 0);
    summary.swirl_defect = struct('total_regions', 0, 'avg_severity', 0);
    summary.void_cop = struct('total_voids', 0, 'total_cops', 0);
    summary.crack = struct('total_segments', 0, 'total_junctions', 0);
    summary.dopant_uniformity = struct('avg_uniformity', 0);
    
    % Aggregate data from all images
    for i = 1:summary.total_images
        field_name = sprintf('image_%d', i);
        if isfield(detection_results, field_name)
            image_results = detection_results.(field_name);
            
            % Aggregate oxygen precipitation
            if isfield(image_results, 'oxygen_precipitation') && ...
               isfield(image_results.oxygen_precipitation, 'precipitate_locations')
                summary.oxygen_precipitation.total_precipitates = ...
                    summary.oxygen_precipitation.total_precipitates + ...
                    length(image_results.oxygen_precipitation.precipitate_locations);
            end
            
            % Aggregate dislocations
            if isfield(image_results, 'dislocation') && ...
               isfield(image_results.dislocation, 'dislocation_lines')
                summary.dislocation.total_lines = ...
                    summary.dislocation.total_lines + ...
                    length(image_results.dislocation.dislocation_lines);
            end
            
            % Aggregate swirl defects
            if isfield(image_results, 'swirl_defect') && ...
               isfield(image_results.swirl_defect, 'swirl_patterns')
                summary.swirl_defect.total_regions = ...
                    summary.swirl_defect.total_regions + ...
                    image_results.swirl_defect.swirl_properties.num_regions;
            end
            
            % Aggregate voids and COPs
            if isfield(image_results, 'void_cop')
                if isfield(image_results.void_cop, 'void_locations')
                    summary.void_cop.total_voids = ...
                        summary.void_cop.total_voids + ...
                        length(image_results.void_cop.void_locations);
                end
                if isfield(image_results.void_cop, 'cop_locations')
                    summary.void_cop.total_cops = ...
                        summary.void_cop.total_cops + ...
                        length(image_results.void_cop.cop_locations);
                end
            end
            
            % Aggregate cracks
            if isfield(image_results, 'crack') && ...
               isfield(image_results.crack, 'crack_lengths')
                summary.crack.total_segments = ...
                    summary.crack.total_segments + ...
                    length(image_results.crack.crack_lengths);
            end
            
            % Aggregate dopant uniformity
            if isfield(image_results, 'dopant_uniformity') && ...
               isfield(image_results.dopant_uniformity, 'uniformity_score')
                summary.dopant_uniformity.avg_uniformity = ...
                    summary.dopant_uniformity.avg_uniformity + ...
                    image_results.dopant_uniformity.uniformity_score;
            end
        end
    end
    
    % Calculate averages
    if summary.total_images > 0
        summary.dislocation.avg_density = summary.dislocation.total_lines / summary.total_images;
        summary.swirl_defect.avg_severity = summary.swirl_defect.total_regions / summary.total_images;
        summary.dopant_uniformity.avg_uniformity = summary.dopant_uniformity.avg_uniformity / summary.total_images;
    end
    
end

function displaySummary(detection_results)
    % Display summary of detection results
    
    fprintf('\nDetection Summary\n');
    fprintf('================\n');
    fprintf('Total images processed: %d\n', detection_results.detection_summary.total_images);
    fprintf('Detection modules: %s\n', strjoin(detection_results.detection_summary.detection_modules, ', '));
    
    summary = detection_results.detection_summary;
    
    fprintf('\nDefect Counts:\n');
    fprintf('  Oxygen precipitates: %d\n', summary.oxygen_precipitation.total_precipitates);
    fprintf('  Dislocation lines: %d\n', summary.dislocation.total_lines);
    fprintf('  Swirl defect regions: %d\n', summary.swirl_defect.total_regions);
    fprintf('  Voids: %d\n', summary.void_cop.total_voids);
    fprintf('  COPs: %d\n', summary.void_cop.total_cops);
    fprintf('  Crack segments: %d\n', summary.crack.total_segments);
    
    fprintf('\nQuality Metrics:\n');
    fprintf('  Average dopant uniformity: %.3f\n', summary.dopant_uniformity.avg_uniformity);
    
    if isfield(detection_results, 'defect_classification')
        fprintf('  Overall quality: %s\n', detection_results.defect_classification.overall_quality);
    end
    
    if isfield(detection_results, 'report_filename')
        fprintf('\nReport generated: %s\n', detection_results.report_filename);
    end
    
end
