// Question definitions for the questionnaire system
// As per SRS: Keep a single TS file exporting the question schema to drive rendering and validation
// This ensures consistency between frontend and backend validation

export interface Question {
  id: string;
  type: 'single' | 'multi' | 'text';
  label: string;
  required: boolean;
  options?: string[];
  maxLength?: number;
  maxSelections?: number;
  placeholder?: string;
}

// Question configuration matching the SRS validation rules
export const questions: Question[] = [
  {
    id: 'q1',
    type: 'single',
    label: 'What is your preferred option?',
    required: true,
    options: ['A', 'B', 'C'],
  },
  {
    id: 'q2',
    type: 'multi',
    label: 'Select all that apply (max 3):',
    required: false,
    options: ['X', 'Y', 'Z'],
    maxSelections: 3,
  },
  {
    id: 'q3',
    type: 'text',
    label: 'Additional comments (optional):',
    required: false,
    maxLength: 500,
    placeholder: 'Enter your comments here...',
  },
];

// Validation rules matching the backend Zod schemas
export const validationRules = {
  q1: {
    required: true,
    allowedValues: ['A', 'B', 'C'],
  },
  q2: {
    required: false,
    allowedValues: ['X', 'Y', 'Z'],
    maxSelections: 3,
  },
  q3: {
    required: false,
    maxLength: 500,
  },
};

// Helper function to get question by ID
export function getQuestionById(id: string): Question | undefined {
  return questions.find(q => q.id === id);
}

// Helper function to validate answers against the schema
export function validateAnswers(answers: Record<string, any>): { isValid: boolean; errors: string[] } {
  const errors: string[] = [];
  
  // Validate q1 (required single choice)
  if (!answers.q1 || !validationRules.q1.allowedValues.includes(answers.q1)) {
    errors.push('Question 1 is required and must be A, B, or C');
  }
  
  // Validate q2 (optional multi select)
  if (answers.q2) {
    if (!Array.isArray(answers.q2)) {
      errors.push('Question 2 must be an array');
    } else if (answers.q2.length > validationRules.q2.maxSelections!) {
      errors.push(`Question 2 can have maximum ${validationRules.q2.maxSelections} selections`);
    } else {
      const invalidOptions = answers.q2.filter((opt: string) => !validationRules.q2.allowedValues.includes(opt));
      if (invalidOptions.length > 0) {
        errors.push(`Question 2 contains invalid options: ${invalidOptions.join(', ')}`);
      }
    }
  }
  
  // Validate q3 (optional text)
  if (answers.q3 && typeof answers.q3 === 'string') {
    if (answers.q3.length > validationRules.q3.maxLength!) {
      errors.push(`Question 3 text cannot exceed ${validationRules.q3.maxLength} characters`);
    }
  }
  
  return {
    isValid: errors.length === 0,
    errors,
  };
}
