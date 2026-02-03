/**
 * Truncate Pipe
 * 
 * Custom pipes in Angular transform data for display in templates.
 * 
 * Pipe Types:
 * - Pure pipes: Only recalculate when input changes (default, more efficient)
 * - Impure pipes: Recalculate on every change detection cycle
 * 
 * This pipe truncates text to a specified length and adds ellipsis.
 * 
 * Usage in template:
 * {{ longText | truncate:50 }}
 * {{ longText | truncate:50:'...' }}
 */

import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'truncate',
  // pure: true is the default (only recalculates when input changes)
  // Set to false if you need it to recalculate on every change detection
  standalone: true // Standalone pipe (Angular 14+)
})
export class TruncatePipe implements PipeTransform {
  /**
   * Transform method - required by PipeTransform interface
   * 
   * @param value - Input value to transform
   * @param limit - Maximum length before truncation
   * @param trail - String to append when truncated (default: '...')
   * @returns Truncated string
   * 
   * @example
   * 'Hello World' | truncate:5 -> 'Hello...'
   * 'Hello World' | truncate:5:'***' -> 'Hello***'
   */
  transform(value: string | null | undefined, limit: number = 20, trail: string = '...'): string {
    // Handle null/undefined values
    if (!value) {
      return '';
    }

    // If value is shorter than limit, return as-is
    if (value.length <= limit) {
      return value;
    }

    // Truncate and add trail
    return value.substring(0, limit) + trail;
  }
}

