class WeatherApp {
    constructor() {
        // Note: Replace with your actual OpenWeather API key
        this.apiKey = 'f42cea6e1876705c19c2cbae652d8019'; 
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
