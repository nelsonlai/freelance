/** @type {import('next').NextConfig} */
const nextConfig = {
  // Enable experimental features for better performance
  experimental: {
    appDir: true,
  },
  
  // Environment variables for the frontend
  env: {
    API_BASE_URL: process.env.API_BASE_URL || 'http://localhost:4000',
  },
  
  // Image optimization settings
  images: {
    domains: [],
  },
  
  // Redirects for better UX (commented out since we now have a home page)
  // async redirects() {
  //   return [
  //     {
  //       source: '/',
  //       destination: '/questionnaire',
  //       permanent: false,
  //     },
  //   ];
  // },
};

module.exports = nextConfig;
