# 8. Testing & CI/CD - Quality Assurance and Deployment

Testing and CI/CD are essential for maintaining code quality and enabling reliable deployments. This lesson covers advanced testing techniques, continuous integration, and deployment practices for professional Python development.

## Advanced Testing with pytest

### Basic pytest Setup

```python
import pytest
import unittest
from unittest.mock import Mock, patch, MagicMock
import sys
import os

# Add project root to path
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

# Sample code to test
class Calculator:
    """Simple calculator class for testing."""
    
    def add(self, a, b):
        """Add two numbers."""
        if not isinstance(a, (int, float)) or not isinstance(b, (int, float)):
            raise TypeError("Arguments must be numbers")
        return a + b
    
    def divide(self, a, b):
        """Divide two numbers."""
        if not isinstance(a, (int, float)) or not isinstance(b, (int, float)):
            raise TypeError("Arguments must be numbers")
        if b == 0:
            raise ValueError("Cannot divide by zero")
        return a / b
    
    def multiply(self, a, b):
        """Multiply two numbers."""
        if not isinstance(a, (int, float)) or not isinstance(b, (int, float)):
            raise TypeError("Arguments must be numbers")
        return a * b

# Basic pytest tests
def test_calculator_add():
    """Test calculator addition."""
    calc = Calculator()
    assert calc.add(2, 3) == 5
    assert calc.add(-1, 1) == 0
    assert calc.add(0, 0) == 0

def test_calculator_divide():
    """Test calculator division."""
    calc = Calculator()
    assert calc.divide(10, 2) == 5
    assert calc.divide(7, 3) == pytest.approx(2.3333333333333335)
    
    # Test division by zero
    with pytest.raises(ValueError, match="Cannot divide by zero"):
        calc.divide(10, 0)

def test_calculator_type_errors():
    """Test calculator type error handling."""
    calc = Calculator()
    
    with pytest.raises(TypeError, match="Arguments must be numbers"):
        calc.add("2", 3)
    
    with pytest.raises(TypeError, match="Arguments must be numbers"):
        calc.divide(10, "2")

# Parametrized tests
@pytest.mark.parametrize("a,b,expected", [
    (2, 3, 5),
    (-1, 1, 0),
    (0, 0, 0),
    (1.5, 2.5, 4.0)
])
def test_add_parametrized(a, b, expected):
    """Parametrized test for addition."""
    calc = Calculator()
    assert calc.add(a, b) == expected

@pytest.mark.parametrize("a,b,expected", [
    (10, 2, 5),
    (15, 3, 5),
    (7, 2, 3.5),
    (0, 5, 0)
])
def test_divide_parametrized(a, b, expected):
    """Parametrized test for division."""
    calc = Calculator()
    assert calc.divide(a, b) == expected

# Fixtures
@pytest.fixture
def calculator():
    """Fixture providing a calculator instance."""
    return Calculator()

@pytest.fixture
def sample_data():
    """Fixture providing sample test data."""
    return {
        'numbers': [1, 2, 3, 4, 5],
        'strings': ['hello', 'world', 'python'],
        'mixed': [1, 'hello', 3.14, 'world']
    }

def test_calculator_with_fixture(calculator, sample_data):
    """Test using fixtures."""
    # Test with numbers from fixture
    for num in sample_data['numbers']:
        assert calculator.add(num, 0) == num
    
    # Test type errors with mixed data
    for item in sample_data['mixed']:
        if not isinstance(item, (int, float)):
            with pytest.raises(TypeError):
                calculator.add(item, 1)

# Markers and conditional tests
@pytest.mark.slow
def test_slow_operation():
    """Slow test that should be marked."""
    import time
    time.sleep(0.1)  # Simulate slow operation
    assert True

@pytest.mark.skip(reason="Feature not implemented yet")
def test_skipped_feature():
    """Test that is skipped."""
    assert False

@pytest.mark.skipif(sys.version_info < (3, 8), reason="Requires Python 3.8+")
def test_python_version_dependent():
    """Test that depends on Python version."""
    assert sys.version_info >= (3, 8)

# Run basic tests
if __name__ == "__main__":
    pytest.main([__file__, "-v"])
```

