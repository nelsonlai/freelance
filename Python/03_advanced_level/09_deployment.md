# 9. Deployment and Production - Taking Applications Live

Deployment and production management are crucial for bringing applications to users. This lesson covers packaging, containerization, cloud deployment, and production best practices for professional Python development.

## Application Packaging

### Python Package Structure

```python
# This would be the structure of a Python package
package_structure = """
my_package/
├── README.md
├── setup.py
├── pyproject.toml
├── requirements.txt
├── requirements-dev.txt
├── .gitignore
├── .pre-commit-config.yaml
├── tests/
│   ├── __init__.py
│   ├── test_main.py
│   └── conftest.py
├── src/
│   └── my_package/
│       ├── __init__.py
│       ├── main.py
│       ├── models/
│       │   ├── __init__.py
│       │   └── user.py
│       ├── services/
│       │   ├── __init__.py
│       │   └── api.py
│       └── utils/
│           ├── __init__.py
│           └── helpers.py
└── docs/
    ├── index.md
    └── api.md
"""

# setup.py example
setup_py_content = """
from setuptools import setup, find_packages

with open("README.md", "r", encoding="utf-8") as fh:
    long_description = fh.read()

with open("requirements.txt", "r", encoding="utf-8") as fh:
    requirements = [line.strip() for line in fh if line.strip() and not line.startswith("#")]

setup(
    name="my-package",
    version="1.0.0",
    author="Your Name",
    author_email="your.email@example.com",
    description="A sample Python package",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/yourusername/my-package",
    project_urls={
        "Bug Tracker": "https://github.com/yourusername/my-package/issues",
    },
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
    package_dir={"": "src"},
    packages=find_packages(where="src"),
    python_requires=">=3.8",
    install_requires=requirements,
    extras_require={
        "dev": [
            "pytest>=7.0",
            "pytest-cov>=4.0",
            "black>=23.0",
            "flake8>=6.0",
            "mypy>=1.0",
        ],
    },
    entry_points={
        "console_scripts": [
            "my-package=my_package.main:main",
        ],
    },
)
"""

# pyproject.toml example
pyproject_toml_content = """
[build-system]
requires = ["setuptools>=61.0", "wheel"]
build-backend = "setuptools.build_meta"

[project]
name = "my-package"
version = "1.0.0"
description = "A sample Python package"
readme = "README.md"
requires-python = ">=3.8"
license = {text = "MIT"}
authors = [
    {name = "Your Name", email = "your.email@example.com"},
]
classifiers = [
    "Development Status :: 4 - Beta",
    "Intended Audience :: Developers",
    "License :: OSI Approved :: MIT License",
    "Operating System :: OS Independent",
    "Programming Language :: Python :: 3",
    "Programming Language :: Python :: 3.8",
    "Programming Language :: Python :: 3.9",
    "Programming Language :: Python :: 3.10",
    "Programming Language :: Python :: 3.11",
]
dependencies = [
    "requests>=2.28.0",
    "fastapi>=0.100.0",
    "uvicorn[standard]>=0.23.0",
]

[project.optional-dependencies]
dev = [
    "pytest>=7.0",
    "pytest-cov>=4.0",
    "black>=23.0",
    "flake8>=6.0",
    "mypy>=1.0",
    "pre-commit>=3.0",
]

[project.scripts]
my-package = "my_package.main:main"

[tool.setuptools.packages.find]
where = ["src"]

[tool.black]
line-length = 88
target-version = ['py38']
include = '\.pyi?$'
extend-exclude = '''
/(
  # directories
  \.eggs
  | \.git
  | \.hg
  | \.mypy_cache
  | \.tox
  | \.venv
  | build
  | dist
)/
'''

[tool.isort]
profile = "black"
multi_line_output = 3
line_length = 88

[tool.mypy]
python_version = "3.8"
warn_return_any = true
warn_unused_configs = true
disallow_untyped_defs = true

[tool.pytest.ini_options]
testpaths = ["tests"]
python_files = ["test_*.py"]
python_classes = ["Test*"]
python_functions = ["test_*"]
addopts = "-v --tb=short"
"""

print("Package structure:")
print(package_structure)
print("\nsetup.py content:")
print(setup_py_content)
print("\npyproject.toml content:")
print(pyproject_toml_content)
```

### Building and Distributing Packages

