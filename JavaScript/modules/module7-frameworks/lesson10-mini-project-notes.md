# Lesson 10: Mini Project - Notes App

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Build a complete React notes application
- Use React Hooks for state management
- Implement CRUD operations for notes
- Integrate with local storage
- Create reusable components
- Build a responsive user interface

## 📚 Project Overview

We'll build a notes application that includes:
- Create, read, update, delete notes
- Local storage persistence
- Search and filter functionality
- Responsive design
- Component reusability

## 🏗️ Project Structure

```
notes-app/
├── package.json
├── public/
│   └── index.html
├── src/
│   ├── App.js
│   ├── index.js
│   ├── components/
│   │   ├── NoteCard.js
│   │   ├── NoteEditor.js
│   │   ├── SearchBar.js
│   │   └── NoteList.js
│   └── hooks/
│       └── useNotes.js
└── styles/
    └── App.css
```

## 💻 Complete Implementation

### App.js
```javascript
import React, { useState, useEffect } from 'react';
import './styles/App.css';
import NoteEditor from './components/NoteEditor';
import NoteList from './components/NoteList';
import SearchBar from './components/SearchBar';
import { useNotes } from './hooks/useNotes';

function App() {
    const [searchTerm, setSearchTerm] = useState('');
    const [selectedNote, setSelectedNote] = useState(null);
    const [isEditing, setIsEditing] = useState(false);
    
    const { 
        notes, 
        loading, 
        addNote, 
        updateNote, 
        deleteNote, 
        searchNotes 
    } = useNotes();
    
    const filteredNotes = searchTerm 
        ? searchNotes(searchTerm)
        : notes;
    
    const handleNoteSelect = (note) => {
        setSelectedNote(note);
        setIsEditing(false);
    };
    
    const handleEditNote = (note) => {
        setSelectedNote(note);
        setIsEditing(true);
    };
    
    const handleSaveNote = (noteData) => {
        if (isEditing && selectedNote) {
            updateNote(selectedNote.id, noteData);
        } else {
            addNote(noteData);
        }
        setSelectedNote(null);
        setIsEditing(false);
    };
    
    const handleDeleteNote = (noteId) => {
        if (window.confirm('Are you sure you want to delete this note?')) {
            deleteNote(noteId);
            if (selectedNote && selectedNote.id === noteId) {
                setSelectedNote(null);
                setIsEditing(false);
            }
        }
    };
    
    const handleNewNote = () => {
        setSelectedNote(null);
        setIsEditing(true);
    };
    
    return (
        <div className="app">
            <header className="app-header">
                <h1>Notes App</h1>
                <button className="new-note-btn" onClick={handleNewNote}>
                    New Note
                </button>
            </header>
            
            <main className="app-main">
                <div className="sidebar">
                    <SearchBar 
                        value={searchTerm}
                        onChange={setSearchTerm}
                        placeholder="Search notes..."
                    />
                    
                    <NoteList
                        notes={filteredNotes}
                        selectedNote={selectedNote}
                        onNoteSelect={handleNoteSelect}
                        onEditNote={handleEditNote}
                        onDeleteNote={handleDeleteNote}
                    />
                </div>
                
                <div className="main-content">
                    {selectedNote || isEditing ? (
                        <NoteEditor
                            note={selectedNote}
                            isEditing={isEditing}
                            onSave={handleSaveNote}
                            onCancel={() => {
                                setSelectedNote(null);
                                setIsEditing(false);
                            }}
                        />
                    ) : (
                        <div className="welcome">
                            <h2>Welcome to Notes App</h2>
                            <p>Select a note from the sidebar or create a new one.</p>
                        </div>
                    )}
                </div>
            </main>
        </div>
    );
}

export default App;
```