### Mocking and Test Doubles

```python
import requests
from unittest.mock import Mock, patch, MagicMock
import json

class WeatherService:
    """Weather service that fetches data from API."""
    
    def __init__(self, api_key):
        self.api_key = api_key
        self.base_url = "https://api.weather.com"
    
    def get_weather(self, city):
        """Get weather for a city."""
        url = f"{self.base_url}/weather"
        params = {'city': city, 'api_key': self.api_key}
        
        try:
            response = requests.get(url, params=params, timeout=5)
            response.raise_for_status()
            return response.json()
        except requests.RequestException as e:
            raise Exception(f"Weather service error: {e}")

class WeatherApp:
    """Weather application."""
    
    def __init__(self, weather_service):
        self.weather_service = weather_service
    
    def get_weather_summary(self, city):
        """Get weather summary for a city."""
        try:
            weather_data = self.weather_service.get_weather(city)
            return {
                'city': city,
                'temperature': weather_data.get('temperature'),
                'condition': weather_data.get('condition'),
                'humidity': weather_data.get('humidity')
            }
        except Exception as e:
            return {'error': str(e)}

# Mock tests
def test_weather_service_with_mock():
    """Test weather service with mocked requests."""
    # Create mock response
    mock_response = Mock()
    mock_response.json.return_value = {
        'temperature': 25,
        'condition': 'sunny',
        'humidity': 60
    }
    mock_response.raise_for_status.return_value = None
    
    # Mock requests.get
    with patch('requests.get', return_value=mock_response) as mock_get:
        weather_service = WeatherService('test-api-key')
        result = weather_service.get_weather('London')
        
        assert result['temperature'] == 25
        assert result['condition'] == 'sunny'
        mock_get.assert_called_once()

def test_weather_service_error_handling():
    """Test weather service error handling."""
    with patch('requests.get') as mock_get:
        # Mock request exception
        mock_get.side_effect = requests.RequestException("Network error")
        
        weather_service = WeatherService('test-api-key')
        
        with pytest.raises(Exception, match="Weather service error"):
            weather_service.get_weather('London')

def test_weather_app_integration():
    """Test weather app integration."""
    # Mock weather service
    mock_service = Mock()
    mock_service.get_weather.return_value = {
        'temperature': 22,
        'condition': 'cloudy',
        'humidity': 70
    }
    
    # Test weather app
    app = WeatherApp(mock_service)
    result = app.get_weather_summary('Paris')
    
    assert result['city'] == 'Paris'
    assert result['temperature'] == 22
    assert result['condition'] == 'cloudy'
    mock_service.get_weather.assert_called_once_with('Paris')

def test_weather_app_error_handling():
    """Test weather app error handling."""
    mock_service = Mock()
    mock_service.get_weather.side_effect = Exception("Service unavailable")
    
    app = WeatherApp(mock_service)
    result = app.get_weather_summary('Tokyo')
    
    assert 'error' in result
    assert result['error'] == "Service unavailable"

# MagicMock examples
def test_magic_mock_example():
    """Test using MagicMock."""
    mock_obj = MagicMock()
    mock_obj.some_method.return_value = "mocked result"
    mock_obj.some_attribute = "mocked attribute"
    
    assert mock_obj.some_method() == "mocked result"
    assert mock_obj.some_attribute == "mocked attribute"
    
    # Verify method was called
    mock_obj.some_method.assert_called_once()

# Context manager mocking
def test_context_manager_mocking():
    """Test mocking context managers."""
    mock_file = MagicMock()
    mock_file.read.return_value = "file content"
    mock_file.__enter__.return_value = mock_file
    mock_file.__exit__.return_value = None
    
    with patch('builtins.open', return_value=mock_file):
        with open('test.txt', 'r') as f:
            content = f.read()
        
        assert content == "file content"
```

