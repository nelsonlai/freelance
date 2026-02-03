function train_defect_classifier()
% TRAIN_DEFECT_CLASSIFIER Trains a ResNet-18 model for silicon ingot defect classification
%
% This script:
% 1. Loads and prepares the dataset
% 2. Creates data augmentation pipeline
% 3. Sets up training options
% 4. Trains the model
% 5. Evaluates performance
% 6. Saves the trained model

fprintf('Starting silicon ingot defect classification training...\n');

%% 1. Dataset Preparation
fprintf('Preparing dataset...\n');

% Define paths
dataPath = fullfile('..', 'data', 'labeled');
trainPath = fullfile(dataPath, 'train');
valPath = fullfile(dataPath, 'validation');
testPath = fullfile(dataPath, 'test');

% Check if dataset exists
if ~exist(dataPath, 'dir')
    error('Dataset not found at: %s\nPlease run prepare_dataset.m first.', dataPath);
end

% Create image datastores
imdsTrain = imageDatastore(trainPath, 'IncludeSubfolders', true, 'LabelSource', 'foldernames');
imdsValidation = imageDatastore(valPath, 'IncludeSubfolders', true, 'LabelSource', 'foldernames');
imdsTest = imageDatastore(testPath, 'IncludeSubfolders', true, 'LabelSource', 'foldernames');

% Display dataset information
fprintf('Training images: %d\n', numel(imdsTrain.Files));
fprintf('Validation images: %d\n', numel(imdsValidation.Files));
fprintf('Test images: %d\n', numel(imdsTest.Files));

% Display class distribution
[uniqueLabels, ~, idx] = unique(imdsTrain.Labels);
counts = accumarray(idx, 1);
fprintf('Class distribution:\n');
for i = 1:length(uniqueLabels)
    fprintf('  %s: %d images\n', string(uniqueLabels(i)), counts(i));
end

%% 2. Data Augmentation
fprintf('Setting up data augmentation...\n');

% Define augmentation pipeline
imageAugmenter = imageDataAugmenter(...
    'RandRotation', [-15, 15], ...
    'RandXReflection', true, ...
    'RandYReflection', false, ...
    'RandXTranslation', [-10, 10], ...
    'RandYTranslation', [-10, 10], ...
    'RandXScale', [0.9, 1.1], ...
    'RandYScale', [0.9, 1.1], ...
    'RandContrast', [0.8, 1.2], ...
    'RandBrightness', [-0.1, 0.1]);

% Create augmented image datastores
augimdsTrain = augmentedImageDatastore([224, 224, 3], imdsTrain, 'DataAugmentation', imageAugmenter);
augimdsValidation = augmentedImageDatastore([224, 224, 3], imdsValidation);

%% 3. Model Architecture
fprintf('Creating model architecture...\n');

% Get number of classes
numClasses = numel(uniqueLabels);
fprintf('Number of classes: %d\n', numClasses);

% Create model
lgraph = model_architecture(numClasses);

%% 4. Training Options
fprintf('Setting up training options...\n');

% Define training options
options = trainingOptions('sgdm', ...
    'InitialLearnRate', 0.001, ...
    'MaxEpochs', 30, ...
    'MiniBatchSize', 32, ...
    'ValidationData', augimdsValidation, ...
    'ValidationFrequency', 50, ...
    'ValidationPatience', 5, ...
    'Shuffle', 'every-epoch', ...
    'Verbose', true, ...
    'VerboseFrequency', 10, ...
    'Plots', 'training-progress', ...
    'ExecutionEnvironment', 'auto', ...
    'LearnRateSchedule', 'piecewise', ...
    'LearnRateDropFactor', 0.1, ...
    'LearnRateDropPeriod', 10, ...
    'L2Regularization', 0.0001, ...
    'GradientThreshold', 1);

%% 5. Training
fprintf('Starting training...\n');
fprintf('This may take several hours depending on dataset size and hardware.\n');

% Train the model
[trainedModel, info] = trainNetwork(augimdsTrain, lgraph, options);

%% 6. Evaluation
fprintf('Evaluating model performance...\n');

% Test on validation set
[YPred, scores] = classify(trainedModel, augimdsValidation);
YValidation = imdsValidation.Labels;

% Calculate accuracy
accuracy = sum(YPred == YValidation) / numel(YValidation);
fprintf('Validation Accuracy: %.2f%%\n', accuracy * 100);

% Display confusion matrix
figure;
confusionchart(YValidation, YPred);
title('Validation Confusion Matrix');

% Calculate per-class metrics
[confMat, order] = confusionmat(YValidation, YPred);
precision = diag(confMat) ./ sum(confMat, 2);
recall = diag(confMat) ./ sum(confMat, 1)';
f1Score = 2 * (precision .* recall) ./ (precision + recall);

fprintf('Per-class metrics:\n');
for i = 1:length(order)
    fprintf('  %s: Precision=%.3f, Recall=%.3f, F1=%.3f\n', ...
        string(order(i)), precision(i), recall(i), f1Score(i));
end

%% 7. Test Set Evaluation
fprintf('Evaluating on test set...\n');

augimdsTest = augmentedImageDatastore([224, 224, 3], imdsTest);
[YPredTest, scoresTest] = classify(trainedModel, augimdsTest);
YTest = imdsTest.Labels;

testAccuracy = sum(YPredTest == YTest) / numel(YTest);
fprintf('Test Accuracy: %.2f%%\n', testAccuracy * 100);

% Test confusion matrix
figure;
confusionchart(YTest, YPredTest);
title('Test Confusion Matrix');

%% 8. Save Model
fprintf('Saving trained model...\n');

% Create models directory if it doesn't exist
modelsDir = fullfile('..', 'models');
if ~exist(modelsDir, 'dir')
    mkdir(modelsDir);
end

% Save model with timestamp
timestamp = datestr(now, 'yyyymmdd_HHMMSS');
modelFile = fullfile(modelsDir, sprintf('defect_classifier_v%s.mat', timestamp));
save(modelFile, 'trainedModel', 'info', 'accuracy', 'testAccuracy');

% Also save as default version
defaultModelFile = fullfile(modelsDir, 'defect_classifier_v1.mat');
save(defaultModelFile, 'trainedModel', 'info', 'accuracy', 'testAccuracy');

fprintf('Model saved to: %s\n', modelFile);
fprintf('Default model saved to: %s\n', defaultModelFile);

%% 9. Training Summary
fprintf('\n=== Training Summary ===\n');
fprintf('Final Validation Accuracy: %.2f%%\n', accuracy * 100);
fprintf('Final Test Accuracy: %.2f%%\n', testAccuracy * 100);
fprintf('Total Training Time: %.2f minutes\n', info.TrainingTime / 60);
fprintf('Model saved successfully!\n');

end