### hooks/useNotes.js
```javascript
import { useState, useEffect, useCallback } from 'react';

export function useNotes() {
    const [notes, setNotes] = useState([]);
    const [loading, setLoading] = useState(true);
    
    // Load notes from localStorage on mount
    useEffect(() => {
        const savedNotes = localStorage.getItem('notes');
        if (savedNotes) {
            try {
                setNotes(JSON.parse(savedNotes));
            } catch (error) {
                console.error('Error loading notes:', error);
            }
        }
        setLoading(false);
    }, []);
    
    // Save notes to localStorage whenever notes change
    useEffect(() => {
        if (!loading) {
            localStorage.setItem('notes', JSON.stringify(notes));
        }
    }, [notes, loading]);
    
    const addNote = useCallback((noteData) => {
        const newNote = {
            id: Date.now(),
            title: noteData.title || 'Untitled',
            content: noteData.content || '',
            createdAt: new Date().toISOString(),
            updatedAt: new Date().toISOString(),
            tags: noteData.tags || []
        };
        
        setNotes(prev => [newNote, ...prev]);
        return newNote;
    }, []);
    
    const updateNote = useCallback((id, noteData) => {
        setNotes(prev => prev.map(note => 
            note.id === id 
                ? { 
                    ...note, 
                    ...noteData, 
                    updatedAt: new Date().toISOString() 
                }
                : note
        ));
    }, []);
    
    const deleteNote = useCallback((id) => {
        setNotes(prev => prev.filter(note => note.id !== id));
    }, []);
    
    const searchNotes = useCallback((searchTerm) => {
        if (!searchTerm.trim()) return notes;
        
        const term = searchTerm.toLowerCase();
        return notes.filter(note => 
            note.title.toLowerCase().includes(term) ||
            note.content.toLowerCase().includes(term) ||
            note.tags.some(tag => tag.toLowerCase().includes(term))
        );
    }, [notes]);
    
    const getNoteById = useCallback((id) => {
        return notes.find(note => note.id === id);
    }, [notes]);
    
    return {
        notes,
        loading,
        addNote,
        updateNote,
        deleteNote,
        searchNotes,
        getNoteById
    };
}
```

### components/NoteEditor.js
```javascript
import React, { useState, useEffect } from 'react';

function NoteEditor({ note, isEditing, onSave, onCancel }) {
    const [formData, setFormData] = useState({
        title: '',
        content: '',
        tags: []
    });
    
    const [tagInput, setTagInput] = useState('');
    
    useEffect(() => {
        if (note) {
            setFormData({
                title: note.title || '',
                content: note.content || '',
                tags: note.tags || []
            });
        } else {
            setFormData({
                title: '',
                content: '',
                tags: []
            });
        }
    }, [note]);
    
    const handleChange = (e) => {
        const { name, value } = e.target;
        setFormData(prev => ({
            ...prev,
            [name]: value
        }));
    };
    
    const handleAddTag = (e) => {
        if (e.key === 'Enter' && tagInput.trim()) {
            e.preventDefault();
            const newTag = tagInput.trim();
            if (!formData.tags.includes(newTag)) {
                setFormData(prev => ({
                    ...prev,
                    tags: [...prev.tags, newTag]
                }));
            }
            setTagInput('');
        }
    };
    
    const handleRemoveTag = (tagToRemove) => {
        setFormData(prev => ({
            ...prev,
            tags: prev.tags.filter(tag => tag !== tagToRemove)
        }));
    };
    
    const handleSave = (e) => {
        e.preventDefault();
        onSave(formData);
    };
    
    const handleCancel = () => {
        onCancel();
    };
    
    return (
        <div className="note-editor">
            <form onSubmit={handleSave}>
                <div className="editor-header">
                    <input
                        type="text"
                        name="title"
                        value={formData.title}
                        onChange={handleChange}
                        placeholder="Note title..."
                        className="title-input"
                    />
                    
                    <div className="editor-actions">
                        <button type="button" onClick={handleCancel}>
                            Cancel
                        </button>
                        <button type="submit">
                            {isEditing ? 'Update' : 'Save'}
                        </button>
                    </div>
                </div>
                
                <div className="tags-section">
                    <div className="tags-input">
                        <input
                            type="text"
                            value={tagInput}
                            onChange={(e) => setTagInput(e.target.value)}
                            onKeyPress={handleAddTag}
                            placeholder="Add tags..."
                        />
                    </div>
                    
                    <div className="tags-list">
                        {formData.tags.map(tag => (
                            <span key={tag} className="tag">
                                {tag}
                                <button 
                                    type="button"
                                    onClick={() => handleRemoveTag(tag)}
                                    className="tag-remove"
                                >
                                    ×
                                </button>
                            </span>
                        ))}
                    </div>
                </div>
                
                <textarea
                    name="content"
                    value={formData.content}
                    onChange={handleChange}
                    placeholder="Write your note here..."
                    className="content-textarea"
                />
            </form>
        </div>
    );
}

export default NoteEditor;
```

