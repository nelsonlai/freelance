// @ts-nocheck
import { Directive, Input, TemplateRef, ViewContainerRef } from '@angular/core';

@Directive({
  selector: '[appIfViewport]',
  standalone: true,
})
export class IfViewportDirective {
  private hasView = false;
  private minWidth = 768;

  constructor(private templateRef: TemplateRef<unknown>, private viewContainer: ViewContainerRef) {}

  @Input()
  set appIfViewport(minWidth: number) {
    this.minWidth = minWidth || 768;
    this.updateView();
  }

  ngOnInit(): void {
    this.updateView();
    window.addEventListener('resize', this.updateView);
  }

  ngOnDestroy(): void {
    window.removeEventListener('resize', this.updateView);
  }

  private updateView = () => {
    const shouldShow = window.innerWidth >= this.minWidth;
    if (shouldShow && !this.hasView) {
      this.viewContainer.createEmbeddedView(this.templateRef);
      this.hasView = true;
    } else if (!shouldShow && this.hasView) {
      this.viewContainer.clear();
      this.hasView = false;
    }
  };
}
