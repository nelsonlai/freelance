/**
 * Filter Pipe
 * 
 * Custom pipe for filtering arrays.
 * 
 * Note: This is an impure pipe because it needs to recalculate
 * when the array changes. Be careful with performance on large arrays.
 * 
 * For better performance with large datasets, consider filtering
 * in the component or using a service.
 */

import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'filter',
  // Impure pipe - recalculates on every change detection
  // Use with caution on large arrays
  pure: false,
  standalone: true
})
export class FilterPipe implements PipeTransform {
  /**
   * Filter array based on search term
   * 
   * @param items - Array to filter
   * @param searchTerm - Term to search for
   * @param property - Property name to search in (optional)
   * @returns Filtered array
   * 
   * @example
   * users | filter:'john' -> filters users where any property contains 'john'
   * users | filter:'john':'name' -> filters users where name contains 'john'
   */
  transform<T>(items: T[] | null | undefined, searchTerm: string, property?: string): T[] {
    if (!items || !searchTerm) {
      return items || [];
    }

    const term = searchTerm.toLowerCase();

    return items.filter(item => {
      if (property) {
        // Search in specific property
        const value = (item as any)[property];
        return value && value.toString().toLowerCase().includes(term);
      } else {
        // Search in all properties
        return Object.values(item as any).some(value =>
          value && value.toString().toLowerCase().includes(term)
        );
      }
    });
  }
}

