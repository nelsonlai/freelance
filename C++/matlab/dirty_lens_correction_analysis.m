% MATLAB Script for Dirty Lens Correction Analysis
% This script provides additional analysis and visualization capabilities
% for dirty camera lens correction algorithms

function dirty_lens_correction_analysis()
    fprintf('=== Dirty Lens Correction Analysis ===\n');
    fprintf('This script provides comprehensive analysis of dirty lens correction algorithms.\n\n');
    
    % Check if images exist in workspace
    if ~exist('originalImage', 'var') || ~exist('correctedImage', 'var')
        fprintf('Error: originalImage and correctedImage variables not found in workspace.\n');
        fprintf('Please run the C++ program and press ''m'' to send data to MATLAB.\n');
        return;
    end
    
    % Display basic information
    fprintf('Image Analysis Results:\n');
    fprintf('Original image size: %d x %d x %d\n', size(originalImage));
    fprintf('Corrected image size: %d x %d x %d\n', size(correctedImage));
    
    % Calculate additional quality metrics
    fprintf('\nCalculating quality metrics...\n');
    
    % Convert to double for calculations
    orig_double = double(originalImage);
    corr_double = double(correctedImage);
    
    % Calculate PSNR
    mse = mean((orig_double(:) - corr_double(:)).^2);
    psnr_val = 20 * log10(255 / sqrt(mse));
    fprintf('PSNR: %.2f dB\n', psnr_val);
    
    % Calculate SSIM (simplified version)
    ssim_val = calculate_ssim(orig_double, corr_double);
    fprintf('SSIM: %.4f\n', ssim_val);
    
    % Calculate MSE
    fprintf('MSE: %.2f\n', mse);
    
    % Calculate structural similarity
    fprintf('\nStructural Analysis:\n');
    
    % Edge detection comparison
    orig_edges = edge(rgb2gray(originalImage), 'canny');
    corr_edges = edge(rgb2gray(correctedImage), 'canny');
    
    edge_similarity = sum(orig_edges(:) & corr_edges(:)) / sum(orig_edges(:) | corr_edges(:));
    fprintf('Edge similarity: %.4f\n', edge_similarity);
    
    % Histogram analysis
    fprintf('\nHistogram Analysis:\n');
    
    % Convert to grayscale for histogram analysis
    orig_gray = rgb2gray(originalImage);
    corr_gray = rgb2gray(correctedImage);
    
    % Calculate histogram statistics
    orig_mean = mean(orig_gray(:));
    corr_mean = mean(corr_gray(:));
    orig_std = std(double(orig_gray(:)));
    corr_std = std(double(corr_gray(:)));
    
    fprintf('Original - Mean: %.2f, Std: %.2f\n', orig_mean, orig_std);
    fprintf('Corrected - Mean: %.2f, Std: %.2f\n', corr_mean, corr_std);
    
    % Contrast improvement
    contrast_improvement = (corr_std - orig_std) / orig_std * 100;
    fprintf('Contrast improvement: %.2f%%\n', contrast_improvement);
    
    % Create comprehensive visualization
    create_comprehensive_visualization(originalImage, correctedImage, orig_edges, corr_edges);
    
    % Frequency domain analysis
    fprintf('\nFrequency Domain Analysis:\n');
    frequency_domain_analysis(originalImage, correctedImage);
    
    % Noise analysis
    fprintf('\nNoise Analysis:\n');
    noise_analysis(originalImage, correctedImage);
    
    fprintf('\nAnalysis complete!\n');
end

function ssim_val = calculate_ssim(img1, img2)
    % Simplified SSIM calculation
    % Convert to grayscale if needed
    if size(img1, 3) == 3
        img1 = rgb2gray(uint8(img1));
        img2 = rgb2gray(uint8(img2));
    end
    
    img1 = double(img1);
    img2 = double(img2);
    
    % Constants
    C1 = 6.5025; % (0.01*255)^2
    C2 = 58.5225; % (0.03*255)^2
    
    % Calculate means
    mu1 = mean(img1(:));
    mu2 = mean(img2(:));
    
    % Calculate variances and covariance
    sigma1_sq = var(img1(:));
    sigma2_sq = var(img2(:));
    sigma12 = cov(img1(:), img2(:));
    sigma12 = sigma12(1,2);
    
    % Calculate SSIM
    numerator = (2*mu1*mu2 + C1) * (2*sigma12 + C2);
    denominator = (mu1^2 + mu2^2 + C1) * (sigma1_sq + sigma2_sq + C2);
    
    ssim_val = numerator / denominator;
end

