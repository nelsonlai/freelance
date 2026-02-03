import type { Metadata } from 'next';
import './globals.css';

export const metadata: Metadata = {
  title: 'User Form',
  description: 'First name, last name, email form with Next.js + Express + MySQL',
};

export default function RootLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  return (
    <html lang="en">
      <body>{children}</body>
    </html>
  );
}
