/**
 * Currency Format Pipe
 * 
 * Custom pipe for formatting currency values.
 * This is a simple example - Angular's built-in CurrencyPipe is more feature-rich.
 * 
 * This demonstrates:
 * - Custom formatting logic
 * - Parameter handling
 * - Default values
 */

import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'currencyFormat',
  standalone: true
})
export class CurrencyFormatPipe implements PipeTransform {
  /**
   * Format a number as currency
   * 
   * @param value - Numeric value to format
   * @param currency - Currency code (default: 'USD')
   * @param symbol - Currency symbol (default: '$')
   * @returns Formatted currency string
   * 
   * @example
   * 1234.56 | currencyFormat -> '$1,234.56'
   * 1234.56 | currencyFormat:'EUR':'€' -> '€1,234.56'
   */
  transform(value: number | null | undefined, currency: string = 'USD', symbol: string = '$'): string {
    if (value === null || value === undefined || isNaN(value)) {
      return `${symbol}0.00`;
    }

    // Format number with commas and 2 decimal places
    const formatted = value.toFixed(2).replace(/\B(?=(\d{3})+(?!\d))/g, ',');
    return `${symbol}${formatted}`;
  }
}

