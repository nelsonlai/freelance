function [swirl_patterns, severity_score, orientation_field] = detect_swirl_defects(ir_image, varargin)
%DETECT_SWIRL_DEFECTS Detect swirl defects in infrared images using FFT and Gabor filtering
%
% Inputs:
%   ir_image - Infrared image (grayscale)
%   varargin - Optional parameters:
%     'fft_threshold' - Threshold for FFT magnitude analysis
%     'gabor_frequencies' - Frequencies for Gabor filter bank
%     'gabor_orientations' - Orientations for Gabor filter bank
%     'min_swirl_size' - Minimum swirl pattern size
%     'max_swirl_size' - Maximum swirl pattern size
%
% Outputs:
%   swirl_patterns - Binary mask showing detected swirl patterns
%   severity_score - Severity score (0-1) for swirl defects
%   orientation_field - Orientation field showing swirl directions

    % Parse input parameters
    p = inputParser;
    addParameter(p, 'fft_threshold', 0.1, @isnumeric);
    addParameter(p, 'gabor_frequencies', [0.1, 0.2, 0.3], @isnumeric);
    addParameter(p, 'gabor_orientations', 0:30:150, @isnumeric);
    addParameter(p, 'min_swirl_size', 20, @isnumeric);
    addParameter(p, 'max_swirl_size', 200, @isnumeric);
    parse(p, varargin{:});
    
    params = p.Results;
    
    % Convert to double for processing
    if ~isa(ir_image, 'double')
        ir_image = double(ir_image) / 255.0;
    end
    
    fprintf('Detecting swirl defects...\n');
    
    % Step 1: Preprocessing - enhance contrast and reduce noise
    enhanced_image = adapthisteq(ir_image);
    denoised_image = imgaussfilt(enhanced_image, 1);
    
    % Step 2: FFT Analysis for circular/rotational patterns
    fft_image = fft2(denoised_image);
    fft_magnitude = abs(fftshift(fft_image));
    fft_phase = angle(fftshift(fft_image));
    
    % Create frequency mask for circular patterns
    [M, N] = size(denoised_image);
    center_x = N / 2 + 1;
    center_y = M / 2 + 1;
    
    [X, Y] = meshgrid(1:N, 1:M);
    distance_from_center = sqrt((X - center_x).^2 + (Y - center_y).^2);
    
    % Define frequency bands for swirl detection
    min_freq = params.min_swirl_size / min(M, N);
    max_freq = params.max_swirl_size / min(M, N);
    
    frequency_mask = (distance_from_center >= min_freq) & (distance_from_center <= max_freq);
    
    % Apply frequency mask to FFT magnitude
    filtered_fft = fft_magnitude .* frequency_mask;
    
    % Step 3: Gabor Filter Bank for orientation analysis
    gabor_responses = cell(length(params.gabor_frequencies), length(params.gabor_orientations));
    gabor_magnitude = zeros(size(denoised_image));
    
    for i = 1:length(params.gabor_frequencies)
        freq = params.gabor_frequencies(i);
        for j = 1:length(params.gabor_orientations)
            orientation = params.gabor_orientations(j);
            
            % Create Gabor filter
            gabor_filter = createGaborFilter(freq, orientation, M, N);
            
            % Apply filter
            filtered_image = ifft2(fft2(denoised_image) .* fft2(gabor_filter));
            gabor_responses{i, j} = abs(filtered_image);
            
            % Accumulate magnitude
            gabor_magnitude = gabor_magnitude + abs(filtered_image);
        end
    end
    
    % Normalize Gabor magnitude
    gabor_magnitude = gabor_magnitude / max(gabor_magnitude(:));
    
    % Step 4: Orientation Field Analysis
    orientation_field = computeOrientationField(denoised_image);
    
    % Step 5: Detect swirl patterns using template matching
    swirl_patterns = detectSwirlPatterns(denoised_image, orientation_field);
    
    % Step 6: Combine FFT and Gabor analysis
    % Create composite swirl detection map
    fft_normalized = filtered_fft / max(filtered_fft(:));
    composite_map = fft_normalized .* gabor_magnitude;
    
    % Apply threshold to create binary swirl mask
    swirl_threshold = params.fft_threshold * max(composite_map(:));
    swirl_binary = composite_map > swirl_threshold;
    
    % Morphological operations to clean up
    se = strel('disk', 3);
    swirl_binary = imopen(swirl_binary, se);
    swirl_binary = imclose(swirl_binary, se);
    
    % Step 7: Calculate severity score
    severity_score = calculateSwirlSeverity(swirl_binary, composite_map);
    
    % Step 8: Analyze swirl characteristics
    swirl_properties = analyzeSwirlProperties(swirl_binary, orientation_field);
    
    % Display results
    fprintf('Swirl severity score: %.3f\n', severity_score);
    fprintf('Detected %d swirl regions\n', swirl_properties.num_regions);
    
    % Visualization
    figure('Name', 'Swirl Defect Detection Results');
    
    subplot(2, 4, 1);
    imshow(ir_image, []);
    title('Original IR Image');
    
    subplot(2, 4, 2);
    imshow(enhanced_image, []);
    title('Enhanced Image');
    
    subplot(2, 4, 3);
    imshow(log(fft_magnitude + 1), []);
    title('FFT Magnitude');
    
    subplot(2, 4, 4);
    imshow(log(filtered_fft + 1), []);
    title('Filtered FFT');
    
    subplot(2, 4, 5);
    imshow(gabor_magnitude, []);
    title('Gabor Magnitude');
    
    subplot(2, 4, 6);
    imshow(orientation_field, []);
    title('Orientation Field');
    colormap(hsv);
    
    subplot(2, 4, 7);
    imshow(composite_map, []);
    title('Composite Swirl Map');
    
    subplot(2, 4, 8);
    imshow(swirl_binary);
    title('Detected Swirl Patterns');
    
    % Additional visualization for orientation field
    figure('Name', 'Swirl Orientation Analysis');
    
    subplot(1, 2, 1);
    imshow(ir_image, []);
    hold on;
    visualizeOrientationField(orientation_field, 10);
    title('Swirl Orientation Field Overlay');
    hold off;
    
    subplot(1, 2, 2);
    histogram(orientation_field(:), 36);
    title('Orientation Distribution');
    xlabel('Orientation (degrees)');
    ylabel('Frequency');
    
    % Save results
    results.swirl_patterns = swirl_binary;
    results.severity_score = severity_score;
    results.orientation_field = orientation_field;
    results.composite_map = composite_map;
    results.gabor_magnitude = gabor_magnitude;
    results.fft_analysis = fft_magnitude;
    results.swirl_properties = swirl_properties;
    results.parameters = params;
    
    assignin('base', 'swirl_defect_results', results);
    
