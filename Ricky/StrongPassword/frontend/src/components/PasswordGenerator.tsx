'use client';

import React, { useState, useEffect } from 'react';
import { Copy, Eye, EyeOff, RefreshCw } from 'lucide-react';
import { PasswordGenerator as PasswordGen } from '../utils/passwordGenerator';
import { PasswordGeneratorOptions } from '../types';
import toast from 'react-hot-toast';

interface PasswordGeneratorProps {
  onPasswordGenerated: (password: string) => void;
  initialPassword?: string;
}

export default function PasswordGenerator({ onPasswordGenerated, initialPassword = '' }: PasswordGeneratorProps) {
  const [password, setPassword] = useState(initialPassword || 'Click Generate to create a password');
  const [showPassword, setShowPassword] = useState(false);
  const [options, setOptions] = useState<PasswordGeneratorOptions>({
    length: 16,
    includeUppercase: true,
    includeLowercase: true,
    includeNumbers: true,
    includeSymbols: true,
  });

  useEffect(() => {
    if (initialPassword) {
      setPassword(initialPassword);
    } else {
      generateNewPassword();
    }
  }, [initialPassword]);

  // Generate initial password on component mount
  useEffect(() => {
    // Generate initial password when component mounts
    generateNewPassword();
  }, []);

  const generateNewPassword = () => {
    try {
      const newPassword = PasswordGen.generatePassword(options);
      setPassword(newPassword);
      onPasswordGenerated(newPassword);
    } catch (error) {
      toast.error('Failed to generate password');
    }
  };

  const copyToClipboard = async () => {
    try {
      await navigator.clipboard.writeText(password);
      toast.success('Password copied to clipboard!');
    } catch (error) {
      toast.error('Failed to copy password');
    }
  };

  const handleOptionChange = (key: keyof PasswordGeneratorOptions, value: boolean | number) => {
    const newOptions = { ...options, [key]: value };
    
    // Ensure at least one character class is selected
    if (key === 'includeUppercase' || key === 'includeLowercase' || key === 'includeNumbers' || key === 'includeSymbols') {
      const enabledClasses = [
        newOptions.includeUppercase,
        newOptions.includeLowercase,
        newOptions.includeNumbers,
        newOptions.includeSymbols
      ].filter(Boolean).length;
      
      if (enabledClasses === 0) {
        toast.error('At least one character class must be selected');
        return;
      }
    }
    
    setOptions(newOptions);
  };

  const getPasswordStrength = () => {
    if (!password) return { score: 0, label: 'No Password', color: 'text-gray-500' };
    return PasswordGen.getPasswordStrength(password);
  };

  const strength = getPasswordStrength();

  return (
    <div className="card space-y-4">
      <h3 className="text-lg font-semibold text-gray-900">Password Generator</h3>
      
      {/* Generated Password Display */}
      <div className="space-y-2">
        <label className="block text-sm font-medium text-gray-700">Generated Password</label>
        <div className="flex items-center space-x-2">
          <div className="flex-1 relative">
            <input
              type={showPassword ? 'text' : 'password'}
              value={password}
              onChange={(e) => setPassword(e.target.value)}
              className="input pr-20"
              placeholder="Generate a password..."
            />
            <button
              type="button"
              onClick={() => setShowPassword(!showPassword)}
              className="absolute right-2 top-1/2 transform -translate-y-1/2 text-gray-500 hover:text-gray-700"
            >
              {showPassword ? <EyeOff size={20} /> : <Eye size={20} />}
            </button>
          </div>
          <button
            type="button"
            onClick={copyToClipboard}
            className="btn-secondary flex items-center space-x-2"
          >
            <Copy size={16} />
            <span>Copy</span>
          </button>
          <button
            type="button"
            onClick={generateNewPassword}
            className="btn-primary flex items-center space-x-2"
          >
            <RefreshCw size={16} />
            <span>Generate</span>
          </button>
        </div>
        
        {/* Password Strength Indicator */}
        {password && (
          <div className="flex items-center space-x-2">
            <span className="text-sm text-gray-600">Strength:</span>
            <span className={`text-sm font-medium ${strength.color}`}>
              {strength.label}
            </span>
            <div className="flex-1 bg-gray-200 rounded-full h-2">
              <div
                className={`h-2 rounded-full transition-all duration-300 ${
                  strength.score <= 2 ? 'bg-red-500' :
                  strength.score <= 4 ? 'bg-yellow-500' :
                  strength.score <= 6 ? 'bg-blue-500' : 'bg-green-500'
                }`}
                style={{ width: `${(strength.score / 8) * 100}%` }}
              />
            </div>
          </div>
        )}
      </div>

      {/* Length Slider */}
      <div className="space-y-2">
        <label className="block text-sm font-medium text-gray-700">
          Length: {options.length}
        </label>
        <input
          type="range"
          min="8"
          max="64"
          value={options.length}
          onChange={(e) => handleOptionChange('length', parseInt(e.target.value))}
          className="w-full h-2 bg-gray-200 rounded-lg appearance-none cursor-pointer slider"
        />
        <div className="flex justify-between text-xs text-gray-500">
          <span>8</span>
          <span>64</span>
        </div>
      </div>

      {/* Character Class Toggles */}
      <div className="space-y-3">
        <label className="block text-sm font-medium text-gray-700">Character Classes</label>
        <div className="grid grid-cols-2 gap-3">
          <label className="flex items-center space-x-2">
            <input
              type="checkbox"
              checked={options.includeUppercase}
              onChange={(e) => handleOptionChange('includeUppercase', e.target.checked)}
              className="rounded border-gray-300 text-primary-600 focus:ring-primary-500"
            />
            <span className="text-sm text-gray-700">Uppercase (A-Z)</span>
          </label>
          
          <label className="flex items-center space-x-2">
            <input
              type="checkbox"
              checked={options.includeLowercase}
              onChange={(e) => handleOptionChange('includeLowercase', e.target.checked)}
              className="rounded border-gray-300 text-primary-600 focus:ring-primary-500"
            />
            <span className="text-sm text-gray-700">Lowercase (a-z)</span>
          </label>
          
          <label className="flex items-center space-x-2">
            <input
              type="checkbox"
              checked={options.includeNumbers}
              onChange={(e) => handleOptionChange('includeNumbers', e.target.checked)}
              className="rounded border-gray-300 text-primary-600 focus:ring-primary-500"
            />
            <span className="text-sm text-gray-700">Numbers (0-9)</span>
          </label>
          
          <label className="flex items-center space-x-2">
            <input
              type="checkbox"
              checked={options.includeSymbols}
              onChange={(e) => handleOptionChange('includeSymbols', e.target.checked)}
              className="rounded border-gray-300 text-primary-600 focus:ring-primary-500"
            />
            <span className="text-sm text-gray-700">Symbols (!@#$%^&*)</span>
          </label>
        </div>
      </div>
    </div>
  );
}
