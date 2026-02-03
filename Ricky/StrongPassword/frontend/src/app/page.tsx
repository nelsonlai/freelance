'use client';

import React, { useState, useEffect } from 'react';
import { Shield, Database, Code, AlertTriangle } from 'lucide-react';
import RecordsTable from '../components/RecordsTable';
import PasswordGenerator from '../components/PasswordGenerator';
import { recordApi } from '../services/api';
import { Record as AppRecord, CreateRecordRequest, UpdateRecordRequest } from '../types';
import toast from 'react-hot-toast';

export default function HomePage() {
  const [records, setRecords] = useState<AppRecord[]>([]);
  const [isLoading, setIsLoading] = useState(true);
  const [showPasswords, setShowPasswords] = useState(false);
  const [generatedPassword, setGeneratedPassword] = useState<string>('');

  useEffect(() => {
    loadRecords();
  }, []);



  const loadRecords = async () => {
    try {
      setIsLoading(true);
      const response = await recordApi.getAll(showPasswords);
      setRecords(response.items);
    } catch (error: any) {
      const message = error.response?.data?.error?.message || 'Failed to load records';
      toast.error(message);
    } finally {
      setIsLoading(false);
    }
  };

  const handleCreateRecord = async (data: CreateRecordRequest) => {
    try {
      await recordApi.create(data);
      toast.success('Record created successfully!');
      loadRecords();
    } catch (error: any) {
      const message = error.response?.data?.error?.message || 'Failed to create record';
      toast.error(message);
      throw error;
    }
  };

  const handleUpdateRecord = async (id: string, data: UpdateRecordRequest) => {
    try {
      await recordApi.update(id, data);
      toast.success('Record updated successfully!');
      loadRecords();
    } catch (error: any) {
      const message = error.response?.data?.error?.message || 'Failed to update record';
      toast.error(message);
      throw error;
    }
  };

  const handleDeleteRecord = async (id: string) => {
    try {
      await recordApi.delete(id);
      toast.success('Record deleted successfully!');
      loadRecords();
    } catch (error: any) {
      const message = error.response?.data?.error?.message || 'Failed to delete record';
      toast.error(message);
      throw error;
    }
  };

  const handlePasswordGenerated = (password: string) => {
    // Store the generated password in the main component state
    setGeneratedPassword(password);
    console.log('Password generated:', password);
  };

  const togglePasswordVisibility = () => {
    setShowPasswords(!showPasswords);
    // Reload records with new password visibility setting
    setTimeout(() => loadRecords(), 100);
  };

  return (
    <div className="min-h-screen bg-gray-50">
      {/* Header */}
      <header className="bg-white shadow-sm border-b border-gray-200">
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
          <div className="flex items-center justify-between h-16">
            <div className="flex items-center space-x-3">
              <Shield className="h-8 w-8 text-primary-600" />
              <div>
                <h1 className="text-xl font-bold text-gray-900">Password CRUD Demo</h1>
                <p className="text-sm text-gray-500">Plain text storage demo application</p>
              </div>
            </div>
            <div className="flex items-center space-x-4">
              <div className="flex items-center space-x-2 text-sm text-gray-600">
                <Database className="h-4 w-4" />
                <span>SQLite</span>
              </div>
              <div className="flex items-center space-x-2 text-sm text-gray-600">
                <Code className="h-4 w-4" />
                <span>Next.js + Express</span>
              </div>
            </div>
          </div>
        </div>
      </header>

      {/* Demo Warning */}
      <div className="bg-yellow-50 border-b border-yellow-200">
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-3">
          <div className="flex items-center space-x-2">
            <AlertTriangle className="h-5 w-5 text-yellow-600" />
            <span className="text-sm text-yellow-800">
              <strong>Demo Mode:</strong> This application stores passwords in plain text for demonstration purposes only. 
              Do not use in production environments.
            </span>
          </div>
        </div>
      </div>

      {/* Main Content */}
      <main className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-8">
        <div className="space-y-8">
          {/* Top Section - Password Generator */}
          <div className="w-full">
            <PasswordGenerator 
              onPasswordGenerated={handlePasswordGenerated}
              initialPassword={generatedPassword}
            />
          </div>

          {/* Bottom Section - Records Management */}
          <div className="w-full">
            {isLoading ? (
              <div className="card text-center py-12">
                <div className="animate-spin rounded-full h-12 w-12 border-b-2 border-primary-600 mx-auto mb-4"></div>
                <p className="text-gray-600">Loading records...</p>
              </div>
            ) : (
              <RecordsTable
                records={records}
                onRefresh={loadRecords}
                onCreateRecord={handleCreateRecord}
                onUpdateRecord={handleUpdateRecord}
                onDeleteRecord={handleDeleteRecord}
              />
            )}
          </div>
        </div>
      </main>

      {/* Footer */}
      <footer className="bg-white border-t border-gray-200 mt-16">
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-8">
          <div className="text-center text-sm text-gray-500">
            <p>Password CRUD Demo Application - Built with Next.js, Express.js, Prisma, and SQLite</p>
            <p className="mt-2">
              <strong>⚠️ Security Notice:</strong> This is a demo application that stores passwords in plain text. 
              Never use this approach in production systems.
            </p>
          </div>
        </div>
      </footer>
    </div>
  );
}
