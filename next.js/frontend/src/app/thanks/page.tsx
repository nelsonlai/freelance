// Thank you page component
// As per SRS: /thanks — submission confirmation; show last 6 chars of id
// This page confirms successful submission and displays the response ID

'use client';

import { useSearchParams } from 'next/navigation';
import Link from 'next/link';

export default function ThanksPage() {
  const searchParams = useSearchParams();
  const responseId = searchParams.get('rid');

  // Extract last 6 characters of the response ID for display
  const displayId = responseId ? responseId.slice(-6) : '';

  return (
    <div className="min-h-screen bg-gray-50 py-12">
      <div className="max-w-2xl mx-auto px-4 text-center">
        {/* Success icon */}
        <div className="mb-6">
          <div className="mx-auto w-16 h-16 bg-success-100 rounded-full flex items-center justify-center">
            <svg
              className="w-8 h-8 text-success-600"
              fill="none"
              stroke="currentColor"
              viewBox="0 0 24 24"
            >
              <path
                strokeLinecap="round"
                strokeLinejoin="round"
                strokeWidth={2}
                d="M5 13l4 4L19 7"
              />
            </svg>
          </div>
        </div>

        {/* Success message */}
        <h1 className="text-3xl font-bold text-gray-900 mb-4">
          Thank You!
        </h1>
        
        <p className="text-lg text-gray-600 mb-6">
          Your questionnaire has been submitted successfully.
        </p>

        {/* Response ID display */}
        {responseId && (
          <div className="card mb-8">
            <h2 className="text-lg font-semibold text-gray-900 mb-2">
              Response ID
            </h2>
            <p className="text-sm text-gray-600 mb-2">
              Please save this ID for your records:
            </p>
            <div className="bg-gray-100 p-3 rounded-lg">
              <code className="text-lg font-mono text-gray-800">
                {responseId}
              </code>
            </div>
            <p className="text-xs text-gray-500 mt-2">
              Last 6 characters: <strong>{displayId}</strong>
            </p>
          </div>
        )}

        {/* Additional information */}
        <div className="card mb-8">
          <h3 className="text-lg font-semibold text-gray-900 mb-3">
            What happens next?
          </h3>
          <ul className="text-left text-gray-600 space-y-2">
            <li className="flex items-start">
              <span className="text-success-600 mr-2">✓</span>
              Your responses have been securely stored
            </li>
            <li className="flex items-start">
              <span className="text-success-600 mr-2">✓</span>
              All data is anonymous and confidential
            </li>
            <li className="flex items-start">
              <span className="text-success-600 mr-2">✓</span>
              Your feedback will help improve our services
            </li>
          </ul>
        </div>

        {/* Action buttons */}
        <div className="space-y-3">
          <Link
            href="/questionnaire"
            className="btn-primary inline-block w-full sm:w-auto"
          >
            Submit Another Response
          </Link>
          
          <div className="text-sm text-gray-500">
            Or{' '}
            <Link
              href="/"
              className="text-primary-600 hover:text-primary-700 underline"
            >
              return to home
            </Link>
          </div>
        </div>

        {/* Footer note */}
        <div className="mt-12 text-xs text-gray-400">
          <p>
            If you have any questions about your submission, please contact support.
          </p>
        </div>
      </div>
    </div>
  );
}
