/**
 * RxJS Demo Component
 * 
 * Demonstrates RxJS Observables and operators:
 * - Creating observables
 * - Subscribing to observables
 * - Operators (map, filter, debounceTime, etc.)
 * - Subject and BehaviorSubject
 * - Error handling
 */

import { Component, OnInit, OnDestroy } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { Subject, BehaviorSubject, Observable, of, from, interval, timer } from 'rxjs';
import { map, filter, debounceTime, distinctUntilChanged, take, catchError } from 'rxjs/operators';

@Component({
  selector: 'app-rxjs-demo',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './rxjs-demo.component.html',
  styleUrls: ['./rxjs-demo.component.scss']
})
export class RxjsDemoComponent implements OnInit, OnDestroy {
  // Observable examples
  simpleObservable$: Observable<number> = of(1, 2, 3, 4, 5);
  arrayObservable$: Observable<number> = from([10, 20, 30, 40, 50]);
  intervalObservable$: Observable<number> = interval(1000).pipe(take(10));
  timerObservable$: Observable<number> = timer(2000, 1000).pipe(take(5));

  // Subject examples
  private subject = new Subject<string>();
  subjectMessages: string[] = [];

  // BehaviorSubject example
  private behaviorSubject = new BehaviorSubject<number>(0);
  behaviorSubjectValue$ = this.behaviorSubject.asObservable();
  currentBehaviorValue = 0;

  // Search with debounce
  searchTerm = '';
  searchResults: string[] = [];
  private searchSubject = new Subject<string>();

  // Counter
  counter = 0;
  private counterSubscription: any;

  ngOnInit(): void {
    // Subscribe to subject
    this.subject.subscribe(message => {
      this.subjectMessages.push(message);
    });

    // Subscribe to behavior subject
    this.behaviorSubject.subscribe(value => {
      this.currentBehaviorValue = value;
    });

    // Search with debounce
    this.searchSubject.pipe(
      debounceTime(300),
      distinctUntilChanged(),
      map(term => this.performSearch(term))
    ).subscribe(results => {
      this.searchResults = results;
    });
  }

  ngOnDestroy(): void {
    if (this.counterSubscription) {
      this.counterSubscription.unsubscribe();
    }
  }

  // Observable examples
  runSimpleObservable(): void {
    this.simpleObservable$.subscribe(value => {
      console.log('Simple Observable:', value);
    });
  }

  runArrayObservable(): void {
    this.arrayObservable$.pipe(
      map(x => x * 2),
      filter(x => x > 50)
    ).subscribe(value => {
      console.log('Array Observable (transformed):', value);
    });
  }

  runIntervalObservable(): void {
    this.intervalObservable$.subscribe(value => {
      console.log('Interval Observable:', value);
    });
  }

  // Subject examples
  sendSubjectMessage(): void {
    this.subject.next(`Message ${Date.now()}`);
  }

  // BehaviorSubject examples
  incrementBehaviorSubject(): void {
    this.behaviorSubject.next(this.currentBehaviorValue + 1);
  }

  decrementBehaviorSubject(): void {
    this.behaviorSubject.next(this.currentBehaviorValue - 1);
  }

  // Search example
  onSearchChange(): void {
    this.searchSubject.next(this.searchTerm);
  }

  private performSearch(term: string): string[] {
    if (!term) return [];
    const items = ['Apple', 'Banana', 'Cherry', 'Date', 'Elderberry'];
    return items.filter(item => item.toLowerCase().includes(term.toLowerCase()));
  }

  // Counter example
  startCounter(): void {
    this.counter = 0;
    this.counterSubscription = interval(1000).subscribe(() => {
      this.counter++;
    });
  }

  stopCounter(): void {
    if (this.counterSubscription) {
      this.counterSubscription.unsubscribe();
    }
  }
}

