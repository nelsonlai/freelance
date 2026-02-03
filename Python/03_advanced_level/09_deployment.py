# Deployment Examples
import os
import subprocess
import json
import shutil
from datetime import datetime
import zipfile
import tarfile

print("Deployment Examples")
print("=" * 20)

# 1. Packaging Python Apps
print("1. Packaging Python Apps")
print("-" * 25)

def create_setup_py():
    """Create setup.py for packaging."""
    setup_content = '''from setuptools import setup, find_packages

with open("README.md", "r", encoding="utf-8") as fh:
    long_description = fh.read()

with open("requirements.txt", "r", encoding="utf-8") as fh:
    requirements = [line.strip() for line in fh if line.strip() and not line.startswith("#")]

setup(
    name="my-python-app",
    version="1.0.0",
    author="Your Name",
    author_email="your.email@example.com",
    description="A simple Python application",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/yourusername/my-python-app",
    packages=find_packages(),
    classifiers=[
        "Development Status :: 4 - Beta",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: Python :: 3.11",
    ],
    python_requires=">=3.8",
    install_requires=requirements,
    entry_points={
        "console_scripts": [
            "my-app=my_python_app.main:main",
        ],
    },
)
'''
    
    with open('setup.py', 'w') as f:
        f.write(setup_content)
    
    print("setup.py created")

def create_requirements_txt():
    """Create requirements.txt file."""
    requirements = [
        "requests>=2.25.0",
        "flask>=2.0.0",
        "pandas>=1.3.0",
        "numpy>=1.21.0",
        "pytest>=6.0.0",
        "pytest-cov>=2.12.0"
    ]
    
    with open('requirements.txt', 'w') as f:
        f.write('\n'.join(requirements))
    
    print("requirements.txt created")

def create_manifest_in():
    """Create MANIFEST.in file."""
    manifest_content = '''include README.md
include LICENSE
include requirements.txt
recursive-include my_python_app *.py
recursive-exclude * __pycache__
recursive-exclude * *.py[co]
'''
    
    with open('MANIFEST.in', 'w') as f:
        f.write(manifest_content)
    
    print("MANIFEST.in created")

def create_package_structure():
    """Create package structure."""
    # Create package directory
    os.makedirs('my_python_app', exist_ok=True)
    
    # Create __init__.py
    with open('my_python_app/__init__.py', 'w') as f:
        f.write('"""My Python App package."""\n__version__ = "1.0.0"\n')
    
    # Create main.py
    main_content = '''"""Main module for my Python app."""

def main():
    """Main function."""
    print("Hello from My Python App!")

if __name__ == "__main__":
    main()
'''
    
    with open('my_python_app/main.py', 'w') as f:
        f.write(main_content)
    
    print("Package structure created")

# Create packaging files
create_setup_py()
create_requirements_txt()
create_manifest_in()
create_package_structure()

# Build package
print("\nBuilding package...")
try:
    # Build source distribution
    subprocess.run(['python', 'setup.py', 'sdist'], check=True)
    print("Source distribution created")
    
    # Build wheel
    subprocess.run(['python', 'setup.py', 'bdist_wheel'], check=True)
    print("Wheel distribution created")
    
except subprocess.CalledProcessError as e:
    print(f"Build failed: {e}")

# 2. Virtual Environments
print("\n2. Virtual Environments")
print("-" * 25)

def create_virtual_environment():
    """Create and manage virtual environment."""
    venv_name = 'my_app_env'
    
    try:
        # Create virtual environment
        subprocess.run(['python', '-m', 'venv', venv_name], check=True)
        print(f"Virtual environment '{venv_name}' created")
        
        # Activate virtual environment (simulation)
        if os.name == 'nt':  # Windows
            activate_script = os.path.join(venv_name, 'Scripts', 'activate.bat')
        else:  # Unix/Linux/MacOS
            activate_script = os.path.join(venv_name, 'bin', 'activate')
        
        print(f"Activate with: {activate_script}")
        
        # Install requirements in virtual environment
        pip_path = os.path.join(venv_name, 'bin', 'pip') if os.name != 'nt' else os.path.join(venv_name, 'Scripts', 'pip.exe')
        subprocess.run([pip_path, 'install', '-r', 'requirements.txt'], check=True)
        print("Requirements installed in virtual environment")
        
    except subprocess.CalledProcessError as e:
        print(f"Virtual environment creation failed: {e}")

