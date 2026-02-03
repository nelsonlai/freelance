// Exercise 3: API Data Synchronization System
// This exercise demonstrates building a data synchronization system with APIs

console.log("=== Exercise 3: API Data Synchronization System ===");

// Data synchronization manager
class DataSyncManager {
    constructor() {
        this.syncQueue = [];
        this.isProcessing = false;
        this.syncInterval = null;
        this.conflictResolution = 'server-wins'; // 'server-wins', 'client-wins', 'manual'
        this.lastSyncTime = null;
        this.syncStatus = 'idle'; // 'idle', 'syncing', 'error'
        this.eventListeners = new Map();
    }
    
    // Add event listener
    on(event, callback) {
        if (!this.eventListeners.has(event)) {
            this.eventListeners.set(event, []);
        }
        this.eventListeners.get(event).push(callback);
    }
    
    // Emit event
    emit(event, data) {
        if (this.eventListeners.has(event)) {
            this.eventListeners.get(event).forEach(callback => {
                try {
                    callback(data);
                } catch (error) {
                    console.error(`Error in event listener for ${event}:`, error);
                }
            });
        }
    }
    
    // Mock API client
    async mockAPICall(endpoint, method = 'GET', data = null) {
        return new Promise((resolve, reject) => {
            console.log(`API Call: ${method} ${endpoint}`);
            
            setTimeout(() => {
                // Simulate different API responses
                if (endpoint.includes('/error')) {
                    reject(new Error('API Error'));
                    return;
                }
                
                if (endpoint.includes('/conflict')) {
                    resolve({
                        status: 409,
                        data: { message: 'Conflict detected', serverData: { id: 1, version: 2 } }
                    });
                    return;
                }
                
                // Success response
                const response = {
                    status: 200,
                    data: {
                        id: Math.floor(Math.random() * 1000),
                        timestamp: new Date().toISOString(),
                        ...data
                    }
                };
                
                resolve(response);
            }, Math.random() * 1000 + 500);
        });
    }
    
    // Add item to sync queue
    addToSyncQueue(item) {
        const syncItem = {
            id: item.id || Date.now(),
            type: item.type || 'update',
            data: item.data,
            timestamp: new Date().toISOString(),
            retryCount: 0,
            maxRetries: 3
        };
        
        this.syncQueue.push(syncItem);
        this.emit('itemQueued', syncItem);
        
        console.log(`Item added to sync queue: ${syncItem.type} ${syncItem.id}`);
        
        // Start processing if not already running
        if (!this.isProcessing) {
            this.processSyncQueue();
        }
    }
    
    // Process sync queue
    async processSyncQueue() {
        if (this.isProcessing || this.syncQueue.length === 0) {
            return;
        }
        
        this.isProcessing = true;
        this.syncStatus = 'syncing';
        this.emit('syncStarted', { queueLength: this.syncQueue.length });
        
        console.log(`Processing sync queue with ${this.syncQueue.length} items`);
        
        while (this.syncQueue.length > 0) {
            const item = this.syncQueue.shift();
            
            try {
                await this.syncItem(item);
                this.emit('itemSynced', item);
            } catch (error) {
                console.error(`Failed to sync item ${item.id}:`, error.message);
                
                if (item.retryCount < item.maxRetries) {
                    item.retryCount++;
                    this.syncQueue.push(item);
                    this.emit('itemRetry', { item, retryCount: item.retryCount });
                } else {
                    this.emit('itemFailed', { item, error: error.message });
                }
            }
            
            // Small delay between requests
            await this.delay(100);
        }
        
        this.isProcessing = false;
        this.syncStatus = 'idle';
        this.lastSyncTime = new Date().toISOString();
        this.emit('syncCompleted', { timestamp: this.lastSyncTime });
        
        console.log('Sync queue processing completed');
    }
    