### Test Coverage and Quality

```python
import coverage
from unittest.mock import patch

# Coverage testing
def test_coverage_example():
    """Example of testing with coverage."""
    # This would typically be run with pytest-cov
    # pytest --cov=my_module --cov-report=html
    
    calc = Calculator()
    
    # Test all methods to achieve 100% coverage
    assert calc.add(1, 2) == 3
    assert calc.divide(4, 2) == 2
    assert calc.multiply(3, 4) == 12
    
    # Test error cases
    with pytest.raises(TypeError):
        calc.add("1", 2)
    
    with pytest.raises(ValueError):
        calc.divide(1, 0)

# Test quality metrics
class TestQualityMetrics:
    """Test class demonstrating quality metrics."""
    
    def setup_method(self):
        """Setup for each test method."""
        self.calc = Calculator()
    
    def teardown_method(self):
        """Cleanup after each test method."""
        pass
    
    def test_addition_positive_numbers(self):
        """Test addition with positive numbers."""
        assert self.calc.add(5, 3) == 8
    
    def test_addition_negative_numbers(self):
        """Test addition with negative numbers."""
        assert self.calc.add(-5, -3) == -8
    
    def test_addition_mixed_numbers(self):
        """Test addition with mixed positive/negative numbers."""
        assert self.calc.add(5, -3) == 2
    
    def test_division_normal_cases(self):
        """Test division with normal cases."""
        assert self.calc.divide(10, 2) == 5
        assert self.calc.divide(15, 3) == 5
    
    def test_division_decimal_result(self):
        """Test division resulting in decimal."""
        assert self.calc.divide(7, 2) == 3.5
    
    def test_division_by_zero(self):
        """Test division by zero error."""
        with pytest.raises(ValueError):
            self.calc.divide(10, 0)
    
    def test_type_validation(self):
        """Test type validation for all methods."""
        with pytest.raises(TypeError):
            self.calc.add("1", 2)
        
        with pytest.raises(TypeError):
            self.calc.divide(10, "2")
        
        with pytest.raises(TypeError):
            self.calc.multiply("3", 4)
```

## Continuous Integration

### GitHub Actions Workflow

```python
# This would be in .github/workflows/ci.yml
github_actions_workflow = """
name: CI/CD Pipeline

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
        python-version: [3.8, 3.9, '3.10', '3.11']
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Set up Python ${{ matrix.python-version }}
      uses: actions/setup-python@v4
      with:
        python-version: ${{ matrix.python-version }}
    
    - name: Cache pip dependencies
      uses: actions/cache@v3
      with:
        path: ~/.cache/pip
        key: ${{ runner.os }}-pip-${{ hashFiles('**/requirements.txt') }}
    
    - name: Install dependencies
      run: |
        python -m pip install --upgrade pip
        pip install -r requirements.txt
        pip install -r requirements-dev.txt
    
    - name: Lint with flake8
      run: |
        flake8 . --count --select=E9,F63,F7,F82 --show-source --statistics
        flake8 . --count --exit-zero --max-complexity=10 --max-line-length=127 --statistics
    
    - name: Test with pytest
      run: |
        pytest --cov=. --cov-report=xml --cov-report=html
    
    - name: Upload coverage to Codecov
      uses: codecov/codecov-action@v3
      with:
        file: ./coverage.xml
        flags: unittests
        name: codecov-umbrella

  security:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v3
    
    - name: Run security scan
      run: |
        pip install bandit safety
        bandit -r . -f json -o bandit-report.json
        safety check --json --output safety-report.json
    
    - name: Upload security reports
      uses: actions/upload-artifact@v3
      with:
        name: security-reports
        path: |
          bandit-report.json
          safety-report.json

  build:
    needs: [test, security]
    runs-on: ubuntu-latest
    if: github.ref == 'refs/heads/main'
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Set up Python
      uses: actions/setup-python@v4
      with:
        python-version: '3.11'
    
    - name: Install build dependencies
      run: |
        python -m pip install --upgrade pip
        pip install build twine
    
    - name: Build package
      run: python -m build
    
    - name: Upload to PyPI
      env:
        TWINE_USERNAME: __token__
        TWINE_PASSWORD: ${{ secrets.PYPI_TOKEN }}
      run: twine upload dist/*
"""

print("GitHub Actions workflow example:")
print(github_actions_workflow)
```

