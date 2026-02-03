// Exercise 1: Weather API Client
// This exercise demonstrates building a weather API client using fetch

console.log("=== Exercise 1: Weather API Client ===");

// Mock weather API responses
const mockWeatherAPI = {
    getCurrentWeather: (city) => {
        return new Promise((resolve) => {
            setTimeout(() => {
                const weatherData = {
                    city: city,
                    temperature: Math.floor(Math.random() * 30) + 10, // 10-40°C
                    humidity: Math.floor(Math.random() * 40) + 30, // 30-70%
                    description: ['Sunny', 'Cloudy', 'Rainy', 'Partly Cloudy'][Math.floor(Math.random() * 4)],
                    windSpeed: Math.floor(Math.random() * 20) + 5, // 5-25 km/h
                    timestamp: new Date().toISOString()
                };
                resolve(weatherData);
            }, 500);
        });
    },
    
    getForecast: (city, days = 5) => {
        return new Promise((resolve) => {
            setTimeout(() => {
                const forecast = [];
                for (let i = 0; i < days; i++) {
                    const date = new Date();
                    date.setDate(date.getDate() + i);
                    
                    forecast.push({
                        date: date.toISOString().split('T')[0],
                        high: Math.floor(Math.random() * 15) + 20, // 20-35°C
                        low: Math.floor(Math.random() * 10) + 10, // 10-20°C
                        description: ['Sunny', 'Cloudy', 'Rainy', 'Partly Cloudy'][Math.floor(Math.random() * 4)],
                        precipitation: Math.floor(Math.random() * 30) // 0-30%
                    });
                }
                resolve({ city, forecast });
            }, 800);
        });
    }
};

// Weather API client class
class WeatherAPIClient {
    constructor(apiKey = 'demo-key') {
        this.apiKey = apiKey;
        this.baseUrl = 'https://api.weather.com';
        this.cache = new Map();
        this.cacheTimeout = 10 * 60 * 1000; // 10 minutes
    }
    
    // Get current weather for a city
    async getCurrentWeather(city) {
        try {
            console.log(`Fetching current weather for ${city}...`);
            
            // Check cache first
            const cacheKey = `current_${city}`;
            const cached = this.getFromCache(cacheKey);
            if (cached) {
                console.log('Using cached data');
                return cached;
            }
            
            // Make API request (simulated)
            const weatherData = await mockWeatherAPI.getCurrentWeather(city);
            
            // Cache the result
            this.setCache(cacheKey, weatherData);
            
            console.log(`Current weather for ${city}:`, weatherData);
            return weatherData;
            
        } catch (error) {
            console.error(`Error fetching current weather for ${city}:`, error.message);
            throw error;
        }
    }
    
    // Get weather forecast for a city
    async getForecast(city, days = 5) {
        try {
            console.log(`Fetching ${days}-day forecast for ${city}...`);
            
            // Check cache first
            const cacheKey = `forecast_${city}_${days}`;
            const cached = this.getFromCache(cacheKey);
            if (cached) {
                console.log('Using cached forecast data');
                return cached;
            }
            
            // Make API request (simulated)
            const forecastData = await mockWeatherAPI.getForecast(city, days);
            
            // Cache the result
            this.setCache(cacheKey, forecastData);
            
            console.log(`Forecast for ${city}:`, forecastData);
            return forecastData;
            
        } catch (error) {
            console.error(`Error fetching forecast for ${city}:`, error.message);
            throw error;
        }
    }
    
    // Get weather for multiple cities
    async getWeatherForMultipleCities(cities) {
        try {
            console.log(`Fetching weather for ${cities.length} cities...`);
            
            const promises = cities.map(city => this.getCurrentWeather(city));
            const results = await Promise.allSettled(promises);
            
            const weatherData = [];
            results.forEach((result, index) => {
                if (result.status === 'fulfilled') {
                    weatherData.push(result.value);
                } else {
                    console.error(`Failed to get weather for ${cities[index]}:`, result.reason);
                    weatherData.push({
                        city: cities[index],
                        error: result.reason.message
                    });
                }
            });
            
            return weatherData;
            
        } catch (error) {
            console.error('Error fetching weather for multiple cities:', error.message);
            throw error;
        }
    }
    
    // Cache management
    getFromCache(key) {
        const cached = this.cache.get(key);
        if (cached && Date.now() - cached.timestamp < this.cacheTimeout) {
            return cached.data;
        }
        this.cache.delete(key);
        return null;
    }
    
