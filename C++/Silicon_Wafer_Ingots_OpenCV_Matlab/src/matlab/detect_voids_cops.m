function [void_locations, void_sizes, cop_locations, cop_sizes] = detect_voids_cops(image, varargin)
%DETECT_VOIDS_COPS Detect voids, microvoids, and COPs using blob detection and watershed segmentation
%
% Inputs:
%   image - High-resolution optical image (grayscale)
%   varargin - Optional parameters:
%     'detection_method' - Detection method ('log', 'watershed', 'both')
%     'min_void_size' - Minimum void size in pixels
%     'max_void_size' - Maximum void size in pixels
%     'min_cop_size' - Minimum COP size in pixels
%     'max_cop_size' - Maximum COP size in pixels
%     'log_sigma' - Sigma for Laplacian of Gaussian
%     'watershed_threshold' - Threshold for watershed segmentation
%
% Outputs:
%   void_locations - Nx2 matrix of void center coordinates
%   void_sizes - Nx1 vector of void sizes
%   cop_locations - Mx2 matrix of COP center coordinates
%   cop_sizes - Mx1 vector of COP sizes

    % Parse input parameters
    p = inputParser;
    addParameter(p, 'detection_method', 'both', @ischar);
    addParameter(p, 'min_void_size', 5, @isnumeric);
    addParameter(p, 'max_void_size', 100, @isnumeric);
    addParameter(p, 'min_cop_size', 2, @isnumeric);
    addParameter(p, 'max_cop_size', 20, @isnumeric);
    addParameter(p, 'log_sigma', 1.5, @isnumeric);
    addParameter(p, 'watershed_threshold', 0.1, @isnumeric);
    parse(p, varargin{:});
    
    params = p.Results;
    
    % Convert to double for processing
    if ~isa(image, 'double')
        image = double(image) / 255.0;
    end
    
    fprintf('Detecting voids and COPs...\n');
    
    % Step 1: Preprocessing - enhance contrast and reduce noise
    enhanced_image = adapthisteq(image);
    denoised_image = imgaussfilt(enhanced_image, 0.5);
    
    % Step 2: Detect voids using Laplacian of Gaussian (LoG)
    void_locations_log = [];
    void_sizes_log = [];
    
    if strcmp(params.detection_method, 'log') || strcmp(params.detection_method, 'both')
        [void_locations_log, void_sizes_log] = detectVoidsLoG(denoised_image, params);
    end
    
    % Step 3: Detect voids using Watershed segmentation
    void_locations_watershed = [];
    void_sizes_watershed = [];
    
    if strcmp(params.detection_method, 'watershed') || strcmp(params.detection_method, 'both')
        [void_locations_watershed, void_sizes_watershed] = detectVoidsWatershed(denoised_image, params);
    end
    
    % Step 4: Combine results from both methods
    if strcmp(params.detection_method, 'both')
        [void_locations, void_sizes] = combineVoidDetections(void_locations_log, void_sizes_log, ...
                                                           void_locations_watershed, void_sizes_watershed);
    elseif strcmp(params.detection_method, 'log')
        void_locations = void_locations_log;
        void_sizes = void_sizes_log;
    else % watershed
        void_locations = void_locations_watershed;
        void_sizes = void_sizes_watershed;
    end
    
    % Step 5: Detect COPs (Crystal-Originated Particles) - surface pits
    [cop_locations, cop_sizes] = detectCOPs(denoised_image, params);
    
    % Step 6: Filter detections by size
    % Filter voids
    valid_voids = (void_sizes >= params.min_void_size) & (void_sizes <= params.max_void_size);
    void_locations = void_locations(valid_voids, :);
    void_sizes = void_sizes(valid_voids);
    
    % Filter COPs
    valid_cops = (cop_sizes >= params.min_cop_size) & (cop_sizes <= params.max_cop_size);
    cop_locations = cop_locations(valid_cops, :);
    cop_sizes = cop_sizes(valid_cops);
    
    % Step 7: Analyze void and COP characteristics
    void_properties = analyzeVoidProperties(void_locations, void_sizes);
    cop_properties = analyzeCOPProperties(cop_locations, cop_sizes);
    
    % Display results
    fprintf('Found %d voids (average size: %.2f pixels)\n', length(void_sizes), mean(void_sizes));
    fprintf('Found %d COPs (average size: %.2f pixels)\n', length(cop_sizes), mean(cop_sizes));
    
    % Visualization
    figure('Name', 'Void and COP Detection Results');
    
    subplot(2, 4, 1);
    imshow(image, []);
    title('Original Image');
    
    subplot(2, 4, 2);
    imshow(enhanced_image, []);
    title('Enhanced Image');
    
    subplot(2, 4, 3);
    imshow(denoised_image, []);
    title('Denoised Image');
    
    subplot(2, 4, 4);
    % Show LoG response
    log_response = computeLoGResponse(denoised_image, params.log_sigma);
    imshow(log_response, []);
    title('LoG Response');
    
    subplot(2, 4, 5);
    % Show watershed segmentation
    watershed_result = performWatershedSegmentation(denoised_image, params);
    imshow(watershed_result, []);
    title('Watershed Segmentation');
    
    subplot(2, 4, 6);
    histogram(void_sizes, 20);
    title('Void Size Distribution');
    xlabel('Size (pixels)');
    ylabel('Count');
    
    subplot(2, 4, 7);
    histogram(cop_sizes, 20);
    title('COP Size Distribution');
    xlabel('Size (pixels)');
    ylabel('Count');
    
    subplot(2, 4, 8);
    imshow(image, []);
    hold on;
    if ~isempty(void_locations)
        plot(void_locations(:, 1), void_locations(:, 2), 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'red');
    end
    if ~isempty(cop_locations)
        plot(cop_locations(:, 1), cop_locations(:, 2), 'bo', 'MarkerSize', 6, 'MarkerFaceColor', 'blue');
    end
    title('Detected Voids (red) and COPs (blue)');
    legend('Voids', 'COPs', 'Location', 'best');
    hold off;
    
    % Save results
    results.void_locations = void_locations;
    results.void_sizes = void_sizes;
    results.cop_locations = cop_locations;
    results.cop_sizes = cop_sizes;
    results.void_properties = void_properties;
    results.cop_properties = cop_properties;
    results.parameters = params;
    
    assignin('base', 'void_cop_results', results);
    
