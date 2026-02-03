# Lesson 9: Mini Project - Movie Search App

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Build a complete React movie search application
- Integrate with external APIs (OMDb API)
- Implement search functionality and filtering
- Use React Hooks for state management
- Create responsive components
- Handle loading states and errors

## 📚 Project Overview

We'll build a movie search application that includes:
- Movie search functionality
- Movie details display
- Favorites management
- Responsive design
- API integration with OMDb

## 🏗️ Project Structure

```
movie-search-app/
├── package.json
├── public/
│   └── index.html
├── src/
│   ├── App.js
│   ├── index.js
│   ├── components/
│   │   ├── MovieCard.js
│   │   ├── MovieDetails.js
│   │   ├── SearchBar.js
│   │   └── FavoritesList.js
│   └── hooks/
│       └── useMovies.js
└── styles/
    └── App.css
```

## 📝 Package.json

```json
{
  "name": "movie-search-app",
  "version": "1.0.0",
  "dependencies": {
    "react": "^18.0.0",
    "react-dom": "^18.0.0",
    "react-scripts": "5.0.0"
  },
  "scripts": {
    "start": "react-scripts start",
    "build": "react-scripts build",
    "test": "react-scripts test",
    "eject": "react-scripts eject"
  }
}
```

## 💻 Complete Implementation

### App.js
```javascript
import React, { useState, useEffect } from 'react';
import './styles/App.css';
import SearchBar from './components/SearchBar';
import MovieCard from './components/MovieCard';
import MovieDetails from './components/MovieDetails';
import FavoritesList from './components/FavoritesList';
import { useMovies } from './hooks/useMovies';

function App() {
    const [searchTerm, setSearchTerm] = useState('');
    const [selectedMovie, setSelectedMovie] = useState(null);
    const [favorites, setFavorites] = useState([]);
    const [showFavorites, setShowFavorites] = useState(false);
    
    const { movies, loading, error, searchMovies } = useMovies();
    
    useEffect(() => {
        const savedFavorites = localStorage.getItem('movieFavorites');
        if (savedFavorites) {
            setFavorites(JSON.parse(savedFavorites));
        }
    }, []);
    
    useEffect(() => {
        localStorage.setItem('movieFavorites', JSON.stringify(favorites));
    }, [favorites]);
    
    const handleSearch = (term) => {
        setSearchTerm(term);
        if (term.trim()) {
            searchMovies(term);
        }
    };
    
    const handleMovieSelect = (movie) => {
        setSelectedMovie(movie);
    };
    
    const handleAddToFavorites = (movie) => {
        if (!favorites.find(fav => fav.imdbID === movie.imdbID)) {
            setFavorites(prev => [...prev, movie]);
        }
    };
    
    const handleRemoveFromFavorites = (movieId) => {
        setFavorites(prev => prev.filter(fav => fav.imdbID !== movieId));
    };
    
    const isFavorite = (movieId) => {
        return favorites.some(fav => fav.imdbID === movieId);
    };
    
    return (
        <div className="app">
            <header className="app-header">
                <h1>Movie Search App</h1>
                <button 
                    className="favorites-toggle"
                    onClick={() => setShowFavorites(!showFavorites)}
                >
                    {showFavorites ? 'Hide' : 'Show'} Favorites ({favorites.length})
                </button>
            </header>
            
            <main className="app-main">
                <SearchBar onSearch={handleSearch} />
                
                {showFavorites ? (
                    <FavoritesList 
                        favorites={favorites}
                        onRemove={handleRemoveFromFavorites}
                        onSelect={handleMovieSelect}
                    />
                ) : (
                    <div className="movies-container">
                        {loading && <div className="loading">Searching movies...</div>}
                        {error && <div className="error">Error: {error}</div>}
                        
                        {movies.length > 0 && (
                            <div className="movies-grid">
                                {movies.map(movie => (
                                    <MovieCard
                                        key={movie.imdbID}
                                        movie={movie}
                                        onSelect={handleMovieSelect}
                                        onAddToFavorites={handleAddToFavorites}
                                        isFavorite={isFavorite(movie.imdbID)}
                                    />
                                ))}
                            </div>
                        )}
                        
                        {searchTerm && movies.length === 0 && !loading && (
                            <div className="no-results">
                                No movies found for "{searchTerm}"
                            </div>
                        )}
                    </div>
                )}
                
                {selectedMovie && (
                    <MovieDetails 
                        movie={selectedMovie}
                        onClose={() => setSelectedMovie(null)}
                        onAddToFavorites={handleAddToFavorites}
                        isFavorite={isFavorite(selectedMovie.imdbID)}
                    />
                )}
            </main>
        </div>
    );
}

export default App;
```

