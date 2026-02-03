import { Component, Input, Output, EventEmitter } from '@angular/core';

export interface Task {
  id: number;
  title: string;
  complete: boolean;
}

@Component({
  selector: 'app-task-list',
  standalone: true,
  template: `
    <section>
      <h2>{{ heading }}</h2>
      <ul>
        <li *ngFor="let task of tasks; trackBy: trackById">
          <label [class.complete]="task.complete">
            <input
              type="checkbox"
              [checked]="task.complete"
              (change)="toggle.emit(task.id)"
            />
            {{ task.title }}
          </label>
        </li>
      </ul>
      <button type="button" (click)="add.emit()">Add Task</button>
    </section>
  `,
  styles: [
    `
      h2 {
        margin-bottom: 0.5rem;
      }
      label.complete {
        text-decoration: line-through;
        color: #6b7280;
      }
    `,
  ],
})
export class TaskListComponent {
  @Input() heading = 'Tasks';
  @Input() tasks: Task[] = [];
  @Output() toggle = new EventEmitter<number>();
  @Output() add = new EventEmitter<void>();

  trackById = (_: number, task: Task) => task.id;
}