end

function [void_locations, void_sizes] = detectVoidsLoG(image, params)
    % Detect voids using Laplacian of Gaussian blob detection
    
    % Compute LoG response
    log_response = computeLoGResponse(image, params.log_sigma);
    
    % Find local maxima in LoG response
    local_maxima = imregionalmax(log_response);
    
    % Threshold local maxima
    threshold = params.watershed_threshold * max(log_response(:));
    valid_maxima = local_maxima & (log_response > threshold);
    
    % Find connected components
    cc = bwconncomp(valid_maxima);
    stats = regionprops(cc, 'Centroid', 'Area');
    
    % Extract locations and sizes
    void_locations = [];
    void_sizes = [];
    
    for i = 1:length(stats)
        void_locations = [void_locations; stats(i).Centroid];
        void_sizes = [void_sizes; stats(i).Area];
    end
end

function [void_locations, void_sizes] = detectVoidsWatershed(image, params)
    % Detect voids using watershed segmentation
    
    % Compute gradient magnitude
    [Gx, Gy] = imgradientxy(image);
    gradient_magnitude = sqrt(Gx.^2 + Gy.^2);
    
    % Create markers for watershed
    % Use local minima in gradient magnitude as markers
    local_minima = imregionalmin(gradient_magnitude);
    
    % Threshold markers
    threshold = params.watershed_threshold * max(gradient_magnitude(:));
    valid_markers = local_minima & (gradient_magnitude < threshold);
    
    % Clean up markers
    se = strel('disk', 2);
    valid_markers = imopen(valid_markers, se);
    
    % Perform watershed segmentation
    watershed_result = watershed(gradient_magnitude);
    
    % Find regions corresponding to voids (dark regions)
    void_regions = watershed_result > 0;
    
    % Analyze void regions
    cc = bwconncomp(void_regions);
    stats = regionprops(cc, 'Centroid', 'Area', 'MeanIntensity');
    
    % Filter regions based on intensity (voids should be dark)
    void_locations = [];
    void_sizes = [];
    
    for i = 1:length(stats)
        if stats(i).MeanIntensity < 0.5 % Dark regions
            void_locations = [void_locations; stats(i).Centroid];
            void_sizes = [void_sizes; stats(i).Area];
        end
    end
end

