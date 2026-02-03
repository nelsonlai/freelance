function prepare_dataset()
% PREPARE_DATASET Prepares the silicon ingot defect dataset for training
%
% This script:
% 1. Organizes images into train/validation/test splits
% 2. Balances classes by oversampling minority classes
% 3. Creates directory structure
% 4. Generates synthetic data if needed

fprintf('Preparing silicon ingot defect dataset...\n');

%% 1. Define Paths and Parameters
dataPath = fullfile('..', 'data');
labeledPath = fullfile(dataPath, 'labeled');
trainPath = fullfile(dataPath, 'train');
valPath = fullfile(dataPath, 'validation');
testPath = fullfile(dataPath, 'test');

% Class names based on defect types
classNames = {
    'class_1_oxygen',           % Oxygen precipitation / stacking faults
    'class_2_dislocations',     % Dislocations
    'class_3_vacancy',          % Vacancy defects (voids/pits)
    'class_4_interstitial',    % Interstitial defects (dislocation loops)
    'class_5_microvoids',      % Microvoids / COPs
    'class_6_slip_cracks',     % Slip lines / cracks
    'class_7_dopant',          % Dopant nonuniformity
    'class_8_normal'           % Normal (no defect)
};

% Split ratios
trainRatio = 0.7;
valRatio = 0.15;
testRatio = 0.15;

%% 2. Check if labeled data exists
if ~exist(labeledPath, 'dir')
    fprintf('Warning: Labeled data directory not found at: %s\n', labeledPath);
    fprintf('Please create the directory structure and add labeled images.\n');
    fprintf('Expected structure:\n');
    for i = 1:length(classNames)
        fprintf('  %s/\n', fullfile(labeledPath, classNames{i}));
    end
    return;
end

%% 3. Create output directories
fprintf('Creating output directories...\n');
mkdir(trainPath);
mkdir(valPath);
mkdir(testPath);

for i = 1:length(classNames)
    mkdir(fullfile(trainPath, classNames{i}));
    mkdir(fullfile(valPath, classNames{i}));
    mkdir(fullfile(testPath, classNames{i}));
end

%% 4. Process each class
fprintf('Processing classes...\n');

for classIdx = 1:length(classNames)
    className = classNames{classIdx};
    classPath = fullfile(labeledPath, className);
    
    if ~exist(classPath, 'dir')
        fprintf('Warning: Class directory not found: %s\n', classPath);
        continue;
    end
    
    % Get all images in class directory
    imageFiles = dir(fullfile(classPath, '*.jpg'));
    imageFiles = [imageFiles; dir(fullfile(classPath, '*.png'))];
    imageFiles = [imageFiles; dir(fullfile(classPath, '*.jpeg'))];
    
    if isempty(imageFiles)
        fprintf('Warning: No images found in: %s\n', classPath);
        continue;
    end
    
    fprintf('Processing %s: %d images\n', className, length(imageFiles));
    
    % Shuffle images
    randIdx = randperm(length(imageFiles));
    imageFiles = imageFiles(randIdx);
    
    % Calculate split indices
    numImages = length(imageFiles);
    trainEnd = round(numImages * trainRatio);
    valEnd = trainEnd + round(numImages * valRatio);
    
    % Copy images to respective directories
    for imgIdx = 1:numImages
        srcFile = fullfile(classPath, imageFiles(imgIdx).name);
        
        if imgIdx <= trainEnd
            dstPath = fullfile(trainPath, className);
        elseif imgIdx <= valEnd
            dstPath = fullfile(valPath, className);
        else
            dstPath = fullfile(testPath, className);
        end
        
        % Copy file
        copyfile(srcFile, dstPath);
    end
    
    fprintf('  Train: %d, Validation: %d, Test: %d\n', ...
        trainEnd, valEnd - trainEnd, numImages - valEnd);
end

%% 5. Generate synthetic data if needed
fprintf('Checking for class imbalance...\n');

% Count images in each class
classCounts = zeros(length(classNames), 3); % [train, val, test]

for classIdx = 1:length(classNames)
    className = classNames{classIdx};
    
    trainCount = length(dir(fullfile(trainPath, className, '*.jpg'))) + ...
                 length(dir(fullfile(trainPath, className, '*.png'))) + ...
                 length(dir(fullfile(trainPath, className, '*.jpeg')));
    
    valCount = length(dir(fullfile(valPath, className, '*.jpg'))) + ...
               length(dir(fullfile(valPath, className, '*.png'))) + ...
               length(dir(fullfile(valPath, className, '*.jpeg')));
    
    testCount = length(dir(fullfile(testPath, className, '*.jpg'))) + ...
                length(dir(fullfile(testPath, className, '*.png'))) + ...
                length(dir(fullfile(testPath, className, '*.jpeg')));
    
    classCounts(classIdx, :) = [trainCount, valCount, testCount];
end

% Display class distribution
fprintf('\nClass distribution:\n');
fprintf('%-20s %8s %8s %8s %8s\n', 'Class', 'Train', 'Val', 'Test', 'Total');
fprintf('%s\n', repmat('-', 1, 60));

for classIdx = 1:length(classNames)
    total = sum(classCounts(classIdx, :));
    fprintf('%-20s %8d %8d %8d %8d\n', ...
        classNames{classIdx}, classCounts(classIdx, 1), ...
        classCounts(classIdx, 2), classCounts(classIdx, 3), total);
end

%% 6. Generate synthetic data for minority classes
minSamples = 100; % Minimum samples per class

fprintf('\nGenerating synthetic data for classes with < %d samples...\n', minSamples);

for classIdx = 1:length(classNames)
    className = classNames{classIdx};
    trainCount = classCounts(classIdx, 1);
    
    if trainCount < minSamples
        fprintf('Generating synthetic data for %s (has %d samples)\n', className, trainCount);
        
        % Load existing images
        existingFiles = dir(fullfile(trainPath, className, '*.jpg'));
        existingFiles = [existingFiles; dir(fullfile(trainPath, className, '*.png'))];
        existingFiles = [existingFiles; dir(fullfile(trainPath, className, '*.jpeg'))];
        
        if ~isempty(existingFiles)
            % Generate synthetic images using data augmentation
            numToGenerate = minSamples - trainCount;
            
            for genIdx = 1:numToGenerate
                % Randomly select an existing image
                randImgIdx = randi(length(existingFiles));
                srcImgPath = fullfile(trainPath, className, existingFiles(randImgIdx).name);
                
                % Load and augment image
                img = imread(srcImgPath);
                
                % Apply random transformations
                img = imrotate(img, randi([-15, 15]));
                img = imresize(img, [224, 224]);
                
                % Random brightness/contrast adjustment
                img = img * (0.8 + 0.4 * rand()) + (0.1 * rand() - 0.05) * 255;
                img = max(0, min(255, img));
                
                % Save synthetic image
                [~, name, ext] = fileparts(existingFiles(randImgIdx).name);
                syntheticName = sprintf('%s_synthetic_%d%s', name, genIdx, ext);
                syntheticPath = fullfile(trainPath, className, syntheticName);
                
                imwrite(uint8(img), syntheticPath);
            end
            
            fprintf('  Generated %d synthetic images\n', numToGenerate);
        end
    end
end

%% 7. Final Summary
fprintf('\n=== Dataset Preparation Complete ===\n');
fprintf('Dataset structure created at: %s\n', dataPath);
fprintf('Ready for training!\n');

end
