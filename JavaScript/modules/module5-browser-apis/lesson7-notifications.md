# Lesson 7: Notifications API

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Request notification permissions from users
- Send browser notifications
- Handle notification events (click, close, error)
- Create rich notifications with icons and actions
- Manage notification permissions and states
- Implement notification-based features

## 📚 Notifications API Basics

### Requesting Permission
```javascript
async function requestNotificationPermission() {
    if ('Notification' in window) {
        const permission = await Notification.requestPermission();
        return permission === 'granted';
    }
    return false;
}
```

### Sending Notifications
```javascript
function sendNotification(title, options = {}) {
    if (Notification.permission === 'granted') {
        const notification = new Notification(title, {
            body: options.body || '',
            icon: options.icon || '/icon.png',
            badge: options.badge || '/badge.png',
            tag: options.tag || 'default',
            requireInteraction: options.requireInteraction || false
        });
        
        notification.onclick = () => {
            console.log('Notification clicked');
            notification.close();
        };
        
        return notification;
    }
}
```

## 🎯 Practice Exercises

### Exercise 1: Notification Manager
Create a comprehensive notification system:

**Solution:**
```javascript
class NotificationManager {
    constructor() {
        this.permission = Notification.permission;
        this.notifications = new Map();
    }
    
    async requestPermission() {
        if (!('Notification' in window)) {
            console.error('Notifications not supported');
            return false;
        }
        
        if (this.permission === 'default') {
            this.permission = await Notification.requestPermission();
        }
        
        return this.permission === 'granted';
    }
    
    sendNotification(title, options = {}) {
        if (this.permission !== 'granted') {
            console.error('Notification permission not granted');
            return null;
        }
        
        const notification = new Notification(title, {
            body: options.body || '',
            icon: options.icon || '/default-icon.png',
            badge: options.badge || '/default-badge.png',
            tag: options.tag || 'default',
            requireInteraction: options.requireInteraction || false,
            silent: options.silent || false,
            timestamp: Date.now()
        });
        
        this.setupNotificationEvents(notification, options);
        this.notifications.set(notification.tag, notification);
        
        return notification;
    }
    
    setupNotificationEvents(notification, options) {
        notification.onclick = (event) => {
            if (options.onClick) {
                options.onClick(event);
            }
            notification.close();
        };
        
        notification.onclose = (event) => {
            if (options.onClose) {
                options.onClose(event);
            }
            this.notifications.delete(notification.tag);
        };
        
        notification.onerror = (event) => {
            if (options.onError) {
                options.onError(event);
            }
            console.error('Notification error:', event);
        };
    }
    
    closeNotification(tag) {
        const notification = this.notifications.get(tag);
        if (notification) {
            notification.close();
        }
    }
    
    closeAllNotifications() {
        this.notifications.forEach(notification => {
            notification.close();
        });
        this.notifications.clear();
    }
    
    getActiveNotifications() {
        return Array.from(this.notifications.keys());
    }
}

// Usage
const notificationManager = new NotificationManager();

// Request permission and send notification
notificationManager.requestPermission().then(granted => {
    if (granted) {
        notificationManager.sendNotification('Hello!', {
            body: 'This is a test notification',
            icon: '/icon.png',
            tag: 'test',
            onClick: () => console.log('Test notification clicked')
        });
    }
});
```

## 🎯 Key Takeaways

1. **Notifications API** enables browser notifications
2. **Permission handling** is required for notifications
3. **Event handling** for user interaction
4. **Rich notifications** with icons and actions
5. **User experience** considerations for notifications

---

**Next Lesson**: [Lesson 8: Animations with requestAnimationFrame](./lesson8-animations.md)
