import mido
from collections import defaultdict

# Load MIDI file
midi_file = mido.MidiFile('./cs3-1pre.mid')

# Dictionary to store notes by channel
channel_notes = defaultdict(list)

# Track time to keep absolute time
absolute_time = 0

# Parse each message in each track
for i, track in enumerate(midi_file.tracks):
    time = 0
    for msg in track:
        time += msg.time
        if msg.type == 'note_on' and msg.velocity > 0:
            channel_notes[msg.channel].append({
                'note': msg.note,
                'velocity': msg.velocity,
                'time': time,
                'track': i
            })

# Print results
for channel, notes in channel_notes.items():
    print(f"\nChannel {channel}:")
    for note in notes:
        print(f"  Track {note['track']}, Note {note['note']}, Velocity {note['velocity']}, Time {note['time']}")