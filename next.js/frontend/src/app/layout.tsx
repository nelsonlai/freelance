// Root layout component for the Next.js application
// Provides the base HTML structure and global styles

import type { Metadata } from 'next';
import './globals.css';

export const metadata: Metadata = {
  title: 'Questionnaire System',
  description: 'A production-ready questionnaire system for collecting and analyzing responses',
  keywords: 'questionnaire, survey, feedback, data collection',
  authors: [{ name: 'Questionnaire System Team' }],
  viewport: 'width=device-width, initial-scale=1',
};

export default function RootLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  return (
    <html lang="en">
      <head>
        {/* Preconnect to external domains for performance */}
        <link rel="preconnect" href="https://fonts.googleapis.com" />
        <link rel="preconnect" href="https://fonts.gstatic.com" crossOrigin="anonymous" />
        
        {/* Load Inter font for better typography */}
        <link
          href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap"
          rel="stylesheet"
        />
      </head>
      <body className="antialiased">
        {/* Main content */}
        <main>
          {children}
        </main>
        
        {/* Footer */}
        <footer className="bg-gray-800 text-white py-8 mt-16">
          <div className="max-w-6xl mx-auto px-4 text-center">
            <p className="text-gray-300">
              © 2024 Questionnaire System. Built with Next.js and Express.
            </p>
            <p className="text-sm text-gray-400 mt-2">
              Secure • Anonymous • Confidential
            </p>
          </div>
        </footer>
      </body>
    </html>
  );
}
