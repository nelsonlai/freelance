// Main questionnaire page component
// Implements the questionnaire form as specified in the SRS
// Features: client-side validation, submit button disabled during posting, error handling

'use client';

import { useState } from 'react';
import { useRouter } from 'next/navigation';
import { questions, validateAnswers } from '@/lib/questions';

// Interface for form answers
interface FormAnswers {
  q1: string;
  q2: string[];
  q3: string;
}

// Interface for form errors
interface FormErrors {
  [key: string]: string[];
}

export default function QuestionnairePage() {
  const router = useRouter();
  const [answers, setAnswers] = useState<FormAnswers>({
    q1: '',
    q2: [],
    q3: '',
  });
  const [errors, setErrors] = useState<FormErrors>({});
  const [isSubmitting, setIsSubmitting] = useState(false);
  const [generalError, setGeneralError] = useState<string>('');

  // Handle single choice selection
  const handleSingleChoice = (questionId: string, value: string) => {
    setAnswers(prev => ({ ...prev, [questionId]: value }));
    // Clear error for this question
    if (errors[questionId]) {
      setErrors(prev => ({ ...prev, [questionId]: [] }));
    }
  };

  // Handle multi-choice selection
  const handleMultiChoice = (questionId: string, value: string) => {
    setAnswers(prev => {
      const currentSelections = prev[questionId] as string[];
      const isSelected = currentSelections.includes(value);
      
      if (isSelected) {
        // Remove if already selected
        return { ...prev, [questionId]: currentSelections.filter(item => item !== value) };
      } else {
        // Add if not selected and under limit
        const question = questions.find(q => q.id === questionId);
        if (currentSelections.length < (question?.maxSelections || 3)) {
          return { ...prev, [questionId]: [...currentSelections, value] };
        }
      }
      return prev;
    });
    
    // Clear error for this question
    if (errors[questionId]) {
      setErrors(prev => ({ ...prev, [questionId]: [] }));
    }
  };

  // Handle text input
  const handleTextInput = (questionId: string, value: string) => {
    setAnswers(prev => ({ ...prev, [questionId]: value }));
    // Clear error for this question
    if (errors[questionId]) {
      setErrors(prev => ({ ...prev, [questionId]: [] }));
    }
  };

  // Handle form submission
  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setGeneralError('');
    
    // Client-side validation
    const validation = validateAnswers(answers);
    if (!validation.isValid) {
      setErrors({ general: validation.errors });
      return;
    }

    setIsSubmitting(true);

    try {
      // Submit to backend API
      const response = await fetch(`${process.env.NEXT_PUBLIC_API_BASE_URL || 'http://localhost:4000'}/api/v1/responses`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ answers }),
      });

      if (!response.ok) {
        const errorData = await response.json();
        throw new Error(errorData.error?.message || 'Failed to submit questionnaire');
      }

      const result = await response.json();
      
      // Redirect to thank you page with response ID as per SRS
      router.push(`/thanks?rid=${result.id}`);
      
    } catch (error) {
      console.error('Submission error:', error);
      setGeneralError(error instanceof Error ? error.message : 'An unexpected error occurred');
    } finally {
      setIsSubmitting(false);
    }
  };

  // Render single choice question
  const renderSingleChoice = (question: any) => (
    <div key={question.id} className="mb-6">
      <label className="form-label">
        {question.label}
        {question.required && <span className="text-red-500 ml-1">*</span>}
      </label>
      <div className="space-y-2">
        {question.options?.map((option: string) => (
          <label key={option} className="flex items-center">
            <input
              type="radio"
              name={question.id}
              value={option}
              checked={answers[question.id] === option}
              onChange={() => handleSingleChoice(question.id, option)}
              className="mr-2"
            />
            <span>{option}</span>
          </label>
        ))}
      </div>
      {errors[question.id] && (
        <p className="text-error-600 text-sm mt-1">{errors[question.id][0]}</p>
      )}
    </div>
  );

  // Render multi-choice question
  const renderMultiChoice = (question: any) => (
    <div key={question.id} className="mb-6">
      <label className="form-label">
        {question.label}
        {question.required && <span className="text-red-500 ml-1">*</span>}
      </label>
      <div className="space-y-2">
        {question.options?.map((option: string) => (
          <label key={option} className="flex items-center">
            <input
              type="checkbox"
              value={option}
              checked={(answers[question.id] as string[]).includes(option)}
              onChange={() => handleMultiChoice(question.id, option)}
              className="mr-2"
            />
            <span>{option}</span>
          </label>
        ))}
      </div>
      {errors[question.id] && (
        <p className="text-error-600 text-sm mt-1">{errors[question.id][0]}</p>
      )}
    </div>
  );

  // Render text question
  const renderTextQuestion = (question: any) => (
    <div key={question.id} className="mb-6">
      <label className="form-label">
        {question.label}
        {question.required && <span className="text-red-500 ml-1">*</span>}
      </label>
      <textarea
        value={answers[question.id]}
        onChange={(e) => handleTextInput(question.id, e.target.value)}
        placeholder={question.placeholder}
        maxLength={question.maxLength}
        rows={3}
        className="form-input"
      />
      {errors[question.id] && (
        <p className="text-error-600 text-sm mt-1">{errors[question.id][0]}</p>
      )}
    </div>
  );

  return (
    <div className="min-h-screen bg-gray-50 py-12">
      <div className="max-w-2xl mx-auto px-4">
        <div className="text-center mb-8">
          <h1 className="text-3xl font-bold text-gray-900 mb-2">
            Questionnaire
          </h1>
          <p className="text-gray-600">
            Please answer the following questions. Your responses are anonymous.
          </p>
        </div>

        <form onSubmit={handleSubmit} className="card">
          {/* Render questions based on their type */}
          {questions.map((question) => {
            switch (question.type) {
              case 'single':
                return renderSingleChoice(question);
              case 'multi':
                return renderMultiChoice(question);
              case 'text':
                return renderTextQuestion(question);
              default:
                return null;
            }
          })}

          {/* General errors */}
          {errors.general && (
            <div className="mb-4 p-3 bg-error-50 border border-error-200 rounded-lg">
              <ul className="text-error-600 text-sm">
                {errors.general.map((error, index) => (
                  <li key={index}>• {error}</li>
                ))}
              </ul>
            </div>
          )}

          {/* API errors */}
          {generalError && (
            <div className="mb-4 p-3 bg-error-50 border border-error-200 rounded-lg">
              <p className="text-error-600 text-sm">{generalError}</p>
            </div>
          )}

          {/* Submit button */}
          <button
            type="submit"
            disabled={isSubmitting}
            className="btn-primary w-full"
          >
            {isSubmitting ? 'Submitting...' : 'Submit Questionnaire'}
          </button>
        </form>
      </div>
    </div>
  );
}
