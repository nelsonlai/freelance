function [dislocation_lines, dislocation_density, slip_patterns] = detect_dislocations(image, varargin)
%DETECT_DISLOCATIONS Detect dislocations and slip lines in optical/IR images
%
% Inputs:
%   image - Input image (optical or IR)
%   varargin - Optional parameters:
%     'edge_method' - Edge detection method ('canny', 'sobel', 'prewitt')
%     'hough_threshold' - Threshold for Hough line detection
%     'min_line_length' - Minimum line length for detection
%     'line_gap' - Maximum gap between line segments
%     'density_window_size' - Window size for density calculation
%
% Outputs:
%   dislocation_lines - Structure array containing detected lines
%   dislocation_density - Density map of dislocation lines
%   slip_patterns - Binary mask showing slip line patterns

    % Parse input parameters
    p = inputParser;
    addParameter(p, 'edge_method', 'canny', @ischar);
    addParameter(p, 'hough_threshold', 0.3, @isnumeric);
    addParameter(p, 'min_line_length', 10, @isnumeric);
    addParameter(p, 'line_gap', 5, @isnumeric);
    addParameter(p, 'density_window_size', 50, @isnumeric);
    parse(p, varargin{:});
    
    params = p.Results;
    
    % Convert to double for processing
    if ~isa(image, 'double')
        image = double(image) / 255.0;
    end
    
    fprintf('Detecting dislocations and slip lines...\n');
    
    % Step 1: Preprocessing - enhance contrast for better edge detection
    enhanced_image = adapthisteq(image);
    
    % Step 2: Edge detection
    switch params.edge_method
        case 'canny'
            edges = edge(enhanced_image, 'canny', [0.1 0.3]);
        case 'sobel'
            edges = edge(enhanced_image, 'sobel');
        case 'prewitt'
            edges = edge(enhanced_image, 'prewitt');
        otherwise
            error('Unknown edge detection method: %s', params.edge_method);
    end
    
    % Step 3: Morphological operations to enhance line structures
    % Use directional structuring elements to enhance lines
    se_horizontal = strel('line', 5, 0);
    se_vertical = strel('line', 5, 90);
    se_diagonal1 = strel('line', 5, 45);
    se_diagonal2 = strel('line', 5, -45);
    
    % Apply directional opening to enhance lines in different orientations
    edges_h = imopen(edges, se_horizontal);
    edges_v = imopen(edges, se_vertical);
    edges_d1 = imopen(edges, se_diagonal1);
    edges_d2 = imopen(edges, se_diagonal2);
    
    % Combine all directional edges
    enhanced_edges = edges_h | edges_v | edges_d1 | edges_d2;
    
    % Step 4: Hough Transform for line detection
    [H, theta, rho] = hough(enhanced_edges);
    
    % Find peaks in Hough space
    peaks = houghpeaks(H, 50, 'threshold', ceil(params.hough_threshold * max(H(:))));
    
    % Extract lines
    dislocation_lines = houghlines(enhanced_edges, theta, rho, peaks, ...
                                  'FillGap', params.line_gap, ...
                                  'MinLength', params.min_line_length);
    
    % Step 5: Create slip pattern mask
    slip_patterns = false(size(image));
    
    if ~isempty(dislocation_lines)
        % Draw lines on the slip pattern mask
        for k = 1:length(dislocation_lines)
            xy = [dislocation_lines(k).point1; dislocation_lines(k).point2];
            
            % Create line mask
            line_mask = false(size(image));
            
            % Calculate line coordinates
            x1 = xy(1, 1); y1 = xy(1, 2);
            x2 = xy(2, 1); y2 = xy(2, 2);
            
            % Use Bresenham's line algorithm or simple interpolation
            num_points = max(abs(x2-x1), abs(y2-y1)) + 1;
            x_line = round(linspace(x1, x2, num_points));
            y_line = round(linspace(y1, y2, num_points));
            
            % Ensure coordinates are within image bounds
            valid_idx = x_line >= 1 & x_line <= size(image, 2) & ...
                       y_line >= 1 & y_line <= size(image, 1);
            
            x_line = x_line(valid_idx);
            y_line = y_line(valid_idx);
            
            % Set line pixels
            for i = 1:length(x_line)
                slip_patterns(y_line(i), x_line(i)) = true;
            end
        end
    end
    
    % Step 6: Calculate dislocation density
    dislocation_density = zeros(size(image));
    
    if ~isempty(dislocation_lines)
        % Create density map using sliding window
        window_size = params.density_window_size;
        half_window = floor(window_size / 2);
        
        for i = half_window + 1:size(image, 1) - half_window
            for j = half_window + 1:size(image, 2) - half_window
                % Define window region
                row_start = i - half_window;
                row_end = i + half_window;
                col_start = j - half_window;
                col_end = j + half_window;
                
                % Count dislocation lines in this window
                line_count = 0;
                for k = 1:length(dislocation_lines)
                    xy = [dislocation_lines(k).point1; dislocation_lines(k).point2];
                    
                    % Check if line intersects with current window
                    if lineIntersectsWindow(xy, [col_start, row_start, col_end, row_end])
                        line_count = line_count + 1;
                    end
                end
                
                % Calculate density (lines per unit area)
                dislocation_density(i, j) = line_count / (window_size^2);
            end
        end
    end
    
    % Step 7: Analyze slip line patterns
    % Detect slip bands and their orientations
    slip_orientations = analyzeSlipOrientations(dislocation_lines);
    
    % Display results
    fprintf('Found %d dislocation lines\n', length(dislocation_lines));
    fprintf('Average dislocation density: %.4f lines/pixel^2\n', mean(dislocation_density(:)));
    
    % Visualization
    figure('Name', 'Dislocation Detection Results');
    
    subplot(2, 3, 1);
    imshow(image, []);
    title('Original Image');
    
    subplot(2, 3, 2);
    imshow(enhanced_image, []);
    title('Enhanced Image');
    
    subplot(2, 3, 3);
    imshow(enhanced_edges);
    title('Enhanced Edges');
    
    subplot(2, 3, 4);
    imshow(slip_patterns);
    title('Slip Line Patterns');
    
    subplot(2, 3, 5);
    imshow(dislocation_density, []);
    title('Dislocation Density Map');
    colorbar;
    
    subplot(2, 3, 6);
    imshow(image, []);
    hold on;
    if ~isempty(dislocation_lines)
        for k = 1:length(dislocation_lines)
            xy = [dislocation_lines(k).point1; dislocation_lines(k).point2];
            plot(xy(:, 1), xy(:, 2), 'LineWidth', 2, 'Color', 'red');
        end
    end
    title('Detected Dislocation Lines');
    hold off;
    
    % Save results
    results.dislocation_lines = dislocation_lines;
    results.dislocation_density = dislocation_density;
    results.slip_patterns = slip_patterns;
    results.slip_orientations = slip_orientations;
    results.parameters = params;
    
    assignin('base', 'dislocation_results', results);
    
