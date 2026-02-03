// Exercise 3: Device Information Display
class DeviceInfo {
    constructor() {
        this.info = this.gatherDeviceInfo();
    }
    
    gatherDeviceInfo() {
        return {
            userAgent: navigator.userAgent,
            platform: navigator.platform,
            language: navigator.language,
            languages: navigator.languages,
            online: navigator.onLine,
            cookieEnabled: navigator.cookieEnabled,
            doNotTrack: navigator.doNotTrack,
            hardwareConcurrency: navigator.hardwareConcurrency,
            screenWidth: screen.width,
            screenHeight: screen.height,
            windowWidth: window.innerWidth,
            windowHeight: window.innerHeight,
            colorDepth: screen.colorDepth,
            pixelDepth: screen.pixelDepth,
            timezone: Intl.DateTimeFormat().resolvedOptions().timeZone
        };
    }
    
    displayInfo(containerId) {
        const container = document.getElementById(containerId);
        const infoHtml = Object.entries(this.info)
            .map(([key, value]) => `<div><strong>${key}:</strong> ${value}</div>`)
            .join('');
        
        container.innerHTML = `
            <h3>Device Information</h3>
            <div class="device-info">${infoHtml}</div>
        `;
    }
    
    isMobile() {
        return /Android|webOS|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent);
    }
    
    isTouchDevice() {
        return 'ontouchstart' in window || navigator.maxTouchPoints > 0;
    }
    
    getConnectionInfo() {
        if ('connection' in navigator) {
            const connection = navigator.connection;
            return {
                effectiveType: connection.effectiveType,
                downlink: connection.downlink,
                rtt: connection.rtt,
                saveData: connection.saveData
            };
        }
        return null;
    }
}

// Usage
const deviceInfo = new DeviceInfo();
deviceInfo.displayInfo('deviceInfoContainer');

console.log('Is mobile:', deviceInfo.isMobile());
console.log('Is touch device:', deviceInfo.isTouchDevice());
console.log('Connection info:', deviceInfo.getConnectionInfo());