### Pre-commit Hooks

```python
# This would be in .pre-commit-config.yaml
pre_commit_config = """
repos:
  - repo: https://github.com/pre-commit/pre-commit-hooks
    rev: v4.4.0
    hooks:
      - id: trailing-whitespace
      - id: end-of-file-fixer
      - id: check-yaml
      - id: check-added-large-files
      - id: check-merge-conflict
  
  - repo: https://github.com/psf/black
    rev: 23.3.0
    hooks:
      - id: black
        language_version: python3
  
  - repo: https://github.com/pycqa/isort
    rev: 5.12.0
    hooks:
      - id: isort
        args: ["--profile", "black"]
  
  - repo: https://github.com/pycqa/flake8
    rev: 6.0.0
    hooks:
      - id: flake8
        args: [--max-line-length=88, --extend-ignore=E203]
  
  - repo: https://github.com/pycqa/bandit
    rev: 1.7.5
    hooks:
      - id: bandit
        args: ["-r", ".", "-f", "json", "-o", "bandit-report.json"]
  
  - repo: https://github.com/pre-commit/mirrors-mypy
    rev: v1.3.0
    hooks:
      - id: mypy
        additional_dependencies: [types-requests, types-PyYAML]
"""

print("\nPre-commit configuration example:")
print(pre_commit_config)
```

## Test-Driven Development (TDD)

### TDD Example

```python
class TDDExample:
    """Example of Test-Driven Development."""
    
    def __init__(self):
        self.items = []
    
    def add_item(self, item):
        """Add item to list."""
        if not item:
            raise ValueError("Item cannot be empty")
        self.items.append(item)
    
    def remove_item(self, item):
        """Remove item from list."""
        if item not in self.items:
            raise ValueError("Item not found")
        self.items.remove(item)
    
    def get_items(self):
        """Get all items."""
        return self.items.copy()
    
    def clear_items(self):
        """Clear all items."""
        self.items.clear()
    
    def item_count(self):
        """Get item count."""
        return len(self.items)

# TDD Tests - Red Phase
def test_tdd_example_initial_state():
    """Test initial state of TDD example."""
    tdd = TDDExample()
    assert tdd.get_items() == []
    assert tdd.item_count() == 0

def test_tdd_add_item():
    """Test adding items."""
    tdd = TDDExample()
    
    tdd.add_item("item1")
    assert tdd.item_count() == 1
    assert "item1" in tdd.get_items()
    
    tdd.add_item("item2")
    assert tdd.item_count() == 2
    assert "item2" in tdd.get_items()

def test_tdd_add_empty_item():
    """Test adding empty item raises error."""
    tdd = TDDExample()
    
    with pytest.raises(ValueError, match="Item cannot be empty"):
        tdd.add_item("")
    
    with pytest.raises(ValueError, match="Item cannot be empty"):
        tdd.add_item(None)

def test_tdd_remove_item():
    """Test removing items."""
    tdd = TDDExample()
    tdd.add_item("item1")
    tdd.add_item("item2")
    
    tdd.remove_item("item1")
    assert tdd.item_count() == 1
    assert "item1" not in tdd.get_items()
    assert "item2" in tdd.get_items()

def test_tdd_remove_nonexistent_item():
    """Test removing non-existent item raises error."""
    tdd = TDDExample()
    tdd.add_item("item1")
    
    with pytest.raises(ValueError, match="Item not found"):
        tdd.remove_item("nonexistent")

def test_tdd_clear_items():
    """Test clearing all items."""
    tdd = TDDExample()
    tdd.add_item("item1")
    tdd.add_item("item2")
    
    assert tdd.item_count() == 2
    tdd.clear_items()
    assert tdd.item_count() == 0
    assert tdd.get_items() == []
```

