% Detection Parameters Configuration
% This file contains all the parameters for the defect detection algorithms

function params = detection_params()
%DETECTION_PARAMS Return detection parameters structure

    params = struct();
    
    % General parameters
    params.general = struct();
    params.general.input_dir = 'data/output/processed';
    params.general.output_dir = 'data/output/results';
    params.general.image_types = {'optical', 'infrared'};
    params.general.detection_modules = {'oxygen', 'dislocation', 'swirl', 'void', 'crack', 'dopant'};
    params.general.generate_report = true;
    params.general.save_results = true;
    params.general.visualize_results = true;
    
    % Oxygen precipitation detection parameters
    params.oxygen_precipitation = struct();
    params.oxygen_precipitation.threshold_method = 'otsu'; % 'otsu', 'adaptive', 'manual'
    params.oxygen_precipitation.threshold_value = 0.5;
    params.oxygen_precipitation.morphology_size = 3;
    params.oxygen_precipitation.min_precipitate_size = 10;
    params.oxygen_precipitation.max_precipitate_size = 1000;
    
    % Dislocation detection parameters
    params.dislocation = struct();
    params.dislocation.edge_method = 'canny'; % 'canny', 'sobel', 'prewitt'
    params.dislocation.hough_threshold = 0.3;
    params.dislocation.min_line_length = 10;
    params.dislocation.line_gap = 5;
    params.dislocation.density_window_size = 50;
    
    % Swirl defect detection parameters
    params.swirl_defect = struct();
    params.swirl_defect.fft_threshold = 0.1;
    params.swirl_defect.gabor_frequencies = [0.1, 0.2, 0.3];
    params.swirl_defect.gabor_orientations = 0:30:150;
    params.swirl_defect.min_swirl_size = 20;
    params.swirl_defect.max_swirl_size = 200;
    
    % Void and COP detection parameters
    params.void_cop = struct();
    params.void_cop.detection_method = 'both'; % 'log', 'watershed', 'both'
    params.void_cop.min_void_size = 5;
    params.void_cop.max_void_size = 100;
    params.void_cop.min_cop_size = 2;
    params.void_cop.max_cop_size = 20;
    params.void_cop.log_sigma = 1.5;
    params.void_cop.watershed_threshold = 0.1;
    
    % Crack detection parameters
    params.crack = struct();
    params.crack.edge_method = 'canny'; % 'canny', 'sobel', 'prewitt'
    params.crack.hough_threshold = 0.3;
    params.crack.min_crack_length = 20;
    params.crack.max_crack_width = 10;
    params.crack.skeleton_method = 'thin'; % 'thin', 'skel'
    
    % Dopant uniformity detection parameters
    params.dopant_uniformity = struct();
    params.dopant_uniformity.analysis_method = 'both'; % 'gradient', 'profile', 'both'
    params.dopant_uniformity.window_size = 50;
    params.dopant_uniformity.gradient_threshold = 0.1;
    params.dopant_uniformity.profile_direction = 'both'; % 'radial', 'axial', 'both'
    params.dopant_uniformity.smoothing_factor = 0.1;
    
    % Image preprocessing parameters
    params.preprocessing = struct();
    params.preprocessing.noise_reduction = true;
    params.preprocessing.contrast_enhancement = true;
    params.preprocessing.normalization = true;
    params.preprocessing.smoothing = 0.5;
    
    % Visualization parameters
    params.visualization = struct();
    params.visualization.show_all = true;
    params.visualization.detection_types = {'oxygen', 'dislocation', 'swirl', 'void', 'crack', 'dopant'};
    params.visualization.overlay_alpha = 0.7;
    params.visualization.save_figure = false;
    params.visualization.output_dir = 'data/output/visualizations';
    
    % Report generation parameters
    params.report = struct();
    params.report.output_format = 'html'; % 'html', 'pdf', 'txt'
    params.report.output_dir = 'data/output/reports';
    params.report.include_images = true;
    params.report.detailed_analysis = true;
    
    % Defect classification parameters
    params.classification = struct();
    params.classification.classification_rules = 'default';
    params.classification.severity_thresholds = struct('low', 0.3, 'medium', 0.6, 'high', 0.8);
    params.classification.output_format = 'struct'; % 'struct', 'table', 'json'
    
end
