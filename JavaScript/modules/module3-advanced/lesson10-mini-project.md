# Lesson 10: Mini Project - Weather App

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Build a complete weather application
- Integrate with a real API (OpenWeather)
- Handle API responses and errors
- Create a responsive user interface
- Implement search functionality
- Apply all concepts from Module 3

## 📚 Project Overview

We'll build a weather application that:
- Fetches current weather data from OpenWeather API
- Displays temperature, humidity, and weather conditions
- Shows a 5-day forecast
- Handles errors gracefully
- Provides a clean, responsive interface

## 🏗️ Project Structure

```
weather-app/
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
    <title>Weather App</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <header>
            <h1>Weather App</h1>
            <div class="search-container">
                <input type="text" id="cityInput" placeholder="Enter city name...">
                <button id="searchBtn">Search</button>
            </div>
        </header>
        
        <main>
            <div id="loading" class="loading hidden">
                <div class="spinner"></div>
                <p>Loading weather data...</p>
            </div>
            
            <div id="error" class="error hidden">
                <p>Error loading weather data. Please try again.</p>
            </div>
            
            <div id="currentWeather" class="weather-card hidden">
                <h2 id="cityName"></h2>
                <div class="current-info">
                    <div class="temperature">
                        <span id="temp"></span>
                        <span class="unit">°C</span>
                    </div>
                    <div class="weather-details">
                        <p id="description"></p>
                        <p>Humidity: <span id="humidity"></span>%</p>
                        <p>Wind: <span id="wind"></span> m/s</p>
                    </div>
                </div>
            </div>
            
            <div id="forecast" class="forecast hidden">
                <h3>5-Day Forecast</h3>
                <div id="forecastList" class="forecast-list"></div>
            </div>
        </main>
    </div>
    
    <script src="script.js"></script>
</body>
</html>
```

## 🎨 CSS Styling

```css
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    background: linear-gradient(135deg, #74b9ff 0%, #0984e3 100%);
    min-height: 100vh;
    padding: 20px;
}

.container {
    max-width: 800px;
    margin: 0 auto;
}

header {
    text-align: center;
    margin-bottom: 30px;
}

h1 {
    color: white;
    font-size: 2.5rem;
    margin-bottom: 20px;
    text-shadow: 2px 2px 4px rgba(0,0,0,0.3);
}

.search-container {
    display: flex;
    gap: 10px;
    justify-content: center;
    max-width: 400px;
    margin: 0 auto;
}

#cityInput {
    flex: 1;
    padding: 12px;
    border: none;
    border-radius: 25px;
    font-size: 16px;
    outline: none;
    box-shadow: 0 2px 10px rgba(0,0,0,0.1);
}

#searchBtn {
    padding: 12px 24px;
    background-color: #00b894;
    color: white;
    border: none;
    border-radius: 25px;
    cursor: pointer;
    font-size: 16px;
    font-weight: bold;
    transition: background-color 0.3s;
}

#searchBtn:hover {
    background-color: #00a085;
}

.weather-card {
    background: white;
    border-radius: 15px;
    padding: 30px;
    box-shadow: 0 10px 30px rgba(0,0,0,0.2);
    margin-bottom: 20px;
}

.current-info {
    display: flex;
    justify-content: space-between;
    align-items: center;
    flex-wrap: wrap;
    gap: 20px;
}

.temperature {
    font-size: 4rem;
    font-weight: bold;
    color: #2d3436;
}

.unit {
    font-size: 2rem;
    color: #636e72;
}

.weather-details p {
    margin: 10px 0;
    color: #636e72;
    font-size: 1.1rem;
}

.forecast {
    background: white;
    border-radius: 15px;
    padding: 30px;
    box-shadow: 0 10px 30px rgba(0,0,0,0.2);
}

.forecast h3 {
    margin-bottom: 20px;
    color: #2d3436;
    text-align: center;
}

.forecast-list {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(150px, 1fr));
    gap: 15px;
}

.forecast-item {
    text-align: center;
    padding: 15px;
    background: #f8f9fa;
    border-radius: 10px;
    border: 1px solid #e9ecef;
}

.forecast-item h4 {
    color: #2d3436;
    margin-bottom: 10px;
}

.forecast-temp {
    font-size: 1.2rem;
    font-weight: bold;
    color: #0984e3;
}

.loading {
    text-align: center;
    color: white;
    font-size: 1.2rem;
}

.spinner {
    width: 40px;
    height: 40px;
    border: 4px solid rgba(255,255,255,0.3);
    border-top: 4px solid white;
    border-radius: 50%;
    animation: spin 1s linear infinite;
    margin: 0 auto 20px;
}

@keyframes spin {
    0% { transform: rotate(0deg); }
    100% { transform: rotate(360deg); }
}

.error {
    background: #e74c3c;
    color: white;
    padding: 20px;
    border-radius: 10px;
    text-align: center;
    font-size: 1.1rem;
}

.hidden {
    display: none;
}

@media (max-width: 600px) {
    .current-info {
        flex-direction: column;
        text-align: center;
    }
    
    .temperature {
        font-size: 3rem;
    }
    
    .forecast-list {
        grid-template-columns: repeat(auto-fit, minmax(120px, 1fr));
    }
}
```

