# Lesson 2: Geolocation API

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Request and handle user location permissions
- Get current position with different accuracy levels
- Watch position changes for real-time tracking
- Calculate distances between coordinates
- Handle geolocation errors gracefully
- Implement location-based features

## 📚 Geolocation API Basics

### Getting Current Position
```javascript
// Basic geolocation
navigator.geolocation.getCurrentPosition(
    (position) => {
        console.log('Latitude:', position.coords.latitude);
        console.log('Longitude:', position.coords.longitude);
        console.log('Accuracy:', position.coords.accuracy);
    },
    (error) => {
        console.error('Geolocation error:', error.message);
    }
);
```

### Position Options
```javascript
const options = {
    enableHighAccuracy: true,    // Use GPS if available
    timeout: 10000,              // 10 seconds timeout
    maximumAge: 60000            // Cache for 1 minute
};

navigator.geolocation.getCurrentPosition(
    (position) => {
        console.log('High accuracy position:', position.coords);
    },
    (error) => {
        console.error('Error:', error.message);
    },
    options
);
```

### Watching Position Changes
```javascript
const watchId = navigator.geolocation.watchPosition(
    (position) => {
        console.log('Position updated:', position.coords);
    },
    (error) => {
        console.error('Watch error:', error.message);
    },
    {
        enableHighAccuracy: true,
        timeout: 5000,
        maximumAge: 1000
    }
);

// Stop watching
navigator.geolocation.clearWatch(watchId);
```

## 🗺️ Coordinate Calculations

### Distance Between Two Points
```javascript
function calculateDistance(lat1, lon1, lat2, lon2) {
    const R = 6371; // Earth's radius in kilometers
    const dLat = (lat2 - lat1) * Math.PI / 180;
    const dLon = (lon2 - lon1) * Math.PI / 180;
    
    const a = Math.sin(dLat/2) * Math.sin(dLat/2) +
              Math.cos(lat1 * Math.PI / 180) * Math.cos(lat2 * Math.PI / 180) *
              Math.sin(dLon/2) * Math.sin(dLon/2);
    
    const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
    const distance = R * c;
    
    return distance;
}

// Usage
const distance = calculateDistance(40.7128, -74.0060, 34.0522, -118.2437);
console.log('Distance:', distance.toFixed(2), 'km');
```

## 🎯 Practice Exercises

### Exercise 1: Location Tracker
Create a location tracking application:

