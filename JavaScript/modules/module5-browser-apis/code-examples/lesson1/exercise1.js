// Exercise 1: Responsive Design Helper
class ResponsiveHelper {
    constructor() {
        this.breakpoints = {
            mobile: 768,
            tablet: 1024,
            desktop: 1200
        };
        
        this.currentBreakpoint = this.getCurrentBreakpoint();
        this.setupResizeListener();
    }
    
    getCurrentBreakpoint() {
        const width = window.innerWidth;
        
        if (width < this.breakpoints.mobile) return 'mobile';
        if (width < this.breakpoints.tablet) return 'tablet';
        if (width < this.breakpoints.desktop) return 'desktop';
        return 'large';
    }
    
    setupResizeListener() {
        window.addEventListener('resize', () => {
            const newBreakpoint = this.getCurrentBreakpoint();
            if (newBreakpoint !== this.currentBreakpoint) {
                const oldBreakpoint = this.currentBreakpoint;
                this.currentBreakpoint = newBreakpoint;
                this.onBreakpointChange(oldBreakpoint, newBreakpoint);
            }
        });
    }
    
    onBreakpointChange(oldBreakpoint, newBreakpoint) {
        console.log(`Breakpoint changed: ${oldBreakpoint} → ${newBreakpoint}`);
        
        // Dispatch custom event
        window.dispatchEvent(new CustomEvent('breakpointChange', {
            detail: { oldBreakpoint, newBreakpoint }
        }));
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

// Usage
const responsive = new ResponsiveHelper();

window.addEventListener('breakpointChange', (event) => {
    const { oldBreakpoint, newBreakpoint } = event.detail;
    console.log(`Responsive change: ${oldBreakpoint} → ${newBreakpoint}`);
});
