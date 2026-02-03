// Exercise 1: Data Persistence Manager
// This exercise demonstrates JSON and LocalStorage for data persistence

console.log("=== Exercise 1: Data Persistence Manager ===");

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

// Data persistence manager
class DataPersistenceManager {
    constructor(storage = new LocalStorageSimulator()) {
        this.storage = storage;
        this.dataVersion = '1.0';
        this.compressionEnabled = false;
    }
    
    // Save data with error handling and validation
    save(key, data, options = {}) {
        try {
            // Validate data
            if (!this.validateData(data)) {
                throw new Error('Invalid data format');
            }
            
            // Prepare data for storage
            const storageData = {
                version: this.dataVersion,
                timestamp: new Date().toISOString(),
                data: data,
                options: options
            };
            
            // Convert to JSON
            const jsonString = JSON.stringify(storageData);
            
            // Compress if enabled
            const finalData = this.compressionEnabled ? this.compress(jsonString) : jsonString;
            
            // Save to storage
            this.storage.setItem(key, finalData);
            
            console.log(`✓ Data saved successfully: ${key}`);
            return true;
            
        } catch (error) {
            console.error(`✗ Error saving data: ${error.message}`);
            return false;
        }
    }
    
    // Load data with error handling and validation
    load(key, defaultValue = null) {
        try {
            const storedData = this.storage.getItem(key);
            
            if (storedData === null) {
                console.log(`No data found for key: ${key}`);
                return defaultValue;
            }
            
            // Decompress if needed
            const jsonString = this.compressionEnabled ? this.decompress(storedData) : storedData;
            
            // Parse JSON
            const parsedData = JSON.parse(jsonString);
            
            // Validate version compatibility
            if (!this.isVersionCompatible(parsedData.version)) {
                console.warn(`Version mismatch: stored ${parsedData.version}, current ${this.dataVersion}`);
            }
            
            console.log(`✓ Data loaded successfully: ${key}`);
            return parsedData.data;
            
        } catch (error) {
            console.error(`✗ Error loading data: ${error.message}`);
            return defaultValue;
        }
    }
    
    // Remove data
    remove(key) {
        this.storage.removeItem(key);
        console.log(`✓ Data removed: ${key}`);
    }
    
    // Check if data exists
    exists(key) {
        return this.storage.getItem(key) !== null;
    }
    
    // Get all keys
    getAllKeys() {
        const keys = [];
        for (let i = 0; i < this.storage.length; i++) {
            keys.push(this.storage.key(i));
        }
        return keys;
    }
    
    // Clear all data
    clear() {
        this.storage.clear();
        console.log("✓ All data cleared");
    }
    
    // Validate data before saving
    validateData(data) {
        if (data === null || data === undefined) {
            return false;
        }
        
        // Check for circular references
        try {
            JSON.stringify(data);
            return true;
        } catch (error) {
            return false;
        }
    }
    
    // Check version compatibility
    isVersionCompatible(version) {
        const currentMajor = this.dataVersion.split('.')[0];
        const storedMajor = version.split('.')[0];
        return currentMajor === storedMajor;
    }
    
    // Simple compression simulation
    compress(data) {
        // In a real application, you would use actual compression
        return `COMPRESSED:${data}`;
    }
    
    // Simple decompression simulation
    decompress(data) {
        if (data.startsWith('COMPRESSED:')) {
            return data.substring(11);
        }
        return data;
    }
    
    // Export data
    exportData(keys = null) {
        const exportKeys = keys || this.getAllKeys();
        const exportData = {
            version: this.dataVersion,
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
                throw new Error('Invalid import data format');
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
            console.error(`✗ Import error: ${error.message}`);
            return false;
        }
    }
}

// Test the data persistence manager
console.log("Testing data persistence manager...");

const persistenceManager = new DataPersistenceManager();

// Test 1: Basic save and load
console.log("\n=== Test 1: Basic Save and Load ===");

const userProfile = {
    name: "Alice Johnson",
    email: "alice@example.com",
    preferences: {
        theme: "dark",
        language: "en",
        notifications: true
    },
    lastLogin: new Date().toISOString()
};

persistenceManager.save('userProfile', userProfile);
const loadedProfile = persistenceManager.load('userProfile');
console.log("Loaded profile:", loadedProfile);

