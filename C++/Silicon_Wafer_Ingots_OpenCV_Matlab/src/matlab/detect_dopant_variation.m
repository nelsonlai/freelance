function [uniformity_score, variation_maps, resistivity_profiles] = detect_dopant_variation(image, varargin)
%DETECT_DOPANT_VARIATION Detect dopant nonuniformity using gradient analysis
%
% Inputs:
%   image - Resistivity map or correlated optical image (grayscale)
%   varargin - Optional parameters:
%     'analysis_method' - Analysis method ('gradient', 'profile', 'both')
%     'window_size' - Window size for local analysis
%     'gradient_threshold' - Threshold for gradient magnitude
%     'profile_direction' - Profile direction ('radial', 'axial', 'both')
%     'smoothing_factor' - Smoothing factor for profiles
%
% Outputs:
%   uniformity_score - Overall uniformity score (0-1, higher is better)
%   variation_maps - Structure containing various variation maps
%   resistivity_profiles - Structure containing resistivity profiles

    % Parse input parameters
    p = inputParser;
    addParameter(p, 'analysis_method', 'both', @ischar);
    addParameter(p, 'window_size', 50, @isnumeric);
    addParameter(p, 'gradient_threshold', 0.1, @isnumeric);
    addParameter(p, 'profile_direction', 'both', @ischar);
    addParameter(p, 'smoothing_factor', 0.1, @isnumeric);
    parse(p, varargin{:});
    
    params = p.Results;
    
    % Convert to double for processing
    if ~isa(image, 'double')
        image = double(image) / 255.0;
    end
    
    fprintf('Analyzing dopant uniformity...\n');
    
    % Step 1: Preprocessing - smooth image to reduce noise
    smoothed_image = imgaussfilt(image, 1);
    
    % Step 2: Gradient analysis
    variation_maps = struct();
    
    if strcmp(params.analysis_method, 'gradient') || strcmp(params.analysis_method, 'both')
        variation_maps = performGradientAnalysis(smoothed_image, params);
    end
    
    % Step 3: Profile analysis
    resistivity_profiles = struct();
    
    if strcmp(params.analysis_method, 'profile') || strcmp(params.analysis_method, 'both')
        resistivity_profiles = performProfileAnalysis(smoothed_image, params);
    end
    
    % Step 4: Calculate uniformity score
    uniformity_score = calculateUniformityScore(smoothed_image, variation_maps, resistivity_profiles);
    
    % Step 5: Analyze variation characteristics
    variation_analysis = analyzeVariationCharacteristics(variation_maps, resistivity_profiles);
    
    % Display results
    fprintf('Uniformity score: %.3f (higher is better)\n', uniformity_score);
    fprintf('Standard deviation: %.4f\n', variation_analysis.overall_std);
    fprintf('Coefficient of variation: %.2f%%\n', variation_analysis.coefficient_variation * 100);
    
    % Visualization
    figure('Name', 'Dopant Uniformity Analysis Results');
    
    subplot(2, 4, 1);
    imshow(image, []);
    title('Original Image');
    
    subplot(2, 4, 2);
    imshow(smoothed_image, []);
    title('Smoothed Image');
    
    if isfield(variation_maps, 'gradient_magnitude')
        subplot(2, 4, 3);
        imshow(variation_maps.gradient_magnitude, []);
        title('Gradient Magnitude');
        colorbar;
    end
    
    if isfield(variation_maps, 'local_std')
        subplot(2, 4, 4);
        imshow(variation_maps.local_std, []);
        title('Local Standard Deviation');
        colorbar;
    end
    
    if isfield(variation_maps, 'variation_map')
        subplot(2, 4, 5);
        imshow(variation_maps.variation_map, []);
        title('Variation Map');
        colorbar;
    end
    
    if isfield(resistivity_profiles, 'radial_profile')
        subplot(2, 4, 6);
        plot(resistivity_profiles.radial_profile);
        title('Radial Profile');
        xlabel('Radius (pixels)');
        ylabel('Intensity');
    end
    
    if isfield(resistivity_profiles, 'axial_profile')
        subplot(2, 4, 7);
        plot(resistivity_profiles.axial_profile);
        title('Axial Profile');
        xlabel('Position (pixels)');
        ylabel('Intensity');
    end
    
    subplot(2, 4, 8);
    histogram(image(:), 50);
    title('Intensity Distribution');
    xlabel('Intensity');
    ylabel('Frequency');
    
    % Additional visualization for detailed analysis
    figure('Name', 'Detailed Uniformity Analysis');
    
    subplot(2, 3, 1);
    imshow(image, []);
    hold on;
    % Draw center lines for profile analysis
    [M, N] = size(image);
    plot([N/2, N/2], [1, M], 'r--', 'LineWidth', 2);
    plot([1, N], [M/2, M/2], 'b--', 'LineWidth', 2);
    title('Profile Analysis Lines');
    hold off;
    
    subplot(2, 3, 2);
    if isfield(variation_maps, 'gradient_magnitude')
        imshow(variation_maps.gradient_magnitude, []);
        title('Gradient Magnitude Map');
        colorbar;
    end
    
    subplot(2, 3, 3);
    if isfield(variation_maps, 'local_std')
        imshow(variation_maps.local_std, []);
        title('Local Standard Deviation Map');
        colorbar;
    end
    
    subplot(2, 3, 4);
    if isfield(resistivity_profiles, 'radial_profile')
        plot(resistivity_profiles.radial_profile, 'b-', 'LineWidth', 2);
        hold on;
        if isfield(resistivity_profiles, 'radial_profile_smooth')
            plot(resistivity_profiles.radial_profile_smooth, 'r--', 'LineWidth', 2);
        end
        title('Radial Profile (Blue: Original, Red: Smoothed)');
        xlabel('Radius (pixels)');
        ylabel('Intensity');
        legend('Original', 'Smoothed', 'Location', 'best');
        hold off;
    end
    
    subplot(2, 3, 5);
    if isfield(resistivity_profiles, 'axial_profile')
        plot(resistivity_profiles.axial_profile, 'b-', 'LineWidth', 2);
        hold on;
        if isfield(resistivity_profiles, 'axial_profile_smooth')
            plot(resistivity_profiles.axial_profile_smooth, 'r--', 'LineWidth', 2);
        end
        title('Axial Profile (Blue: Original, Red: Smoothed)');
        xlabel('Position (pixels)');
        ylabel('Intensity');
        legend('Original', 'Smoothed', 'Location', 'best');
        hold off;
    end
    
    subplot(2, 3, 6);
    % Show uniformity score and statistics
    text(0.1, 0.8, sprintf('Uniformity Score: %.3f', uniformity_score), 'FontSize', 12);
    text(0.1, 0.6, sprintf('Overall Std: %.4f', variation_analysis.overall_std), 'FontSize', 12);
    text(0.1, 0.4, sprintf('CV: %.2f%%', variation_analysis.coefficient_variation * 100), 'FontSize', 12);
    text(0.1, 0.2, sprintf('Range: %.4f', variation_analysis.intensity_range), 'FontSize', 12);
    title('Uniformity Statistics');
    axis off;
    
    % Save results
    results.uniformity_score = uniformity_score;
    results.variation_maps = variation_maps;
    results.resistivity_profiles = resistivity_profiles;
    results.variation_analysis = variation_analysis;
    results.parameters = params;
    
    assignin('base', 'dopant_uniformity_results', results);
    
