function load_model()
% LOAD_MODEL Loads the trained defect classification model
%
% This function loads the trained model and stores it in the base workspace
% for use by the classify_defect function

% Define model file path
modelPath = fullfile('..', 'models', 'defect_classifier_v1.mat');

% Check if model file exists
if ~exist(modelPath, 'file')
    error('Model file not found: %s\nPlease train the model first.', modelPath);
end

% Load the model
fprintf('Loading model from: %s\n', modelPath);
load(modelPath, 'trainedModel');

% Store in base workspace for persistent access
assignin('base', 'trainedModel', trainedModel);

fprintf('Model loaded successfully.\n');
fprintf('Model type: %s\n', class(trainedModel));
fprintf('Number of classes: %d\n', numel(trainedModel.Layers(end).Classes));

% Display class names
if isprop(trainedModel.Layers(end), 'Classes')
    fprintf('Class names:\n');
    for i = 1:length(trainedModel.Layers(end).Classes)
        fprintf('  %d. %s\n', i, trainedModel.Layers(end).Classes{i});
    end
end

end
