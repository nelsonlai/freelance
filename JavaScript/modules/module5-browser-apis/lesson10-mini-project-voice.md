# Lesson 10: Mini Project - Voice Note App

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Build a complete voice note application
- Integrate Speech Recognition API for voice input
- Use Text-to-Speech API for audio playback
- Implement note management and storage
- Handle microphone permissions and errors
- Create a responsive voice interface

## 📚 Project Overview

We'll build a voice note application that includes:
- Speech recognition for voice input
- Text-to-speech for note playback
- Note management (save, load, delete)
- Browser notifications for voice events
- Responsive design for mobile use

## 🏗️ Project Structure

```
voice-note-app/
├── index.html
├── style.css
└── script.js
```

## 📝 HTML Structure

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Voice Note App</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <header>
            <h1>Voice Note App</h1>
            <div class="controls">
                <button id="startBtn" class="btn primary">Start Recording</button>
                <button id="stopBtn" class="btn secondary" disabled>Stop Recording</button>
                <button id="playBtn" class="btn tertiary" disabled>Play Last Note</button>
            </div>
        </header>
        
        <main>
            <div class="status">
                <div id="statusText">Ready to record</div>
                <div id="recordingIndicator" class="recording-indicator hidden"></div>
            </div>
            
            <div class="transcript">
                <h3>Live Transcript</h3>
                <div id="liveTranscript" class="transcript-content"></div>
            </div>
            
            <div class="notes">
                <h3>Voice Notes</h3>
                <div id="notesList" class="notes-list"></div>
            </div>
        </main>
    </div>
    
    <script src="script.js"></script>
</body>
</html>
```

## 💻 JavaScript Implementation

```javascript
class VoiceNoteApp {
    constructor() {
        this.recognition = null;
        this.synthesis = window.speechSynthesis;
        this.isRecording = false;
        this.isPlaying = false;
        this.notes = [];
        this.currentTranscript = '';
        
        this.setupElements();
        this.setupRecognition();
        this.setupEventListeners();
        this.loadNotes();
    }
    
    setupElements() {
        this.startBtn = document.getElementById('startBtn');
        this.stopBtn = document.getElementById('stopBtn');
        this.playBtn = document.getElementById('playBtn');
        this.statusText = document.getElementById('statusText');
        this.recordingIndicator = document.getElementById('recordingIndicator');
        this.liveTranscript = document.getElementById('liveTranscript');
        this.notesList = document.getElementById('notesList');
    }
    
    setupRecognition() {
        if ('webkitSpeechRecognition' in window || 'SpeechRecognition' in window) {
            this.recognition = new webkitSpeechRecognition() || new SpeechRecognition();
            
            this.recognition.continuous = true;
            this.recognition.interimResults = true;
            this.recognition.lang = 'en-US';
            
            this.recognition.onstart = () => {
                this.onRecognitionStart();
            };
            
            this.recognition.onresult = (event) => {
                this.onRecognitionResult(event);
            };
            
            this.recognition.onerror = (event) => {
                this.onRecognitionError(event);
            };
            
            this.recognition.onend = () => {
                this.onRecognitionEnd();
            };
        } else {
            this.showError('Speech recognition not supported in this browser');
        }
    }
    
    setupEventListeners() {
        this.startBtn.addEventListener('click', () => this.startRecording());
        this.stopBtn.addEventListener('click', () => this.stopRecording());
        this.playBtn.addEventListener('click', () => this.playLastNote());
    }
    
    async startRecording() {
        try {
            // Request microphone permission
            await navigator.mediaDevices.getUserMedia({ audio: true });
            
            if (this.recognition) {
                this.recognition.start();
            }
        } catch (error) {
            this.showError('Microphone access denied');
        }
    }
    
    stopRecording() {
        if (this.recognition && this.isRecording) {
            this.recognition.stop();
        }
    }
    
    onRecognitionStart() {
        this.isRecording = true;
        this.startBtn.disabled = true;
        this.stopBtn.disabled = false;
        this.statusText.textContent = 'Recording...';
        this.recordingIndicator.classList.remove('hidden');
        this.currentTranscript = '';
        
        // Show notification
        this.showNotification('Recording started', 'Voice note recording is active');
    }
    
    onRecognitionResult(event) {
        let finalTranscript = '';
        let interimTranscript = '';
        
        for (let i = event.resultIndex; i < event.results.length; i++) {
            const transcript = event.results[i][0].transcript;
            
            if (event.results[i].isFinal) {
                finalTranscript += transcript;
            } else {
                interimTranscript += transcript;
            }
        }
        
        this.currentTranscript = finalTranscript;
        
        // Update live transcript display
        this.liveTranscript.innerHTML = `
            <div class="final">${finalTranscript}</div>
            <div class="interim">${interimTranscript}</div>
        `;
    }
    
    onRecognitionError(event) {
        console.error('Recognition error:', event.error);
        
        let errorMessage = 'Recognition error occurred';
        switch(event.error) {
            case 'no-speech':
                errorMessage = 'No speech detected';
                break;
            case 'audio-capture':
                errorMessage = 'Audio capture failed';
                break;
            case 'not-allowed':
                errorMessage = 'Microphone access denied';
                break;
            case 'network':
                errorMessage = 'Network error';
                break;
        }
        
        this.showError(errorMessage);
        this.stopRecording();
    }
    
