// Exercise 2: LocalStorage Data Manager
// This exercise demonstrates advanced LocalStorage usage with data management

console.log("=== Exercise 2: LocalStorage Data Manager ===");

// Enhanced LocalStorage simulator for Node.js
class LocalStorageSimulator {
    constructor() {
        this.store = {};
    }
    
    setItem(key, value) {
        this.store[key] = String(value);
        console.log(`localStorage.setItem('${key}', '${value}')`);
    }
    
    getItem(key) {
        const value = this.store[key];
        console.log(`localStorage.getItem('${key}') = ${value}`);
        return value;
    }
    
    removeItem(key) {
        delete this.store[key];
        console.log(`localStorage.removeItem('${key}')`);
    }
    
    clear() {
        this.store = {};
        console.log("localStorage.clear()");
    }
    
    get length() {
        return Object.keys(this.store).length;
    }
    
    key(index) {
        const keys = Object.keys(this.store);
        return keys[index];
    }
}

// Advanced data manager with LocalStorage
class LocalStorageDataManager {
    constructor(storage = new LocalStorageSimulator()) {
        this.storage = storage;
        this.prefix = 'app_';
        this.version = '1.0';
        this.compression = false;
    }
    
    // Generate full key with prefix
    getFullKey(key) {
        return `${this.prefix}${key}`;
    }
    
    // Save data with metadata
    save(key, data, options = {}) {
        try {
            const fullKey = this.getFullKey(key);
            const metadata = {
                version: this.version,
                timestamp: new Date().toISOString(),
                size: JSON.stringify(data).length,
                ...options
            };
            
            const storageData = {
                metadata,
                data
            };
            
            const jsonString = JSON.stringify(storageData);
            this.storage.setItem(fullKey, jsonString);
            
            console.log(`✓ Data saved: ${key} (${metadata.size} bytes)`);
            return true;
            
        } catch (error) {
            console.error(`✗ Error saving ${key}:`, error.message);
            return false;
        }
    }
    
    // Load data with metadata
    load(key, defaultValue = null) {
        try {
            const fullKey = this.getFullKey(key);
            const storedData = this.storage.getItem(fullKey);
            
            if (storedData === null) {
                return defaultValue;
            }
            
            const parsed = JSON.parse(storedData);
            
            // Check version compatibility
            if (parsed.metadata.version !== this.version) {
                console.warn(`Version mismatch for ${key}: stored ${parsed.metadata.version}, current ${this.version}`);
            }
            
            console.log(`✓ Data loaded: ${key} (${parsed.metadata.size} bytes)`);
            return parsed.data;
            
        } catch (error) {
            console.error(`✗ Error loading ${key}:`, error.message);
            return defaultValue;
        }
    }
    
    // Remove data
    remove(key) {
        const fullKey = this.getFullKey(key);
        this.storage.removeItem(fullKey);
        console.log(`✓ Data removed: ${key}`);
    }
    
    // Check if data exists
    exists(key) {
        const fullKey = this.getFullKey(key);
        return this.storage.getItem(fullKey) !== null;
    }
    
    // Get all keys with prefix
    getAllKeys() {
        const keys = [];
        for (let i = 0; i < this.storage.length; i++) {
            const key = this.storage.key(i);
            if (key && key.startsWith(this.prefix)) {
                keys.push(key.substring(this.prefix.length));
            }
        }
        return keys;
    }
    
    // Get storage statistics
    getStats() {
        const keys = this.getAllKeys();
        const stats = {
            totalKeys: keys.length,
            totalSize: 0,
            keys: {}
        };
        
        keys.forEach(key => {
            const data = this.load(key);
            if (data !== null) {
                const size = JSON.stringify(data).length;
                stats.totalSize += size;
                stats.keys[key] = size;
            }
        });
        
        return stats;
    }
    
    // Clear all data with prefix
    clear() {
        const keys = this.getAllKeys();
        keys.forEach(key => this.remove(key));
        console.log(`✓ Cleared ${keys.length} items`);
    }
    
    // Export data
    exportData(keys = null) {
        const exportKeys = keys || this.getAllKeys();
        const exportData = {
            version: this.version,
            exportDate: new Date().toISOString(),
            data: {}
        };
        
        exportKeys.forEach(key => {
            const data = this.load(key);
            if (data !== null) {
                exportData.data[key] = data;
            }
        });
        
        return exportData;
    }
    
    // Import data
    importData(importData) {
        try {
            if (!importData.data) {
                throw new Error('Invalid import data');
            }
            
            let importedCount = 0;
            for (const [key, data] of Object.entries(importData.data)) {
                if (this.save(key, data)) {
                    importedCount++;
                }
            }
            
            console.log(`✓ Imported ${importedCount} items`);
            return true;
            
        } catch (error) {
            console.error(`✗ Import error:`, error.message);
            return false;
        }
    }
}

// User preferences manager
class UserPreferencesManager extends LocalStorageDataManager {
    constructor() {
        super();
        this.preferencesKey = 'userPreferences';
    }
    
    getPreferences() {
        return this.load(this.preferencesKey, {
            theme: 'light',
            language: 'en',
            notifications: true,
            autoSave: true,
            fontSize: 14
        });
    }
    
    updatePreferences(updates) {
        const current = this.getPreferences();
        const updated = { ...current, ...updates };
        return this.save(this.preferencesKey, updated);
    }
    
    resetPreferences() {
        this.remove(this.preferencesKey);
        console.log('✓ Preferences reset to defaults');
    }
}