**Solution:**
```javascript
class LocationTracker {
    constructor() {
        this.currentPosition = null;
        this.watchId = null;
        this.isTracking = false;
        this.positionHistory = [];
    }
    
    async getCurrentLocation() {
        return new Promise((resolve, reject) => {
            if (!navigator.geolocation) {
                reject(new Error('Geolocation not supported'));
                return;
            }
            
            navigator.geolocation.getCurrentPosition(
                (position) => {
                    this.currentPosition = position;
                    this.positionHistory.push({
                        ...position,
                        timestamp: new Date()
                    });
                    resolve(position);
                },
                (error) => {
                    reject(error);
                },
                {
                    enableHighAccuracy: true,
                    timeout: 10000,
                    maximumAge: 60000
                }
            );
        });
    }
    
    startTracking() {
        if (this.isTracking) return;
        
        this.watchId = navigator.geolocation.watchPosition(
            (position) => {
                this.currentPosition = position;
                this.positionHistory.push({
                    ...position,
                    timestamp: new Date()
                });
                this.onPositionUpdate(position);
            },
            (error) => {
                this.onError(error);
            },
            {
                enableHighAccuracy: true,
                timeout: 5000,
                maximumAge: 1000
            }
        );
        
        this.isTracking = true;
    }
    
    stopTracking() {
        if (this.watchId) {
            navigator.geolocation.clearWatch(this.watchId);
            this.watchId = null;
            this.isTracking = false;
        }
    }
    
    onPositionUpdate(position) {
        console.log('Position updated:', {
            lat: position.coords.latitude,
            lng: position.coords.longitude,
            accuracy: position.coords.accuracy
        });
    }
    
    onError(error) {
        console.error('Geolocation error:', error.message);
    }
    
    getPositionHistory() {
        return this.positionHistory;
    }
    
    calculateTotalDistance() {
        if (this.positionHistory.length < 2) return 0;
        
        let totalDistance = 0;
        for (let i = 1; i < this.positionHistory.length; i++) {
            const prev = this.positionHistory[i - 1];
            const curr = this.positionHistory[i];
            
            const distance = this.calculateDistance(
                prev.coords.latitude,
                prev.coords.longitude,
                curr.coords.latitude,
                curr.coords.longitude
            );
            
            totalDistance += distance;
        }
        
        return totalDistance;
    }
    
    calculateDistance(lat1, lon1, lat2, lon2) {
        const R = 6371; // Earth's radius in kilometers
        const dLat = (lat2 - lat1) * Math.PI / 180;
        const dLon = (lon2 - lon1) * Math.PI / 180;
        
        const a = Math.sin(dLat/2) * Math.sin(dLat/2) +
                  Math.cos(lat1 * Math.PI / 180) * Math.cos(lat2 * Math.PI / 180) *
                  Math.sin(dLon/2) * Math.sin(dLon/2);
        
        const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
        return R * c;
    }
}

// Usage
const tracker = new LocationTracker();

// Get current location
tracker.getCurrentLocation()
    .then(position => {
        console.log('Current location:', position.coords);
    })
    .catch(error => {
        console.error('Error getting location:', error.message);
    });

// Start tracking
tracker.startTracking();
```

### Exercise 2: Location-Based Services
Create a service that finds nearby locations:

**Solution:**
```javascript
class LocationService {
    constructor() {
        this.userLocation = null;
        this.nearbyPlaces = [];
    }
    
    async getUserLocation() {
        return new Promise((resolve, reject) => {
            navigator.geolocation.getCurrentPosition(
                (position) => {
                    this.userLocation = position;
                    resolve(position);
                },
                (error) => {
                    reject(error);
                },
                {
                    enableHighAccuracy: true,
                    timeout: 10000,
                    maximumAge: 300000 // 5 minutes
                }
            );
        });
    }
    
    findNearbyPlaces(places, radiusKm = 5) {
        if (!this.userLocation) {
            throw new Error('User location not available');
        }
        
        const userLat = this.userLocation.coords.latitude;
        const userLng = this.userLocation.coords.longitude;
        
        this.nearbyPlaces = places.filter(place => {
            const distance = this.calculateDistance(
                userLat, userLng,
                place.latitude, place.longitude
            );
            
            place.distance = distance;
            return distance <= radiusKm;
        });
        
        // Sort by distance
        this.nearbyPlaces.sort((a, b) => a.distance - b.distance);
        
        return this.nearbyPlaces;
    }
    
    calculateDistance(lat1, lon1, lat2, lon2) {
        const R = 6371; // Earth's radius in kilometers
        const dLat = (lat2 - lat1) * Math.PI / 180;
        const dLon = (lon2 - lon1) * Math.PI / 180;
        
        const a = Math.sin(dLat/2) * Math.sin(dLat/2) +
                  Math.cos(lat1 * Math.PI / 180) * Math.cos(lat2 * Math.PI / 180) *
                  Math.sin(dLon/2) * Math.sin(dLon/2);
        
        const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
        return R * c;
    }
    
    getDirectionsToPlace(place) {
        if (!this.userLocation) {
            throw new Error('User location not available');
        }
        
        const userLat = this.userLocation.coords.latitude;
        const userLng = this.userLocation.coords.longitude;
        
        // Generate Google Maps directions URL
        const directionsUrl = `https://www.google.com/maps/dir/${userLat},${userLng}/${place.latitude},${place.longitude}`;
        
        return {
            distance: place.distance,
            directionsUrl: directionsUrl,
            estimatedTime: this.estimateTravelTime(place.distance)
        };
    }
    
    estimateTravelTime(distanceKm) {
        // Assume average walking speed of 5 km/h
        const walkingTime = (distanceKm / 5) * 60; // minutes
        return Math.round(walkingTime);
    }
}