## 💻 JavaScript Functionality

```javascript
class WeatherApp {
    constructor() {
        this.apiKey = 'YOUR_API_KEY'; // Replace with your OpenWeather API key
        this.baseUrl = 'https://api.openweathermap.org/data/2.5';
        
        this.cityInput = document.getElementById('cityInput');
        this.searchBtn = document.getElementById('searchBtn');
        this.loading = document.getElementById('loading');
        this.error = document.getElementById('error');
        this.currentWeather = document.getElementById('currentWeather');
        this.forecast = document.getElementById('forecast');
        
        this.init();
    }
    
    init() {
        this.searchBtn.addEventListener('click', () => this.searchWeather());
        this.cityInput.addEventListener('keypress', (e) => {
            if (e.key === 'Enter') {
                this.searchWeather();
            }
        });
        
        // Load default city on startup
        this.searchWeather('London');
    }
    
    async searchWeather(city = null) {
        const cityName = city || this.cityInput.value.trim();
        
        if (!cityName) {
            this.showError('Please enter a city name');
            return;
        }
        
        this.showLoading();
        
        try {
            const [currentData, forecastData] = await Promise.all([
                this.fetchCurrentWeather(cityName),
                this.fetchForecast(cityName)
            ]);
            
            this.displayCurrentWeather(currentData);
            this.displayForecast(forecastData);
            this.hideLoading();
            
        } catch (error) {
            console.error('Weather fetch error:', error);
            this.showError('Failed to fetch weather data. Please check the city name.');
            this.hideLoading();
        }
    }
    
    async fetchCurrentWeather(city) {
        const url = `${this.baseUrl}/weather?q=${city}&appid=${this.apiKey}&units=metric`;
        const response = await fetch(url);
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        return await response.json();
    }
    
    async fetchForecast(city) {
        const url = `${this.baseUrl}/forecast?q=${city}&appid=${this.apiKey}&units=metric`;
        const response = await fetch(url);
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        return await response.json();
    }
    
    displayCurrentWeather(data) {
        document.getElementById('cityName').textContent = `${data.name}, ${data.sys.country}`;
        document.getElementById('temp').textContent = Math.round(data.main.temp);
        document.getElementById('description').textContent = data.weather[0].description;
        document.getElementById('humidity').textContent = data.main.humidity;
        document.getElementById('wind').textContent = data.wind.speed;
        
        this.currentWeather.classList.remove('hidden');
    }
    
    displayForecast(data) {
        const forecastList = document.getElementById('forecastList');
        forecastList.innerHTML = '';
        
        // Get daily forecasts (every 8th item for 5-day forecast)
        const dailyForecasts = data.list.filter((item, index) => index % 8 === 0).slice(0, 5);
        
        dailyForecasts.forEach(forecast => {
            const forecastItem = document.createElement('div');
            forecastItem.className = 'forecast-item';
            
            const date = new Date(forecast.dt * 1000);
            const dayName = date.toLocaleDateString('en-US', { weekday: 'short' });
            
            forecastItem.innerHTML = `
                <h4>${dayName}</h4>
                <p>${forecast.weather[0].description}</p>
                <div class="forecast-temp">
                    ${Math.round(forecast.main.temp)}°C
                </div>
            `;
            
            forecastList.appendChild(forecastItem);
        });
        
        this.forecast.classList.remove('hidden');
    }
    
    showLoading() {
        this.hideAll();
        this.loading.classList.remove('hidden');
    }
    
    hideLoading() {
        this.loading.classList.add('hidden');
    }
    
    showError(message) {
        this.hideAll();
        this.error.querySelector('p').textContent = message;
        this.error.classList.remove('hidden');
    }
    
    hideAll() {
        this.loading.classList.add('hidden');
        this.error.classList.add('hidden');
        this.currentWeather.classList.add('hidden');
        this.forecast.classList.add('hidden');
    }
}

// Initialize the app
const weatherApp = new WeatherApp();
```

## 🎯 Key Features Implemented

1. **API Integration** - Fetches real weather data
2. **Error Handling** - Graceful error management
3. **Responsive Design** - Works on all devices
4. **Search Functionality** - City search with Enter key support
5. **Loading States** - Visual feedback during API calls
6. **Forecast Display** - 5-day weather forecast

## 🎯 Key Takeaways

1. **API integration** enables real-world data
2. **Error handling** provides better user experience
3. **Async/await** manages asynchronous operations
4. **Responsive design** works on all devices
5. **Loading states** improve perceived performance

## 🚀 Next Steps

Congratulations! You've completed Module 3. You now understand:

- Asynchronous JavaScript programming
- Fetch API and HTTP requests
- REST API concepts
- Advanced DOM manipulation
- Form handling and validation
- Timers and intervals
- Date and time handling
- Regular expressions
- Debugging techniques
- Building complete applications

**Ready for Module 4: Modern ES6+ Features!** 🎉

---

**Next Module**: [Module 4: Modern ES6+ Features](../module4-modern-es6/README.md)