## Performance Testing

### Load Testing Example

```python
import time
import threading
from concurrent.futures import ThreadPoolExecutor
import statistics

class PerformanceTest:
    """Performance testing utilities."""
    
    @staticmethod
    def measure_execution_time(func, *args, **kwargs):
        """Measure execution time of a function."""
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        
        return {
            'result': result,
            'execution_time': end_time - start_time
        }
    
    @staticmethod
    def load_test(func, num_threads=10, iterations=100):
        """Perform load testing on a function."""
        results = []
        
        def worker():
            for _ in range(iterations):
                start_time = time.time()
                func()
                end_time = time.time()
                results.append(end_time - start_time)
        
        with ThreadPoolExecutor(max_workers=num_threads) as executor:
            futures = [executor.submit(worker) for _ in range(num_threads)]
            
            for future in futures:
                future.result()
        
        return {
            'total_executions': len(results),
            'average_time': statistics.mean(results),
            'median_time': statistics.median(results),
            'min_time': min(results),
            'max_time': max(results),
            'std_deviation': statistics.stdev(results) if len(results) > 1 else 0
        }

# Performance test examples
def expensive_operation():
    """Simulate an expensive operation."""
    time.sleep(0.01)  # 10ms delay
    return sum(range(1000))

def test_performance_measurement():
    """Test performance measurement."""
    result = PerformanceTest.measure_execution_time(expensive_operation)
    
    assert 'result' in result
    assert 'execution_time' in result
    assert result['execution_time'] > 0.01  # Should take at least 10ms

def test_load_testing():
    """Test load testing."""
    stats = PerformanceTest.load_test(expensive_operation, num_threads=5, iterations=10)
    
    assert stats['total_executions'] == 50  # 5 threads * 10 iterations
    assert stats['average_time'] > 0
    assert stats['min_time'] > 0
    assert stats['max_time'] > stats['min_time']

# Benchmarking
def benchmark_comparison():
    """Compare performance of different implementations."""
    def list_comprehension():
        return [x**2 for x in range(1000)]
    
    def map_function():
        return list(map(lambda x: x**2, range(1000)))
    
    def for_loop():
        result = []
        for x in range(1000):
            result.append(x**2)
        return result
    
    implementations = [
        ('List Comprehension', list_comprehension),
        ('Map Function', map_function),
        ('For Loop', for_loop)
    ]
    
    results = {}
    for name, func in implementations:
        result = PerformanceTest.measure_execution_time(func)
        results[name] = result['execution_time']
    
    print("\nBenchmark Results:")
    for name, time_taken in sorted(results.items(), key=lambda x: x[1]):
        print(f"  {name}: {time_taken:.6f} seconds")
    
    return results

# Run performance tests
if __name__ == "__main__":
    test_performance_measurement()
    test_load_testing()
    benchmark_comparison()
```

## Deployment and DevOps

### Docker Configuration

