/**
 * Cookie Service
 * 
 * This service provides methods to manage browser cookies.
 * 
 * Cookies vs LocalStorage/SessionStorage:
 * - Cookies are sent with every HTTP request (including to server)
 * - Cookies have size limit (~4KB) vs ~5-10MB for storage APIs
 * - Cookies can be set with expiration dates
 * - Cookies can be restricted to specific paths and domains
 * - Cookies support HttpOnly and Secure flags for security
 * 
 * Use Cases:
 * - Authentication tokens (though HttpOnly cookies are more secure)
 * - User preferences that need to be sent to server
 * - Tracking/analytics (with user consent)
 * - CSRF tokens
 * - Language/locale preferences
 * 
 * Security Considerations:
 * - Never store sensitive data in cookies without encryption
 * - Use HttpOnly flag to prevent JavaScript access (XSS protection)
 * - Use Secure flag for HTTPS-only transmission
 * - Use SameSite attribute to prevent CSRF attacks
 */

import { Injectable } from '@angular/core';
import { environment } from '../../../../environments/environment';

/**
 * Cookie Options Interface
 * 
 * Defines options for setting cookies
 */
export interface CookieOptions {
  /**
   * Expiration date/time for the cookie
   * If not set, cookie expires when browser closes (session cookie)
   */
  expires?: Date | number; // Date object or days from now

  /**
   * Path where cookie is available
   * Default: '/' (entire domain)
   */
  path?: string;

  /**
   * Domain where cookie is available
   * Default: current domain
   */
  domain?: string;

  /**
   * If true, cookie is only sent over HTTPS
   * Important for security in production
   */
  secure?: boolean;

  /**
   * If true, cookie is not accessible via JavaScript (HttpOnly)
   * Note: This can only be set server-side, not from JavaScript
   */
  httpOnly?: boolean;

  /**
   * SameSite attribute to prevent CSRF attacks
   * 'strict': Cookie not sent on cross-site requests
   * 'lax': Cookie sent on top-level navigation (default in modern browsers)
   * 'none': Cookie sent on all requests (requires Secure flag)
   */
  sameSite?: 'strict' | 'lax' | 'none';
}

@Injectable({
  providedIn: 'root'
})
export class CookieService {
  private readonly prefix: string = environment.storage.cookiePrefix;

  /**
   * Set a cookie
   * 
   * @param key - Cookie name (without prefix)
   * @param value - Cookie value
   * @param options - Cookie options (expiration, path, etc.)
   * 
   * @example
   * // Set a cookie that expires in 7 days
   * this.cookieService.set('user_pref', 'dark_mode', { expires: 7 });
   * 
   * @example
   * // Set a secure cookie
   * this.cookieService.set('token', 'abc123', { secure: true, sameSite: 'strict' });
   */
  set(key: string, value: string, options: CookieOptions = {}): void {
    const prefixedKey = `${this.prefix}${key}`;
    let cookieString = `${this.encode(prefixedKey)}=${this.encode(value)}`;

    // Handle expiration
    if (options.expires) {
      let expiresDate: Date;
      
      if (typeof options.expires === 'number') {
        // If number, treat as days from now
        expiresDate = new Date();
        expiresDate.setTime(expiresDate.getTime() + (options.expires * 24 * 60 * 60 * 1000));
      } else {
        expiresDate = options.expires;
      }
      
      cookieString += `; expires=${expiresDate.toUTCString()}`;
    }

    // Handle path
    if (options.path) {
      cookieString += `; path=${options.path}`;
    } else {
      cookieString += `; path=/`;
    }

    // Handle domain
    if (options.domain) {
      cookieString += `; domain=${options.domain}`;
    }

    // Handle secure flag
    if (options.secure) {
      cookieString += `; secure`;
    }

    // Handle SameSite
    if (options.sameSite) {
      cookieString += `; samesite=${options.sameSite}`;
    }

    // Note: httpOnly cannot be set from JavaScript for security reasons
    // It must be set server-side via Set-Cookie header

    document.cookie = cookieString;
  }

  /**
   * Get a cookie value
   * 
   * @param key - Cookie name (without prefix)
   * @returns Cookie value or null if not found
   * 
   * @example
   * const theme = this.cookieService.get('theme'); // Returns 'dark' or null
   */
  get(key: string): string | null {
    const prefixedKey = `${this.prefix}${key}`;
    const nameEQ = `${this.encode(prefixedKey)}=`;
    const cookies = document.cookie.split(';');

    for (let i = 0; i < cookies.length; i++) {
      let cookie = cookies[i];
      while (cookie.charAt(0) === ' ') {
        cookie = cookie.substring(1, cookie.length);
      }
      if (cookie.indexOf(nameEQ) === 0) {
        return this.decode(cookie.substring(nameEQ.length, cookie.length));
      }
    }

    return null;
  }

  /**
   * Remove a cookie
   * 
   * This is done by setting the cookie with an expiration date in the past
   * 
   * @param key - Cookie name (without prefix)
   * @param options - Options (path, domain) must match original cookie
   * 
   * @example
   * this.cookieService.remove('user_pref');
   */
  remove(key: string, options: Pick<CookieOptions, 'path' | 'domain'> = {}): void {
    const prefixedKey = `${this.prefix}${key}`;
    let cookieString = `${this.encode(prefixedKey)}=; expires=Thu, 01 Jan 1970 00:00:00 UTC`;

    if (options.path) {
      cookieString += `; path=${options.path}`;
    } else {
      cookieString += `; path=/`;
    }

    if (options.domain) {
      cookieString += `; domain=${options.domain}`;
    }

    document.cookie = cookieString;
  }

  /**
   * Check if a cookie exists
   * 
   * @param key - Cookie name (without prefix)
   * @returns true if cookie exists, false otherwise
   */
  has(key: string): boolean {
    return this.get(key) !== null;
  }

  /**
   * Get all cookies as an object
   * 
   * @returns Object with cookie names as keys and values as values
   */
  getAll(): { [key: string]: string } {
    const cookies: { [key: string]: string } = {};
    const cookieArray = document.cookie.split(';');

    for (let i = 0; i < cookieArray.length; i++) {
      const cookie = cookieArray[i].trim();
      if (cookie) {
        const [name, value] = cookie.split('=');
        const decodedName = this.decode(name);
        
        // Only include cookies with our prefix
        if (decodedName.startsWith(this.prefix)) {
          const key = decodedName.substring(this.prefix.length);
          cookies[key] = this.decode(value);
        }
      }
    }

    return cookies;
  }

  /**
   * Encode a cookie value to handle special characters
   * 
   * @param value - Value to encode
   * @returns Encoded value
   */
  private encode(value: string): string {
    return encodeURIComponent(value);
  }

  /**
   * Decode a cookie value
   * 
   * @param value - Value to decode
   * @returns Decoded value
   */
  private decode(value: string): string {
    return decodeURIComponent(value);
  }
}

