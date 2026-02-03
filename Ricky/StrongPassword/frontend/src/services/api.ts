import axios from 'axios';
import { CreateRecordRequest, UpdateRecordRequest, RecordsListResponse, Record } from '../types';

const API_BASE_URL = process.env.NEXT_PUBLIC_API_URL || 'http://localhost:4000/api/v1';

const api = axios.create({
  baseURL: API_BASE_URL,
  headers: {
    'Content-Type': 'application/json',
  },
});

// Request interceptor for logging
api.interceptors.request.use(
  (config) => {
    console.log(`🚀 ${config.method?.toUpperCase()} ${config.url}`);
    return config;
  },
  (error) => {
    return Promise.reject(error);
  }
);

// Response interceptor for error handling
api.interceptors.response.use(
  (response) => response,
  (error) => {
    console.error('API Error:', error.response?.data || error.message);
    return Promise.reject(error);
  }
);

export const recordApi = {
  // Get all records
  getAll: async (includePassword: boolean = false): Promise<RecordsListResponse> => {
    const response = await api.get(`/records?includePassword=${includePassword}`);
    return response.data;
  },

  // Get record by ID
  getById: async (id: string, includePassword: boolean = false): Promise<Record> => {
    const response = await api.get(`/records/${id}?includePassword=${includePassword}`);
    return response.data;
  },

  // Create new record
  create: async (data: CreateRecordRequest): Promise<Record> => {
    const response = await api.post('/records', data);
    return response.data;
  },

  // Update record
  update: async (id: string, data: UpdateRecordRequest): Promise<Record> => {
    const response = await api.patch(`/records/${id}`, data);
    return response.data;
  },

  // Delete record
  delete: async (id: string): Promise<void> => {
    await api.delete(`/records/${id}`);
  },
};

export default api;