# Create virtual environment
create_virtual_environment()

# 3. Docker Basics
print("\n3. Docker Basics")
print("-" * 15)

def create_dockerfile():
    """Create Dockerfile for containerization."""
    dockerfile_content = '''# Use Python 3.11 slim image
FROM python:3.11-slim

# Set working directory
WORKDIR /app

# Set environment variables
ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1

# Install system dependencies
RUN apt-get update && apt-get install -y \\
    gcc \\
    && rm -rf /var/lib/apt/lists/*

# Copy requirements first for better caching
COPY requirements.txt .

# Install Python dependencies
RUN pip install --no-cache-dir -r requirements.txt

# Copy application code
COPY . .

# Create non-root user
RUN adduser --disabled-password --gecos '' appuser
RUN chown -R appuser:appuser /app
USER appuser

# Expose port
EXPOSE 8000

# Health check
HEALTHCHECK --interval=30s --timeout=30s --start-period=5s --retries=3 \\
    CMD curl -f http://localhost:8000/health || exit 1

# Run application
CMD ["python", "my_python_app/main.py"]
'''
    
    with open('Dockerfile', 'w') as f:
        f.write(dockerfile_content)
    
    print("Dockerfile created")

def create_docker_compose():
    """Create docker-compose.yml file."""
    compose_content = '''version: '3.8'

services:
  app:
    build: .
    ports:
      - "8000:8000"
    environment:
      - FLASK_ENV=production
      - DATABASE_URL=sqlite:///app.db
    volumes:
      - ./data:/app/data
    restart: unless-stopped
    
  nginx:
    image: nginx:alpine
    ports:
      - "80:80"
    volumes:
      - ./nginx.conf:/etc/nginx/nginx.conf
    depends_on:
      - app
    restart: unless-stopped
    
  redis:
    image: redis:alpine
    ports:
      - "6379:6379"
    restart: unless-stopped
'''
    
    with open('docker-compose.yml', 'w') as f:
        f.write(compose_content)
    
    print("docker-compose.yml created")

def create_dockerignore():
    """Create .dockerignore file."""
    dockerignore_content = '''# Python
__pycache__/
*.py[cod]
*$py.class
*.so
.Python
build/
develop-eggs/
dist/
downloads/
eggs/
.eggs/
lib/
lib64/
parts/
sdist/
var/
wheels/
*.egg-info/
.installed.cfg
*.egg

# Virtual environments
venv/
env/
ENV/

# IDE
.vscode/
.idea/
*.swp
*.swo

# OS
.DS_Store
Thumbs.db

# Git
.git/
.gitignore

# Docker
Dockerfile
docker-compose.yml
.dockerignore

# Documentation
README.md
docs/
'''
    
    with open('.dockerignore', 'w') as f:
        f.write(dockerignore_content)
    
    print(".dockerignore created")

# Create Docker files
create_dockerfile()
create_docker_compose()
create_dockerignore()

# 4. Cloud Deployment
print("\n4. Cloud Deployment")
print("-" * 20)

