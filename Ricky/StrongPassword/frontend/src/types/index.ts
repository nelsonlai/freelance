export interface Record {
  id: string;
  username: string;
  email: string;
  password?: string;
  createdAt: string;
  updatedAt: string;
}

export interface CreateRecordRequest {
  username: string;
  email: string;
  password: string;
}

export interface UpdateRecordRequest {
  username?: string;
  email?: string;
  password?: string;
}

export interface RecordsListResponse {
  items: Record[];
  total: number;
}

export interface ErrorResponse {
  error: {
    code: 'VALIDATION_ERROR' | 'NOT_FOUND' | 'CONFLICT' | 'BAD_REQUEST' | 'INTERNAL_ERROR';
    message: string;
    details?: { [key: string]: any };
  };
}

export interface PasswordGeneratorOptions {
  length: number;
  includeUppercase: boolean;
  includeLowercase: boolean;
  includeNumbers: boolean;
  includeSymbols: boolean;
}