// Test 2: Complex data structures
console.log("\n=== Test 2: Complex Data Structures ===");

const todoList = [
    { id: 1, text: "Learn JavaScript", completed: false, priority: "high" },
    { id: 2, text: "Build a project", completed: true, priority: "medium" },
    { id: 3, text: "Deploy to production", completed: false, priority: "low" }
];

const projectData = {
    name: "My Project",
    todos: todoList,
    settings: {
        autoSave: true,
        theme: "light"
    },
    metadata: {
        created: new Date().toISOString(),
        version: "1.0.0"
    }
};

persistenceManager.save('projectData', projectData);
const loadedProject = persistenceManager.load('projectData');
console.log("Loaded project:", loadedProject);

// Test 3: Error handling
console.log("\n=== Test 3: Error Handling ===");

// Test circular reference
const circularObj = { name: "test" };
circularObj.self = circularObj;

persistenceManager.save('circularTest', circularObj);

// Test invalid data
persistenceManager.save('invalidTest', null);

// Test 4: Data management
console.log("\n=== Test 4: Data Management ===");

console.log("All keys:", persistenceManager.getAllKeys());
console.log("'userProfile' exists:", persistenceManager.exists('userProfile'));
console.log("'nonexistent' exists:", persistenceManager.exists('nonexistent'));

// Test 5: Export and import
console.log("\n=== Test 5: Export and Import ===");

const exportData = persistenceManager.exportData();
console.log("Export data:", JSON.stringify(exportData, null, 2));

// Create new manager for import test
const newManager = new DataPersistenceManager();
newManager.importData(exportData);

console.log("Imported keys:", newManager.getAllKeys());

// Test 6: Version compatibility
console.log("\n=== Test 6: Version Compatibility ===");

const oldData = {
    version: '0.9',
    timestamp: new Date().toISOString(),
    data: { test: 'old version data' }
};

// Simulate old data
newManager.storage.setItem('oldData', JSON.stringify(oldData));
const loadedOldData = newManager.load('oldData');
console.log("Loaded old data:", loadedOldData);

// Test 7: Compression
console.log("\n=== Test 7: Compression ===");

const compressionManager = new DataPersistenceManager();
compressionManager.compressionEnabled = true;

const largeData = {
    items: Array.from({ length: 100 }, (_, i) => ({
        id: i,
        name: `Item ${i}`,
        description: `This is item number ${i} with some description text`
    }))
};

compressionManager.save('largeData', largeData);
const loadedLargeData = compressionManager.load('largeData');
console.log("Loaded large data items:", loadedLargeData.items.length);

// Test 8: Batch operations
console.log("\n=== Test 8: Batch Operations ===");

class BatchPersistenceManager extends DataPersistenceManager {
    constructor(storage = new LocalStorageSimulator()) {
        super(storage);
        this.batch = {};
    }
    
    batchSave(key, data) {
        this.batch[key] = data;
        console.log(`Added to batch: ${key}`);
    }
    
    commitBatch() {
        const results = {};
        let successCount = 0;
        
        for (const [key, data] of Object.entries(this.batch)) {
            results[key] = this.save(key, data);
            if (results[key]) successCount++;
        }
        
        console.log(`Batch committed: ${successCount}/${Object.keys(this.batch).length} successful`);
        this.batch = {};
        return results;
    }
    
    rollbackBatch() {
        console.log(`Batch rolled back: ${Object.keys(this.batch).length} items discarded`);
        this.batch = {};
    }
}

const batchManager = new BatchPersistenceManager();

// Add items to batch
batchManager.batchSave('item1', { name: 'Item 1', value: 100 });
batchManager.batchSave('item2', { name: 'Item 2', value: 200 });
batchManager.batchSave('item3', { name: 'Item 3', value: 300 });

// Commit batch
const batchResults = batchManager.commitBatch();
console.log("Batch results:", batchResults);

console.log("\n=== Data Persistence Manager Summary ===");
console.log("✓ Enhanced data persistence with error handling");
console.log("✓ Data validation and version compatibility");
console.log("✓ Compression and decompression support");
console.log("✓ Export and import functionality");
console.log("✓ Batch operations for multiple items");
console.log("✓ Comprehensive data management features");
console.log("✓ Cross-environment compatibility");
