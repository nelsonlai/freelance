function processed_image = preprocess_image(image, varargin)
%PREPROCESS_IMAGE Additional MATLAB-side preprocessing for defect detection
%
% Inputs:
%   image - Input image (grayscale)
%   varargin - Optional parameters:
%     'noise_reduction' - Enable noise reduction (true/false)
%     'contrast_enhancement' - Enable contrast enhancement (true/false)
%     'normalization' - Enable intensity normalization (true/false)
%     'smoothing' - Smoothing factor (0-1)
%
% Outputs:
%   processed_image - Preprocessed image

    % Parse input parameters
    p = inputParser;
    addParameter(p, 'noise_reduction', true, @islogical);
    addParameter(p, 'contrast_enhancement', true, @islogical);
    addParameter(p, 'normalization', true, @islogical);
    addParameter(p, 'smoothing', 0.5, @isnumeric);
    parse(p, varargin{:});
    
    params = p.Results;
    
    % Convert to double for processing
    if ~isa(image, 'double')
        image = double(image) / 255.0;
    end
    
    processed_image = image;
    
    % Step 1: Noise reduction
    if params.noise_reduction
        processed_image = imgaussfilt(processed_image, params.smoothing);
    end
    
    % Step 2: Contrast enhancement
    if params.contrast_enhancement
        processed_image = adapthisteq(processed_image);
    end
    
    % Step 3: Intensity normalization
    if params.normalization
        processed_image = (processed_image - min(processed_image(:))) / ...
                         (max(processed_image(:)) - min(processed_image(:)));
    end
    
end
