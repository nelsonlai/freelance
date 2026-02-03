import essentia
from essentia.standard import (
    MonoLoader, FrameGenerator,
    Windowing, Spectrum, MFCC,
    ZeroCrossingRate, SpectralCentroidTime,
    Danceability  # needs essentia ≥2.x
)
import numpy as np

# 1. Load audio (mono, 44.1 kHz)
loader = MonoLoader(filename='performances/performance1.wav', sampleRate=44100)
audio = loader()

# 2. Set up frame processing
frameSize = 1024
hopSize = 512
w = Windowing(type='hann')
spectrum = Spectrum()
mfcc_algo = MFCC()
zcr_algo = ZeroCrossingRate()
centroid_algo = SpectralCentroidTime()
dance_algo = Danceability()  # from Essentia standard algorithms

# Prepare containers
mfccs, zcrs, centroids = [], [], []

# 3. Iterate through frames and extract features
for frame in FrameGenerator(audio, frameSize=frameSize, hopSize=hopSize, startFromZero=True):
    win = w(frame)
    spec = spectrum(win)
    bands, coeffs = mfcc_algo(spec)
    mfccs.append(coeffs)
    zcrs.append(zcr_algo(frame))
    centroids.append(centroid_algo(spec))

# 4. Extract global danceability over the whole track
dance_params = dance_algo(audio)
# dance_algo returns a dict: {danceability, bpm, bpm_confidence}
danceability = dance_params['danceability']
bpm = dance_params.get('bpm', None)

# Convert lists to NumPy arrays
mfccs = np.array(mfccs)          # shape: (#frames, 13)
zcrs = np.array(zcrs)
centroids = np.array(centroids)

# 5. Summarize features
print("MFCCs mean per coefficient:", mfccs.mean(axis=0))
print("ZCR mean:", zcrs.mean())
print("Spectral centroid mean:", centroids.mean())
print(f"Danceability: {danceability:.3f}, BPM: {bpm:.1f}")