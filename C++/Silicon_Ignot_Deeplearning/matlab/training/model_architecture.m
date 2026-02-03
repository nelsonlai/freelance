function net = model_architecture(numClasses)
% MODEL_ARCHITECTURE Creates a ResNet-18 based model for silicon ingot defect classification
% 
% Input:
%   numClasses - Number of defect classes (default: 8)
%
% Output:
%   net - Layer graph for the neural network
%
% Defect Classes:
%   1. Oxygen precipitation / stacking faults
%   2. Dislocations
%   3. Vacancy defects (voids/pits)
%   4. Interstitial defects (dislocation loops)
%   5. Microvoids / COPs
%   6. Slip lines / cracks
%   7. Dopant nonuniformity
%   8. Normal (no defect)

if nargin < 1
    numClasses = 8; % Default number of classes
end

fprintf('Creating ResNet-18 model for %d defect classes...\n', numClasses);

% Load pre-trained ResNet-18 model
net = resnet18('Weights', 'imagenet');

% Convert to layer graph for modification
lgraph = layerGraph(net);

% Define new layers for defect classification
newFCLayer = fullyConnectedLayer(numClasses, ...
    'Name', 'fc_defects', ...
    'WeightLearnRateFactor', 10, ...
    'BiasLearnRateFactor', 10);

newSoftmaxLayer = softmaxLayer('Name', 'softmax');

newClassLayer = classificationLayer('Name', 'classoutput');

% Replace the final classification layers
lgraph = replaceLayer(lgraph, 'fc1000', newFCLayer);
lgraph = replaceLayer(lgraph, 'prob', newSoftmaxLayer);
lgraph = replaceLayer(lgraph, 'ClassificationLayer_predictions', newClassLayer);

% Freeze early layers to prevent overfitting
% Keep only the last few layers trainable
layersToFreeze = {'conv1', 'bn_conv1', 'res2a_branch2a', 'res2a_branch2b', ...
                  'res2b_branch2a', 'res2b_branch2b', 'res3a_branch1', ...
                  'res3a_branch2a', 'res3a_branch2b', 'res3b_branch2a', ...
                  'res3b_branch2b', 'res4a_branch1', 'res4a_branch2a', ...
                  'res4a_branch2b', 'res4b_branch2a', 'res4b_branch2b'};

for i = 1:length(layersToFreeze)
    layerName = layersToFreeze{i};
    if ismember(layerName, {lgraph.Layers.Name})
        layerIdx = find(strcmp({lgraph.Layers.Name}, layerName));
        if ~isempty(layerIdx)
            lgraph.Layers(layerIdx).WeightLearnRateFactor = 0;
            lgraph.Layers(layerIdx).BiasLearnRateFactor = 0;
        end
    end
end

fprintf('Model architecture created successfully.\n');
fprintf('Total layers: %d\n', numel(lgraph.Layers));
fprintf('Trainable layers: %d\n', sum([lgraph.Layers.WeightLearnRateFactor] > 0));

% Display model summary
analyzeNetwork(lgraph);

end