    // Sync individual item
    async syncItem(item) {
        console.log(`Syncing item: ${item.type} ${item.id}`);
        
        try {
            let response;
            
            switch (item.type) {
                case 'create':
                    response = await this.mockAPICall('/api/items', 'POST', item.data);
                    break;
                case 'update':
                    response = await this.mockAPICall(`/api/items/${item.id}`, 'PUT', item.data);
                    break;
                case 'delete':
                    response = await this.mockAPICall(`/api/items/${item.id}`, 'DELETE');
                    break;
                default:
                    throw new Error(`Unknown sync type: ${item.type}`);
            }
            
            if (response.status === 409) {
                // Handle conflict
                await this.handleConflict(item, response.data);
            } else if (response.status >= 200 && response.status < 300) {
                console.log(`Successfully synced ${item.type} ${item.id}`);
            } else {
                throw new Error(`API returned status ${response.status}`);
            }
            
        } catch (error) {
            throw error;
        }
    }
    
    // Handle sync conflicts
    async handleConflict(item, conflictData) {
        console.log(`Handling conflict for item ${item.id}`);
        
        this.emit('conflictDetected', {
            item,
            serverData: conflictData.serverData,
            clientData: item.data
        });
        
        switch (this.conflictResolution) {
            case 'server-wins':
                console.log('Resolving conflict: server wins');
                // Update local data with server data
                break;
            case 'client-wins':
                console.log('Resolving conflict: client wins');
                // Force update server with client data
                await this.mockAPICall(`/api/items/${item.id}`, 'PUT', item.data);
                break;
            case 'manual':
                console.log('Conflict requires manual resolution');
                this.emit('manualResolutionRequired', {
                    item,
                    serverData: conflictData.serverData,
                    clientData: item.data
                });
                break;
        }
    }
    
    // Start automatic sync
    startAutoSync(intervalMs = 30000) {
        if (this.syncInterval) {
            clearInterval(this.syncInterval);
        }
        
        this.syncInterval = setInterval(() => {
            this.processSyncQueue();
        }, intervalMs);
        
        console.log(`Auto-sync started with ${intervalMs}ms interval`);
        this.emit('autoSyncStarted', { interval: intervalMs });
    }
    
    // Stop automatic sync
    stopAutoSync() {
        if (this.syncInterval) {
            clearInterval(this.syncInterval);
            this.syncInterval = null;
            console.log('Auto-sync stopped');
            this.emit('autoSyncStopped');
        }
    }
    
    // Force sync all pending items
    async forceSync() {
        console.log('Force sync requested');
        this.emit('forceSyncRequested');
        await this.processSyncQueue();
    }
    
    // Get sync status
    getSyncStatus() {
        return {
            status: this.syncStatus,
            queueLength: this.syncQueue.length,
            isProcessing: this.isProcessing,
            lastSyncTime: this.lastSyncTime,
            autoSyncActive: this.syncInterval !== null,
            conflictResolution: this.conflictResolution
        };
    }
    
    // Clear sync queue
    clearQueue() {
        const clearedCount = this.syncQueue.length;
        this.syncQueue = [];
        console.log(`Cleared ${clearedCount} items from sync queue`);
        this.emit('queueCleared', { clearedCount });
    }
    
    // Utility method
    delay(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }
}

// Data model for testing
class DataModel {
    constructor() {
        this.items = new Map();
        this.syncManager = new DataSyncManager();
        this.setupEventListeners();
    }
    
    setupEventListeners() {
        this.syncManager.on('itemSynced', (item) => {
            console.log(`✅ Item synced: ${item.type} ${item.id}`);
        });
        
        this.syncManager.on('itemFailed', ({ item, error }) => {
            console.log(`❌ Item failed: ${item.type} ${item.id} - ${error}`);
        });
        
        this.syncManager.on('conflictDetected', ({ item, serverData, clientData }) => {
            console.log(`⚠️ Conflict detected for item ${item.id}`);
            console.log('Server data:', serverData);
            console.log('Client data:', clientData);
        });
        
        this.syncManager.on('syncCompleted', ({ timestamp }) => {
            console.log(`🔄 Sync completed at ${timestamp}`);
        });
    }
    