```python
import subprocess
import os
import shutil
from pathlib import Path

class PackageBuilder:
    """Utility class for building Python packages."""
    
    @staticmethod
    def clean_build_directories():
        """Clean build directories."""
        dirs_to_clean = ['build', 'dist', '*.egg-info']
        for pattern in dirs_to_clean:
            for path in Path('.').glob(pattern):
                if path.is_dir():
                    shutil.rmtree(path)
                    print(f"Removed {path}")
    
    @staticmethod
    def build_package():
        """Build the package."""
        try:
            # Clean first
            PackageBuilder.clean_build_directories()
            
            # Build wheel and source distribution
            subprocess.run([
                'python', '-m', 'build'
            ], check=True)
            
            print("Package built successfully!")
            
        except subprocess.CalledProcessError as e:
            print(f"Build failed: {e}")
            return False
        
        return True
    
    @staticmethod
    def check_package():
        """Check the package for issues."""
        try:
            subprocess.run([
                'python', '-m', 'twine', 'check', 'dist/*'
            ], check=True)
            print("Package check passed!")
            return True
        except subprocess.CalledProcessError as e:
            print(f"Package check failed: {e}")
            return False
    
    @staticmethod
    def upload_to_testpypi():
        """Upload to TestPyPI."""
        try:
            subprocess.run([
                'python', '-m', 'twine', 'upload',
                '--repository', 'testpypi',
                'dist/*'
            ], check=True)
            print("Uploaded to TestPyPI successfully!")
            return True
        except subprocess.CalledProcessError as e:
            print(f"Upload to TestPyPI failed: {e}")
            return False
    
    @staticmethod
    def upload_to_pypi():
        """Upload to PyPI."""
        try:
            subprocess.run([
                'python', '-m', 'twine', 'upload',
                'dist/*'
            ], check=True)
            print("Uploaded to PyPI successfully!")
            return True
        except subprocess.CalledProcessError as e:
            print(f"Upload to PyPI failed: {e}")
            return False

# Example usage
def demonstrate_package_building():
    """Demonstrate package building process."""
    print("=== Package Building Demo ===")
    
    # This would be run in a real project
    # builder = PackageBuilder()
    # builder.build_package()
    # builder.check_package()
    
    print("Package building process:")
    print("1. Clean build directories")
    print("2. Build wheel and source distribution")
    print("3. Check package for issues")
    print("4. Upload to TestPyPI for testing")
    print("5. Upload to PyPI for production")

demonstrate_package_building()
```

## Containerization with Docker

### Docker Best Practices

```python
# Multi-stage Dockerfile
multi_stage_dockerfile = """
# Build stage
FROM python:3.11-slim as builder

WORKDIR /app

# Install build dependencies
RUN apt-get update && apt-get install -y \\
    gcc \\
    g++ \\
    && rm -rf /var/lib/apt/lists/*

# Copy requirements and install Python dependencies
COPY requirements.txt .
RUN pip install --no-cache-dir --user -r requirements.txt

# Production stage
FROM python:3.11-slim as production

# Install runtime dependencies
RUN apt-get update && apt-get install -y \\
    curl \\
    && rm -rf /var/lib/apt/lists/*

# Create non-root user
RUN useradd --create-home --shell /bin/bash app

# Copy Python packages from builder stage
COPY --from=builder /root/.local /home/app/.local

# Set working directory and ownership
WORKDIR /app
RUN chown -R app:app /app

# Switch to non-root user
USER app

# Update PATH
ENV PATH=/home/app/.local/bin:$PATH

# Copy application code
COPY --chown=app:app . .

# Expose port
EXPOSE 8000

# Health check
HEALTHCHECK --interval=30s --timeout=30s --start-period=5s --retries=3 \\
    CMD curl -f http://localhost:8000/health || exit 1

# Run application
CMD ["python", "-m", "uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8000"]
"""

# Docker Compose for development
docker_compose_dev = """
version: '3.8'

services:
  web:
    build:
      context: .
      target: builder
    ports:
      - "8000:8000"
    environment:
      - DEBUG=true
      - DATABASE_URL=postgresql://user:password@db:5432/mydb
    volumes:
      - .:/app
      - /app/__pycache__
    depends_on:
      - db
      - redis
    command: python -m uvicorn main:app --host 0.0.0.0 --port 8000 --reload

  db:
    image: postgres:15-alpine
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

# Production Docker Compose
docker_compose_prod = """
version: '3.8'

services:
  web:
    build:
      context: .
      target: production
    environment:
      - DEBUG=false
      - DATABASE_URL=postgresql://user:password@db:5432/mydb
    depends_on:
      - db
      - redis
    restart: unless-stopped
    deploy:
      replicas: 3
      resources:
        limits:
          memory: 512M
        reservations:
          memory: 256M

  db:
    image: postgres:15-alpine
    environment:
      - POSTGRES_DB=mydb
      - POSTGRES_USER=user
      - POSTGRES_PASSWORD=password
    volumes:
      - postgres_data:/var/lib/postgresql/data
    restart: unless-stopped
    deploy:
      resources:
        limits:
          memory: 1G
        reservations:
          memory: 512M

  redis:
    image: redis:7-alpine
    restart: unless-stopped
    deploy:
      resources:
        limits:
          memory: 256M
        reservations:
          memory: 128M

  nginx:
    image: nginx:alpine
    ports:
      - "80:80"
      - "443:443"
    volumes:
      - ./nginx.conf:/etc/nginx/nginx.conf
      - ./ssl:/etc/nginx/ssl
    depends_on:
      - web
    restart: unless-stopped

volumes:
  postgres_data:
"""

print("Docker configurations:")
print("Multi-stage Dockerfile:")
print(multi_stage_dockerfile)
print("\nDevelopment Docker Compose:")
print(docker_compose_dev)
print("\nProduction Docker Compose:")
print(docker_compose_prod)
```