end

function variation_maps = performGradientAnalysis(image, params)
    % Perform gradient analysis for dopant uniformity
    
    % Calculate gradients
    [Gx, Gy] = imgradientxy(image);
    gradient_magnitude = sqrt(Gx.^2 + Gy.^2);
    
    % Calculate local standard deviation
    local_std = stdfilt(image, ones(params.window_size));
    
    % Calculate local mean
    local_mean = imfilter(image, ones(params.window_size) / params.window_size^2, 'same', 'replicate');
    
    % Calculate coefficient of variation
    coefficient_variation = local_std ./ (local_mean + eps);
    
    % Create variation map
    variation_map = gradient_magnitude + coefficient_variation;
    
    % Normalize variation map
    variation_map = variation_map / max(variation_map(:));
    
    % Store results
    variation_maps.gradient_magnitude = gradient_magnitude;
    variation_maps.local_std = local_std;
    variation_maps.local_mean = local_mean;
    variation_maps.coefficient_variation = coefficient_variation;
    variation_maps.variation_map = variation_map;
end

function resistivity_profiles = performProfileAnalysis(image, params)
    % Perform profile analysis for dopant uniformity
    
    [M, N] = size(image);
    center_x = N / 2;
    center_y = M / 2;
    
    resistivity_profiles = struct();
    
    % Radial profile analysis
    if strcmp(params.profile_direction, 'radial') || strcmp(params.profile_direction, 'both')
        radial_profile = extractRadialProfile(image, center_x, center_y);
        resistivity_profiles.radial_profile = radial_profile;
        
        % Smooth radial profile
        if params.smoothing_factor > 0
            radial_profile_smooth = smoothdata(radial_profile, 'gaussian', params.smoothing_factor * length(radial_profile));
            resistivity_profiles.radial_profile_smooth = radial_profile_smooth;
        end
    end
    
    % Axial profile analysis
    if strcmp(params.profile_direction, 'axial') || strcmp(params.profile_direction, 'both')
        axial_profile = extractAxialProfile(image, center_x, center_y);
        resistivity_profiles.axial_profile = axial_profile;
        
        % Smooth axial profile
        if params.smoothing_factor > 0
            axial_profile_smooth = smoothdata(axial_profile, 'gaussian', params.smoothing_factor * length(axial_profile));
            resistivity_profiles.axial_profile_smooth = axial_profile_smooth;
        end
    end
