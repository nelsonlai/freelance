import { PasswordGenerator } from '../utils/passwordGenerator';

describe('PasswordGenerator', () => {
  describe('generatePassword', () => {
    it('should generate password with specified length', () => {
      const options = {
        length: 16,
        includeUppercase: true,
        includeLowercase: true,
        includeNumbers: true,
        includeSymbols: true,
      };

      const password = PasswordGenerator.generatePassword(options);
      expect(password).toHaveLength(16);
    });

    it('should include at least one character from each enabled class', () => {
      const options = {
        length: 8,
        includeUppercase: true,
        includeLowercase: true,
        includeNumbers: true,
        includeSymbols: false,
      };

      const password = PasswordGenerator.generatePassword(options);
      
      expect(/[A-Z]/.test(password)).toBe(true); // Uppercase
      expect(/[a-z]/.test(password)).toBe(true); // Lowercase
      expect(/\d/.test(password)).toBe(true);    // Numbers
      expect(/[!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?]/.test(password)).toBe(false); // Symbols
    });

    it('should handle minimum length constraint', () => {
      const options = {
        length: 8,
        includeUppercase: true,
        includeLowercase: true,
        includeNumbers: true,
        includeSymbols: true,
      };

      const password = PasswordGenerator.generatePassword(options);
      expect(password.length).toBeGreaterThanOrEqual(8);
    });
  });

  describe('getPasswordStrength', () => {
    it('should return weak for simple passwords', () => {
      const result = PasswordGenerator.getPasswordStrength('password');
      expect(result.label).toBe('Weak');
      expect(result.color).toBe('text-red-500');
    });

    it('should return strong for complex passwords', () => {
      const result = PasswordGenerator.getPasswordStrength('P@ssw0rd!');
      expect(result.label).toBe('Strong');
      expect(result.color).toBe('text-green-500');
    });

    it('should handle empty password', () => {
      const result = PasswordGenerator.getPasswordStrength('');
      expect(result.label).toBe('No Password');
      expect(result.color).toBe('text-gray-500');
    });
  });
});