function create_comprehensive_visualization(orig, corr, orig_edges, corr_edges)
    % Create a comprehensive visualization figure
    figure('Name', 'Dirty Lens Correction Analysis', 'Position', [100, 100, 1200, 800]);
    
    % Original image
    subplot(3, 4, 1);
    imshow(orig);
    title('Original Image');
    
    % Corrected image
    subplot(3, 4, 2);
    imshow(corr);
    title('Corrected Image');
    
    % Difference image
    subplot(3, 4, 3);
    diff_img = abs(double(orig) - double(corr));
    diff_img = uint8(diff_img * 5); % Amplify for visibility
    imshow(diff_img);
    title('Difference (Amplified)');
    
    % Edge comparison
    subplot(3, 4, 4);
    edge_diff = xor(orig_edges, corr_edges);
    imshow(edge_diff);
    title('Edge Differences');
    
    % Histograms
    subplot(3, 4, 5);
    orig_gray = rgb2gray(orig);
    histogram(orig_gray, 'BinWidth', 2);
    title('Original Histogram');
    xlabel('Intensity');
    ylabel('Count');
    
    subplot(3, 4, 6);
    corr_gray = rgb2gray(corr);
    histogram(corr_gray, 'BinWidth', 2);
    title('Corrected Histogram');
    xlabel('Intensity');
    ylabel('Count');
    
    % Color channel analysis
    subplot(3, 4, 7);
    orig_r = orig(:,:,1);
    orig_g = orig(:,:,2);
    orig_b = orig(:,:,3);
    plot([mean(orig_r(:)), mean(orig_g(:)), mean(orig_b(:))], 'ro-', 'LineWidth', 2);
    hold on;
    corr_r = corr(:,:,1);
    corr_g = corr(:,:,2);
    corr_b = corr(:,:,3);
    plot([mean(corr_r(:)), mean(corr_g(:)), mean(corr_b(:))], 'bo-', 'LineWidth', 2);
    title('RGB Channel Means');
    xlabel('Channel (R, G, B)');
    ylabel('Mean Intensity');
    legend('Original', 'Corrected');
    grid on;
    
    % Local contrast analysis
    subplot(3, 4, 8);
    orig_local_std = stdfilt(orig_gray);
    corr_local_std = stdfilt(corr_gray);
    plot(orig_local_std(:), corr_local_std(:), '.', 'MarkerSize', 1);
    xlabel('Original Local Std');
    ylabel('Corrected Local Std');
    title('Local Contrast Comparison');
    grid on;
    
    % Frequency domain visualization
    subplot(3, 4, 9);
    orig_fft = fft2(orig_gray);
    orig_fft_shift = fftshift(orig_fft);
    orig_fft_mag = log(abs(orig_fft_shift) + 1);
    imshow(orig_fft_mag, []);
    title('Original Frequency Domain');
    
    subplot(3, 4, 10);
    corr_fft = fft2(corr_gray);
    corr_fft_shift = fftshift(corr_fft);
    corr_fft_mag = log(abs(corr_fft_shift) + 1);
    imshow(corr_fft_mag, []);
    title('Corrected Frequency Domain');
    
    % Difference in frequency domain
    subplot(3, 4, 11);
    fft_diff = abs(orig_fft_mag - corr_fft_mag);
    imshow(fft_diff, []);
    title('Frequency Domain Difference');
    
    % Quality metrics summary
    subplot(3, 4, 12);
    axis off;
    
    % Calculate metrics
    mse = mean((double(orig(:)) - double(corr(:))).^2);
    psnr_val = 20 * log10(255 / sqrt(mse));
    ssim_val = calculate_ssim(double(orig), double(corr));
    
    text_str = sprintf(['Quality Metrics:\n\n' ...
                       'PSNR: %.2f dB\n' ...
                       'SSIM: %.4f\n' ...
                       'MSE: %.2f\n\n' ...
                       'Contrast:\n' ...
                       'Original Std: %.2f\n' ...
                       'Corrected Std: %.2f\n' ...
                       'Improvement: %.1f%%'], ...
                       psnr_val, ssim_val, mse, ...
                       std(double(orig_gray(:))), ...
                       std(double(corr_gray(:))), ...
                       (std(double(corr_gray(:))) - std(double(orig_gray(:)))) / std(double(orig_gray(:))) * 100);
    
    text(0.1, 0.5, text_str, 'FontSize', 10, 'VerticalAlignment', 'middle');
end