def create_cloud_deployment_configs():
    """Create cloud deployment configurations."""
    
    # AWS Elastic Beanstalk
    aws_config = '''option_settings:
  aws:elasticbeanstalk:container:python:
    WSGIPath: my_python_app.wsgi:application
  aws:elasticbeanstalk:application:environment:
    DJANGO_SETTINGS_MODULE: my_python_app.settings
'''
    
    os.makedirs('.ebextensions', exist_ok=True)
    with open('.ebextensions/python.config', 'w') as f:
        f.write(aws_config)
    
    # Google Cloud App Engine
    app_yaml = '''runtime: python311

env_variables:
  FLASK_ENV: production

handlers:
- url: /.*
  script: auto

automatic_scaling:
  min_instances: 1
  max_instances: 10
'''
    
    with open('app.yaml', 'w') as f:
        f.write(app_yaml)
    
    # Azure App Service
    azure_config = '''{
  "version": "1.0.0",
  "platform": {
    "python": {
      "version": "3.11"
    }
  },
  "app": {
    "name": "my-python-app"
  }
}
'''
    
    with open('azure_config.json', 'w') as f:
        f.write(azure_config)
    
    print("Cloud deployment configurations created")

# Create cloud deployment configs
create_cloud_deployment_configs()

# 5. Environment Configuration
print("\n5. Environment Configuration")
print("-" * 30)

def create_env_config():
    """Create environment configuration files."""
    
    # .env file
    env_content = '''# Development Environment
FLASK_ENV=development
DEBUG=True
SECRET_KEY=dev-secret-key
DATABASE_URL=sqlite:///dev.db

# Production Environment
# FLASK_ENV=production
# DEBUG=False
# SECRET_KEY=your-production-secret-key
# DATABASE_URL=postgresql://user:password@localhost/dbname
'''
    
    with open('.env', 'w') as f:
        f.write(env_content)
    
    # .env.example
    env_example = '''# Environment Variables Template
FLASK_ENV=development
DEBUG=True
SECRET_KEY=your-secret-key
DATABASE_URL=sqlite:///app.db
REDIS_URL=redis://localhost:6379
API_KEY=your-api-key
'''
    
    with open('.env.example', 'w') as f:
        f.write(env_example)
    
    # config.py
    config_content = '''"""Configuration management."""

import os
from dotenv import load_dotenv

# Load environment variables
load_dotenv()

class Config:
    """Base configuration."""
    SECRET_KEY = os.environ.get('SECRET_KEY') or 'dev-secret-key'
    DATABASE_URL = os.environ.get('DATABASE_URL') or 'sqlite:///app.db'
    REDIS_URL = os.environ.get('REDIS_URL') or 'redis://localhost:6379'
    API_KEY = os.environ.get('API_KEY') or ''

class DevelopmentConfig(Config):
    """Development configuration."""
    DEBUG = True
    FLASK_ENV = 'development'

class ProductionConfig(Config):
    """Production configuration."""
    DEBUG = False
    FLASK_ENV = 'production'

class TestingConfig(Config):
    """Testing configuration."""
    TESTING = True
    DATABASE_URL = 'sqlite:///:memory:'

# Configuration dictionary
config = {
    'development': DevelopmentConfig,
    'production': ProductionConfig,
    'testing': TestingConfig,
    'default': DevelopmentConfig
}
'''
    
    with open('config.py', 'w') as f:
        f.write(config_content)
    
    print("Environment configuration files created")

# Create environment configs
create_env_config()

# 6. Monitoring and Logging
print("\n6. Monitoring and Logging")
print("-" * 25)

