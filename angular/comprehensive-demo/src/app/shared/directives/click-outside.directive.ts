/**
 * Click Outside Directive
 * 
 * This directive detects clicks outside the host element.
 * Useful for:
 * - Closing dropdowns when clicking outside
 * - Closing modals
 * - Closing context menus
 * - Any UI element that should close on outside click
 * 
 * This demonstrates:
 * - Event handling
 * - DOM manipulation
 * - Event propagation control
 */

import { Directive, ElementRef, EventEmitter, HostListener, Output, OnInit, OnDestroy } from '@angular/core';

@Directive({
  selector: '[appClickOutside]',
  standalone: true
})
export class ClickOutsideDirective implements OnInit, OnDestroy {
  /**
   * Output event - emits when click outside is detected
   * 
   * @Output() makes this an event that parent components can listen to
   * 
   * Usage: <div (appClickOutside)="handleClickOutside()">Content</div>
   */
  @Output() appClickOutside = new EventEmitter<void>();

  /**
   * Constructor
   * 
   * ElementRef provides access to the host element
   */
  constructor(private elementRef: ElementRef) {}

  /**
   * Lifecycle hook
   */
  ngOnInit(): void {
    // Any initialization code
  }

  /**
   * Lifecycle hook
   */
  ngOnDestroy(): void {
    // Cleanup if needed
  }

  /**
   * Listen to document click events
   * 
   * @param event - Click event
   */
  @HostListener('document:click', ['$event'])
  onClick(event: MouseEvent): void {
    // Check if click was outside the element
    const clickedInside = this.elementRef.nativeElement.contains(event.target);

    if (!clickedInside) {
      // Click was outside, emit event
      this.appClickOutside.emit();
    }
  }
}