// Usage
const locationService = new LocationService();

// Sample places data
const places = [
    { name: 'Central Park', latitude: 40.7829, longitude: -73.9654 },
    { name: 'Times Square', latitude: 40.7580, longitude: -73.9855 },
    { name: 'Brooklyn Bridge', latitude: 40.7061, longitude: -73.9969 },
    { name: 'Statue of Liberty', latitude: 40.6892, longitude: -74.0445 }
];

// Get user location and find nearby places
locationService.getUserLocation()
    .then(() => {
        const nearby = locationService.findNearbyPlaces(places, 10);
        console.log('Nearby places:', nearby);
        
        if (nearby.length > 0) {
            const directions = locationService.getDirectionsToPlace(nearby[0]);
            console.log('Directions to nearest place:', directions);
        }
    })
    .catch(error => {
        console.error('Error:', error.message);
    });
```

## 🚨 Common Mistakes to Avoid

### 1. Not Handling Permission Denied
```javascript
// Wrong - not handling all error cases
navigator.geolocation.getCurrentPosition(success);

// Right - handling all error cases
navigator.geolocation.getCurrentPosition(
    success,
    (error) => {
        switch(error.code) {
            case error.PERMISSION_DENIED:
                console.log('User denied location access');
                break;
            case error.POSITION_UNAVAILABLE:
                console.log('Location information unavailable');
                break;
            case error.TIMEOUT:
                console.log('Location request timed out');
                break;
        }
    }
);
```

### 2. Not Checking API Support
```javascript
// Wrong - assuming geolocation is available
navigator.geolocation.getCurrentPosition(success);

// Right - checking support first
if (navigator.geolocation) {
    navigator.geolocation.getCurrentPosition(success);
} else {
    console.log('Geolocation not supported');
}
```

### 3. Not Using Appropriate Options
```javascript
// Wrong - no options specified
navigator.geolocation.getCurrentPosition(success, error);

// Right - appropriate options for use case
navigator.geolocation.getCurrentPosition(
    success,
    error,
    {
        enableHighAccuracy: true,  // For precise location
        timeout: 10000,            // Reasonable timeout
        maximumAge: 60000          // Cache for 1 minute
    }
);
```

## 🎯 Key Takeaways

1. **Geolocation API** provides access to user location
2. **Permission handling** is crucial for user experience
3. **Options** control accuracy and performance
4. **Error handling** covers all possible scenarios
5. **Distance calculations** enable location-based features
6. **Privacy** - always respect user location data

## 🚀 Next Steps

Great! You now understand the Geolocation API. In the next lesson, we'll learn about:

- **Canvas API** - creating graphics and animations
- **Drawing shapes** - lines, circles, rectangles
- **Image manipulation** - loading and drawing images

## 📚 Additional Resources

- [MDN Geolocation API](https://developer.mozilla.org/en-US/docs/Web/API/Geolocation_API)
- [Geolocation Best Practices](https://developers.google.com/web/fundamentals/native-hardware/user-location)
- [Distance Calculation Formulas](https://en.wikipedia.org/wiki/Haversine_formula)

## 🎉 Congratulations!

You've mastered the Geolocation API! You now understand:

- How to request and handle location permissions
- How to get current position and watch changes
- How to calculate distances between coordinates
- How to build location-based applications

Practice with the exercises, and get ready for Lesson 3 where we'll learn about the Canvas API!

---

**Next Lesson**: [Lesson 3: Canvas API](./lesson3-canvas.md)