def create_logging_config():
    """Create logging configuration."""
    
    # logging_config.py
    logging_config = '''"""Logging configuration."""

import logging
import logging.config
import os
from datetime import datetime

def setup_logging():
    """Setup logging configuration."""
    
    # Create logs directory
    os.makedirs('logs', exist_ok=True)
    
    # Logging configuration
    config = {
        'version': 1,
        'disable_existing_loggers': False,
        'formatters': {
            'standard': {
                'format': '%(asctime)s [%(levelname)s] %(name)s: %(message)s'
            },
            'detailed': {
                'format': '%(asctime)s [%(levelname)s] %(name)s:%(lineno)d: %(message)s'
            }
        },
        'handlers': {
            'default': {
                'level': 'INFO',
                'formatter': 'standard',
                'class': 'logging.StreamHandler',
                'stream': 'ext://sys.stdout'
            },
            'file': {
                'level': 'DEBUG',
                'formatter': 'detailed',
                'class': 'logging.handlers.RotatingFileHandler',
                'filename': 'logs/app.log',
                'maxBytes': 10485760,  # 10MB
                'backupCount': 5
            },
            'error_file': {
                'level': 'ERROR',
                'formatter': 'detailed',
                'class': 'logging.handlers.RotatingFileHandler',
                'filename': 'logs/error.log',
                'maxBytes': 10485760,  # 10MB
                'backupCount': 5
            }
        },
        'loggers': {
            '': {
                'handlers': ['default', 'file'],
                'level': 'DEBUG',
                'propagate': False
            },
            'error': {
                'handlers': ['error_file'],
                'level': 'ERROR',
                'propagate': False
            }
        }
    }
    
    logging.config.dictConfig(config)
    
    # Create logger
    logger = logging.getLogger(__name__)
    logger.info("Logging configured successfully")
    
    return logger

# Example usage
if __name__ == "__main__":
    logger = setup_logging()
    logger.info("Application started")
    logger.warning("This is a warning")
    logger.error("This is an error")
'''
    
    with open('logging_config.py', 'w') as f:
        f.write(logging_config)
    
    # monitoring.py
    monitoring_content = '''"""Monitoring and metrics."""

import time
import psutil
import logging
from datetime import datetime

class SystemMonitor:
    """System monitoring class."""
    
    def __init__(self):
        self.logger = logging.getLogger(__name__)
    
    def get_system_metrics(self):
        """Get system metrics."""
        metrics = {
            'timestamp': datetime.now().isoformat(),
            'cpu_percent': psutil.cpu_percent(interval=1),
            'memory_percent': psutil.virtual_memory().percent,
            'disk_percent': psutil.disk_usage('/').percent,
            'load_average': psutil.getloadavg() if hasattr(psutil, 'getloadavg') else None
        }
        return metrics
    
    def log_metrics(self):
        """Log system metrics."""
        metrics = self.get_system_metrics()
        self.logger.info(f"System metrics: {metrics}")
        return metrics
    
    def check_health(self):
        """Check system health."""
        metrics = self.get_system_metrics()
        
        # Health checks
        health_status = {
            'status': 'healthy',
            'timestamp': metrics['timestamp'],
            'checks': {}
        }
        
        # CPU check
        if metrics['cpu_percent'] > 80:
            health_status['checks']['cpu'] = 'warning'
            health_status['status'] = 'degraded'
        else:
            health_status['checks']['cpu'] = 'ok'
        
        # Memory check
        if metrics['memory_percent'] > 90:
            health_status['checks']['memory'] = 'critical'
            health_status['status'] = 'unhealthy'
        elif metrics['memory_percent'] > 80:
            health_status['checks']['memory'] = 'warning'
            health_status['status'] = 'degraded'
        else:
            health_status['checks']['memory'] = 'ok'
        
        # Disk check
        if metrics['disk_percent'] > 95:
            health_status['checks']['disk'] = 'critical'
            health_status['status'] = 'unhealthy'
        elif metrics['disk_percent'] > 85:
            health_status['checks']['disk'] = 'warning'
            health_status['status'] = 'degraded'
        else:
            health_status['checks']['disk'] = 'ok'
        
        return health_status

# Example usage
if __name__ == "__main__":
    monitor = SystemMonitor()
    health = monitor.check_health()
    print(f"Health status: {health}")
'''
    
    with open('monitoring.py', 'w') as f:
        f.write(monitoring_content)
    
    print("Monitoring and logging configuration created")

# Create monitoring configs
create_logging_config()

# 7. Backup and Recovery
print("\n7. Backup and Recovery")
print("-" * 22)

