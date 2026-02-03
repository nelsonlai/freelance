import { Component, inject } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { AuthService } from './auth.service';

@Component({
  selector: 'app-root',
  imports: [RouterOutlet],
  templateUrl: './app.component.html',
  styleUrl: './app.component.scss'
})
export class AppComponent {
  title = 'week05-06';
  private auth = inject(AuthService);

  constructor() {
    // Auto-login for development/demo purposes
    this.auth.login();
  }
}

