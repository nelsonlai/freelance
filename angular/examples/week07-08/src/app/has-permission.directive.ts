// @ts-nocheck
import { Directive, Input, TemplateRef, ViewContainerRef } from '@angular/core';
import { AuthHttpService } from './auth-http.service';

@Directive({
  selector: '[appHasPermission]',
  standalone: true,
})
export class HasPermissionDirective {
  private hasView = false;

  constructor(
    private templateRef: TemplateRef<unknown>,
    private viewContainer: ViewContainerRef,
    private auth: AuthHttpService,
  ) {}

  @Input()
  set appHasPermission(role: string) {
    const allowed = this.auth.hasRole(role);
    if (allowed && !this.hasView) {
      this.viewContainer.createEmbeddedView(this.templateRef);
      this.hasView = true;
    } else if (!allowed && this.hasView) {
      this.viewContainer.clear();
      this.hasView = false;
    }
  }
}