```python
# This would be in Dockerfile
dockerfile_content = """
FROM python:3.11-slim

WORKDIR /app

# Install system dependencies
RUN apt-get update && apt-get install -y \\
    gcc \\
    && rm -rf /var/lib/apt/lists/*

# Copy requirements first for better caching
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Copy application code
COPY . .

# Create non-root user
RUN useradd --create-home --shell /bin/bash app \\
    && chown -R app:app /app
USER app

# Expose port
EXPOSE 8000

# Health check
HEALTHCHECK --interval=30s --timeout=30s --start-period=5s --retries=3 \\
    CMD curl -f http://localhost:8000/health || exit 1

# Run application
CMD ["python", "-m", "uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8000"]
"""

# Docker Compose
docker_compose_content = """
version: '3.8'

services:
  web:
    build: .
    ports:
      - "8000:8000"
    environment:
      - DATABASE_URL=postgresql://user:password@db:5432/mydb
    depends_on:
      - db
    volumes:
      - .:/app
    command: python -m uvicorn main:app --host 0.0.0.0 --port 8000 --reload

  db:
    image: postgres:15
    environment:
      - POSTGRES_DB=mydb
      - POSTGRES_USER=user
      - POSTGRES_PASSWORD=password
    volumes:
      - postgres_data:/var/lib/postgresql/data
    ports:
      - "5432:5432"

  redis:
    image: redis:7-alpine
    ports:
      - "6379:6379"

  nginx:
    image: nginx:alpine
    ports:
      - "80:80"
    volumes:
      - ./nginx.conf:/etc/nginx/nginx.conf
    depends_on:
      - web

volumes:
  postgres_data:
"""

print("Docker configuration examples:")
print("Dockerfile:")
print(dockerfile_content)
print("\nDocker Compose:")
print(docker_compose_content)
```

### Environment Configuration

```python
import os
from dataclasses import dataclass
from typing import Optional

@dataclass
class Config:
    """Application configuration."""
    debug: bool = False
    database_url: str = "sqlite:///app.db"
    redis_url: str = "redis://localhost:6379"
    secret_key: str = "your-secret-key"
    api_key: Optional[str] = None
    
    @classmethod
    def from_env(cls):
        """Create configuration from environment variables."""
        return cls(
            debug=os.getenv('DEBUG', 'False').lower() == 'true',
            database_url=os.getenv('DATABASE_URL', 'sqlite:///app.db'),
            redis_url=os.getenv('REDIS_URL', 'redis://localhost:6379'),
            secret_key=os.getenv('SECRET_KEY', 'your-secret-key'),
            api_key=os.getenv('API_KEY')
        )

def test_configuration():
    """Test configuration management."""
    # Test default configuration
    config = Config()
    assert config.debug == False
    assert config.database_url == "sqlite:///app.db"
    
    # Test environment-based configuration
    os.environ['DEBUG'] = 'true'
    os.environ['DATABASE_URL'] = 'postgresql://localhost/mydb'
    
    config = Config.from_env()
    assert config.debug == True
    assert config.database_url == 'postgresql://localhost/mydb'
    
    # Cleanup
    del os.environ['DEBUG']
    del os.environ['DATABASE_URL']

# Logging configuration
import logging

def setup_logging(level=logging.INFO):
    """Setup application logging."""
    logging.basicConfig(
        level=level,
        format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
        handlers=[
            logging.FileHandler('app.log'),
            logging.StreamHandler()
        ]
    )

def test_logging():
    """Test logging setup."""
    setup_logging(logging.DEBUG)
    
    logger = logging.getLogger('test')
    logger.debug("Debug message")
    logger.info("Info message")
    logger.warning("Warning message")
    logger.error("Error message")

# Run tests
if __name__ == "__main__":
    test_configuration()
    test_logging()
```

## Key Takeaways

1. **pytest** provides powerful testing capabilities with fixtures and parametrization
2. **Mocking** isolates units under test and controls external dependencies
3. **Test coverage** helps identify untested code and improve quality
4. **CI/CD pipelines** automate testing and deployment processes
5. **TDD** improves code quality by writing tests before implementation
6. **Performance testing** ensures applications meet performance requirements
7. **Docker** provides consistent deployment environments
8. **Configuration management** separates code from environment-specific settings

## Next Steps

In the final lesson, we'll explore Deployment and Production - packaging applications, containerization, and production deployment strategies.
