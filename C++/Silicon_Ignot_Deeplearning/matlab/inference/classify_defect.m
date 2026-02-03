function [classLabel, confidence] = classify_defect(imgArray)
% CLASSIFY_DEFECT Classifies silicon ingot defects using trained model
%
% Input:
%   imgArray - Input image array (from C++)
%
% Output:
%   classLabel - Predicted defect class label
%   confidence - Confidence score for the prediction
%
% This function is called from C++ via MATLAB Engine API

% Persistent variable to store loaded model
persistent trainedModel;

% Load model if not already loaded
if isempty(trainedModel)
    fprintf('Loading trained model...\n');
    load_model();
    trainedModel = evalin('base', 'trainedModel');
end

% Convert input array to proper format
img = preprocess_image(imgArray);

% Run inference
[label, scores] = classify(trainedModel, img);

% Return class and confidence
classLabel = string(label);
confidence = max(scores);

% Optional: Display results for debugging
fprintf('Predicted class: %s, Confidence: %.3f\n', classLabel, confidence);

end

function img = preprocess_image(imgArray)
% PREPROCESS_IMAGE Preprocesses image for neural network input
%
% Input:
%   imgArray - Raw image array from C++
%
% Output:
%   img - Preprocessed image ready for classification

% Convert to double and normalize to [0, 1] if needed
if max(imgArray(:)) > 1
    img = double(imgArray) / 255.0;
else
    img = double(imgArray);
end

% Ensure image is in the correct format for ResNet
% ResNet expects RGB images with values in [0, 1]
if size(img, 3) == 1
    % Convert grayscale to RGB
    img = repmat(img, [1, 1, 3]);
elseif size(img, 3) == 3
    % Already RGB, ensure correct channel order
    % C++ sends BGR, MATLAB expects RGB
    img = img(:, :, [3, 2, 1]);
end

% Resize to 224x224 if needed (ResNet-18 input size)
if size(img, 1) ~= 224 || size(img, 2) ~= 224
    img = imresize(img, [224, 224]);
end

% Apply additional preprocessing if needed
% (e.g., normalization using ImageNet statistics)
meanImg = [0.485, 0.456, 0.406];
stdImg = [0.229, 0.224, 0.225];

for i = 1:3
    img(:, :, i) = (img(:, :, i) - meanImg(i)) / stdImg(i);
end

end
