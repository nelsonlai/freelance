export interface PasswordGeneratorOptions {
  length: number;
  includeUppercase: boolean;
  includeLowercase: boolean;
  includeNumbers: boolean;
  includeSymbols: boolean;
}

export class PasswordGenerator {
  private static readonly UPPERCASE = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
  private static readonly LOWERCASE = 'abcdefghijklmnopqrstuvwxyz';
  private static readonly NUMBERS = '0123456789';
  private static readonly SYMBOLS = '!@#$%^&*()_+-=[]{}|;:,.<>?';

  static generatePassword(options: PasswordGeneratorOptions): string {
    const {
      length,
      includeUppercase,
      includeLowercase,
      includeNumbers,
      includeSymbols
    } = options;

    // Ensure at least one character from each enabled class
    let password = '';
    let availableChars = '';

    if (includeUppercase) {
      password += this.getRandomChar(this.UPPERCASE);
      availableChars += this.UPPERCASE;
    }

    if (includeLowercase) {
      password += this.getRandomChar(this.LOWERCASE);
      availableChars += this.LOWERCASE;
    }

    if (includeNumbers) {
      password += this.getRandomChar(this.NUMBERS);
      availableChars += this.NUMBERS;
    }

    if (includeSymbols) {
      password += this.getRandomChar(this.SYMBOLS);
      availableChars += this.SYMBOLS;
    }

    // Fill the rest of the password with random characters
    const remainingLength = length - password.length;
    for (let i = 0; i < remainingLength; i++) {
      password += this.getRandomChar(availableChars);
    }

    // Shuffle the password to avoid predictable patterns
    return this.shuffleString(password);
  }

  private static getRandomChar(chars: string): string {
    return chars.charAt(Math.floor(Math.random() * chars.length));
  }

  private static shuffleString(str: string): string {
    const arr = str.split('');
    for (let i = arr.length - 1; i > 0; i--) {
      const j = Math.floor(Math.random() * (i + 1));
      [arr[i], arr[j]] = [arr[j], arr[i]];
    }
    return arr.join('');
  }

  static getPasswordStrength(password: string): {
    score: number;
    label: string;
    color: string;
  } {
    let score = 0;
    
    if (password.length >= 8) score += 1;
    if (password.length >= 12) score += 1;
    if (password.length >= 16) score += 1;
    
    if (/[a-z]/.test(password)) score += 1;
    if (/[A-Z]/.test(password)) score += 1;
    if (/\d/.test(password)) score += 1;
    if (/[!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?]/.test(password)) score += 1;

    if (score <= 2) return { score, label: 'Weak', color: 'text-red-500' };
    if (score <= 4) return { score, label: 'Fair', color: 'text-yellow-500' };
    if (score <= 6) return { score, label: 'Good', color: 'text-blue-500' };
    return { score, label: 'Strong', color: 'text-green-500' };
  }
}
