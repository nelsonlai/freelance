# Testing & CI/CD Examples
import unittest
from unittest.mock import Mock, patch, MagicMock
import pytest
import coverage
import subprocess
import os
import json
from typing import List, Dict, Any

print("Testing & CI/CD Examples")
print("=" * 25)

# 1. Unit Testing with unittest
print("1. Unit Testing with unittest")
print("-" * 30)

class Calculator:
    """Simple calculator class for testing."""
    
    def add(self, a: float, b: float) -> float:
        """Add two numbers."""
        return a + b
    
    def subtract(self, a: float, b: float) -> float:
        """Subtract two numbers."""
        return a - b
    
    def multiply(self, a: float, b: float) -> float:
        """Multiply two numbers."""
        return a * b
    
    def divide(self, a: float, b: float) -> float:
        """Divide two numbers."""
        if b == 0:
            raise ValueError("Cannot divide by zero")
        return a / b
    
    def power(self, base: float, exponent: float) -> float:
        """Calculate power."""
        return base ** exponent

class TestCalculator(unittest.TestCase):
    """Test cases for Calculator class."""
    
    def setUp(self):
        """Set up test fixtures."""
        self.calculator = Calculator()
    
    def tearDown(self):
        """Clean up after tests."""
        pass
    
    def test_add(self):
        """Test addition."""
        self.assertEqual(self.calculator.add(2, 3), 5)
        self.assertEqual(self.calculator.add(-1, 1), 0)
        self.assertEqual(self.calculator.add(0, 0), 0)
    
    def test_subtract(self):
        """Test subtraction."""
        self.assertEqual(self.calculator.subtract(5, 3), 2)
        self.assertEqual(self.calculator.subtract(1, 1), 0)
        self.assertEqual(self.calculator.subtract(0, 5), -5)
    
    def test_multiply(self):
        """Test multiplication."""
        self.assertEqual(self.calculator.multiply(2, 3), 6)
        self.assertEqual(self.calculator.multiply(-2, 3), -6)
        self.assertEqual(self.calculator.multiply(0, 5), 0)
    
    def test_divide(self):
        """Test division."""
        self.assertEqual(self.calculator.divide(6, 2), 3)
        self.assertEqual(self.calculator.divide(5, 2), 2.5)
        self.assertEqual(self.calculator.divide(0, 5), 0)
    
    def test_divide_by_zero(self):
        """Test division by zero."""
        with self.assertRaises(ValueError):
            self.calculator.divide(5, 0)
    
    def test_power(self):
        """Test power calculation."""
        self.assertEqual(self.calculator.power(2, 3), 8)
        self.assertEqual(self.calculator.power(5, 0), 1)
        self.assertEqual(self.calculator.power(2, -1), 0.5)
    
    def test_add_with_floats(self):
        """Test addition with floating point numbers."""
        self.assertAlmostEqual(self.calculator.add(0.1, 0.2), 0.3, places=7)
    
    def test_multiply_with_floats(self):
        """Test multiplication with floating point numbers."""
        self.assertAlmostEqual(self.calculator.multiply(0.1, 0.2), 0.02, places=7)

# Run unit tests
if __name__ == '__main__':
    unittest.main(verbosity=2, exit=False)

# 2. Mocking and Test Doubles
print("\n2. Mocking and Test Doubles")
print("-" * 30)

class EmailService:
    """Email service for sending emails."""
    
    def send_email(self, to: str, subject: str, body: str) -> bool:
        """Send an email."""
        # Simulate email sending
        print(f"Sending email to {to}: {subject}")
        return True

class UserService:
    """User service that depends on EmailService."""
    
    def __init__(self, email_service: EmailService):
        self.email_service = email_service
    
    def register_user(self, email: str, name: str) -> bool:
        """Register a new user and send welcome email."""
        # Simulate user registration
        print(f"Registering user: {name} ({email})")
        
        # Send welcome email
        success = self.email_service.send_email(
            email, 
            "Welcome!", 
            f"Hello {name}, welcome to our service!"
        )
        
        return success