// Session data manager
class SessionDataManager extends LocalStorageDataManager {
    constructor() {
        super();
        this.sessionKey = 'sessionData';
        this.sessionTimeout = 24 * 60 * 60 * 1000; // 24 hours
    }
    
    startSession(userId) {
        const sessionData = {
            userId,
            startTime: new Date().toISOString(),
            lastActivity: new Date().toISOString(),
            pageViews: 0,
            actions: []
        };
        
        return this.save(this.sessionKey, sessionData);
    }
    
    updateSession(updates = {}) {
        const session = this.load(this.sessionKey);
        if (!session) {
            console.log('No active session');
            return false;
        }
        
        const updated = {
            ...session,
            ...updates,
            lastActivity: new Date().toISOString()
        };
        
        return this.save(this.sessionKey, updated);
    }
    
    addAction(action) {
        const session = this.load(this.sessionKey);
        if (!session) {
            return false;
        }
        
        session.actions.push({
            action,
            timestamp: new Date().toISOString()
        });
        
        return this.updateSession({ actions: session.actions });
    }
    
    isSessionValid() {
        const session = this.load(this.sessionKey);
        if (!session) {
            return false;
        }
        
        const lastActivity = new Date(session.lastActivity);
        const now = new Date();
        
        return (now - lastActivity) < this.sessionTimeout;
    }
    
    endSession() {
        this.remove(this.sessionKey);
        console.log('✓ Session ended');
    }
}

// Cache manager
class CacheManager extends LocalStorageDataManager {
    constructor() {
        super();
        this.defaultTTL = 60 * 60 * 1000; // 1 hour
    }
    
    set(key, data, ttl = this.defaultTTL) {
        const cacheData = {
            data,
            expires: Date.now() + ttl,
            created: new Date().toISOString()
        };
        
        return this.save(`cache_${key}`, cacheData);
    }
    
    get(key) {
        const cacheData = this.load(`cache_${key}`);
        if (!cacheData) {
            return null;
        }
        
        if (Date.now() > cacheData.expires) {
            this.remove(`cache_${key}`);
            console.log(`Cache expired for ${key}`);
            return null;
        }
        
        return cacheData.data;
    }
    
    clearExpired() {
        const keys = this.getAllKeys().filter(key => key.startsWith('cache_'));
        let clearedCount = 0;
        
        keys.forEach(key => {
            const cacheData = this.load(key);
            if (cacheData && Date.now() > cacheData.expires) {
                this.remove(key);
                clearedCount++;
            }
        });
        
        console.log(`✓ Cleared ${clearedCount} expired cache entries`);
        return clearedCount;
    }
}

// Test the LocalStorage data managers
console.log("Testing LocalStorage data managers...");

// Test 1: Basic data manager
console.log("\n=== Test 1: Basic Data Manager ===");

const dataManager = new LocalStorageDataManager();

const testData = {
    users: [
        { id: 1, name: 'Alice', email: 'alice@example.com' },
        { id: 2, name: 'Bob', email: 'bob@example.com' }
    ],
    settings: {
        theme: 'dark',
        notifications: true
    }
};

dataManager.save('testData', testData);
const loadedData = dataManager.load('testData');
console.log('Loaded data:', loadedData);

// Test 2: User preferences manager
console.log("\n=== Test 2: User Preferences Manager ===");

const prefsManager = new UserPreferencesManager();

console.log('Initial preferences:', prefsManager.getPreferences());

prefsManager.updatePreferences({
    theme: 'dark',
    fontSize: 16,
    notifications: false
});

console.log('Updated preferences:', prefsManager.getPreferences());

// Test 3: Session data manager
console.log("\n=== Test 3: Session Data Manager ===");

const sessionManager = new SessionDataManager();

sessionManager.startSession('user123');
sessionManager.addAction('page_view');
sessionManager.addAction('button_click');
sessionManager.updateSession({ pageViews: 5 });

console.log('Session data:', sessionManager.load('sessionData'));
console.log('Session valid:', sessionManager.isSessionValid());

// Test 4: Cache manager
console.log("\n=== Test 4: Cache Manager ===");

const cacheManager = new CacheManager();

cacheManager.set('api_data', { result: 'cached data' }, 5000); // 5 second TTL
console.log('Cached data:', cacheManager.get('api_data'));

// Simulate cache expiration
setTimeout(() => {
    console.log('After expiration:', cacheManager.get('api_data'));
}, 6000);

// Test 5: Storage statistics
console.log("\n=== Test 5: Storage Statistics ===");

const stats = dataManager.getStats();
console.log('Storage stats:', stats);

// Test 6: Export and import
console.log("\n=== Test 6: Export and Import ===");

const exportData = dataManager.exportData();
console.log('Export data:', JSON.stringify(exportData, null, 2));

const newManager = new LocalStorageDataManager();
newManager.importData(exportData);
console.log('Imported keys:', newManager.getAllKeys());

// Test 7: Data cleanup
console.log("\n=== Test 7: Data Cleanup ===");

console.log('All keys before cleanup:', dataManager.getAllKeys());
dataManager.remove('testData');
console.log('All keys after cleanup:', dataManager.getAllKeys());

console.log("\n=== LocalStorage Data Manager Summary ===");
console.log("✓ Advanced LocalStorage data management");
console.log("✓ Metadata tracking and version control");
console.log("✓ User preferences management");
console.log("✓ Session data tracking");
console.log("✓ Cache management with TTL");
console.log("✓ Storage statistics and monitoring");
console.log("✓ Export and import functionality");
console.log("✓ Data cleanup and maintenance");