def create_backup_script():
    """Create backup script."""
    
    backup_script = '''#!/usr/bin/env python3
"""Backup script for application data."""

import os
import shutil
import tarfile
import zipfile
from datetime import datetime
import json

class BackupManager:
    """Backup management class."""
    
    def __init__(self, backup_dir='backups'):
        self.backup_dir = backup_dir
        os.makedirs(backup_dir, exist_ok=True)
    
    def create_backup(self, source_paths, backup_name=None):
        """Create backup of specified paths."""
        if backup_name is None:
            backup_name = f"backup_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
        
        backup_path = os.path.join(self.backup_dir, f"{backup_name}.tar.gz")
        
        with tarfile.open(backup_path, 'w:gz') as tar:
            for path in source_paths:
                if os.path.exists(path):
                    tar.add(path, arcname=os.path.basename(path))
        
        print(f"Backup created: {backup_path}")
        return backup_path
    
    def restore_backup(self, backup_path, restore_dir='restore'):
        """Restore backup to specified directory."""
        os.makedirs(restore_dir, exist_ok=True)
        
        with tarfile.open(backup_path, 'r:gz') as tar:
            tar.extractall(restore_dir)
        
        print(f"Backup restored to: {restore_dir}")
        return restore_dir
    
    def list_backups(self):
        """List available backups."""
        backups = []
        for file in os.listdir(self.backup_dir):
            if file.endswith('.tar.gz'):
                file_path = os.path.join(self.backup_dir, file)
                stat = os.stat(file_path)
                backups.append({
                    'name': file,
                    'size': stat.st_size,
                    'created': datetime.fromtimestamp(stat.st_ctime).isoformat()
                })
        
        return sorted(backups, key=lambda x: x['created'], reverse=True)
    
    def cleanup_old_backups(self, keep_count=5):
        """Clean up old backups, keeping only specified number."""
        backups = self.list_backups()
        
        if len(backups) > keep_count:
            for backup in backups[keep_count:]:
                backup_path = os.path.join(self.backup_dir, backup['name'])
                os.remove(backup_path)
                print(f"Removed old backup: {backup['name']}")

# Example usage
if __name__ == "__main__":
    backup_manager = BackupManager()
    
    # Create backup
    source_paths = ['my_python_app', 'config.py', 'requirements.txt']
    backup_path = backup_manager.create_backup(source_paths)
    
    # List backups
    backups = backup_manager.list_backups()
    print(f"Available backups: {len(backups)}")
    
    # Cleanup old backups
    backup_manager.cleanup_old_backups(keep_count=3)
'''
    
    with open('backup.py', 'w') as f:
        f.write(backup_script)
    
    print("Backup script created")

# Create backup script
create_backup_script()

# 8. Security Configuration
print("\n8. Security Configuration")
print("-" * 25)

def create_security_config():
    """Create security configuration."""
    
    # security.py
    security_content = '''"""Security configuration and utilities."""

import os
import hashlib
import secrets
from functools import wraps
from flask import request, jsonify

class SecurityManager:
    """Security management class."""
    
    @staticmethod
    def generate_secret_key():
        """Generate a secure secret key."""
        return secrets.token_hex(32)
    
    @staticmethod
    def hash_password(password, salt=None):
        """Hash password with salt."""
        if salt is None:
            salt = secrets.token_hex(16)
        
        password_hash = hashlib.pbkdf2_hmac(
            'sha256',
            password.encode('utf-8'),
            salt.encode('utf-8'),
            100000
        )
        
        return password_hash.hex(), salt
    
    @staticmethod
    def verify_password(password, password_hash, salt):
        """Verify password against hash."""
        computed_hash, _ = SecurityManager.hash_password(password, salt)
        return computed_hash == password_hash
    
    @staticmethod
    def validate_input(data, required_fields):
        """Validate input data."""
        errors = []
        
        for field in required_fields:
            if field not in data:
                errors.append(f"Missing required field: {field}")
            elif not data[field]:
                errors.append(f"Empty value for field: {field}")
        
        return errors

def require_api_key(f):
    """Decorator to require API key."""
    @wraps(f)
    def decorated_function(*args, **kwargs):
        api_key = request.headers.get('X-API-Key')
        
        if not api_key:
            return jsonify({'error': 'API key required'}), 401
        
        # In production, validate against database
        valid_api_key = os.environ.get('API_KEY')
        if api_key != valid_api_key:
            return jsonify({'error': 'Invalid API key'}), 401
        
        return f(*args, **kwargs)
    
    return decorated_function

def rate_limit(max_requests=100, window=3600):
    """Rate limiting decorator."""
    def decorator(f):
        @wraps(f)
        def decorated_function(*args, **kwargs):
            # In production, implement proper rate limiting
            # using Redis or database
            return f(*args, **kwargs)
        
        return decorated_function
    return decorator

# Security headers
SECURITY_HEADERS = {
    'X-Content-Type-Options': 'nosniff',
    'X-Frame-Options': 'DENY',
    'X-XSS-Protection': '1; mode=block',
    'Strict-Transport-Security': 'max-age=31536000; includeSubDomains',
    'Content-Security-Policy': "default-src 'self'"
}

def add_security_headers(response):
    """Add security headers to response."""
    for header, value in SECURITY_HEADERS.items():
        response.headers[header] = value
    return response
'''
    
    with open('security.py', 'w') as f:
        f.write(security_content)
    
    print("Security configuration created")