### hooks/useMovies.js
```javascript
import { useState, useCallback } from 'react';

export function useMovies() {
    const [movies, setMovies] = useState([]);
    const [loading, setLoading] = useState(false);
    const [error, setError] = useState(null);
    
    const searchMovies = useCallback(async (searchTerm) => {
        if (!searchTerm.trim()) return;
        
        setLoading(true);
        setError(null);
        
        try {
            const response = await fetch(
                `https://www.omdbapi.com/?s=${encodeURIComponent(searchTerm)}&apikey=YOUR_API_KEY`
            );
            
            if (!response.ok) {
                throw new Error('Failed to fetch movies');
            }
            
            const data = await response.json();
            
            if (data.Response === 'True') {
                setMovies(data.Search || []);
            } else {
                setMovies([]);
                setError(data.Error || 'No movies found');
            }
        } catch (err) {
            setError(err.message);
            setMovies([]);
        } finally {
            setLoading(false);
        }
    }, []);
    
    return { movies, loading, error, searchMovies };
}
```

### components/MovieCard.js
```javascript
import React from 'react';

function MovieCard({ movie, onSelect, onAddToFavorites, isFavorite }) {
    const handleClick = () => {
        onSelect(movie);
    };
    
    const handleAddToFavorites = (e) => {
        e.stopPropagation();
        onAddToFavorites(movie);
    };
    
    return (
        <div className="movie-card" onClick={handleClick}>
            <div className="movie-poster">
                {movie.Poster !== 'N/A' ? (
                    <img src={movie.Poster} alt={movie.Title} />
                ) : (
                    <div className="no-poster">No Image</div>
                )}
            </div>
            
            <div className="movie-info">
                <h3 className="movie-title">{movie.Title}</h3>
                <p className="movie-year">{movie.Year}</p>
                <p className="movie-type">{movie.Type}</p>
            </div>
            
            <button 
                className={`favorite-btn ${isFavorite ? 'active' : ''}`}
                onClick={handleAddToFavorites}
            >
                {isFavorite ? '♥' : '♡'}
            </button>
        </div>
    );
}

export default MovieCard;
```

### components/MovieDetails.js
```javascript
import React, { useState, useEffect } from 'react';

function MovieDetails({ movie, onClose, onAddToFavorites, isFavorite }) {
    const [details, setDetails] = useState(null);
    const [loading, setLoading] = useState(true);
    
    useEffect(() => {
        const fetchDetails = async () => {
            try {
                const response = await fetch(
                    `https://www.omdbapi.com/?i=${movie.imdbID}&apikey=YOUR_API_KEY`
                );
                const data = await response.json();
                setDetails(data);
            } catch (error) {
                console.error('Error fetching movie details:', error);
            } finally {
                setLoading(false);
            }
        };
        
        fetchDetails();
    }, [movie.imdbID]);
    
    const handleAddToFavorites = () => {
        onAddToFavorites(movie);
    };
    
    if (loading) {
        return (
            <div className="movie-details-overlay">
                <div className="movie-details">
                    <div className="loading">Loading details...</div>
                </div>
            </div>
        );
    }
    
    return (
        <div className="movie-details-overlay" onClick={onClose}>
            <div className="movie-details" onClick={(e) => e.stopPropagation()}>
                <button className="close-btn" onClick={onClose}>×</button>
                
                <div className="details-content">
                    <div className="details-poster">
                        {details.Poster !== 'N/A' ? (
                            <img src={details.Poster} alt={details.Title} />
                        ) : (
                            <div className="no-poster">No Image</div>
                        )}
                    </div>
                    
                    <div className="details-info">
                        <h2>{details.Title}</h2>
                        <p><strong>Year:</strong> {details.Year}</p>
                        <p><strong>Rated:</strong> {details.Rated}</p>
                        <p><strong>Runtime:</strong> {details.Runtime}</p>
                        <p><strong>Genre:</strong> {details.Genre}</p>
                        <p><strong>Director:</strong> {details.Director}</p>
                        <p><strong>Actors:</strong> {details.Actors}</p>
                        <p><strong>Plot:</strong> {details.Plot}</p>
                        <p><strong>IMDb Rating:</strong> {details.imdbRating}</p>
                        
                        <button 
                            className={`favorite-btn ${isFavorite ? 'active' : ''}`}
                            onClick={handleAddToFavorites}
                        >
                            {isFavorite ? 'Remove from Favorites' : 'Add to Favorites'}
                        </button>
                    </div>
                </div>
            </div>
        </div>
    );
}

export default MovieDetails;
```

## 🎯 Key Features Implemented

1. **Movie Search** - Search movies by title
2. **Movie Details** - View detailed information
3. **Favorites Management** - Save and remove favorites
4. **Responsive Design** - Works on all devices
5. **Loading States** - Visual feedback during API calls
6. **Error Handling** - Graceful error management
7. **Local Storage** - Persist favorites between sessions

## 🎯 Key Takeaways

1. **React Hooks** manage component state and side effects
2. **API integration** connects to external data sources
3. **Component composition** builds complex UIs from simple parts
4. **State management** handles application data
5. **User experience** considerations for loading and errors

## 🚀 Next Steps

Congratulations! You've built a complete movie search application. In the next lesson, we'll create:

- **Notes App** - React Hooks for state management
- **Local storage integration** - Persist data between sessions
- **CRUD operations** - Create, read, update, delete notes
- **Component reusability** - Build modular components

---

**Next Lesson**: [Lesson 10: Mini Project - Notes App](./lesson10-mini-project-notes.md)
