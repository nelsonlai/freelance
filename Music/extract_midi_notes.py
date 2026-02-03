import pretty_midi
from collections import defaultdict

# Load the MIDI file
midi_data = pretty_midi.PrettyMIDI('./cs3-1pre.mid')

# Dictionary to group notes by MIDI channel
channel_notes = defaultdict(list)

# Iterate through all instruments (each corresponds to a MIDI track/channel)
for instrument in midi_data.instruments:
    channel = instrument.program if not instrument.is_drum else 9  # channel 9 is usually drums
    for note in instrument.notes:
        channel_notes[channel].append({
            'pitch': note.pitch,                 # MIDI note number (e.g., 60 = Middle C)
            'start': note.start,                 # Note-on time in seconds
            'end': note.end,                     # Note-off time in seconds
            'velocity': note.velocity
        })

# Display notes by channel
for channel, notes in channel_notes.items():
    print(f"\nChannel {channel} ({'Drums' if channel == 9 else 'Program ' + str(channel)}):")
    for note in notes:
        print(f"  Pitch: {note['pitch']}, Start: {note['start']:.3f}s, End: {note['end']:.3f}s, Velocity: {note['velocity']}")