# Create security config
create_security_config()

# 9. Deployment Scripts
print("\n9. Deployment Scripts")
print("-" * 22)

def create_deployment_scripts():
    """Create deployment scripts."""
    
    # deploy.sh
    deploy_script = '''#!/bin/bash
# Deployment script

set -e

echo "Starting deployment..."

# Set variables
APP_NAME="my-python-app"
VERSION="1.0.0"
ENVIRONMENT=${1:-production}

echo "Deploying $APP_NAME version $VERSION to $ENVIRONMENT"

# Create virtual environment
python3 -m venv venv
source venv/bin/activate

# Install dependencies
pip install -r requirements.txt

# Run tests
echo "Running tests..."
python -m pytest tests/ --cov=my_python_app

# Build package
echo "Building package..."
python setup.py sdist bdist_wheel

# Deploy based on environment
case $ENVIRONMENT in
    "production")
        echo "Deploying to production..."
        # Add production deployment commands
        ;;
    "staging")
        echo "Deploying to staging..."
        # Add staging deployment commands
        ;;
    "development")
        echo "Deploying to development..."
        # Add development deployment commands
        ;;
    *)
        echo "Unknown environment: $ENVIRONMENT"
        exit 1
        ;;
esac

echo "Deployment completed successfully!"
'''
    
    with open('deploy.sh', 'w') as f:
        f.write(deploy_script)
    
    # Make executable
    os.chmod('deploy.sh', 0o755)
    
    # deploy.py
    deploy_py = '''#!/usr/bin/env python3
"""Python deployment script."""

import os
import sys
import subprocess
import argparse
from datetime import datetime

class DeploymentManager:
    """Deployment management class."""
    
    def __init__(self, app_name="my-python-app"):
        self.app_name = app_name
        self.start_time = datetime.now()
    
    def run_command(self, command, check=True):
        """Run shell command."""
        print(f"Running: {command}")
        result = subprocess.run(command, shell=True, check=check)
        return result
    
    def create_virtual_environment(self):
        """Create virtual environment."""
        print("Creating virtual environment...")
        self.run_command("python3 -m venv venv")
        self.run_command("source venv/bin/activate && pip install --upgrade pip")
    
    def install_dependencies(self):
        """Install dependencies."""
        print("Installing dependencies...")
        self.run_command("source venv/bin/activate && pip install -r requirements.txt")
    
    def run_tests(self):
        """Run tests."""
        print("Running tests...")
        self.run_command("source venv/bin/activate && python -m pytest tests/ --cov=my_python_app")
    
    def build_package(self):
        """Build package."""
        print("Building package...")
        self.run_command("source venv/bin/activate && python setup.py sdist bdist_wheel")
    
    def deploy(self, environment="production"):
        """Deploy application."""
        print(f"Deploying to {environment}...")
        
        # Environment-specific deployment
        if environment == "production":
            self.deploy_production()
        elif environment == "staging":
            self.deploy_staging()
        elif environment == "development":
            self.deploy_development()
        else:
            raise ValueError(f"Unknown environment: {environment}")
    
    def deploy_production(self):
        """Deploy to production."""
        print("Deploying to production...")
        # Add production deployment logic
        pass
    
    def deploy_staging(self):
        """Deploy to staging."""
        print("Deploying to staging...")
        # Add staging deployment logic
        pass
    
    def deploy_development(self):
        """Deploy to development."""
        print("Deploying to development...")
        # Add development deployment logic
        pass
    
    def cleanup(self):
        """Cleanup after deployment."""
        print("Cleaning up...")
        # Add cleanup logic
        pass
    
    def deploy_full(self, environment="production"):
        """Full deployment process."""
        try:
            self.create_virtual_environment()
            self.install_dependencies()
            self.run_tests()
            self.build_package()
            self.deploy(environment)
            self.cleanup()
            
            end_time = datetime.now()
            duration = end_time - self.start_time
            print(f"Deployment completed successfully in {duration}")
            
        except Exception as e:
            print(f"Deployment failed: {e}")
            sys.exit(1)

def main():
    """Main function."""
    parser = argparse.ArgumentParser(description='Deploy application')
    parser.add_argument('environment', nargs='?', default='production',
                       choices=['production', 'staging', 'development'],
                       help='Deployment environment')
    
    args = parser.parse_args()
    
    deployment_manager = DeploymentManager()
    deployment_manager.deploy_full(args.environment)

if __name__ == "__main__":
    main()
'''
    
    with open('deploy.py', 'w') as f:
        f.write(deploy_py)
    
    # Make executable
    os.chmod('deploy.py', 0o755)
    
    print("Deployment scripts created")