    // Create item
    createItem(data) {
        const id = Date.now();
        const item = {
            id,
            ...data,
            createdAt: new Date().toISOString(),
            updatedAt: new Date().toISOString()
        };
        
        this.items.set(id, item);
        
        // Add to sync queue
        this.syncManager.addToSyncQueue({
            id,
            type: 'create',
            data: item
        });
        
        return item;
    }
    
    // Update item
    updateItem(id, updates) {
        const item = this.items.get(id);
        if (!item) {
            throw new Error(`Item ${id} not found`);
        }
        
        const updatedItem = {
            ...item,
            ...updates,
            updatedAt: new Date().toISOString()
        };
        
        this.items.set(id, updatedItem);
        
        // Add to sync queue
        this.syncManager.addToSyncQueue({
            id,
            type: 'update',
            data: updatedItem
        });
        
        return updatedItem;
    }
    
    // Delete item
    deleteItem(id) {
        const item = this.items.get(id);
        if (!item) {
            throw new Error(`Item ${id} not found`);
        }
        
        this.items.delete(id);
        
        // Add to sync queue
        this.syncManager.addToSyncQueue({
            id,
            type: 'delete',
            data: null
        });
        
        return true;
    }
    
    // Get item
    getItem(id) {
        return this.items.get(id);
    }
    
    // Get all items
    getAllItems() {
        return Array.from(this.items.values());
    }
    
    // Get sync manager
    getSyncManager() {
        return this.syncManager;
    }
}

// Test the data synchronization system
console.log("Testing data synchronization system...");

const dataModel = new DataModel();
const syncManager = dataModel.getSyncManager();

// Test 1: Create items
console.log("\n=== Test 1: Creating Items ===");
const item1 = dataModel.createItem({ name: 'Task 1', description: 'First task' });
const item2 = dataModel.createItem({ name: 'Task 2', description: 'Second task' });
const item3 = dataModel.createItem({ name: 'Task 3', description: 'Third task' });

console.log('Created items:', dataModel.getAllItems().length);

// Test 2: Update items
console.log("\n=== Test 2: Updating Items ===");
dataModel.updateItem(item1.id, { name: 'Updated Task 1', status: 'completed' });
dataModel.updateItem(item2.id, { status: 'in-progress' });

// Test 3: Delete item
console.log("\n=== Test 3: Deleting Item ===");
dataModel.deleteItem(item3.id);

// Test 4: Manual sync
console.log("\n=== Test 4: Manual Sync ===");
setTimeout(async () => {
    await syncManager.forceSync();
}, 1000);

// Test 5: Auto-sync
console.log("\n=== Test 5: Auto-Sync ===");
syncManager.startAutoSync(5000); // 5 second interval

// Test 6: Conflict resolution
console.log("\n=== Test 6: Conflict Resolution ===");
setTimeout(() => {
    syncManager.addToSyncQueue({
        id: 'conflict-test',
        type: 'update',
        data: { name: 'Conflicting data' }
    });
}, 2000);

// Test 7: Sync status monitoring
console.log("\n=== Test 7: Sync Status Monitoring ===");
setInterval(() => {
    const status = syncManager.getSyncStatus();
    console.log('Sync status:', status);
}, 3000);

// Test 8: Error handling
console.log("\n=== Test 8: Error Handling ===");
setTimeout(() => {
    syncManager.addToSyncQueue({
        id: 'error-test',
        type: 'update',
        data: { name: 'Error test' }
    });
}, 4000);

// Cleanup after 10 seconds
setTimeout(() => {
    syncManager.stopAutoSync();
    console.log('\n=== Test completed ===');
}, 10000);

console.log("\n=== API Data Synchronization System Summary ===");
console.log("✓ Data synchronization queue management");
console.log("✓ Automatic retry logic for failed syncs");
console.log("✓ Conflict detection and resolution strategies");
console.log("✓ Event-driven architecture with listeners");
console.log("✓ Auto-sync with configurable intervals");
console.log("✓ Manual sync and force sync capabilities");
console.log("✓ Sync status monitoring and reporting");
console.log("✓ Error handling and recovery mechanisms");
console.log("✓ Offline-first data management patterns");
console.log("✓ Real-world API integration scenarios");
