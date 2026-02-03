import librosa
import librosa.display
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
import os

# Config
AUDIO_FOLDER = "performances"
FILE_NAMES = ["performance1.wav"]

def extract_features(audio_path):
    y, sr = librosa.load(audio_path)
    
    # Tempo (beats per minute)
    tempo, beats = librosa.beat.beat_track(y=y, sr=sr)
    
    # Rubato (tempo variation)
    if len(beats) > 1:
        beat_times = librosa.frames_to_time(beats, sr=sr)
        intervals = np.diff(beat_times)
        rubato_std = np.std(intervals)
    else:
        rubato_std = 0.0

    # Dynamics (RMS = root-mean-square energy)
    rms = librosa.feature.rms(y=y)[0]
    dynamics_mean = np.mean(rms)
    dynamics_std = np.std(rms)

    return {
        "tempo": tempo,
        "rubato": rubato_std,
        "dynamics_mean": dynamics_mean,
        "dynamics_std": dynamics_std
    }

# Extract features for all performances
data = []
for file in FILE_NAMES:
    print(f"Processing {file}...")
    path = os.path.join(AUDIO_FOLDER, file)
    features = extract_features(path)
    features['name'] = file
    data.append(features)

df = pd.DataFrame(data)
print("\n=== Extracted Performance Features ===")
print(df)

# Save for report
df.to_csv("performance_features.csv", index=False)

# PCA to find representative performance
X = df[['tempo', 'rubato', 'dynamics_mean', 'dynamics_std']]
print("\n=== PCA Analysis ===")
pca = PCA(n_components=1)
principal_components = pca.fit_transform(X)
df['PCA_score'] = principal_components

# Find the most representative (closest to mean)
representative_index = np.argmin(np.abs(df['PCA_score'] - df['PCA_score'].mean()))
representative_performance = df.iloc[representative_index]['name']

print(f"\n🎹 Representative Performance: {representative_performance}")

# Optional: Visualize
df.plot(kind='bar', x='name', y=['tempo', 'rubato', 'dynamics_mean', 'dynamics_std'], figsize=(10,6))
plt.title("Comparison of Performance Parameters")
plt.ylabel("Value")
plt.tight_layout()
plt.savefig("performance_comparison.png")
plt.show()