### Docker Utilities

```python
import docker
import time
from contextlib import contextmanager

class DockerManager:
    """Docker management utilities."""
    
    def __init__(self):
        self.client = docker.from_env()
    
    def build_image(self, tag, path=".", dockerfile="Dockerfile"):
        """Build Docker image."""
        try:
            image, build_logs = self.client.images.build(
                path=path,
                tag=tag,
                dockerfile=dockerfile,
                rm=True
            )
            print(f"Image {tag} built successfully!")
            return image
        except docker.errors.BuildError as e:
            print(f"Build failed: {e}")
            return None
    
    def run_container(self, image, ports=None, environment=None, volumes=None):
        """Run Docker container."""
        try:
            container = self.client.containers.run(
                image,
                detach=True,
                ports=ports or {},
                environment=environment or {},
                volumes=volumes or {}
            )
            print(f"Container {container.short_id} started!")
            return container
        except docker.errors.ContainerError as e:
            print(f"Container failed to start: {e}")
            return None
    
    def stop_container(self, container_id):
        """Stop Docker container."""
        try:
            container = self.client.containers.get(container_id)
            container.stop()
            print(f"Container {container_id} stopped!")
            return True
        except docker.errors.NotFound:
            print(f"Container {container_id} not found!")
            return False
    
    def get_container_logs(self, container_id):
        """Get container logs."""
        try:
            container = self.client.containers.get(container_id)
            return container.logs().decode('utf-8')
        except docker.errors.NotFound:
            return "Container not found!"
    
    def list_containers(self, all_containers=False):
        """List Docker containers."""
        containers = self.client.containers.list(all=all_containers)
        for container in containers:
            print(f"ID: {container.short_id}, Image: {container.image.tags}, Status: {container.status}")
        return containers
    
    def cleanup(self):
        """Clean up stopped containers and unused images."""
        try:
            # Remove stopped containers
            stopped_containers = self.client.containers.list(filters={"status": "exited"})
            for container in stopped_containers:
                container.remove()
                print(f"Removed stopped container {container.short_id}")
            
            # Remove unused images
            self.client.images.prune()
            print("Cleaned up unused images!")
            
        except Exception as e:
            print(f"Cleanup failed: {e}")

# Example usage
def demonstrate_docker_management():
    """Demonstrate Docker management."""
    print("=== Docker Management Demo ===")
    
    # This would be used in a real project
    # docker_manager = DockerManager()
    # image = docker_manager.build_image("my-app:latest")
    # container = docker_manager.run_container(image, ports={"8000": "8000"})
    
    print("Docker management operations:")
    print("1. Build image")
    print("2. Run container")
    print("3. Monitor logs")
    print("4. Stop container")
    print("5. Cleanup resources")

demonstrate_docker_management()
```

