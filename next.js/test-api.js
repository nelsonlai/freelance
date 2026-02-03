// Simple API test script
// Use this to test the backend API endpoints
// Run with: node test-api.js

const API_BASE = 'http://localhost:4000';

// Test data
const testResponse = {
  answers: {
    q1: 'A',
    q2: ['X', 'Y'],
    q3: 'This is a test response from the API test script'
  }
};

// Helper function to make HTTP requests
async function makeRequest(url, options = {}) {
  try {
    const response = await fetch(url, {
      headers: {
        'Content-Type': 'application/json',
        ...options.headers
      },
      ...options
    });
    
    const data = await response.json();
    return { status: response.status, data };
  } catch (error) {
    return { status: 'ERROR', data: { error: error.message } };
  }
}

// Test functions
async function testHealthCheck() {
  console.log('🏥 Testing health check...');
  const result = await makeRequest(`${API_BASE}/health`);
  console.log(`Status: ${result.status}`);
  console.log('Response:', result.data);
  console.log('---');
}

async function testCreateResponse() {
  console.log('📝 Testing response creation...');
  const result = await makeRequest(`${API_BASE}/api/v1/responses`, {
    method: 'POST',
    body: JSON.stringify(testResponse)
  });
  console.log(`Status: ${result.status}`);
  console.log('Response:', result.data);
  
  if (result.status === 201 && result.data.id) {
    console.log('✅ Response created successfully!');
    return result.data.id;
  } else {
    console.log('❌ Failed to create response');
    return null;
  }
}

async function testGetResponse(responseId) {
  if (!responseId) {
    console.log('⏭️  Skipping response retrieval test');
    return;
  }
  
  console.log('🔍 Testing response retrieval...');
  const result = await makeRequest(`${API_BASE}/api/v1/responses/${responseId}`);
  console.log(`Status: ${result.status}`);
  console.log('Response:', result.data);
  console.log('---');
}

async function testGetMetrics() {
  console.log('📊 Testing metrics endpoint...');
  const result = await makeRequest(`${API_BASE}/api/v1/metrics`);
  console.log(`Status: ${result.status}`);
  console.log('Response:', result.data);
  console.log('---');
}

async function testInvalidRequest() {
  console.log('🚫 Testing invalid request handling...');
  const invalidResponse = {
    answers: {
      q1: 'INVALID', // Invalid value
      q2: ['X', 'Y', 'Z', 'W'], // Too many selections
      q3: 'A'.repeat(600) // Too long text
    }
  };
  
  const result = await makeRequest(`${API_BASE}/api/v1/responses`, {
    method: 'POST',
    body: JSON.stringify(invalidResponse)
  });
  console.log(`Status: ${result.status}`);
  console.log('Response:', result.data);
  console.log('---');
}

// Main test runner
async function runTests() {
  console.log('🧪 Starting API tests...\n');
  
  try {
    // Test health check
    await testHealthCheck();
    
    // Test creating a response
    const responseId = await testCreateResponse();
    
    // Test retrieving the response
    await testGetResponse(responseId);
    
    // Test metrics endpoint
    await testGetMetrics();
    
    // Test invalid request handling
    await testInvalidRequest();
    
    console.log('🎉 All tests completed!');
    
  } catch (error) {
    console.error('❌ Test suite failed:', error);
  }
}

// Run tests if this script is executed directly
if (typeof require !== 'undefined' && require.main === module) {
  runTests();
}

module.exports = { runTests };