function [cop_locations, cop_sizes] = detectCOPs(image, params)
    % Detect COPs (Crystal-Originated Particles) - surface pits
    
    % High-pass filtering to enhance surface pits
    h = fspecial('laplacian', 0.2);
    high_pass = imfilter(image, h);
    
    % Threshold to find pits
    threshold = 0.1 * max(high_pass(:));
    pit_mask = high_pass > threshold;
    
    % Morphological operations to clean up
    se = strel('disk', 1);
    pit_mask = imopen(pit_mask, se);
    pit_mask = imclose(pit_mask, se);
    
    % Find connected components
    cc = bwconncomp(pit_mask);
    stats = regionprops(cc, 'Centroid', 'Area');
    
    % Extract COP locations and sizes
    cop_locations = [];
    cop_sizes = [];
    
    for i = 1:length(stats)
        cop_locations = [cop_locations; stats(i).Centroid];
        cop_sizes = [cop_sizes; stats(i).Area];
    end
end

function log_response = computeLoGResponse(image, sigma)
    % Compute Laplacian of Gaussian response
    
    % Create LoG kernel
    kernel_size = ceil(6 * sigma);
    if mod(kernel_size, 2) == 0
        kernel_size = kernel_size + 1;
    end
    
    [X, Y] = meshgrid(-kernel_size/2:kernel_size/2, -kernel_size/2:kernel_size/2);
    
    % LoG kernel
    log_kernel = -(1 / (pi * sigma^4)) * (1 - (X.^2 + Y.^2) / (2 * sigma^2)) .* ...
                 exp(-(X.^2 + Y.^2) / (2 * sigma^2));
    
    % Apply filter
    log_response = imfilter(image, log_kernel, 'same', 'replicate');
end

function watershed_result = performWatershedSegmentation(image, params)
    % Perform watershed segmentation
    
    % Compute gradient magnitude
    [Gx, Gy] = imgradientxy(image);
    gradient_magnitude = sqrt(Gx.^2 + Gy.^2);
    
    % Create markers
    local_minima = imregionalmin(gradient_magnitude);
    threshold = params.watershed_threshold * max(gradient_magnitude(:));
    markers = local_minima & (gradient_magnitude < threshold);
    
    % Clean up markers
    se = strel('disk', 2);
    markers = imopen(markers, se);
    
    % Perform watershed
    watershed_result = watershed(gradient_magnitude);
end

function [combined_locations, combined_sizes] = combineVoidDetections(loc1, size1, loc2, size2)
    % Combine void detections from different methods
    
    % Simple combination - take union of detections
    combined_locations = [loc1; loc2];
    combined_sizes = [size1; size2];
    
    % Remove duplicates based on proximity
    if ~isempty(combined_locations)
        % Calculate distance matrix
        distances = pdist2(combined_locations, combined_locations);
        
        % Find pairs that are too close (within 5 pixels)
        [row, col] = find(triu(distances < 5, 1));
        
        % Remove duplicates (keep the one with larger size)
        to_remove = [];
        for i = 1:length(row)
            if combined_sizes(row(i)) > combined_sizes(col(i))
                to_remove = [to_remove; col(i)];
            else
                to_remove = [to_remove; row(i)];
            end
        end
        
        % Remove duplicates
        valid_indices = setdiff(1:size(combined_locations, 1), to_remove);
        combined_locations = combined_locations(valid_indices, :);
        combined_sizes = combined_sizes(valid_indices);
    end
end

function properties = analyzeVoidProperties(locations, sizes)
    % Analyze properties of detected voids
    
    properties.num_voids = length(sizes);
    properties.average_size = mean(sizes);
    properties.size_std = std(sizes);
    properties.total_area = sum(sizes);
    
    if ~isempty(locations)
        properties.density = properties.num_voids / (size(locations, 1) * size(locations, 2));
        properties.spatial_distribution = analyzeSpatialDistribution(locations);
    else
        properties.density = 0;
        properties.spatial_distribution = [];
    end
end

function properties = analyzeCOPProperties(locations, sizes)
    % Analyze properties of detected COPs
    
    properties.num_cops = length(sizes);
    properties.average_size = mean(sizes);
    properties.size_std = std(sizes);
    properties.total_area = sum(sizes);
    
    if ~isempty(locations)
        properties.density = properties.num_cops / (size(locations, 1) * size(locations, 2));
        properties.spatial_distribution = analyzeSpatialDistribution(locations);
    else
        properties.density = 0;
        properties.spatial_distribution = [];
    end
end

function distribution = analyzeSpatialDistribution(locations)
    % Analyze spatial distribution of detected features
    
    if isempty(locations)
        distribution = [];
        return;
    end
    
    % Calculate distances between all pairs
    distances = pdist(locations);
    
    distribution.mean_distance = mean(distances);
    distribution.std_distance = std(distances);
    distribution.min_distance = min(distances);
    distribution.max_distance = max(distances);
end