    setCache(key, data) {
        this.cache.set(key, {
            data,
            timestamp: Date.now()
        });
    }
    
    clearCache() {
        this.cache.clear();
        console.log('Weather cache cleared');
    }
    
    // Get cache statistics
    getCacheStats() {
        const now = Date.now();
        let validEntries = 0;
        let expiredEntries = 0;
        
        for (const [key, value] of this.cache) {
            if (now - value.timestamp < this.cacheTimeout) {
                validEntries++;
            } else {
                expiredEntries++;
            }
        }
        
        return {
            totalEntries: this.cache.size,
            validEntries,
            expiredEntries,
            cacheTimeout: this.cacheTimeout
        };
    }
}

// Weather display utility
class WeatherDisplay {
    static formatTemperature(temp) {
        return `${temp}°C`;
    }
    
    static formatWeatherCard(weather) {
        if (weather.error) {
            return `❌ ${weather.city}: ${weather.error}`;
        }
        
        return `
🌤️ ${weather.city}
   Temperature: ${this.formatTemperature(weather.temperature)}
   Description: ${weather.description}
   Humidity: ${weather.humidity}%
   Wind: ${weather.windSpeed} km/h
   Updated: ${new Date(weather.timestamp).toLocaleTimeString()}
        `.trim();
    }
    
    static formatForecastCard(forecast) {
        let card = `📅 ${forecast.city} - ${forecast.forecast.length}-Day Forecast\n`;
        
        forecast.forecast.forEach(day => {
            card += `
   ${day.date}: ${day.description}
   High: ${this.formatTemperature(day.high)} | Low: ${this.formatTemperature(day.low)}
   Precipitation: ${day.precipitation}%
            `.trim() + '\n';
        });
        
        return card.trim();
    }
}

// Test the weather API client
console.log("Testing weather API client...");

const weatherClient = new WeatherAPIClient('demo-api-key');

// Test 1: Get current weather for a single city
console.log("\n=== Test 1: Single City Weather ===");
weatherClient.getCurrentWeather('London')
    .then(weather => {
        console.log(WeatherDisplay.formatWeatherCard(weather));
    })
    .catch(error => {
        console.error('Test 1 failed:', error.message);
    });

// Test 2: Get weather forecast
console.log("\n=== Test 2: Weather Forecast ===");
weatherClient.getForecast('Paris', 3)
    .then(forecast => {
        console.log(WeatherDisplay.formatForecastCard(forecast));
    })
    .catch(error => {
        console.error('Test 2 failed:', error.message);
    });

// Test 3: Get weather for multiple cities
console.log("\n=== Test 3: Multiple Cities Weather ===");
const cities = ['Tokyo', 'New York', 'Sydney', 'Berlin'];
weatherClient.getWeatherForMultipleCities(cities)
    .then(weatherData => {
        weatherData.forEach(weather => {
            console.log(WeatherDisplay.formatWeatherCard(weather));
            console.log('---');
        });
    })
    .catch(error => {
        console.error('Test 3 failed:', error.message);
    });

// Test 4: Cache functionality
console.log("\n=== Test 4: Cache Functionality ===");
weatherClient.getCurrentWeather('Madrid')
    .then(() => {
        // This should use cache
        return weatherClient.getCurrentWeather('Madrid');
    })
    .then(() => {
        const stats = weatherClient.getCacheStats();
        console.log('Cache stats:', stats);
    })
    .catch(error => {
        console.error('Test 4 failed:', error.message);
    });

// Test 5: Error handling
console.log("\n=== Test 5: Error Handling ===");
weatherClient.getCurrentWeather('InvalidCity')
    .then(weather => {
        console.log('Unexpected success:', weather);
    })
    .catch(error => {
        console.log('Expected error handled:', error.message);
    });

// Test 6: Cache management
console.log("\n=== Test 6: Cache Management ===");
setTimeout(() => {
    const stats = weatherClient.getCacheStats();
    console.log('Final cache stats:', stats);
    
    weatherClient.clearCache();
    console.log('Cache cleared');
}, 2000);

console.log("\n=== Weather API Client Summary ===");
console.log("✓ Weather API client with current weather and forecast");
console.log("✓ Caching system to reduce API calls");
console.log("✓ Multiple city weather fetching");
console.log("✓ Error handling and fallback mechanisms");
console.log("✓ Weather data formatting and display");
console.log("✓ Cache statistics and management");
console.log("✓ Promise-based asynchronous operations");
console.log("✓ Real-world API integration patterns");
