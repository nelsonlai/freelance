function [precipitate_locations, size_distribution, density_map] = detect_oxygen_precipitation(ir_image, varargin)
%DETECT_OXYGEN_PRECIPITATION Detect oxygen precipitation and stacking faults in IR images
%
% Inputs:
%   ir_image - Infrared image (grayscale)
%   varargin - Optional parameters:
%     'threshold_method' - Thresholding method ('otsu', 'adaptive', 'manual')
%     'threshold_value' - Manual threshold value (if method is 'manual')
%     'morphology_size' - Size of morphological operations kernel
%     'min_precipitate_size' - Minimum precipitate size in pixels
%     'max_precipitate_size' - Maximum precipitate size in pixels
%
% Outputs:
%   precipitate_locations - Nx2 matrix of precipitate center coordinates
%   size_distribution - Nx1 vector of precipitate sizes
%   density_map - Image showing precipitate density distribution

    % Parse input parameters
    p = inputParser;
    addParameter(p, 'threshold_method', 'otsu', @ischar);
    addParameter(p, 'threshold_value', 0.5, @isnumeric);
    addParameter(p, 'morphology_size', 3, @isnumeric);
    addParameter(p, 'min_precipitate_size', 10, @isnumeric);
    addParameter(p, 'max_precipitate_size', 1000, @isnumeric);
    parse(p, varargin{:});
    
    params = p.Results;
    
    % Convert to double for processing
    if ~isa(ir_image, 'double')
        ir_image = double(ir_image) / 255.0;
    end
    
    fprintf('Detecting oxygen precipitation...\n');
    
    % Step 1: Apply thresholding to identify dark precipitate regions
    switch params.threshold_method
        case 'otsu'
            threshold = graythresh(ir_image);
            binary_mask = ir_image < threshold;
        case 'adaptive'
            binary_mask = imbinarize(ir_image, 'adaptive');
        case 'manual'
            binary_mask = ir_image < params.threshold_value;
        otherwise
            error('Unknown threshold method: %s', params.threshold_method);
    end
    
    % Step 2: Morphological operations to clean up the binary mask
    se = strel('disk', params.morphology_size);
    
    % Opening to remove small noise
    binary_mask = imopen(binary_mask, se);
    
    % Closing to fill small holes
    binary_mask = imclose(binary_mask, se);
    
    % Step 3: Connected component analysis
    cc = bwconncomp(binary_mask);
    stats = regionprops(cc, 'Area', 'Centroid', 'BoundingBox', 'Eccentricity');
    
    % Step 4: Filter precipitates by size
    valid_precipitates = [];
    precipitate_locations = [];
    size_distribution = [];
    
    for i = 1:length(stats)
        area = stats(i).Area;
        if area >= params.min_precipitate_size && area <= params.max_precipitate_size
            valid_precipitates = [valid_precipitates, i];
            precipitate_locations = [precipitate_locations; stats(i).Centroid];
            size_distribution = [size_distribution; area];
        end
    end
    
    % Step 5: Detect stacking faults using edge detection
    % Stacking faults appear as linear features
    edges = edge(ir_image, 'canny', [0.1 0.2]);
    
    % Apply Hough transform to detect lines
    [H, theta, rho] = hough(edges);
    peaks = houghpeaks(H, 20, 'threshold', ceil(0.3 * max(H(:))));
    lines = houghlines(edges, theta, rho, peaks, 'FillGap', 5, 'MinLength', 7);
    
    % Step 6: Create density map
    density_map = zeros(size(ir_image));
    
    % Create density map based on precipitate locations
    if ~isempty(precipitate_locations)
        % Use Gaussian kernel to create density distribution
        sigma = 20; % Standard deviation for Gaussian kernel
        for i = 1:size(precipitate_locations, 1)
            center = precipitate_locations(i, :);
            size_val = size_distribution(i);
            
            % Create Gaussian kernel centered at precipitate location
            [X, Y] = meshgrid(1:size(ir_image, 2), 1:size(ir_image, 1));
            gaussian_kernel = exp(-((X - center(1)).^2 + (Y - center(2)).^2) / (2 * sigma^2));
            
            % Weight by precipitate size
            density_map = density_map + gaussian_kernel * size_val;
        end
    end
    
    % Normalize density map
    if max(density_map(:)) > 0
        density_map = density_map / max(density_map(:));
    end
    
    % Display results
    fprintf('Found %d oxygen precipitates\n', length(valid_precipitates));
    fprintf('Average precipitate size: %.2f pixels\n', mean(size_distribution));
    fprintf('Found %d potential stacking fault lines\n', length(lines));
    
    % Visualization
    figure('Name', 'Oxygen Precipitation Detection Results');
    
    subplot(2, 3, 1);
    imshow(ir_image, []);
    title('Original IR Image');
    
    subplot(2, 3, 2);
    imshow(binary_mask);
    title('Binary Mask');
    
    subplot(2, 3, 3);
    imshow(edges);
    title('Edge Detection (Stacking Faults)');
    
    subplot(2, 3, 4);
    imshow(density_map, []);
    title('Precipitate Density Map');
    
    subplot(2, 3, 5);
    histogram(size_distribution, 20);
    title('Precipitate Size Distribution');
    xlabel('Size (pixels)');
    ylabel('Count');
    
    subplot(2, 3, 6);
    imshow(ir_image, []);
    hold on;
    if ~isempty(precipitate_locations)
        plot(precipitate_locations(:, 1), precipitate_locations(:, 2), 'r+', 'MarkerSize', 10);
    end
    if ~isempty(lines)
        for k = 1:length(lines)
            xy = [lines(k).point1; lines(k).point2];
            plot(xy(:, 1), xy(:, 2), 'LineWidth', 2, 'Color', 'yellow');
        end
    end
    title('Detected Precipitates and Stacking Faults');
    hold off;
    
    % Save results
    results.precipitate_locations = precipitate_locations;
    results.size_distribution = size_distribution;
    results.density_map = density_map;
    results.stacking_fault_lines = lines;
    results.binary_mask = binary_mask;
    results.parameters = params;
    
    assignin('base', 'oxygen_precipitation_results', results);
    
end