class TestUserService(unittest.TestCase):
    """Test cases for UserService with mocking."""
    
    def setUp(self):
        """Set up test fixtures."""
        self.mock_email_service = Mock(spec=EmailService)
        self.user_service = UserService(self.mock_email_service)
    
    def test_register_user_success(self):
        """Test successful user registration."""
        # Configure mock
        self.mock_email_service.send_email.return_value = True
        
        # Test
        result = self.user_service.register_user("test@example.com", "Test User")
        
        # Assertions
        self.assertTrue(result)
        self.mock_email_service.send_email.assert_called_once_with(
            "test@example.com",
            "Welcome!",
            "Hello Test User, welcome to our service!"
        )
    
    def test_register_user_email_failure(self):
        """Test user registration when email fails."""
        # Configure mock
        self.mock_email_service.send_email.return_value = False
        
        # Test
        result = self.user_service.register_user("test@example.com", "Test User")
        
        # Assertions
        self.assertFalse(result)
        self.mock_email_service.send_email.assert_called_once()
    
    def test_register_user_email_exception(self):
        """Test user registration when email raises exception."""
        # Configure mock
        self.mock_email_service.send_email.side_effect = Exception("Email service unavailable")
        
        # Test
        with self.assertRaises(Exception):
            self.user_service.register_user("test@example.com", "Test User")
        
        # Assertions
        self.mock_email_service.send_email.assert_called_once()

# Test mocking
test_suite = unittest.TestLoader().loadTestsFromTestCase(TestUserService)
unittest.TextTestRunner(verbosity=2).run(test_suite)

# 3. Test-Driven Development (TDD)
print("\n3. Test-Driven Development (TDD)")
print("-" * 35)

class BankAccount:
    """Bank account class developed using TDD."""
    
    def __init__(self, initial_balance: float = 0.0):
        self.balance = initial_balance
        self.transactions = []
    
    def deposit(self, amount: float) -> bool:
        """Deposit money into the account."""
        if amount <= 0:
            return False
        
        self.balance += amount
        self.transactions.append(('deposit', amount))
        return True
    
    def withdraw(self, amount: float) -> bool:
        """Withdraw money from the account."""
        if amount <= 0 or amount > self.balance:
            return False
        
        self.balance -= amount
        self.transactions.append(('withdraw', amount))
        return True
    
    def get_balance(self) -> float:
        """Get current balance."""
        return self.balance
    
    def get_transactions(self) -> List[tuple]:
        """Get transaction history."""
        return self.transactions.copy()

class TestBankAccount(unittest.TestCase):
    """Test cases for BankAccount developed using TDD."""
    
    def setUp(self):
        """Set up test fixtures."""
        self.account = BankAccount()
    
    def test_initial_balance(self):
        """Test initial balance."""
        self.assertEqual(self.account.get_balance(), 0.0)
    
    def test_deposit_positive_amount(self):
        """Test depositing positive amount."""
        result = self.account.deposit(100.0)
        self.assertTrue(result)
        self.assertEqual(self.account.get_balance(), 100.0)
    
    def test_deposit_negative_amount(self):
        """Test depositing negative amount."""
        result = self.account.deposit(-50.0)
        self.assertFalse(result)
        self.assertEqual(self.account.get_balance(), 0.0)
    
    def test_deposit_zero_amount(self):
        """Test depositing zero amount."""
        result = self.account.deposit(0.0)
        self.assertFalse(result)
        self.assertEqual(self.account.get_balance(), 0.0)
    
    def test_withdraw_positive_amount(self):
        """Test withdrawing positive amount."""
        self.account.deposit(100.0)
        result = self.account.withdraw(50.0)
        self.assertTrue(result)
        self.assertEqual(self.account.get_balance(), 50.0)
    
    def test_withdraw_negative_amount(self):
        """Test withdrawing negative amount."""
        self.account.deposit(100.0)
        result = self.account.withdraw(-50.0)
        self.assertFalse(result)
        self.assertEqual(self.account.get_balance(), 100.0)
    
    def test_withdraw_zero_amount(self):
        """Test withdrawing zero amount."""
        self.account.deposit(100.0)
        result = self.account.withdraw(0.0)
        self.assertFalse(result)
        self.assertEqual(self.account.get_balance(), 100.0)
    
    def test_withdraw_insufficient_funds(self):
        """Test withdrawing more than available balance."""
        self.account.deposit(50.0)
        result = self.account.withdraw(100.0)
        self.assertFalse(result)
        self.assertEqual(self.account.get_balance(), 50.0)
    
    def test_transaction_history(self):
        """Test transaction history."""
        self.account.deposit(100.0)
        self.account.withdraw(30.0)
        self.account.deposit(20.0)
        
        transactions = self.account.get_transactions()
        expected = [('deposit', 100.0), ('withdraw', 30.0), ('deposit', 20.0)]
        self.assertEqual(transactions, expected)
    
    def test_multiple_deposits_and_withdrawals(self):
        """Test multiple deposits and withdrawals."""
        self.account.deposit(100.0)
        self.account.withdraw(30.0)
        self.account.deposit(20.0)
        self.account.withdraw(10.0)
        
        self.assertEqual(self.account.get_balance(), 80.0)
        self.assertEqual(len(self.account.get_transactions()), 4)