## Cloud Deployment

### AWS Deployment

```python
# AWS deployment configuration
aws_deployment_config = {
    "region": "us-west-2",
    "instance_type": "t3.micro",
    "ami_id": "ami-0c02fb55956c7d316",  # Amazon Linux 2
    "security_groups": [
        {
            "name": "web-sg",
            "rules": [
                {"type": "ssh", "port": 22, "source": "0.0.0.0/0"},
                {"type": "http", "port": 80, "source": "0.0.0.0/0"},
                {"type": "https", "port": 443, "source": "0.0.0.0/0"},
                {"type": "custom", "port": 8000, "source": "0.0.0.0/0"}
            ]
        }
    ],
    "user_data": """
#!/bin/bash
yum update -y
yum install -y python3 python3-pip git nginx

# Install application
git clone https://github.com/yourusername/your-app.git /opt/app
cd /opt/app
pip3 install -r requirements.txt

# Configure nginx
cat > /etc/nginx/conf.d/app.conf << EOF
server {
    listen 80;
    server_name _;
    
    location / {
        proxy_pass http://127.0.0.1:8000;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
}
EOF

# Start services
systemctl enable nginx
systemctl start nginx

# Start application
cd /opt/app
python3 -m uvicorn main:app --host 0.0.0.0 --port 8000 --daemon
"""
}

# Terraform configuration
terraform_config = """
provider "aws" {
  region = "us-west-2"
}

resource "aws_instance" "web" {
  ami           = "ami-0c02fb55956c7d316"
  instance_type = "t3.micro"
  
  security_groups = [aws_security_group.web.name]
  
  user_data = file("user_data.sh")
  
  tags = {
    Name = "web-server"
  }
}

resource "aws_security_group" "web" {
  name        = "web-sg"
  description = "Security group for web server"
  
  ingress {
    from_port   = 22
    to_port     = 22
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
  
  ingress {
    from_port   = 80
    to_port     = 80
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
  
  ingress {
    from_port   = 443
    to_port     = 443
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
  
  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }
}

resource "aws_db_instance" "database" {
  identifier = "mydb"
  engine     = "postgres"
  engine_version = "15.2"
  instance_class = "db.t3.micro"
  allocated_storage = 20
  
  db_name  = "mydb"
  username = "user"
  password = "password"
  
  vpc_security_group_ids = [aws_security_group.db.id]
  
  backup_retention_period = 7
  backup_window          = "03:00-04:00"
  maintenance_window     = "sun:04:00-sun:05:00"
  
  skip_final_snapshot = true
}

resource "aws_security_group" "db" {
  name        = "db-sg"
  description = "Security group for database"
  
  ingress {
    from_port   = 5432
    to_port     = 5432
    protocol    = "tcp"
    security_groups = [aws_security_group.web.id]
  }
}
"""

print("AWS deployment configuration:")
print(aws_deployment_config)
print("\nTerraform configuration:")
print(terraform_config)
```

### Kubernetes Deployment

```python
# Kubernetes deployment manifests
kubernetes_manifests = {
    "deployment": """
apiVersion: apps/v1
kind: Deployment
metadata:
  name: web-app
  labels:
    app: web-app
spec:
  replicas: 3
  selector:
    matchLabels:
      app: web-app
  template:
    metadata:
      labels:
        app: web-app
    spec:
      containers:
      - name: web-app
        image: your-registry/web-app:latest
        ports:
        - containerPort: 8000
        env:
        - name: DATABASE_URL
          valueFrom:
            secretKeyRef:
              name: app-secrets
              key: database-url
        - name: REDIS_URL
          valueFrom:
            secretKeyRef:
              name: app-secrets
              key: redis-url
        resources:
          requests:
            memory: "256Mi"
            cpu: "250m"
          limits:
            memory: "512Mi"
            cpu: "500m"
        livenessProbe:
          httpGet:
            path: /health
            port: 8000
          initialDelaySeconds: 30
          periodSeconds: 10
        readinessProbe:
          httpGet:
            path: /ready
            port: 8000
          initialDelaySeconds: 5
          periodSeconds: 5
""",
    
    "service": """
apiVersion: v1
kind: Service
metadata:
  name: web-app-service
spec:
  selector:
    app: web-app
  ports:
    - protocol: TCP
      port: 80
      targetPort: 8000
  type: LoadBalancer
""",
    
    "ingress": """
apiVersion: networking.k8s.io/v1
kind: Ingress
metadata:
  name: web-app-ingress
  annotations:
    nginx.ingress.kubernetes.io/rewrite-target: /
spec:
  rules:
  - host: your-domain.com
    http:
      paths:
      - path: /
        pathType: Prefix
        backend:
          service:
            name: web-app-service
            port:
              number: 80
""",
    
    "secret": """
apiVersion: v1
kind: Secret
metadata:
  name: app-secrets
type: Opaque
data:
  database-url: cG9zdGdyZXNxbDovL3VzZXI6cGFzc3dvcmRAZGI6NTQzMi9teWRi
  redis-url: cmVkaXM6Ly9yZWRpczozNjc5
""",
    
    "configmap": """
apiVersion: v1
kind: ConfigMap
metadata:
  name: app-config
data:
  DEBUG: "false"
  LOG_LEVEL: "info"
  MAX_WORKERS: "4"
"""
}

print("Kubernetes deployment manifests:")
for name, manifest in kubernetes_manifests.items():
    print(f"\n{name.upper()}:")
    print(manifest)
```

