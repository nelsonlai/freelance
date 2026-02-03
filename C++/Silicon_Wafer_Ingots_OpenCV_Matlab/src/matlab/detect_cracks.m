function [crack_topology, crack_widths, crack_lengths] = detect_cracks(image, varargin)
%DETECT_CRACKS Detect cracks and slip lines using edge detection and skeletonization
%
% Inputs:
%   image - Optical image (grayscale)
%   varargin - Optional parameters:
%     'edge_method' - Edge detection method ('canny', 'sobel', 'prewitt')
%     'hough_threshold' - Threshold for Hough line detection
%     'min_crack_length' - Minimum crack length
%     'max_crack_width' - Maximum crack width
%     'skeleton_method' - Skeletonization method ('thin', 'skel')
%
% Outputs:
%   crack_topology - Structure containing crack network information
%   crack_widths - Vector of crack widths at various points
%   crack_lengths - Vector of crack lengths

    % Parse input parameters
    p = inputParser;
    addParameter(p, 'edge_method', 'canny', @ischar);
    addParameter(p, 'hough_threshold', 0.3, @isnumeric);
    addParameter(p, 'min_crack_length', 20, @isnumeric);
    addParameter(p, 'max_crack_width', 10, @isnumeric);
    addParameter(p, 'skeleton_method', 'thin', @ischar);
    parse(p, varargin{:});
    
    params = p.Results;
    
    % Convert to double for processing
    if ~isa(image, 'double')
        image = double(image) / 255.0;
    end
    
    fprintf('Detecting cracks and slip lines...\n');
    
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
    
    % Step 3: Morphological operations to enhance crack structures
    % Use directional structuring elements to enhance linear features
    se_horizontal = strel('line', 7, 0);
    se_vertical = strel('line', 7, 90);
    se_diagonal1 = strel('line', 7, 45);
    se_diagonal2 = strel('line', 7, -45);
    
    % Apply directional opening to enhance cracks in different orientations
    edges_h = imopen(edges, se_horizontal);
    edges_v = imopen(edges, se_vertical);
    edges_d1 = imopen(edges, se_diagonal1);
    edges_d2 = imopen(edges, se_diagonal2);
    
    % Combine all directional edges
    enhanced_edges = edges_h | edges_v | edges_d1 | edges_d2;
    
    % Step 4: Skeletonization to extract crack topology
    switch params.skeleton_method
        case 'thin'
            skeleton = bwmorph(enhanced_edges, 'thin', Inf);
        case 'skel'
            skeleton = bwmorph(enhanced_edges, 'skel', Inf);
        otherwise
            error('Unknown skeletonization method: %s', params.skeleton_method);
    end
    
    % Step 5: Analyze crack topology
    crack_topology = analyzeCrackTopology(skeleton);
    
    % Step 6: Detect crack lines using Hough transform
    [H, theta, rho] = hough(enhanced_edges);
    peaks = houghpeaks(H, 50, 'threshold', ceil(params.hough_threshold * max(H(:))));
    crack_lines = houghlines(enhanced_edges, theta, rho, peaks, ...
                           'FillGap', 5, 'MinLength', params.min_crack_length);
    
    % Step 7: Calculate crack widths using distance transform
    crack_widths = calculateCrackWidths(enhanced_edges, skeleton);
    
    % Step 8: Calculate crack lengths
    crack_lengths = calculateCrackLengths(crack_lines, skeleton);
    
    % Step 9: Filter cracks by width and length
    valid_cracks = (crack_widths <= params.max_crack_width) & ...
                  (crack_lengths >= params.min_crack_length);
    
    % Filter results
    crack_widths = crack_widths(valid_cracks);
    crack_lengths = crack_lengths(valid_cracks);
    
    % Step 10: Analyze crack characteristics
    crack_properties = analyzeCrackProperties(crack_topology, crack_widths, crack_lengths);
    
    % Display results
    fprintf('Found %d crack segments\n', length(crack_lengths));
    fprintf('Average crack width: %.2f pixels\n', mean(crack_widths));
    fprintf('Average crack length: %.2f pixels\n', mean(crack_lengths));
    fprintf('Crack network has %d junctions\n', crack_topology.num_junctions);
    
    % Visualization
    figure('Name', 'Crack Detection Results');
    
    subplot(2, 4, 1);
    imshow(image, []);
    title('Original Image');
    
    subplot(2, 4, 2);
    imshow(enhanced_image, []);
    title('Enhanced Image');
    
    subplot(2, 4, 3);
    imshow(edges);
    title('Edge Detection');
    
    subplot(2, 4, 4);
    imshow(enhanced_edges);
    title('Enhanced Edges');
    
    subplot(2, 4, 5);
    imshow(skeleton);
    title('Crack Skeleton');
    
    subplot(2, 4, 6);
    histogram(crack_widths, 20);
    title('Crack Width Distribution');
    xlabel('Width (pixels)');
    ylabel('Count');
    
    subplot(2, 4, 7);
    histogram(crack_lengths, 20);
    title('Crack Length Distribution');
    xlabel('Length (pixels)');
    ylabel('Count');
    
    subplot(2, 4, 8);
    imshow(image, []);
    hold on;
    if ~isempty(crack_lines)
        for k = 1:length(crack_lines)
            xy = [crack_lines(k).point1; crack_lines(k).point2];
            plot(xy(:, 1), xy(:, 2), 'LineWidth', 2, 'Color', 'red');
        end
    end
    title('Detected Cracks');
    hold off;
    
    % Additional visualization for crack topology
    figure('Name', 'Crack Topology Analysis');
    
    subplot(1, 3, 1);
    imshow(skeleton);
    hold on;
    plot(crack_topology.junctions(:, 1), crack_topology.junctions(:, 2), 'ro', 'MarkerSize', 8);
    title('Crack Junctions');
    hold off;
    
    subplot(1, 3, 2);
    imshow(crack_topology.branch_map, []);
    title('Crack Branch Map');
    colormap(jet);
    
    subplot(1, 3, 3);
    imshow(crack_topology.width_map, []);
    title('Crack Width Map');
    colorbar;
    
    % Save results
    results.crack_topology = crack_topology;
    results.crack_widths = crack_widths;
    results.crack_lengths = crack_lengths;
    results.crack_lines = crack_lines;
    results.skeleton = skeleton;
    results.enhanced_edges = enhanced_edges;
    results.crack_properties = crack_properties;
    results.parameters = params;
    
    assignin('base', 'crack_results', results);
    
