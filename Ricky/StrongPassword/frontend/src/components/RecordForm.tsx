'use client';

import React, { useState, useEffect } from 'react';
import { X, Save, User, Mail, Lock } from 'lucide-react';
import { Record as AppRecord, CreateRecordRequest, UpdateRecordRequest } from '../types';
import PasswordGenerator from './PasswordGenerator';
import toast from 'react-hot-toast';

interface RecordFormProps {
  record?: AppRecord;
  isOpen: boolean;
  onClose: () => void;
  onSubmit: (data: CreateRecordRequest | UpdateRecordRequest) => Promise<void>;
  mode: 'create' | 'edit';
}

export default function RecordForm({ record, isOpen, onClose, onSubmit, mode }: RecordFormProps) {
  const [formData, setFormData] = useState<CreateRecordRequest>({
    username: '',
    email: '',
    password: '',
  });
  const [errors, setErrors] = useState<Record<string, string>>({});
  const [isSubmitting, setIsSubmitting] = useState(false);
  const [showPasswordGenerator, setShowPasswordGenerator] = useState(false);

  useEffect(() => {
    if (record && mode === 'edit') {
      setFormData({
        username: record.username,
        email: record.email,
        password: record.password || '',
      });
    } else {
      setFormData({
        username: '',
        email: '',
        password: '',
      });
    }
    setErrors({});
  }, [record, mode, isOpen]);

  const validateForm = (): boolean => {
    const newErrors: Record<string, string> = {};

    // Username validation
    if (!formData.username.trim()) {
      newErrors.username = 'Username is required';
    } else if (formData.username.length < 3) {
      newErrors.username = 'Username must be at least 3 characters';
    } else if (formData.username.length > 50) {
      newErrors.username = 'Username must be at most 50 characters';
    } else if (!/^[A-Za-z0-9_\-\.]+$/.test(formData.username)) {
      newErrors.username = 'Username can only contain letters, numbers, underscores, hyphens, and dots';
    }

    // Email validation
    if (!formData.email.trim()) {
      newErrors.email = 'Email is required';
    } else if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(formData.email)) {
      newErrors.email = 'Please enter a valid email address';
    }

    // Password validation
    if (mode === 'create' && !formData.password.trim()) {
      newErrors.password = 'Password is required';
    } else if (formData.password && formData.password.length < 8) {
      newErrors.password = 'Password must be at least 8 characters';
    } else if (formData.password && formData.password.length > 128) {
      newErrors.password = 'Password must be at most 128 characters';
    } else if (formData.password) {
      const hasLower = /[a-z]/.test(formData.password);
      const hasUpper = /[A-Z]/.test(formData.password);
      const hasDigit = /\d/.test(formData.password);
      const hasSymbol = /[!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?]/.test(formData.password);
      
      const classes = [hasLower, hasUpper, hasDigit, hasSymbol].filter(Boolean);
      if (classes.length < 3) {
        newErrors.password = 'Password must contain at least 3 character classes (lowercase, uppercase, digits, symbols)';
      }
    }

    setErrors(newErrors);
    return Object.keys(newErrors).length === 0;
  };

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    
    if (!validateForm()) {
      return;
    }

    setIsSubmitting(true);
    try {
      if (mode === 'create') {
        await onSubmit(formData as CreateRecordRequest);
        toast.success('Record created successfully!');
      } else {
        const updateData: UpdateRecordRequest = {};
        if (formData.username !== record?.username) updateData.username = formData.username;
        if (formData.email !== record?.email) updateData.email = formData.email;
        if (formData.password) updateData.password = formData.password;
        
        await onSubmit(updateData);
        toast.success('Record updated successfully!');
      }
      onClose();
    } catch (error: any) {
      const message = error.response?.data?.error?.message || 'An error occurred';
      toast.error(message);
    } finally {
      setIsSubmitting(false);
    }
  };

  const handleInputChange = (field: keyof CreateRecordRequest, value: string) => {
    setFormData(prev => ({ ...prev, [field]: value }));
    // Clear error when user starts typing
    if (errors[field]) {
      setErrors(prev => ({ ...prev, [field]: '' }));
    }
  };

  const handlePasswordGenerated = (password: string) => {
    setFormData(prev => ({ ...prev, password }));
    setErrors(prev => ({ ...prev, password: '' }));
  };

  if (!isOpen) return null;

  return (
    <div className="fixed inset-0 bg-black bg-opacity-50 flex items-center justify-center p-4 z-50">
      <div className="bg-white rounded-lg shadow-xl max-w-2xl w-full max-h-[90vh] overflow-y-auto">
        <div className="flex items-center justify-between p-6 border-b border-gray-200">
          <h2 className="text-xl font-semibold text-gray-900">
            {mode === 'create' ? 'Create New Record' : 'Edit Record'}
          </h2>
          <button
            onClick={onClose}
            className="text-gray-400 hover:text-gray-600 transition-colors"
          >
            <X size={24} />
          </button>
        </div>

        <form onSubmit={handleSubmit} className="p-6 space-y-6">
          {/* Username Field */}
          <div>
            <label className="block text-sm font-medium text-gray-700 mb-2">
              <User size={16} className="inline mr-2" />
              Username
            </label>
            <input
              type="text"
              value={formData.username}
              onChange={(e) => handleInputChange('username', e.target.value)}
              className={`input ${errors.username ? 'border-red-500 focus:ring-red-500' : ''}`}
              placeholder="Enter username"
            />
            {errors.username && (
              <p className="mt-1 text-sm text-red-600">{errors.username}</p>
            )}
          </div>

          {/* Email Field */}
          <div>
            <label className="block text-sm font-medium text-gray-700 mb-2">
              <Mail size={16} className="inline mr-2" />
              Email
            </label>
            <input
              type="email"
              value={formData.email}
              onChange={(e) => handleInputChange('email', e.target.value)}
              className={`input ${errors.email ? 'border-red-500 focus:ring-red-500' : ''}`}
              placeholder="Enter email address"
            />
            {errors.email && (
              <p className="mt-1 text-sm text-red-600">{errors.email}</p>
            )}
          </div>

          {/* Password Field */}
          <div>
            <div className="flex items-center justify-between mb-2">
              <label className="block text-sm font-medium text-gray-700">
                <Lock size={16} className="inline mr-2" />
                Password
                {mode === 'edit' && <span className="text-gray-500 text-xs ml-2">(optional)</span>}
              </label>
              <button
                type="button"
                onClick={() => setShowPasswordGenerator(!showPasswordGenerator)}
                className="text-sm text-primary-600 hover:text-primary-700"
              >
                {showPasswordGenerator ? 'Hide Generator' : 'Show Generator'}
              </button>
            </div>
            
            <input
              type="text"
              value={formData.password}
              onChange={(e) => handleInputChange('password', e.target.value)}
              className={`input ${errors.password ? 'border-red-500 focus:ring-red-500' : ''}`}
              placeholder={mode === 'create' ? 'Enter password' : 'Leave empty to keep current password'}
            />
            {errors.password && (
              <p className="mt-1 text-sm text-red-600">{errors.password}</p>
            )}
          </div>

          {/* Password Generator */}
          {showPasswordGenerator && (
            <div className="border-t pt-4">
              <PasswordGenerator
                onPasswordGenerated={handlePasswordGenerated}
                initialPassword={formData.password}
              />
            </div>
          )}

          {/* Form Actions */}
          <div className="flex items-center justify-end space-x-3 pt-4 border-t border-gray-200">
            <button
              type="button"
              onClick={onClose}
              className="btn-secondary"
              disabled={isSubmitting}
            >
              Cancel
            </button>
            <button
              type="submit"
              className="btn-primary flex items-center space-x-2"
              disabled={isSubmitting}
            >
              <Save size={16} />
              <span>{isSubmitting ? 'Saving...' : mode === 'create' ? 'Create' : 'Update'}</span>
            </button>
          </div>
        </form>
      </div>
    </div>
  );
}