## Production Monitoring

### Application Monitoring

```python
import logging
import time
import psutil
import requests
from datetime import datetime
from typing import Dict, Any

class ApplicationMonitor:
    """Application monitoring utilities."""
    
    def __init__(self):
        self.logger = logging.getLogger(__name__)
        self.metrics = {}
    
    def get_system_metrics(self) -> Dict[str, Any]:
        """Get system metrics."""
        return {
            'cpu_percent': psutil.cpu_percent(interval=1),
            'memory_percent': psutil.virtual_memory().percent,
            'disk_percent': psutil.disk_usage('/').percent,
            'load_average': psutil.getloadavg() if hasattr(psutil, 'getloadavg') else None,
            'timestamp': datetime.utcnow().isoformat()
        }
    
    def get_application_metrics(self) -> Dict[str, Any]:
        """Get application-specific metrics."""
        return {
            'active_connections': self.get_active_connections(),
            'response_time': self.get_response_time(),
            'error_rate': self.get_error_rate(),
            'timestamp': datetime.utcnow().isoformat()
        }
    
    def get_active_connections(self) -> int:
        """Get number of active connections."""
        # This would be implemented based on your application
        return 0
    
    def get_response_time(self) -> float:
        """Get average response time."""
        # This would be implemented based on your application
        return 0.0
    
    def get_error_rate(self) -> float:
        """Get error rate."""
        # This would be implemented based on your application
        return 0.0
    
    def health_check(self) -> Dict[str, Any]:
        """Perform health check."""
        health_status = {
            'status': 'healthy',
            'timestamp': datetime.utcnow().isoformat(),
            'checks': {}
        }
        
        # Check system resources
        system_metrics = self.get_system_metrics()
        if system_metrics['cpu_percent'] > 80:
            health_status['checks']['cpu'] = 'warning'
            health_status['status'] = 'degraded'
        
        if system_metrics['memory_percent'] > 90:
            health_status['checks']['memory'] = 'critical'
            health_status['status'] = 'unhealthy'
        
        if system_metrics['disk_percent'] > 85:
            health_status['checks']['disk'] = 'warning'
            health_status['status'] = 'degraded'
        
        # Check application health
        app_metrics = self.get_application_metrics()
        if app_metrics['error_rate'] > 0.1:  # 10% error rate
            health_status['checks']['error_rate'] = 'critical'
            health_status['status'] = 'unhealthy'
        
        return health_status
    
    def log_metrics(self):
        """Log metrics."""
        system_metrics = self.get_system_metrics()
        app_metrics = self.get_application_metrics()
        
        self.logger.info(f"System metrics: {system_metrics}")
        self.logger.info(f"Application metrics: {app_metrics}")
    
    def send_metrics_to_external_service(self, endpoint: str):
        """Send metrics to external monitoring service."""
        try:
            metrics = {
                'system': self.get_system_metrics(),
                'application': self.get_application_metrics(),
                'health': self.health_check()
            }
            
            response = requests.post(endpoint, json=metrics, timeout=5)
            response.raise_for_status()
            
        except Exception as e:
            self.logger.error(f"Failed to send metrics: {e}")

# Example usage
def demonstrate_monitoring():
    """Demonstrate monitoring capabilities."""
    print("=== Application Monitoring Demo ===")
    
    monitor = ApplicationMonitor()
    
    # Get metrics
    system_metrics = monitor.get_system_metrics()
    app_metrics = monitor.get_application_metrics()
    health_status = monitor.health_check()
    
    print("System metrics:")
    for key, value in system_metrics.items():
        print(f"  {key}: {value}")
    
    print("\nApplication metrics:")
    for key, value in app_metrics.items():
        print(f"  {key}: {value}")
    
    print(f"\nHealth status: {health_status['status']}")
    if health_status['checks']:
        print("Health checks:")
        for check, status in health_status['checks'].items():
            print(f"  {check}: {status}")

demonstrate_monitoring()
```

