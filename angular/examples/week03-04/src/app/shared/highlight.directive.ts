// @ts-nocheck
import { Directive, ElementRef, HostListener, Input, Renderer2 } from '@angular/core';

@Directive({
  selector: '[appHighlight]',
  standalone: true,
})
export class HighlightDirective {
  @Input('appHighlight') highlightColor = '#fde68a';
  @Input() appHighlightHoverColor = '#facc15';

  private defaultBackground = 'transparent';

  constructor(private element: ElementRef<HTMLElement>, private renderer: Renderer2) {}

  ngOnInit(): void {
    this.defaultBackground = getComputedStyle(this.element.nativeElement).backgroundColor;
    this.applyColor(this.highlightColor);
  }

  @HostListener('mouseenter') onEnter(): void {
    this.applyColor(this.appHighlightHoverColor);
  }

  @HostListener('mouseleave') onLeave(): void {
    this.applyColor(this.highlightColor);
  }

  private applyColor(color: string): void {
    this.renderer.setStyle(this.element.nativeElement, 'backgroundColor', color);
    this.renderer.setStyle(this.element.nativeElement, 'transition', 'background-color 150ms ease');
  }
}
