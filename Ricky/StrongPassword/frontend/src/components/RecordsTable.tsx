'use client';

import React, { useState } from 'react';
import { Edit, Trash2, Eye, EyeOff, Copy, Plus } from 'lucide-react';
import { Record as AppRecord } from '../types';
import RecordForm from './RecordForm';
import toast from 'react-hot-toast';

interface RecordsTableProps {
  records: AppRecord[];
  onRefresh: () => void;
  onCreateRecord: (data: any) => Promise<void>;
  onUpdateRecord: (id: string, data: any) => Promise<void>;
  onDeleteRecord: (id: string) => Promise<void>;
}

export default function RecordsTable({ 
  records, 
  onRefresh, 
  onCreateRecord, 
  onUpdateRecord, 
  onDeleteRecord 
}: RecordsTableProps) {
  const [isCreateModalOpen, setIsCreateModalOpen] = useState(false);
  const [editingRecord, setEditingRecord] = useState<AppRecord | null>(null);
  const [showPasswords, setShowPasswords] = useState(false);
  const [deletingId, setDeletingId] = useState<string | null>(null);

  const handleEdit = (record: AppRecord) => {
    setEditingRecord(record);
  };

  const handleDelete = async (id: string) => {
    if (!confirm('Are you sure you want to delete this record? This action cannot be undone.')) {
      return;
    }

    setDeletingId(id);
    try {
      await onDeleteRecord(id);
      toast.success('Record deleted successfully!');
      onRefresh();
    } catch (error: any) {
      const message = error.response?.data?.error?.message || 'Failed to delete record';
      toast.error(message);
    } finally {
      setDeletingId(null);
    }
  };

  const handleCreateSubmit = async (data: any) => {
    await onCreateRecord(data);
    onRefresh();
  };

  const handleUpdateSubmit = async (data: any) => {
    if (editingRecord) {
      await onUpdateRecord(editingRecord.id, data);
      onRefresh();
    }
  };

  const copyToClipboard = async (text: string, field: string) => {
    try {
      await navigator.clipboard.writeText(text);
      toast.success(`${field} copied to clipboard!`);
    } catch (error) {
      toast.error('Failed to copy to clipboard');
    }
  };

  const formatDate = (dateString: string) => {
    return new Date(dateString).toLocaleString();
  };

  return (
    <div className="space-y-6">
      {/* Header */}
      <div className="flex items-center justify-between">
        <div>
          <h2 className="text-2xl font-bold text-gray-900">Records</h2>
          <p className="text-gray-600">Manage your password records</p>
        </div>
        <div className="flex items-center space-x-3">
          <button
            onClick={() => setShowPasswords(!showPasswords)}
            className="btn-secondary flex items-center space-x-2"
          >
            {showPasswords ? <EyeOff size={16} /> : <Eye size={16} />}
            <span>{showPasswords ? 'Hide' : 'Show'} Passwords</span>
          </button>
          <button
            onClick={() => setIsCreateModalOpen(true)}
            className="btn-primary flex items-center space-x-2"
          >
            <Plus size={16} />
            <span>Add Record</span>
          </button>
        </div>
      </div>

      {/* Records Table */}
      <div className="card overflow-hidden">
        {records.length === 0 ? (
          <div className="text-center py-12">
            <div className="text-gray-400 mb-4">
              <svg className="mx-auto h-12 w-12" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9 12h6m-6 4h6m2 5H7a2 2 0 01-2-2V5a2 2 0 012-2h5.586a1 1 0 01.707.293l5.414 5.414a1 1 0 01.293.707V19a2 2 0 01-2 2z" />
              </svg>
            </div>
            <h3 className="text-lg font-medium text-gray-900 mb-2">No records yet</h3>
            <p className="text-gray-600 mb-4">Get started by creating your first password record.</p>
            <button
              onClick={() => setIsCreateModalOpen(true)}
              className="btn-primary"
            >
              Create Record
            </button>
          </div>
        ) : (
          <div className="overflow-x-auto">
            <table className="min-w-full divide-y divide-gray-200">
              <thead className="bg-gray-50">
                <tr>
                  <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                    ID
                  </th>
                  <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                    Username
                  </th>
                  <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                    Email
                  </th>
                  {showPasswords && (
                    <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                      Password
                    </th>
                  )}
                  <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                    Created At
                  </th>
                  <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                    Updated At
                  </th>
                  <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                    Actions
                  </th>
                </tr>
              </thead>
              <tbody className="bg-white divide-y divide-gray-200">
                {records.map((record) => (
                  <tr key={record.id} className="hover:bg-gray-50">
                    <td className="px-6 py-4 whitespace-nowrap text-sm font-mono text-gray-900">
                      {record.id.slice(0, 8)}...
                    </td>
                    <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-900">
                      {record.username}
                    </td>
                    <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-900">
                      {record.email}
                    </td>
                    {showPasswords && (
                      <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-900">
                        <div className="flex items-center space-x-2">
                          <span className="font-mono bg-gray-100 px-2 py-1 rounded">
                            {record.password || '••••••••'}
                          </span>
                          {record.password && (
                            <button
                              onClick={() => copyToClipboard(record.password!, 'Password')}
                              className="text-gray-400 hover:text-gray-600"
                            >
                              <Copy size={14} />
                            </button>
                          )}
                        </div>
                      </td>
                    )}
                    <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
                      {formatDate(record.createdAt)}
                    </td>
                    <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
                      {formatDate(record.updatedAt)}
                    </td>
                    <td className="px-6 py-4 whitespace-nowrap text-sm font-medium">
                      <div className="flex items-center space-x-2">
                        <button
                          onClick={() => handleEdit(record)}
                          className="text-primary-600 hover:text-primary-900 transition-colors"
                        >
                          <Edit size={16} />
                        </button>
                        <button
                          onClick={() => handleDelete(record.id)}
                          disabled={deletingId === record.id}
                          className="text-danger-600 hover:text-danger-900 transition-colors disabled:opacity-50"
                        >
                          <Trash2 size={16} />
                        </button>
                      </div>
                    </td>
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
        )}
      </div>

      {/* Create Modal */}
      <RecordForm
        isOpen={isCreateModalOpen}
        onClose={() => setIsCreateModalOpen(false)}
        onSubmit={handleCreateSubmit}
        mode="create"
      />

      {/* Edit Modal */}
      <RecordForm
        record={editingRecord ?? undefined}
        isOpen={!!editingRecord}
        onClose={() => setEditingRecord(null)}
        onSubmit={handleUpdateSubmit}
        mode="edit"
      />
    </div>
  );
}