# Test TDD implementation
test_suite = unittest.TestLoader().loadTestsFromTestCase(TestBankAccount)
unittest.TextTestRunner(verbosity=2).run(test_suite)

# 4. Integration Testing
print("\n4. Integration Testing")
print("-" * 22)

class DatabaseService:
    """Database service for integration testing."""
    
    def __init__(self):
        self.data = {}
    
    def save_user(self, user_id: str, user_data: Dict[str, Any]) -> bool:
        """Save user data."""
        self.data[user_id] = user_data
        return True
    
    def get_user(self, user_id: str) -> Dict[str, Any]:
        """Get user data."""
        return self.data.get(user_id, {})

class CacheService:
    """Cache service for integration testing."""
    
    def __init__(self):
        self.cache = {}
    
    def set(self, key: str, value: Any) -> bool:
        """Set cache value."""
        self.cache[key] = value
        return True
    
    def get(self, key: str) -> Any:
        """Get cache value."""
        return self.cache.get(key)

class UserManager:
    """User manager that integrates multiple services."""
    
    def __init__(self, db_service: DatabaseService, cache_service: CacheService):
        self.db_service = db_service
        self.cache_service = cache_service
    
    def create_user(self, user_id: str, user_data: Dict[str, Any]) -> bool:
        """Create a new user."""
        # Save to database
        db_success = self.db_service.save_user(user_id, user_data)
        
        if db_success:
            # Cache the user data
            self.cache_service.set(f"user:{user_id}", user_data)
            return True
        
        return False
    
    def get_user(self, user_id: str) -> Dict[str, Any]:
        """Get user data."""
        # Try cache first
        cached_user = self.cache_service.get(f"user:{user_id}")
        if cached_user:
            return cached_user
        
        # Fallback to database
        user_data = self.db_service.get_user(user_id)
        if user_data:
            # Cache the result
            self.cache_service.set(f"user:{user_id}", user_data)
        
        return user_data

class TestUserManagerIntegration(unittest.TestCase):
    """Integration tests for UserManager."""
    
    def setUp(self):
        """Set up test fixtures."""
        self.db_service = DatabaseService()
        self.cache_service = CacheService()
        self.user_manager = UserManager(self.db_service, self.cache_service)
    
    def test_create_user_integration(self):
        """Test user creation integration."""
        user_id = "user123"
        user_data = {"name": "John Doe", "email": "john@example.com"}
        
        # Create user
        result = self.user_manager.create_user(user_id, user_data)
        
        # Verify integration
        self.assertTrue(result)
        
        # Check database
        db_user = self.db_service.get_user(user_id)
        self.assertEqual(db_user, user_data)
        
        # Check cache
        cached_user = self.cache_service.get(f"user:{user_id}")
        self.assertEqual(cached_user, user_data)
    
    def test_get_user_cache_integration(self):
        """Test user retrieval with cache integration."""
        user_id = "user456"
        user_data = {"name": "Jane Smith", "email": "jane@example.com"}
        
        # Create user
        self.user_manager.create_user(user_id, user_data)
        
        # Get user (should come from cache)
        retrieved_user = self.user_manager.get_user(user_id)
        self.assertEqual(retrieved_user, user_data)
        
        # Verify cache was used
        cached_user = self.cache_service.get(f"user:{user_id}")
        self.assertEqual(cached_user, user_data)
    
    def test_get_user_database_fallback(self):
        """Test user retrieval with database fallback."""
        user_id = "user789"
        user_data = {"name": "Bob Johnson", "email": "bob@example.com"}
        
        # Save directly to database (bypass cache)
        self.db_service.save_user(user_id, user_data)
        
        # Get user (should come from database and cache)
        retrieved_user = self.user_manager.get_user(user_id)
        self.assertEqual(retrieved_user, user_data)
        
        # Verify cache was populated
        cached_user = self.cache_service.get(f"user:{user_id}")
        self.assertEqual(cached_user, user_data)

