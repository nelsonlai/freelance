/**
 * Highlight Directive
 * 
 * Custom directives in Angular allow you to:
 * - Manipulate the DOM
 * - Add behavior to elements
 * - Create reusable UI components
 * 
 * Directive Types:
 * - Component directives: Components with templates
 * - Structural directives: Modify DOM structure (*ngIf, *ngFor)
 * - Attribute directives: Modify element appearance/behavior
 * 
 * This is an attribute directive that highlights an element
 * when the mouse hovers over it.
 */

import { Directive, ElementRef, HostListener, Input, Renderer2, OnInit, OnDestroy } from '@angular/core';

@Directive({
  selector: '[appHighlight]',
  standalone: true
})
export class HighlightDirective implements OnInit, OnDestroy {
  /**
   * Input property - allows parent to pass data to directive
   * 
   * @Input() makes this property bindable from the template
   * 
   * Usage: <div [appHighlight]="'yellow'">Content</div>
   */
  @Input() appHighlight: string = 'yellow';

  /**
   * Default highlight color
   */
  @Input() defaultColor: string = 'transparent';

  /**
   * Current background color
   */
  private currentColor: string = '';

  /**
   * Constructor with Dependency Injection
   * 
   * ElementRef: Reference to the DOM element
   * Renderer2: Safe way to manipulate DOM (works with SSR)
   */
  constructor(
    private el: ElementRef,
    private renderer: Renderer2
  ) {}

  /**
   * Lifecycle hook - called after directive is initialized
   */
  ngOnInit(): void {
    // Set initial background color
    this.currentColor = this.defaultColor;
    this.setBackgroundColor(this.currentColor);
  }

  /**
   * Lifecycle hook - called when directive is destroyed
   */
  ngOnDestroy(): void {
    // Cleanup if needed
    this.setBackgroundColor('');
  }

  /**
   * HostListener - listens to DOM events on the host element
   * 
   * @HostListener('eventName') decorator listens to events
   * 
   * This listens to mouseenter event
   */
  @HostListener('mouseenter') onMouseEnter(): void {
    // Change background color on hover
    this.setBackgroundColor(this.appHighlight || 'yellow');
  }

  /**
   * HostListener for mouseleave event
   */
  @HostListener('mouseleave') onMouseLeave(): void {
    // Restore original background color
    this.setBackgroundColor(this.defaultColor);
  }

  /**
   * Set background color using Renderer2
   * 
   * Renderer2 is the safe way to manipulate DOM in Angular.
   * It works with:
   * - Server-side rendering (SSR)
   * - Web Workers
   * - Native mobile apps
   * 
   * @param color - Color to set
   */
  private setBackgroundColor(color: string): void {
    this.renderer.setStyle(this.el.nativeElement, 'background-color', color);
  }
}