end

function radial_profile = extractRadialProfile(image, center_x, center_y)
    % Extract radial profile from center
    
    [M, N] = size(image);
    max_radius = min(center_x, center_y, N - center_x, M - center_y);
    
    radial_profile = zeros(1, round(max_radius));
    
    for r = 1:round(max_radius)
        % Sample points on circle
        theta = linspace(0, 2*pi, 8*r);
        x = center_x + r * cos(theta);
        y = center_y + r * sin(theta);
        
        % Interpolate values
        values = interp2(image, x, y, 'linear', 0);
        radial_profile(r) = mean(values);
    end
end

function axial_profile = extractAxialProfile(image, center_x, center_y)
    % Extract axial profile through center
    
    [M, N] = size(image);
    
    % Horizontal profile
    horizontal_profile = image(round(center_y), :);
    
    % Vertical profile
    vertical_profile = image(:, round(center_x));
    
    % Combine profiles (average)
    axial_profile = (horizontal_profile + vertical_profile') / 2;
end

function uniformity_score = calculateUniformityScore(image, variation_maps, resistivity_profiles)
    % Calculate overall uniformity score
    
    % Calculate overall statistics
    overall_std = std(image(:));
    overall_mean = mean(image(:));
    coefficient_variation = overall_std / overall_mean;
    
    % Calculate gradient-based uniformity
    if isfield(variation_maps, 'gradient_magnitude')
        gradient_uniformity = 1 - mean(variation_maps.gradient_magnitude(:));
    else
        gradient_uniformity = 0.5;
    end
    
    % Calculate profile-based uniformity
    profile_uniformity = 0.5;
    if isfield(resistivity_profiles, 'radial_profile')
        radial_std = std(resistivity_profiles.radial_profile);
        radial_uniformity = 1 - radial_std / mean(resistivity_profiles.radial_profile);
        profile_uniformity = radial_uniformity;
    end
    
    if isfield(resistivity_profiles, 'axial_profile')
        axial_std = std(resistivity_profiles.axial_profile);
        axial_uniformity = 1 - axial_std / mean(resistivity_profiles.axial_profile);
        profile_uniformity = (profile_uniformity + axial_uniformity) / 2;
    end
    
    % Calculate overall uniformity score
    uniformity_score = (gradient_uniformity + profile_uniformity) / 2;
    
    % Normalize to 0-1 range
    uniformity_score = max(0, min(1, uniformity_score));
end

function analysis = analyzeVariationCharacteristics(variation_maps, resistivity_profiles)
    % Analyze variation characteristics
    
    analysis = struct();
    
    % Overall statistics
    if isfield(variation_maps, 'local_std')
        analysis.overall_std = mean(variation_maps.local_std(:));
    else
        analysis.overall_std = 0;
    end
    
    if isfield(variation_maps, 'local_mean')
        analysis.overall_mean = mean(variation_maps.local_mean(:));
        analysis.coefficient_variation = analysis.overall_std / analysis.overall_mean;
    else
        analysis.overall_mean = 0;
        analysis.coefficient_variation = 0;
    end
    
    % Intensity range
    if isfield(variation_maps, 'local_mean')
        analysis.intensity_range = max(variation_maps.local_mean(:)) - min(variation_maps.local_mean(:));
    else
        analysis.intensity_range = 0;
    end
    
    % Profile analysis
    if isfield(resistivity_profiles, 'radial_profile')
        analysis.radial_std = std(resistivity_profiles.radial_profile);
        analysis.radial_range = max(resistivity_profiles.radial_profile) - min(resistivity_profiles.radial_profile);
    end
    
    if isfield(resistivity_profiles, 'axial_profile')
        analysis.axial_std = std(resistivity_profiles.axial_profile);
        analysis.axial_range = max(resistivity_profiles.axial_profile) - min(resistivity_profiles.axial_profile);
    end
end
