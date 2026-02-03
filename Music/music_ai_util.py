import os
import subprocess
import urllib.request
from music21 import stream, note
import markovify
import random

# Configuration
SOUNDFONT_URL = "https://ftp.osuosl.org/pub/musescore/soundfont/FluidR3_GM.sf2"
SOUNDFONT_PATH = os.path.expanduser("./FluidR3_GM.sf2")
NUM_VARIATIONS = 3

# Ensure output directories
os.makedirs("output", exist_ok=True)
os.makedirs(os.path.dirname(SOUNDFONT_PATH), exist_ok=True)

# STEP 1: Ensure SoundFont exists
def ensure_soundfont():
    if not os.path.exists(SOUNDFONT_PATH):
        print("🎵 Downloading SoundFont...")
        urllib.request.urlretrieve(SOUNDFONT_URL, SOUNDFONT_PATH)
        print(f"✅ Downloaded: {SOUNDFONT_PATH}")
    else:
        print(f"🎼 Using SoundFont: {SOUNDFONT_PATH}")

# STEP 2: AI model with Markov Chain
def build_markov_model(notes):
    return markovify.Text(' '.join(notes), state_size=8)

def generate_variation(model, length=48):
    result = []
    while len(result) < length:
        sentence = model.make_sentence(tries=100)
        if sentence:
            result += sentence.split()
    return result[:length]

# STEP 3: Create music21 stream
def notes_to_stream(notes):
    s = stream.Stream()
    for pitch in notes:
        n = note.Note(pitch)
        n.quarterLength = 1
        s.append(n)
    return s

# STEP 4: Export to MIDI and convert to WAV using FluidSynth
def export_to_midi_and_wav(m21_stream, midi_path, wav_path):
    m21_stream.write('midi', fp=midi_path)

    cmd = [
        "fluidsynth",
        "-ni", SOUNDFONT_PATH,
        midi_path,
        "-F", wav_path,
        "-r", "44100"
    ]

    result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    if result.returncode != 0:
        print("❌ FluidSynth Error:")
        print(result.stderr.decode())
    else:
        print(f"✅ Exported WAV: {wav_path}")

# Main function
def run_project():
    print("🚀 Starting AI Composition Workflow...")
    ensure_soundfont()

    original_theme = ['C4', 'B3', 'E4', 'D4', 'C4', 'B3', 'E4', 'D4', 'C4', 'B3', 'E4', 'D4', 'C4', 'B3']
    model = build_markov_model(original_theme)


    for i in range(1, NUM_VARIATIONS + 1):
        notes = generate_variation(model)
        random.shuffle(notes)
        print(f"\n🎼 Variation {i}: {notes}")
        s = notes_to_stream(notes)

        midi_file = f"output/variation{i}.mid"
        wav_file = f"output/variation{i}.wav"
        export_to_midi_and_wav(s, midi_file, wav_file)

    print("\n🎉 Done! All AI variations exported to 'output/' folder.")

# Run
if __name__ == "__main__":
    run_project()