end

function gabor_filter = createGaborFilter(frequency, orientation, M, N)
    % Create Gabor filter in frequency domain
    
    % Convert orientation to radians
    theta = deg2rad(orientation);
    
    % Create coordinate grids
    [X, Y] = meshgrid(-N/2:N/2-1, -M/2:M/2-1);
    
    % Rotate coordinates
    X_rot = X * cos(theta) + Y * sin(theta);
    Y_rot = -X * sin(theta) + Y * cos(theta);
    
    % Create Gaussian envelope
    sigma_x = 1 / (2 * pi * frequency);
    sigma_y = sigma_x * 2; % Elongated in perpendicular direction
    
    gaussian = exp(-(X_rot.^2 / (2 * sigma_x^2) + Y_rot.^2 / (2 * sigma_y^2)));
    
    % Create sinusoidal component
    sinusoidal = exp(1i * 2 * pi * frequency * X_rot);
    
    % Combine to create Gabor filter
    gabor_filter = gaussian .* sinusoidal;
end

function orientation_field = computeOrientationField(image)
    % Compute orientation field using gradient analysis
    
    % Calculate gradients
    [Gx, Gy] = imgradientxy(image);
    
    % Calculate orientation
    orientation_field = atan2d(Gy, Gx);
    
    % Normalize to 0-180 degrees
    orientation_field = mod(orientation_field, 180);
end

function swirl_patterns = detectSwirlPatterns(image, orientation_field)
    % Detect swirl patterns using orientation field analysis
    
    % Calculate orientation gradient
    [Gx_orient, Gy_orient] = imgradientxy(orientation_field);
    
    % Detect regions with high orientation gradient (swirl centers)
    orientation_gradient_magnitude = sqrt(Gx_orient.^2 + Gy_orient.^2);
    
    % Threshold to find potential swirl centers
    threshold = 0.3 * max(orientation_gradient_magnitude(:));
    swirl_centers = orientation_gradient_magnitude > threshold;
    
    % Morphological operations to clean up
    se = strel('disk', 5);
    swirl_patterns = imopen(swirl_centers, se);
    swirl_patterns = imclose(swirl_patterns, se);
end

function severity_score = calculateSwirlSeverity(swirl_binary, composite_map)
    % Calculate severity score based on swirl characteristics
    
    % Area coverage
    area_coverage = sum(swirl_binary(:)) / numel(swirl_binary);
    
    % Average intensity in swirl regions
    swirl_intensity = mean(composite_map(swirl_binary));
    
    % Number of connected components
    cc = bwconncomp(swirl_binary);
    num_regions = cc.NumObjects;
    
    % Calculate severity score (0-1)
    severity_score = min(1.0, area_coverage * 10 + swirl_intensity * 0.5 + num_regions * 0.01);
end

function properties = analyzeSwirlProperties(swirl_binary, orientation_field)
    % Analyze properties of detected swirl patterns
    
    cc = bwconncomp(swirl_binary);
    properties.num_regions = cc.NumObjects;
    
    if properties.num_regions > 0
        stats = regionprops(cc, 'Area', 'Centroid', 'Eccentricity');
        properties.areas = [stats.Area];
        properties.centroids = [stats.Centroid];
        properties.eccentricities = [stats.Eccentricity];
        properties.average_area = mean(properties.areas);
        properties.total_area = sum(properties.areas);
    else
        properties.areas = [];
        properties.centroids = [];
        properties.eccentricities = [];
        properties.average_area = 0;
        properties.total_area = 0;
    end
end

function visualizeOrientationField(orientation_field, step_size)
    % Visualize orientation field as arrows
    
    [M, N] = size(orientation_field);
    
    for i = 1:step_size:M
        for j = 1:step_size:N
            orientation = orientation_field(i, j);
            
            % Convert orientation to vector
            dx = cosd(orientation);
            dy = sind(orientation);
            
            % Draw arrow
            quiver(j, i, dx, dy, 'r', 'LineWidth', 1, 'MaxHeadSize', 0.5);
        end
    end
end