### components/NoteList.js
```javascript
import React from 'react';
import NoteCard from './NoteCard';

function NoteList({ notes, selectedNote, onNoteSelect, onEditNote, onDeleteNote }) {
    if (notes.length === 0) {
        return (
            <div className="note-list">
                <div className="empty-state">
                    <p>No notes found</p>
                    <p>Create your first note!</p>
                </div>
            </div>
        );
    }
    
    return (
        <div className="note-list">
            {notes.map(note => (
                <NoteCard
                    key={note.id}
                    note={note}
                    isSelected={selectedNote && selectedNote.id === note.id}
                    onSelect={onNoteSelect}
                    onEdit={onEditNote}
                    onDelete={onDeleteNote}
                />
            ))}
        </div>
    );
}

export default NoteList;
```

### components/NoteCard.js
```javascript
import React from 'react';

function NoteCard({ note, isSelected, onSelect, onEdit, onDelete }) {
    const handleClick = () => {
        onSelect(note);
    };
    
    const handleEdit = (e) => {
        e.stopPropagation();
        onEdit(note);
    };
    
    const handleDelete = (e) => {
        e.stopPropagation();
        onDelete(note.id);
    };
    
    const formatDate = (dateString) => {
        return new Date(dateString).toLocaleDateString();
    };
    
    const truncateContent = (content, maxLength = 100) => {
        if (content.length <= maxLength) return content;
        return content.substring(0, maxLength) + '...';
    };
    
    return (
        <div 
            className={`note-card ${isSelected ? 'selected' : ''}`}
            onClick={handleClick}
        >
            <div className="note-header">
                <h3 className="note-title">{note.title}</h3>
                <div className="note-actions">
                    <button 
                        className="edit-btn"
                        onClick={handleEdit}
                        title="Edit note"
                    >
                        ✏️
                    </button>
                    <button 
                        className="delete-btn"
                        onClick={handleDelete}
                        title="Delete note"
                    >
                        🗑️
                    </button>
                </div>
            </div>
            
            <div className="note-content">
                <p>{truncateContent(note.content)}</p>
            </div>
            
            <div className="note-footer">
                <div className="note-tags">
                    {note.tags.map(tag => (
                        <span key={tag} className="tag">{tag}</span>
                    ))}
                </div>
                <div className="note-date">
                    {formatDate(note.updatedAt)}
                </div>
            </div>
        </div>
    );
}

export default NoteCard;
```

## 🎯 Key Features Implemented

1. **CRUD Operations** - Create, read, update, delete notes
2. **Local Storage** - Persist notes between sessions
3. **Search Functionality** - Find notes by title, content, or tags
4. **Tag System** - Organize notes with tags
5. **Responsive Design** - Works on all devices
6. **Component Reusability** - Modular component structure
7. **State Management** - React Hooks for state

## 🎯 Key Takeaways

1. **React Hooks** manage component state and side effects
2. **Local storage** persists data between sessions
3. **Component composition** builds complex UIs from simple parts
4. **CRUD operations** handle data manipulation
5. **Search functionality** improves user experience

## 🚀 Next Steps

Congratulations! You've completed Module 7. You now understand:

- Frontend frameworks and their purposes
- React.js fundamentals and setup
- JSX syntax and component creation
- Props and state management
- Event handling in React
- Conditional rendering and lists
- React Hooks for state management
- Routing and navigation
- Building complete React applications

**Ready for Module 8: Capstone Projects & Final Topics!** 🎉

---

**Next Module**: [Module 8: Capstone Projects & Final Topics](../module8-capstone/README.md)