function frequency_domain_analysis(orig, corr)
    % Convert to grayscale
    orig_gray = rgb2gray(orig);
    corr_gray = rgb2gray(corr);
    
    % Calculate FFT
    orig_fft = fft2(double(orig_gray));
    corr_fft = fft2(double(corr_gray));
    
    % Calculate power spectral density
    orig_psd = abs(orig_fft).^2;
    corr_psd = abs(corr_fft).^2;
    
    % Calculate radial power spectrum
    [M, N] = size(orig_gray);
    center_x = floor(M/2) + 1;
    center_y = floor(N/2) + 1;
    
    % Create distance matrix
    [X, Y] = meshgrid(1:N, 1:M);
    distances = sqrt((X - center_y).^2 + (Y - center_x).^2);
    
    % Calculate radial power spectrum
    max_radius = min(center_x, center_y);
    radii = 1:max_radius;
    
    orig_radial_psd = zeros(size(radii));
    corr_radial_psd = zeros(size(radii));
    
    for i = 1:length(radii)
        mask = (distances >= radii(i)-0.5) & (distances < radii(i)+0.5);
        orig_radial_psd(i) = mean(orig_psd(mask));
        corr_radial_psd(i) = mean(corr_psd(mask));
    end
    
    % Plot radial power spectrum
    figure('Name', 'Frequency Domain Analysis', 'Position', [200, 200, 800, 400]);
    
    subplot(1, 2, 1);
    semilogy(radii, orig_radial_psd, 'r-', 'LineWidth', 2);
    hold on;
    semilogy(radii, corr_radial_psd, 'b-', 'LineWidth', 2);
    xlabel('Spatial Frequency (pixels)');
    ylabel('Power Spectral Density');
    title('Radial Power Spectrum');
    legend('Original', 'Corrected');
    grid on;
    
    subplot(1, 2, 2);
    plot(radii, corr_radial_psd ./ orig_radial_psd, 'g-', 'LineWidth', 2);
    xlabel('Spatial Frequency (pixels)');
    ylabel('Power Ratio (Corrected/Original)');
    title('Frequency Response Ratio');
    grid on;
    
    fprintf('High-frequency content analysis complete.\n');
end

function noise_analysis(orig, corr)
    % Convert to grayscale
    orig_gray = rgb2gray(orig);
    corr_gray = rgb2gray(corr);
    
    % Estimate noise using Laplacian
    orig_laplacian = conv2(double(orig_gray), [0 -1 0; -1 4 -1; 0 -1 0], 'same');
    corr_laplacian = conv2(double(corr_gray), [0 -1 0; -1 4 -1; 0 -1 0], 'same');
    
    orig_noise_estimate = std(orig_laplacian(:));
    corr_noise_estimate = std(corr_laplacian(:));
    
    fprintf('Noise estimate (Laplacian std):\n');
    fprintf('Original: %.2f\n', orig_noise_estimate);
    fprintf('Corrected: %.2f\n', corr_noise_estimate);
    
    % Calculate noise reduction
    noise_reduction = (orig_noise_estimate - corr_noise_estimate) / orig_noise_estimate * 100;
    fprintf('Noise reduction: %.2f%%\n', noise_reduction);
    
    % Create noise analysis figure
    figure('Name', 'Noise Analysis', 'Position', [300, 300, 800, 400]);
    
    subplot(1, 2, 1);
    histogram(orig_laplacian(:), 'BinWidth', 1);
    title('Original Image Noise Distribution');
    xlabel('Laplacian Response');
    ylabel('Count');
    grid on;
    
    subplot(1, 2, 2);
    histogram(corr_laplacian(:), 'BinWidth', 1);
    title('Corrected Image Noise Distribution');
    xlabel('Laplacian Response');
    ylabel('Count');
    grid on;
end

% Additional utility functions for advanced analysis

function analyze_color_channels(img, title_str)
    % Analyze individual color channels
    figure('Name', title_str, 'Position', [400, 400, 1000, 300]);
    
    for i = 1:3
        subplot(1, 3, i);
        channel = img(:,:,i);
        histogram(channel, 'BinWidth', 2);
        channel_names = {'Red', 'Green', 'Blue'};
        title([channel_names{i} ' Channel']);
        xlabel('Intensity');
        ylabel('Count');
        grid on;
    end
end

function calculate_sharpness_metrics(img)
    % Calculate various sharpness metrics
    gray_img = rgb2gray(img);
    
    % Laplacian variance
    laplacian_kernel = [0 -1 0; -1 4 -1; 0 -1 0];
    laplacian_response = conv2(double(gray_img), laplacian_kernel, 'same');
    laplacian_variance = var(laplacian_response(:));
    
    % Gradient magnitude
    [Gx, Gy] = gradient(double(gray_img));
    gradient_magnitude = sqrt(Gx.^2 + Gy.^2);
    gradient_mean = mean(gradient_magnitude(:));
    
    % Tenenbaum gradient
    tenenbaum_kernel_x = [-1 0 1; -2 0 2; -1 0 1];
    tenenbaum_kernel_y = [-1 -2 -1; 0 0 0; 1 2 1];
    tx = conv2(double(gray_img), tenenbaum_kernel_x, 'same');
    ty = conv2(double(gray_img), tenenbaum_kernel_y, 'same');
    tenenbaum_gradient = sqrt(tx.^2 + ty.^2);
    tenenbaum_mean = mean(tenenbaum_gradient(:));
    
    fprintf('Sharpness Metrics:\n');
    fprintf('Laplacian Variance: %.2f\n', laplacian_variance);
    fprintf('Gradient Mean: %.2f\n', gradient_mean);
    fprintf('Tenenbaum Gradient: %.2f\n', tenenbaum_mean);
end

% Run the analysis if this script is executed directly
if nargin == 0
    dirty_lens_correction_analysis();
end