    onRecognitionEnd() {
        this.isRecording = false;
        this.startBtn.disabled = false;
        this.stopBtn.disabled = true;
        this.statusText.textContent = 'Ready to record';
        this.recordingIndicator.classList.add('hidden');
        
        // Save the note if there's content
        if (this.currentTranscript.trim()) {
            this.saveNote(this.currentTranscript);
        }
        
        // Show notification
        this.showNotification('Recording stopped', 'Voice note saved');
    }
    
    saveNote(transcript) {
        const note = {
            id: Date.now(),
            text: transcript.trim(),
            timestamp: new Date(),
            duration: 0
        };
        
        this.notes.unshift(note);
        this.saveNotes();
        this.displayNotes();
        this.playBtn.disabled = false;
    }
    
    playLastNote() {
        if (this.notes.length > 0 && !this.isPlaying) {
            const lastNote = this.notes[0];
            this.playText(lastNote.text);
        }
    }
    
    playText(text) {
        if (this.synthesis.speaking) {
            this.synthesis.cancel();
        }
        
        const utterance = new SpeechSynthesisUtterance(text);
        utterance.rate = 0.9;
        utterance.pitch = 1;
        utterance.volume = 1;
        
        utterance.onstart = () => {
            this.isPlaying = true;
            this.playBtn.disabled = true;
            this.statusText.textContent = 'Playing...';
        };
        
        utterance.onend = () => {
            this.isPlaying = false;
            this.playBtn.disabled = false;
            this.statusText.textContent = 'Ready to record';
        };
        
        utterance.onerror = (event) => {
            console.error('Speech synthesis error:', event.error);
            this.isPlaying = false;
            this.playBtn.disabled = false;
            this.statusText.textContent = 'Playback error';
        };
        
        this.synthesis.speak(utterance);
    }
    
    displayNotes() {
        this.notesList.innerHTML = '';
        
        this.notes.forEach(note => {
            const noteElement = document.createElement('div');
            noteElement.className = 'note-item';
            noteElement.innerHTML = `
                <div class="note-content">
                    <p class="note-text">${note.text}</p>
                    <p class="note-time">${note.timestamp.toLocaleString()}</p>
                </div>
                <div class="note-actions">
                    <button class="btn-small" onclick="voiceApp.playText('${note.text.replace(/'/g, "\\'")}')">Play</button>
                    <button class="btn-small delete" onclick="voiceApp.deleteNote(${note.id})">Delete</button>
                </div>
            `;
            this.notesList.appendChild(noteElement);
        });
    }
    
    deleteNote(noteId) {
        if (confirm('Are you sure you want to delete this note?')) {
            this.notes = this.notes.filter(note => note.id !== noteId);
            this.saveNotes();
            this.displayNotes();
            
            if (this.notes.length === 0) {
                this.playBtn.disabled = true;
            }
        }
    }
    
    saveNotes() {
        localStorage.setItem('voiceNotes', JSON.stringify(this.notes));
    }
    
    loadNotes() {
        const saved = localStorage.getItem('voiceNotes');
        if (saved) {
            this.notes = JSON.parse(saved);
            this.displayNotes();
            
            if (this.notes.length > 0) {
                this.playBtn.disabled = false;
            }
        }
    }
    
    async showNotification(title, body) {
        if (Notification.permission === 'granted') {
            new Notification(title, { body });
        } else if (Notification.permission === 'default') {
            const permission = await Notification.requestPermission();
            if (permission === 'granted') {
                new Notification(title, { body });
            }
        }
    }
    
    showError(message) {
        this.statusText.textContent = message;
        this.statusText.className = 'error';
        
        setTimeout(() => {
            this.statusText.textContent = 'Ready to record';
            this.statusText.className = '';
        }, 3000);
    }
}

// Initialize the voice note app
const voiceApp = new VoiceNoteApp();
```

## 🎯 Key Features Implemented

1. **Speech Recognition** - Convert voice to text
2. **Text-to-Speech** - Play notes as audio
3. **Note Management** - Save, load, and delete notes
4. **Live Transcript** - Real-time speech display
5. **Browser Notifications** - Voice event notifications
6. **Responsive Design** - Mobile-friendly interface

## 🎯 Key Takeaways

1. **Speech Recognition API** enables voice input
2. **Text-to-Speech API** provides audio output
3. **Permission handling** for microphone access
4. **Error handling** for speech recognition failures
5. **Local storage** for note persistence
6. **User experience** considerations for voice apps

## 🚀 Next Steps

Congratulations! You've completed Module 5. You now understand:

- Window, Navigator, and History APIs
- Geolocation API for location-based features
- Canvas API for graphics and drawing
- FileReader API for file handling
- Clipboard API for copy/paste functionality
- Speech Recognition API for voice input
- Notifications API for browser notifications
- requestAnimationFrame for smooth animations
- Building complete browser-based applications

**Ready for Module 6: Node.js & Backend Basics!** 🎉

---

**Next Module**: [Module 6: Node.js & Backend Basics](../module6-nodejs/README.md)
