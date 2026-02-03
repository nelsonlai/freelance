// Home page component
// Provides a landing page and navigation to the questionnaire

import Link from 'next/link';

export default function HomePage() {
  return (
    <div className="min-h-screen bg-gray-50 py-12">
      <div className="max-w-4xl mx-auto px-4 text-center">
        {/* Hero Section */}
        <div className="mb-12">
          <h1 className="text-4xl md:text-6xl font-bold text-gray-900 mb-6">
            Welcome to the
            <span className="text-primary-600 block">Questionnaire System</span>
          </h1>
          <p className="text-xl text-gray-600 mb-8 max-w-2xl mx-auto">
            A production-ready platform for collecting and analyzing questionnaire responses. 
            Built with modern technologies and security best practices.
          </p>
          
          {/* Call to Action */}
          <div className="space-y-4">
            <Link
              href="/questionnaire"
              className="btn-primary text-lg px-8 py-3 inline-block"
            >
              Start Questionnaire
            </Link>
            
            <div className="text-sm text-gray-500">
              Takes only 2-3 minutes to complete
            </div>
          </div>
        </div>

        {/* Features Section */}
        <div className="grid md:grid-cols-3 gap-8 mb-16">
          <div className="card text-center">
            <div className="w-12 h-12 bg-primary-100 rounded-lg flex items-center justify-center mx-auto mb-4">
              <svg className="w-6 h-6 text-primary-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9 12l2 2 4-4m6 2a9 9 0 11-18 0 9 9 0 0118 0z" />
              </svg>
            </div>
            <h3 className="text-lg font-semibold text-gray-900 mb-2">Secure & Private</h3>
            <p className="text-gray-600">Your responses are completely anonymous and securely stored</p>
          </div>
          
          <div className="card text-center">
            <div className="w-12 h-12 bg-success-100 rounded-lg flex items-center justify-center mx-auto mb-4">
              <svg className="w-6 h-6 text-success-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M13 10V3L4 14h7v7l9-11h-7z" />
              </svg>
            </div>
            <h3 className="text-lg font-semibold text-gray-900 mb-2">Fast & Easy</h3>
            <p className="text-gray-600">Simple questions that take just minutes to complete</p>
          </div>
          
          <div className="card text-center">
            <div className="w-12 h-12 bg-blue-100 rounded-lg flex items-center justify-center mx-auto mb-4">
              <svg className="w-6 h-6 text-blue-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9 19v-6a2 2 0 00-2-2H5a2 2 0 00-2 2v6a2 2 0 002 2h2a2 2 0 002-2zm0 0V9a2 2 0 012-2h2a2 2 0 012 2v10m-6 0a2 2 0 002 2h2a2 2 0 002-2m0 0V5a2 2 0 012-2h2a2 2 0 012 2v14a2 2 0 01-2 2h-2a2 2 0 01-2-2z" />
              </svg>
            </div>
            <h3 className="text-lg font-semibold text-gray-900 mb-2">Data Insights</h3>
            <p className="text-gray-600">Help us improve by providing valuable feedback</p>
          </div>
        </div>

        {/* Technology Stack */}
        <div className="bg-white rounded-lg shadow-md p-8">
          <h2 className="text-2xl font-bold text-gray-900 mb-6">Built with Modern Technologies</h2>
          <div className="grid grid-cols-2 md:grid-cols-4 gap-6">
            <div className="text-center">
              <div className="text-2xl font-bold text-primary-600 mb-2">Next.js</div>
              <div className="text-sm text-gray-600">React Framework</div>
            </div>
            <div className="text-center">
              <div className="text-2xl font-bold text-green-600 mb-2">Express</div>
              <div className="text-sm text-gray-600">Node.js Backend</div>
            </div>
            <div className="text-center">
              <div className="text-2xl font-bold text-blue-600 mb-2">Prisma</div>
              <div className="text-sm text-gray-600">Database ORM</div>
            </div>
            <div className="text-center">
              <div className="text-2xl font-bold text-purple-600 mb-2">MySQL</div>
              <div className="text-sm text-gray-600">Database</div>
            </div>
          </div>
        </div>

        {/* Footer CTA */}
        <div className="mt-16">
          <p className="text-lg text-gray-600 mb-6">
            Ready to get started?
          </p>
          <Link
            href="/questionnaire"
            className="btn-primary text-lg px-8 py-3 inline-block"
          >
            Begin Questionnaire
          </Link>
        </div>
      </div>
    </div>
  );
}