end

function topology = analyzeCrackTopology(skeleton)
    % Analyze crack topology from skeleton
    
    % Find junctions (points with more than 2 neighbors)
    junctions = findJunctions(skeleton);
    
    % Find endpoints (points with exactly 1 neighbor)
    endpoints = findEndpoints(skeleton);
    
    % Find branches (connected components between junctions)
    branches = findBranches(skeleton, junctions);
    
    % Create branch map
    branch_map = zeros(size(skeleton));
    for i = 1:length(branches)
        branch_map(branches{i}) = i;
    end
    
    % Calculate topology metrics
    topology.num_junctions = size(junctions, 1);
    topology.num_endpoints = size(endpoints, 1);
    topology.num_branches = length(branches);
    topology.junctions = junctions;
    topology.endpoints = endpoints;
    topology.branches = branches;
    topology.branch_map = branch_map;
    
    % Calculate connectivity
    topology.connectivity = calculateConnectivity(junctions, branches);
end

function junctions = findJunctions(skeleton)
    % Find junction points in skeleton
    
    % Count neighbors for each pixel
    neighbor_count = zeros(size(skeleton));
    
    for i = 2:size(skeleton, 1)-1
        for j = 2:size(skeleton, 2)-1
            if skeleton(i, j)
                % Count 8-connected neighbors
                neighbors = skeleton(i-1:i+1, j-1:j+1);
                neighbor_count(i, j) = sum(neighbors(:)) - 1; % Subtract center pixel
            end
        end
    end
    
    % Find points with more than 2 neighbors
    junction_mask = neighbor_count > 2;
    [row, col] = find(junction_mask);
    junctions = [col, row]; % [x, y] format