end

function intersects = lineIntersectsWindow(line_points, window)
    % Check if a line intersects with a rectangular window
    % window = [x1, y1, x2, y2] (top-left and bottom-right corners)
    
    x1 = line_points(1, 1); y1 = line_points(1, 2);
    x2 = line_points(2, 1); y2 = line_points(2, 2);
    
    wx1 = window(1); wy1 = window(2);
    wx2 = window(3); wy2 = window(4);
    
    % Check if any endpoint is inside the window
    if (x1 >= wx1 && x1 <= wx2 && y1 >= wy1 && y1 <= wy2) || ...
       (x2 >= wx1 && x2 <= wx2 && y2 >= wy1 && y2 <= wy2)
        intersects = true;
        return;
    end
    
    % Check if line intersects window boundaries
    % This is a simplified check - for more accuracy, implement proper
    % line-rectangle intersection algorithm
    intersects = false;
end

function orientations = analyzeSlipOrientations(dislocation_lines)
    % Analyze the orientations of slip lines
    
    if isempty(dislocation_lines)
        orientations = [];
        return;
    end
    
    orientations = zeros(length(dislocation_lines), 1);
    
    for i = 1:length(dislocation_lines)
        xy = [dislocation_lines(i).point1; dislocation_lines(i).point2];
        dx = xy(2, 1) - xy(1, 1);
        dy = xy(2, 2) - xy(1, 2);
        
        % Calculate angle in degrees
        orientations(i) = atan2d(dy, dx);
    end
    
    % Group orientations into slip systems
    % Common slip systems in silicon: {111}<110>
    % This is a simplified analysis
end