# Create deployment scripts
create_deployment_scripts()

# 10. Documentation
print("\n10. Documentation")
print("-" * 18)

def create_documentation():
    """Create deployment documentation."""
    
    # README.md
    readme_content = '''# My Python App

A simple Python application with comprehensive deployment configuration.

## Features

- Python 3.11+ support
- Virtual environment management
- Docker containerization
- Cloud deployment ready
- Monitoring and logging
- Security configuration
- Automated testing

## Installation

### Local Development

1. Clone the repository:
```bash
git clone https://github.com/yourusername/my-python-app.git
cd my-python-app
```

2. Create virtual environment:
```bash
python3 -m venv venv
source venv/bin/activate  # On Windows: venv\\Scripts\\activate
```

3. Install dependencies:
```bash
pip install -r requirements.txt
```

4. Run the application:
```bash
python my_python_app/main.py
```

### Docker

1. Build the image:
```bash
docker build -t my-python-app .
```

2. Run the container:
```bash
docker run -p 8000:8000 my-python-app
```

### Docker Compose

```bash
docker-compose up -d
```

## Deployment

### Production Deployment

1. Set environment variables:
```bash
export FLASK_ENV=production
export SECRET_KEY=your-secret-key
export DATABASE_URL=your-database-url
```

2. Run deployment script:
```bash
./deploy.sh production
```

### Cloud Deployment

#### AWS Elastic Beanstalk
```bash
eb init
eb create production
eb deploy
```

#### Google Cloud App Engine
```bash
gcloud app deploy
```

#### Azure App Service
```bash
az webapp up --name my-python-app
```

## Testing

Run tests:
```bash
python -m pytest tests/ --cov=my_python_app
```

## Monitoring

The application includes:
- Health check endpoint: `/health`
- System metrics monitoring
- Structured logging
- Error tracking

## Security

- API key authentication
- Rate limiting
- Security headers
- Input validation
- Password hashing

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests
5. Submit a pull request

## License

MIT License - see LICENSE file for details.
'''
    
    with open('README.md', 'w') as f:
        f.write(readme_content)
    
    print("Documentation created")

# Create documentation
create_documentation()

print("\nDeployment examples completed!")