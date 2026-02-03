// Lesson 1: Window, Navigator, History APIs Examples

console.log("=== Window API Examples ===");

// Window dimensions
console.log('Window size:', window.innerWidth, 'x', window.innerHeight);
console.log('Screen size:', screen.width, 'x', screen.height);
console.log('Window position:', window.screenX, window.screenY);
console.log('Scroll position:', window.scrollX, window.scrollY);

// Window events
window.addEventListener('resize', () => {
    console.log('Window resized:', window.innerWidth, 'x', window.innerHeight);
});

window.addEventListener('scroll', () => {
    console.log('Scroll position:', window.scrollY);
});

console.log("\n=== Navigator API Examples ===");

// Device information
console.log('User Agent:', navigator.userAgent);
console.log('Platform:', navigator.platform);
console.log('Language:', navigator.language);
console.log('Languages:', navigator.languages);
console.log('Online:', navigator.onLine);
console.log('Cookies enabled:', navigator.cookieEnabled);
console.log('Do not track:', navigator.doNotTrack);

// Device capabilities
console.log('CPU cores:', navigator.hardwareConcurrency);

if ('memory' in performance) {
    console.log('Device memory:', performance.memory);
}

if ('connection' in navigator) {
    const connection = navigator.connection;
    console.log('Connection type:', connection.effectiveType);
    console.log('Downlink:', connection.downlink);
    console.log('RTT:', connection.rtt);
}

console.log("\n=== History API Examples ===");

console.log('History length:', history.length);

// Listen for popstate events
window.addEventListener('popstate', (event) => {
    console.log('State:', event.state);
    console.log('URL:', window.location.href);
});

// Example navigation (commented out to avoid actual navigation)
// history.pushState({ page: 'home' }, 'Home', '/home');
// history.replaceState({ page: 'about' }, 'About', '/about');

console.log("\n=== Responsive Helper Example ===");

class ResponsiveHelper {
    constructor() {
        this.breakpoints = {
            mobile: 768,
            tablet: 1024,
            desktop: 1200
        };
        
        this.currentBreakpoint = this.getCurrentBreakpoint();
        console.log('Current breakpoint:', this.currentBreakpoint);
    }
    
    getCurrentBreakpoint() {
        const width = window.innerWidth;
        
        if (width < this.breakpoints.mobile) return 'mobile';
        if (width < this.breakpoints.tablet) return 'tablet';
        if (width < this.breakpoints.desktop) return 'desktop';
        return 'large';
    }
    
    isMobile() {
        return this.currentBreakpoint === 'mobile';
    }
    
    isTablet() {
        return this.currentBreakpoint === 'tablet';
    }
    
    isDesktop() {
        return this.currentBreakpoint === 'desktop' || this.currentBreakpoint === 'large';
    }
}

const responsive = new ResponsiveHelper();
console.log('Is mobile:', responsive.isMobile());
console.log('Is tablet:', responsive.isTablet());
console.log('Is desktop:', responsive.isDesktop());
