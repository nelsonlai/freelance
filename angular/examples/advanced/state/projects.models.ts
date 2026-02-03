// @ts-nocheck
export interface Project {
  id: string;
  name: string;
  status: 'draft' | 'active' | 'archived';
  budget?: number;
  tenantId: string;
}