# Test integration
test_suite = unittest.TestLoader().loadTestsFromTestCase(TestUserManagerIntegration)
unittest.TextTestRunner(verbosity=2).run(test_suite)

# 5. Code Coverage
print("\n5. Code Coverage")
print("-" * 18)

def calculate_coverage():
    """Calculate code coverage."""
    
    # Start coverage
    cov = coverage.Coverage()
    cov.start()
    
    # Run tests
    test_suite = unittest.TestLoader().loadTestsFromTestCase(TestCalculator)
    unittest.TextTestRunner(verbosity=0).run(test_suite)
    
    # Stop coverage
    cov.stop()
    cov.save()
    
    # Generate report
    cov.report()
    
    # Generate HTML report
    cov.html_report(directory='htmlcov')
    
    return cov

# Test coverage
try:
    coverage_result = calculate_coverage()
    print("Code coverage analysis completed")
except Exception as e:
    print(f"Coverage analysis failed: {e}")

# 6. Continuous Integration
print("\n6. Continuous Integration")
print("-" * 28)

def create_ci_config():
    """Create CI configuration files."""
    
    # GitHub Actions workflow
    github_actions = '''
name: Python CI

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

jobs:
  test:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        python-version: [3.8, 3.9, 3.10, 3.11]

    steps:
    - uses: actions/checkout@v3
    
    - name: Set up Python ${{ matrix.python-version }}
      uses: actions/setup-python@v3
      with:
        python-version: ${{ matrix.python-version }}
    
    - name: Install dependencies
      run: |
        python -m pip install --upgrade pip
        pip install -r requirements.txt
        pip install pytest pytest-cov
    
    - name: Lint with flake8
      run: |
        pip install flake8
        flake8 . --count --select=E9,F63,F7,F82 --show-source --statistics
    
    - name: Test with pytest
      run: |
        pytest tests/ --cov=. --cov-report=xml
    
    - name: Upload coverage to Codecov
      uses: codecov/codecov-action@v3
      with:
        file: ./coverage.xml
        flags: unittests
        name: codecov-umbrella
'''
    
    with open('.github/workflows/ci.yml', 'w') as f:
        f.write(github_actions)
    
    # GitLab CI configuration
    gitlab_ci = '''
stages:
  - test
  - coverage
  - deploy

variables:
  PIP_CACHE_DIR: "$CI_PROJECT_DIR/.cache/pip"

cache:
  paths:
    - .cache/pip/
    - venv/

before_script:
  - python -m venv venv
  - source venv/bin/activate
  - pip install --upgrade pip
  - pip install -r requirements.txt

test:
  stage: test
  script:
    - source venv/bin/activate
    - pytest tests/ --cov=. --cov-report=xml
  coverage: '/TOTAL.*\s+(\d+%)$/'
  artifacts:
    reports:
      coverage_report:
        coverage_format: cobertura
        path: coverage.xml

deploy:
  stage: deploy
  script:
    - echo "Deploying to production"
  only:
    - main
'''
    
    with open('.gitlab-ci.yml', 'w') as f:
        f.write(gitlab_ci)
    
    # Jenkinsfile
    jenkinsfile = '''
pipeline {
    agent any
    
    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }
        
        stage('Setup') {
            steps {
                sh 'python -m venv venv'
                sh 'source venv/bin/activate && pip install -r requirements.txt'
            }
        }
        
        stage('Test') {
            steps {
                sh 'source venv/bin/activate && pytest tests/ --cov=. --cov-report=xml'
            }
        }
        
        stage('Coverage') {
            steps {
                publishCoverage adapters: [
                    coberturaAdapter('coverage.xml')
                ], sourceFileResolver: sourceFiles('STORE_LAST_BUILD')
            }
        }
        
        stage('Deploy') {
            when {
                branch 'main'
            }
            steps {
                echo 'Deploying to production'
            }
        }
    }
    
    post {
        always {
            cleanWs()
        }
        success {
            echo 'Pipeline succeeded'
        }
        failure {
            echo 'Pipeline failed'
        }
    }
}
'''
    
    with open('Jenkinsfile', 'w') as f:
        f.write(jenkinsfile)
    
    print("CI configuration files created")

