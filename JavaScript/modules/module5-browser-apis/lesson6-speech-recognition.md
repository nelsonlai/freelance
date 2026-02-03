# Lesson 6: Speech Recognition API

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Implement speech recognition in web applications
- Handle speech recognition events and results
- Configure recognition options and languages
- Process continuous speech input
- Handle recognition errors and timeouts
- Create voice-controlled applications

## 📚 Speech Recognition Basics

### Basic Speech Recognition
```javascript
const recognition = new webkitSpeechRecognition() || new SpeechRecognition();

recognition.continuous = false;
recognition.interimResults = false;
recognition.lang = 'en-US';

recognition.onresult = (event) => {
    const transcript = event.results[0][0].transcript;
    console.log('Recognized:', transcript);
};

recognition.onerror = (event) => {
    console.error('Recognition error:', event.error);
};

recognition.start();
```

## 🎯 Practice Exercises

### Exercise 1: Voice Note App
Create a voice note application:

**Solution:**
```javascript
class VoiceNoteApp {
    constructor() {
        this.recognition = null;
        this.isListening = false;
        this.notes = [];
        this.setupRecognition();
    }
    
    setupRecognition() {
        if ('webkitSpeechRecognition' in window || 'SpeechRecognition' in window) {
            this.recognition = new webkitSpeechRecognition() || new SpeechRecognition();
            
            this.recognition.continuous = true;
            this.recognition.interimResults = true;
            this.recognition.lang = 'en-US';
            
            this.recognition.onresult = (event) => {
                this.handleResult(event);
            };
            
            this.recognition.onerror = (event) => {
                this.handleError(event);
            };
            
            this.recognition.onend = () => {
                this.isListening = false;
            };
        } else {
            console.error('Speech recognition not supported');
        }
    }
    
    startListening() {
        if (this.recognition && !this.isListening) {
            this.recognition.start();
            this.isListening = true;
        }
    }
    
    stopListening() {
        if (this.recognition && this.isListening) {
            this.recognition.stop();
            this.isListening = false;
        }
    }
    
    handleResult(event) {
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
        
        if (finalTranscript) {
            this.addNote(finalTranscript);
        }
        
        this.updateDisplay(finalTranscript, interimTranscript);
    }
    
    handleError(event) {
        console.error('Speech recognition error:', event.error);
        this.isListening = false;
    }
    
    addNote(text) {
        const note = {
            id: Date.now(),
            text: text,
            timestamp: new Date(),
            duration: 0
        };
        
        this.notes.push(note);
        this.saveNotes();
    }
    
    updateDisplay(final, interim) {
        // Update UI with recognition results
        const display = document.getElementById('speechDisplay');
        display.innerHTML = `
            <div class="final">${final}</div>
            <div class="interim">${interim}</div>
        `;
    }
    
    saveNotes() {
        localStorage.setItem('voiceNotes', JSON.stringify(this.notes));
    }
    
    loadNotes() {
        const saved = localStorage.getItem('voiceNotes');
        if (saved) {
            this.notes = JSON.parse(saved);
        }
    }
}

// Usage
const voiceApp = new VoiceNoteApp();
```

## 🎯 Key Takeaways

1. **Speech Recognition API** enables voice input
2. **Browser support** varies for speech recognition
3. **Continuous recognition** for ongoing input
4. **Error handling** for recognition failures
5. **User experience** considerations for voice apps

---

**Next Lesson**: [Lesson 7: Notifications API](./lesson7-notifications.md)