### Logging Configuration

```python
import logging
import logging.handlers
import json
from datetime import datetime

class JSONFormatter(logging.Formatter):
    """JSON formatter for structured logging."""
    
    def format(self, record):
        log_entry = {
            'timestamp': datetime.utcnow().isoformat(),
            'level': record.levelname,
            'logger': record.name,
            'message': record.getMessage(),
            'module': record.module,
            'function': record.funcName,
            'line': record.lineno
        }
        
        if record.exc_info:
            log_entry['exception'] = self.formatException(record.exc_info)
        
        return json.dumps(log_entry)

def setup_production_logging():
    """Setup production logging configuration."""
    
    # Create logger
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)
    
    # Remove existing handlers
    for handler in logger.handlers[:]:
        logger.removeHandler(handler)
    
    # Console handler
    console_handler = logging.StreamHandler()
    console_handler.setLevel(logging.INFO)
    console_formatter = logging.Formatter(
        '%(asctime)s - %(name)s - %(levelname)s - %(message)s'
    )
    console_handler.setFormatter(console_formatter)
    logger.addHandler(console_handler)
    
    # File handler
    file_handler = logging.handlers.RotatingFileHandler(
        'app.log',
        maxBytes=10*1024*1024,  # 10MB
        backupCount=5
    )
    file_handler.setLevel(logging.INFO)
    json_formatter = JSONFormatter()
    file_handler.setFormatter(json_formatter)
    logger.addHandler(file_handler)
    
    # Error file handler
    error_handler = logging.handlers.RotatingFileHandler(
        'error.log',
        maxBytes=10*1024*1024,  # 10MB
        backupCount=5
    )
    error_handler.setLevel(logging.ERROR)
    error_handler.setFormatter(json_formatter)
    logger.addHandler(error_handler)
    
    # Syslog handler (for production)
    try:
        syslog_handler = logging.handlers.SysLogHandler()
        syslog_handler.setLevel(logging.WARNING)
        syslog_handler.setFormatter(json_formatter)
        logger.addHandler(syslog_handler)
    except Exception as e:
        logger.warning(f"Could not setup syslog handler: {e}")
    
    return logger

def demonstrate_logging():
    """Demonstrate logging configuration."""
    print("=== Production Logging Demo ===")
    
    logger = setup_production_logging()
    
    # Test different log levels
    logger.debug("This is a debug message")
    logger.info("This is an info message")
    logger.warning("This is a warning message")
    logger.error("This is an error message")
    
    # Test exception logging
    try:
        raise ValueError("This is a test exception")
    except ValueError:
        logger.exception("An exception occurred")
    
    print("Logging demonstration completed. Check app.log and error.log files.")

demonstrate_logging()
```

## Key Takeaways

1. **Package structure** follows Python best practices for distribution
2. **Docker** provides consistent deployment environments
3. **Multi-stage builds** optimize image size and security
4. **Cloud deployment** scales applications to meet demand
5. **Kubernetes** orchestrates containerized applications
6. **Monitoring** ensures application health and performance
7. **Structured logging** improves debugging and analysis
8. **Production practices** focus on reliability and security

## Next Steps

You've completed the Advanced Level! You now have comprehensive knowledge of:
- Advanced OOP and design patterns
- Functional programming techniques
- Concurrency and parallelism
- Data handling with Pandas and NumPy
- Algorithms and problem-solving
- Web development and APIs
- Database management and ORMs
- Testing and CI/CD
- Deployment and production practices

You're ready to specialize in specific areas or start building professional applications!