# Create CI configs
create_ci_config()

# 7. Test Automation
print("\n7. Test Automation")
print("-" * 18)

def run_automated_tests():
    """Run automated tests."""
    
    # Test discovery
    def discover_tests():
        """Discover all test files."""
        test_files = []
        for root, dirs, files in os.walk('.'):
            for file in files:
                if file.startswith('test_') and file.endswith('.py'):
                    test_files.append(os.path.join(root, file))
        return test_files
    
    # Test execution
    def execute_tests(test_files):
        """Execute all test files."""
        results = []
        for test_file in test_files:
            try:
                result = subprocess.run(['python', '-m', 'pytest', test_file, '-v'], 
                                      capture_output=True, text=True)
                results.append({
                    'file': test_file,
                    'success': result.returncode == 0,
                    'output': result.stdout,
                    'error': result.stderr
                })
            except Exception as e:
                results.append({
                    'file': test_file,
                    'success': False,
                    'output': '',
                    'error': str(e)
                })
        return results
    
    # Test reporting
    def generate_test_report(results):
        """Generate test report."""
        total_tests = len(results)
        successful_tests = sum(1 for r in results if r['success'])
        failed_tests = total_tests - successful_tests
        
        report = {
            'total_tests': total_tests,
            'successful_tests': successful_tests,
            'failed_tests': failed_tests,
            'success_rate': (successful_tests / total_tests * 100) if total_tests > 0 else 0,
            'results': results
        }
        
        return report
    
    # Run automated tests
    test_files = discover_tests()
    if not test_files:
        print("No test files found")
        return
    
    results = execute_tests(test_files)
    report = generate_test_report(results)
    
    print(f"Test Report:")
    print(f"Total tests: {report['total_tests']}")
    print(f"Successful: {report['successful_tests']}")
    print(f"Failed: {report['failed_tests']}")
    print(f"Success rate: {report['success_rate']:.1f}%")
    
    return report

# Run automated tests
test_report = run_automated_tests()

# 8. Performance Testing
print("\n8. Performance Testing")
print("-" * 22)

import time
import threading
from concurrent.futures import ThreadPoolExecutor

class PerformanceTest:
    """Performance testing utilities."""
    
    @staticmethod
    def measure_execution_time(func, *args, **kwargs):
        """Measure function execution time."""
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        return result, end_time - start_time
    
    @staticmethod
    def stress_test(func, iterations=1000, *args, **kwargs):
        """Run stress test on a function."""
        results = []
        for i in range(iterations):
            result, execution_time = PerformanceTest.measure_execution_time(func, *args, **kwargs)
            results.append(execution_time)
        return results
    
    @staticmethod
    def concurrent_test(func, num_threads=10, iterations_per_thread=100, *args, **kwargs):
        """Run concurrent test on a function."""
        results = []
        
        def worker():
            thread_results = []
            for _ in range(iterations_per_thread):
                result, execution_time = PerformanceTest.measure_execution_time(func, *args, **kwargs)
                thread_results.append(execution_time)
            return thread_results
        
        with ThreadPoolExecutor(max_workers=num_threads) as executor:
            futures = [executor.submit(worker) for _ in range(num_threads)]
            for future in futures:
                results.extend(future.result())
        
        return results

# Test performance
def sample_function(n):
    """Sample function for performance testing."""
    return sum(range(n))

# Measure execution time
result, execution_time = PerformanceTest.measure_execution_time(sample_function, 1000)
print(f"Sample function execution time: {execution_time:.6f} seconds")

# Stress test
stress_results = PerformanceTest.stress_test(sample_function, 100, 1000)
avg_time = sum(stress_results) / len(stress_results)
print(f"Average execution time over 100 iterations: {avg_time:.6f} seconds")

# Concurrent test
concurrent_results = PerformanceTest.concurrent_test(sample_function, 5, 20, 1000)
avg_concurrent_time = sum(concurrent_results) / len(concurrent_results)
print(f"Average execution time with 5 concurrent threads: {avg_concurrent_time:.6f} seconds")

print("\nTesting & CI/CD examples completed!")