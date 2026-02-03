export interface Record {
  id: string;
  username: string;
  email: string;
  password: string;
  createdAt: Date;
  updatedAt: Date;
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

export interface RecordResponse {
  id: string;
  username: string;
  email: string;
  createdAt: string;
  updatedAt: string;
}

export interface RecordResponseWithPassword extends RecordResponse {
  password: string;
}

export interface RecordsListResponse {
  items: RecordResponse[];
  total: number;
}

export interface RecordsListResponseWithPassword {
  items: RecordResponseWithPassword[];
  total: number;
}

export interface ErrorResponse {
  error: {
    code: 'VALIDATION_ERROR' | 'NOT_FOUND' | 'CONFLICT' | 'BAD_REQUEST' | 'INTERNAL_ERROR';
    message: string;
    details?: { [key: string]: any };
  };
}

export interface ValidationError {
  field: string;
  message: string;
}
