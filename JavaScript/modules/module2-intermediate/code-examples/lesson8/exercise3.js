// Exercise 3: Advanced Event Management System
// This exercise demonstrates a comprehensive event management system

console.log("=== Exercise 3: Advanced Event Management System ===");

// Advanced event emitter with priority and namespacing
class AdvancedEventEmitter {
    constructor() {
        this.events = {};
        this.maxListeners = 10;
        this.warnings = new Set();
    }
    
    addEventListener(event, handler, options = {}) {
        const { priority = 0, once = false, namespace = null } = options;
        
        if (!this.events[event]) {
            this.events[event] = [];
        }
        
        // Check max listeners limit
        if (this.events[event].length >= this.maxListeners) {
            if (!this.warnings.has(event)) {
                console.warn(`Max listeners (${this.maxListeners}) exceeded for event '${event}'`);
                this.warnings.add(event);
            }
        }
        
        const listener = {
            handler,
            priority,
            once,
            namespace,
            id: Date.now() + Math.random()
        };
        
        this.events[event].push(listener);
        
        // Sort by priority (higher priority first)
        this.events[event].sort((a, b) => b.priority - a.priority);
        
        console.log(`Event listener added for '${event}' with priority ${priority}`);
        return listener.id;
    }
    
    removeEventListener(event, listenerId) {
        if (this.events[event]) {
            const index = this.events[event].findIndex(listener => listener.id === listenerId);
            if (index > -1) {
                this.events[event].splice(index, 1);
                console.log(`Event listener removed for '${event}'`);
                return true;
            }
        }
        return false;
    }
    
    removeAllListeners(event) {
        if (event) {
            this.events[event] = [];
            console.log(`All listeners removed for '${event}'`);
        } else {
            this.events = {};
            console.log('All listeners removed');
        }
    }
    
    dispatchEvent(event, data = {}) {
        console.log(`Event '${event}' dispatched`);
        
        if (!this.events[event]) {
            return false;
        }
        
        const listeners = [...this.events[event]]; // Copy to avoid modification during iteration
        const toRemove = [];
        
        listeners.forEach(listener => {
            try {
                listener.handler({ ...data, event, emitter: this });
                
                if (listener.once) {
                    toRemove.push(listener.id);
                }
            } catch (error) {
                console.error(`Error in event listener for '${event}':`, error);
            }
        });
        
        // Remove once listeners
        toRemove.forEach(id => this.removeEventListener(event, id));
        
        return true;
    }
    
    emit(event, data) {
        return this.dispatchEvent(event, data);
    }
    
    on(event, handler, options) {
        return this.addEventListener(event, handler, options);
    }
    
    once(event, handler, options) {
        return this.addEventListener(event, handler, { ...options, once: true });
    }
    
    off(event, listenerId) {
        return this.removeEventListener(event, listenerId);
    }
    
    // Namespace management
    namespace(namespace) {
        return new EventNamespace(this, namespace);
    }
    
    // Event statistics
    getStats() {
        const stats = {
            totalEvents: Object.keys(this.events).length,
            totalListeners: 0,
            events: {}
        };
        
        for (const [event, listeners] of Object.entries(this.events)) {
            stats.events[event] = {
                listenerCount: listeners.length,
                priorities: listeners.map(l => l.priority),
                namespaces: [...new Set(listeners.map(l => l.namespace).filter(Boolean))]
            };
            stats.totalListeners += listeners.length;
        }
        
        return stats;
    }
}

// Event namespace helper
class EventNamespace {
    constructor(emitter, namespace) {
        this.emitter = emitter;
        this.namespace = namespace;
    }
    
    on(event, handler, options = {}) {
        return this.emitter.addEventListener(event, handler, { ...options, namespace: this.namespace });
    }
    
    once(event, handler, options = {}) {
        return this.emitter.addEventListener(event, handler, { ...options, namespace: this.namespace, once: true });
    }
    
    emit(event, data) {
        return this.emitter.dispatchEvent(event, data);
    }
    
    removeAll() {
        for (const [event, listeners] of Object.entries(this.emitter.events)) {
            this.emitter.events[event] = listeners.filter(l => l.namespace !== this.namespace);
        }
        console.log(`All listeners removed for namespace '${this.namespace}'`);
    }
}

// Application state manager with events
class StateManager extends AdvancedEventEmitter {
    constructor(initialState = {}) {
        super();
        this.state = { ...initialState };
        this.history = [];
        this.maxHistorySize = 50;
    }
    
    getState() {
        return { ...this.state };
    }
    
    setState(newState) {
        const previousState = { ...this.state };
        this.state = { ...this.state, ...newState };
        
        // Add to history
        this.history.push({
            timestamp: new Date().toISOString(),
            previous: previousState,
            current: { ...this.state }
        });
        
        // Limit history size
        if (this.history.length > this.maxHistorySize) {
            this.history.shift();
        }
        
        // Emit state change event
        this.emit('stateChanged', {
            previous: previousState,
            current: this.state,
            changes: this.getChanges(previousState, this.state)
        });
        
        console.log('State updated:', this.state);
    }
    