end

function endpoints = findEndpoints(skeleton)
    % Find endpoint points in skeleton
    
    % Count neighbors for each pixel
    neighbor_count = zeros(size(skeleton));
    
    for i = 2:size(skeleton, 1)-1
        for j = 2:size(skeleton, 2)-1
            if skeleton(i, j)
                % Count 8-connected neighbors
                neighbors = skeleton(i-1:i+1, j-1:j+1);
                neighbor_count(i, j) = sum(neighbors(:)) - 1; % Subtract center pixel
            end
        end
    end
    
    % Find points with exactly 1 neighbor
    endpoint_mask = neighbor_count == 1;
    [row, col] = find(endpoint_mask);
    endpoints = [col, row]; % [x, y] format
end

function branches = findBranches(skeleton, junctions)
    % Find branches between junctions
    
    branches = {};
    
    % Create a copy of skeleton for processing
    skeleton_copy = skeleton;
    
    % Mark junctions
    for i = 1:size(junctions, 1)
        skeleton_copy(junctions(i, 2), junctions(i, 1)) = 0;
    end
    
    % Find connected components (branches)
    cc = bwconncomp(skeleton_copy);
    
    for i = 1:cc.NumObjects
        branch_pixels = cc.PixelIdxList{i};
        branches{end+1} = branch_pixels;
    end
end

function connectivity = calculateConnectivity(junctions, branches)
    % Calculate connectivity metrics
    
    connectivity.num_junctions = size(junctions, 1);
    connectivity.num_branches = length(branches);
    connectivity.average_branch_length = 0;
    
    if ~isempty(branches)
        branch_lengths = cellfun(@length, branches);
        connectivity.average_branch_length = mean(branch_lengths);
        connectivity.branch_length_std = std(branch_lengths);
    end
end

function widths = calculateCrackWidths(edges, skeleton)
    % Calculate crack widths using distance transform
    
    % Create distance transform from edges
    distance_transform = bwdist(~edges);
    
    % Extract widths at skeleton points
    widths = distance_transform(skeleton);
    
    % Filter out zero widths
    widths = widths(widths > 0);
    
    % Convert to actual width (multiply by 2 for diameter)
    widths = widths * 2;
end

function lengths = calculateCrackLengths(crack_lines, skeleton)
    % Calculate crack lengths
    
    lengths = [];
    
    if ~isempty(crack_lines)
        for i = 1:length(crack_lines)
            xy = [crack_lines(i).point1; crack_lines(i).point2];
            length_val = sqrt((xy(2, 1) - xy(1, 1))^2 + (xy(2, 2) - xy(1, 2))^2);
            lengths = [lengths; length_val];
        end
    end
    
    % Also calculate lengths from skeleton branches
    cc = bwconncomp(skeleton);
    for i = 1:cc.NumObjects
        branch_pixels = cc.PixelIdxList{i};
        branch_length = length(branch_pixels);
        lengths = [lengths; branch_length];
    end
end

function properties = analyzeCrackProperties(topology, widths, lengths)
    % Analyze crack properties
    
    properties.num_cracks = length(lengths);
    properties.average_width = mean(widths);
    properties.width_std = std(widths);
    properties.average_length = mean(lengths);
    properties.length_std = std(lengths);
    properties.total_crack_length = sum(lengths);
    
    % Crack density
    properties.crack_density = properties.num_cracks / (size(topology.branch_map, 1) * size(topology.branch_map, 2));
    
    % Crack severity score
    properties.severity_score = min(1.0, properties.crack_density * 1000 + properties.average_width * 0.1);
end
