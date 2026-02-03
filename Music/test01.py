import numpy as np
import librosa
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA

# Step 1: Load audio
y, sr = librosa.load('performances/performance1.wav')

# Step 2: Extract MFCCs (Mel Frequency Cepstral Coefficients)
mfccs = librosa.feature.mfcc(y=y, sr=sr, n_mfcc=13)  # shape: (13, time frames)

# Step 3: Transpose to shape (time frames, 13)
mfccs_T = mfccs.T

# Step 4: Apply PCA
pca = PCA(n_components=2)  # reduce to 2D
mfccs_pca = pca.fit_transform(mfccs_T)  # shape: (time frames, 2)

# Step 5: Plot PCA result
plt.figure(figsize=(10, 5))
plt.plot(mfccs_pca[:, 0], label='Principal Component 1')
plt.plot(mfccs_pca[:, 1], label='Principal Component 2')
plt.xlabel('Time Frame')
plt.ylabel('PCA Value')
plt.title('PCA of MFCCs')
plt.legend()
plt.grid(True)
plt.show()