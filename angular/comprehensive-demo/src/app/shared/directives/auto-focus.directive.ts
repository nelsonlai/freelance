/**
 * Auto Focus Directive
 * 
 * This directive automatically focuses an element when it's rendered.
 * Useful for:
 * - Focusing input fields in forms
 * - Focusing search boxes
 * - Improving accessibility
 * 
 * This demonstrates:
 * - Element manipulation
 * - Lifecycle hooks
 * - Focus management
 */

import { Directive, ElementRef, Input, AfterViewInit, OnDestroy } from '@angular/core';

@Directive({
  selector: '[appAutoFocus]',
  standalone: true
})
export class AutoFocusDirective implements AfterViewInit, OnDestroy {
  /**
   * Input to control when to focus
   * If true, element will be focused
   */
  @Input() appAutoFocus: boolean = true;

  /**
   * Delay before focusing (in milliseconds)
   * Useful for animations or when element is not immediately ready
   */
  @Input() focusDelay: number = 0;

  /**
   * Timeout reference for cleanup
   */
  private timeoutId: any;

  /**
   * Constructor
   */
  constructor(private elementRef: ElementRef) {}

  /**
   * Lifecycle hook - called after view is initialized
   * 
   * AfterViewInit is used instead of OnInit because we need
   * the element to be in the DOM before we can focus it.
   */
  ngAfterViewInit(): void {
    if (this.appAutoFocus) {
      // Use setTimeout to ensure element is fully rendered
      this.timeoutId = setTimeout(() => {
        const element = this.elementRef.nativeElement;
        
        // Check if element is focusable
        if (element && typeof element.focus === 'function') {
          element.focus();
        }
      }, this.focusDelay);
    }
  }

  /**
   * Lifecycle hook - cleanup
   */
  ngOnDestroy(): void {
    if (this.timeoutId) {
      clearTimeout(this.timeoutId);
    }
  }
}