    getChanges(previous, current) {
        const changes = {};
        for (const key in current) {
            if (previous[key] !== current[key]) {
                changes[key] = {
                    from: previous[key],
                    to: current[key]
                };
            }
        }
        return changes;
    }
    
    subscribe(selector, handler) {
        // Subscribe to specific state changes
        return this.on('stateChanged', (event) => {
            const relevantChanges = {};
            for (const key in event.changes) {
                if (selector(key, event.changes[key])) {
                    relevantChanges[key] = event.changes[key];
                }
            }
            
            if (Object.keys(relevantChanges).length > 0) {
                handler(relevantChanges, event.current);
            }
        });
    }
    
    undo() {
        if (this.history.length > 0) {
            const lastState = this.history.pop();
            this.state = lastState.previous;
            
            this.emit('stateChanged', {
                previous: lastState.current,
                current: this.state,
                changes: this.getChanges(lastState.current, this.state),
                undo: true
            });
            
            console.log('State undone');
            return true;
        }
        return false;
    }
    
    getHistory() {
        return [...this.history];
    }
}

// Test the advanced event management system
console.log("Testing advanced event management system...");

const stateManager = new StateManager({ count: 0, name: 'Test' });

// Test 1: Basic event handling with priorities
console.log("\n=== Test 1: Event Handling with Priorities ===");

const listener1 = stateManager.on('stateChanged', (event) => {
    console.log('High priority listener:', event.changes);
}, { priority: 10 });

const listener2 = stateManager.on('stateChanged', (event) => {
    console.log('Low priority listener:', event.changes);
}, { priority: 1 });

const listener3 = stateManager.on('stateChanged', (event) => {
    console.log('Medium priority listener:', event.changes);
}, { priority: 5 });

// Change state to trigger events
stateManager.setState({ count: 1 });

// Test 2: Once listeners
console.log("\n=== Test 2: Once Listeners ===");

const onceListener = stateManager.once('stateChanged', (event) => {
    console.log('This will only fire once:', event.changes);
});

stateManager.setState({ count: 2 });
stateManager.setState({ count: 3 }); // This won't trigger the once listener

// Test 3: Namespace management
console.log("\n=== Test 3: Namespace Management ===");

const uiNamespace = stateManager.namespace('ui');
const apiNamespace = stateManager.namespace('api');

uiNamespace.on('stateChanged', (event) => {
    console.log('UI namespace listener:', event.changes);
});

apiNamespace.on('stateChanged', (event) => {
    console.log('API namespace listener:', event.changes);
});

stateManager.setState({ count: 4 });

// Test 4: Selective subscriptions
console.log("\n=== Test 4: Selective Subscriptions ===");

const countSubscription = stateManager.subscribe(
    (key, change) => key === 'count',
    (changes, currentState) => {
        console.log('Count changed:', changes.count);
    }
);

const nameSubscription = stateManager.subscribe(
    (key, change) => key === 'name',
    (changes, currentState) => {
        console.log('Name changed:', changes.name);
    }
);

stateManager.setState({ count: 5 });
stateManager.setState({ name: 'Updated' });
stateManager.setState({ count: 6, name: 'Final' });

// Test 5: Undo functionality
console.log("\n=== Test 5: Undo Functionality ===");

stateManager.setState({ count: 10, name: 'Before Undo' });
stateManager.setState({ count: 20, name: 'After Update' });

console.log('Current state:', stateManager.getState());
stateManager.undo();
console.log('After undo:', stateManager.getState());

// Test 6: Event statistics
console.log("\n=== Test 6: Event Statistics ===");

const stats = stateManager.getStats();
console.log('Event statistics:', stats);

// Test 7: Error handling
console.log("\n=== Test 7: Error Handling ===");

stateManager.on('stateChanged', () => {
    throw new Error('Intentional error for testing');
});

stateManager.on('stateChanged', (event) => {
    console.log('This listener should still work despite the error above');
});

stateManager.setState({ count: 7 });

// Test 8: Listener management
console.log("\n=== Test 8: Listener Management ===");

console.log('Removing specific listener...');
stateManager.off('stateChanged', listener1);

console.log('Removing all listeners for stateChanged...');
stateManager.removeAllListeners('stateChanged');

stateManager.setState({ count: 8 }); // Should not trigger any listeners

console.log("\n=== Advanced Event Management System Summary ===");
console.log("✓ Priority-based event handling");
console.log("✓ Once listeners and automatic cleanup");
console.log("✓ Namespace management for organized events");
console.log("✓ State management with change tracking");
console.log("✓ Selective subscriptions with custom selectors");
console.log("✓ Undo functionality with history tracking");
console.log("✓ Error handling and listener protection");
console.log("✓ Event statistics and monitoring");
console.log("✓ Advanced listener management and cleanup");
