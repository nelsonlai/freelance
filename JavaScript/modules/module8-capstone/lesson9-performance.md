# Lesson 9: Performance Optimization

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Optimize application performance
- Implement code splitting and lazy loading
- Use caching strategies effectively
- Optimize images and assets
- Monitor performance metrics
- Apply best practices for speed

## 📚 Performance Optimization Techniques

### Code Splitting
```javascript
// Lazy loading components
import React, { lazy, Suspense } from 'react';

const LazyComponent = lazy(() => import('./LazyComponent'));

function App() {
    return (
        <div>
            <Suspense fallback={<div>Loading...</div>}>
                <LazyComponent />
            </Suspense>
        </div>
    );
}

// Route-based code splitting
const Home = lazy(() => import('./pages/Home'));
const About = lazy(() => import('./pages/About'));
const Contact = lazy(() => import('./pages/Contact'));
```

### Image Optimization
```javascript
// Lazy loading images
function LazyImage({ src, alt, ...props }) {
    const [isLoaded, setIsLoaded] = useState(false);
    const [isInView, setIsInView] = useState(false);
    const imgRef = useRef();
    
    useEffect(() => {
        const observer = new IntersectionObserver(
            ([entry]) => {
                if (entry.isIntersecting) {
                    setIsInView(true);
                    observer.disconnect();
                }
            },
            { threshold: 0.1 }
        );
        
        if (imgRef.current) {
            observer.observe(imgRef.current);
        }
        
        return () => observer.disconnect();
    }, []);
    
    return (
        <div ref={imgRef} className="image-container">
            {isInView && (
                <img
                    src={src}
                    alt={alt}
                    onLoad={() => setIsLoaded(true)}
                    style={{ opacity: isLoaded ? 1 : 0 }}
                    {...props}
                />
            )}
        </div>
    );
}
```

## 🎯 Practice Exercises

### Exercise 1: Performance Monitoring
Create a performance monitoring system:

**Solution:**
```javascript
class PerformanceMonitor {
    constructor() {
        this.metrics = {};
        this.observers = [];
    }
    
    // Monitor Core Web Vitals
    monitorWebVitals() {
        // Largest Contentful Paint (LCP)
        new PerformanceObserver((list) => {
            const entries = list.getEntries();
            const lastEntry = entries[entries.length - 1];
            this.metrics.lcp = lastEntry.startTime;
        }).observe({ entryTypes: ['largest-contentful-paint'] });
        
        // First Input Delay (FID)
        new PerformanceObserver((list) => {
            const entries = list.getEntries();
            entries.forEach(entry => {
                this.metrics.fid = entry.processingStart - entry.startTime;
            });
        }).observe({ entryTypes: ['first-input'] });
        
        // Cumulative Layout Shift (CLS)
        let clsValue = 0;
        new PerformanceObserver((list) => {
            const entries = list.getEntries();
            entries.forEach(entry => {
                if (!entry.hadRecentInput) {
                    clsValue += entry.value;
                }
            });
            this.metrics.cls = clsValue;
        }).observe({ entryTypes: ['layout-shift'] });
    }
    
    // Monitor resource loading
    monitorResources() {
        const resources = performance.getEntriesByType('resource');
        this.metrics.resources = resources.map(resource => ({
            name: resource.name,
            duration: resource.duration,
            size: resource.transferSize,
            type: resource.initiatorType
        }));
    }
    
    // Monitor memory usage
    monitorMemory() {
        if ('memory' in performance) {
            this.metrics.memory = {
                used: performance.memory.usedJSHeapSize,
                total: performance.memory.totalJSHeapSize,
                limit: performance.memory.jsHeapSizeLimit
            };
        }
    }
    
    // Get performance report
    getReport() {
        this.monitorResources();
        this.monitorMemory();
        
        return {
            timestamp: new Date().toISOString(),
            metrics: this.metrics,
            userAgent: navigator.userAgent,
            connection: navigator.connection ? {
                effectiveType: navigator.connection.effectiveType,
                downlink: navigator.connection.downlink,
                rtt: navigator.connection.rtt
            } : null
        };
    }
    
    // Send report to analytics
    sendReport() {
        const report = this.getReport();
        
        // Send to analytics service
        fetch('/api/analytics/performance', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(report)
        }).catch(error => {
            console.error('Failed to send performance report:', error);
        });
    }
}

// Usage
const monitor = new PerformanceMonitor();
monitor.monitorWebVitals();

// Send report after page load
window.addEventListener('load', () => {
    setTimeout(() => {
        monitor.sendReport();
    }, 2000);
});
```

### Exercise 2: Caching Strategy
Implement a comprehensive caching strategy:

**Solution:**
```javascript
class CacheManager {
    constructor() {
        this.cache = new Map();
        this.maxSize = 100;
        this.ttl = 5 * 60 * 1000; // 5 minutes
    }
    
    // Set cache item with TTL
    set(key, value, ttl = this.ttl) {
        // Remove oldest items if cache is full
        if (this.cache.size >= this.maxSize) {
            const firstKey = this.cache.keys().next().value;
            this.cache.delete(firstKey);
        }
        
        this.cache.set(key, {
            value,
            timestamp: Date.now(),
            ttl
        });
    }
    
    // Get cache item
    get(key) {
        const item = this.cache.get(key);
        
        if (!item) {
            return null;
        }
        
        // Check if item has expired
        if (Date.now() - item.timestamp > item.ttl) {
            this.cache.delete(key);
            return null;
        }
        
        return item.value;
    }
    
    // Clear expired items
    clearExpired() {
        const now = Date.now();
        for (const [key, item] of this.cache.entries()) {
            if (now - item.timestamp > item.ttl) {
                this.cache.delete(key);
            }
        }
    }
    
    // Clear all cache
    clear() {
        this.cache.clear();
    }
    
    // Get cache stats
    getStats() {
        return {
            size: this.cache.size,
            maxSize: this.maxSize,
            keys: Array.from(this.cache.keys())
        };
    }
}

// HTTP cache with service worker
class HTTPCache {
    constructor() {
        this.cacheName = 'http-cache-v1';
    }
    
    async get(request) {
        const cache = await caches.open(this.cacheName);
        const response = await cache.match(request);
        
        if (response) {
            // Check if response is still fresh
            const cachedDate = new Date(response.headers.get('date'));
            const now = new Date();
            const age = now - cachedDate;
            
            // Consider fresh if less than 5 minutes old
            if (age < 5 * 60 * 1000) {
                return response;
            }
        }
        
        return null;
    }
    
    async set(request, response) {
        const cache = await caches.open(this.cacheName);
        await cache.put(request, response.clone());
    }
    
    async delete(request) {
        const cache = await caches.open(this.cacheName);
        await cache.delete(request);
    }
}

// Usage
const cacheManager = new CacheManager();
const httpCache = new HTTPCache();

// Cache API responses
async function fetchWithCache(url) {
    const request = new Request(url);
    
    // Try to get from cache first
    let response = await httpCache.get(request);
    
    if (!response) {
        // Fetch from network
        response = await fetch(request);
        
        // Cache successful responses
        if (response.ok) {
            await httpCache.set(request, response);
        }
    }
    
    return response;
}
```

## 🎯 Key Takeaways

1. **Code splitting** reduces initial bundle size
2. **Lazy loading** improves perceived performance
3. **Caching** reduces server requests
4. **Image optimization** speeds up loading
5. **Performance monitoring** tracks improvements

---

**Next Lesson**: [Lesson 10: Final Project - Full-Stack App](./lesson10-final-project.md)
