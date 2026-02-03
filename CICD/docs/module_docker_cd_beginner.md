<!-- Module: Docker for CD - Beginner's Guide -->
# Module: Docker for Continuous Deployment - Beginner's Guide

## 1. Teaching Objectives

By the end of this module, students will be able to:
- Understand what containers are and why they're essential for CD
- Install Docker and run their first container
- Build Docker images for Python applications
- Use multi-stage builds to optimize images
- Push images to Amazon ECR (Elastic Container Registry)
- Integrate Docker into CD pipelines
- Apply Docker best practices for production deployments

## 2. What is Docker? Understanding Containers

### 2.1 The Problem Docker Solves

**Before Docker:**
- "Works on my machine" - code runs on developer's laptop but fails in production
- Different environments (dev, staging, prod) have different configurations
- Difficult to reproduce issues
- Manual setup of servers, dependencies, configurations
- Inconsistent deployments

**With Docker:**
- Same environment everywhere (dev, staging, production)
- Package everything together (code + dependencies + runtime)
- Easy to reproduce and debug
- Consistent, repeatable deployments
- Fast startup times

### 2.2 Containers vs Virtual Machines

**Virtual Machines (VMs):**
- Each VM has its own operating system
- Heavy (GBs of disk space)
- Slow to start (minutes)
- High resource usage

**Containers:**
- Share the host operating system
- Lightweight (MBs of disk space)
- Fast to start (seconds)
- Low resource usage
- Isolated from other containers

**Analogy**: 
- **VM** = A complete house (foundation, walls, roof, utilities)
- **Container** = An apartment in a building (shares foundation, utilities, but has its own space)

### 2.3 Key Docker Concepts

| Term | Definition | Example |
|------|------------|---------|
| **Image** | A read-only template for creating containers | `python:3.12-slim` |
| **Container** | A running instance of an image | Your app running in a container |
| **Dockerfile** | Instructions for building an image | Recipe for creating your image |
| **Registry** | Storage for images (like GitHub for code) | Docker Hub, Amazon ECR |
| **Docker Hub** | Public registry of Docker images | `docker pull python:3.12` |

## 3. Installing Docker

### 3.1 Installation Steps

**macOS:**
```bash
# Install Docker Desktop from https://www.docker.com/products/docker-desktop
# Or use Homebrew:
brew install --cask docker
```

**Linux (Ubuntu/Debian):**
```bash
# Update package index
sudo apt-get update

# Install Docker
sudo apt-get install docker.io

# Start Docker service
sudo systemctl start docker
sudo systemctl enable docker

# Add your user to docker group (to run without sudo)
sudo usermod -aG docker $USER
# Log out and back in for changes to take effect
```

**Windows:**
- Download Docker Desktop from https://www.docker.com/products/docker-desktop
- Install and restart

### 3.2 Verify Installation

```bash
# Check Docker version
docker --version
# Output: Docker version 24.0.0, build ...

# Run a test container
docker run hello-world
# This should download and run a test image
```

## 4. Your First Container

### 4.1 Running a Simple Container

```bash
# Run a Python container interactively
docker run -it python:3.12-slim python

# You're now in a Python REPL inside the container!
# Try: print("Hello from Docker!")
# Exit with: exit()
```

### 4.2 Understanding Docker Commands

```bash
# docker run: Create and start a container
docker run python:3.12-slim python --version

# docker ps: List running containers
docker ps

# docker ps -a: List all containers (including stopped)
docker ps -a

# docker images: List downloaded images
docker images

# docker stop: Stop a running container
docker stop <container-id>

# docker rm: Remove a container
docker rm <container-id>

# docker rmi: Remove an image
docker rmi <image-id>
```

## 5. Building Docker Images for Python Apps

### 5.1 Understanding Dockerfiles

A Dockerfile is a text file with instructions for building a Docker image. Think of it as a recipe.

**Basic Dockerfile Structure:**
```dockerfile
# Step 1: Choose base image
FROM python:3.12-slim

# Step 2: Set working directory
WORKDIR /app

# Step 3: Copy requirements file
COPY requirements.txt .

# Step 4: Install dependencies
RUN pip install --no-cache-dir -r requirements.txt

# Step 5: Copy application code
COPY app app

# Step 6: Expose port
EXPOSE 8080

# Step 7: Define command to run
CMD ["uvicorn", "app.api:app", "--host", "0.0.0.0", "--port", "8080"]
```

### 5.2 Dockerfile for Our Sample Python App

Let's examine the Dockerfile for our sample Python application:

```dockerfile
# syntax=docker/dockerfile:1.7-labs

# Stage 1: Base image with Python
FROM python:3.12-slim AS base
ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1
WORKDIR /app

# Stage 2: Builder stage (for compiling dependencies)
FROM base AS builder
RUN apt-get update && apt-get install -y build-essential && rm -rf /var/lib/apt/lists/*
COPY requirements.txt requirements-dev.txt ./
RUN pip install --upgrade pip && pip install -r requirements.txt

# Stage 3: Runtime stage (final, minimal image)
FROM base AS runtime
COPY --from=builder /usr/local /usr/local
COPY app app
COPY requirements.txt .
ENV PORT=8080
EXPOSE 8080
CMD ["uvicorn", "app.api:app", "--host", "0.0.0.0", "--port", "8080"]
```

**Explanation:**
- **Multi-stage build**: Creates smaller final image by using separate stages
- **Stage 1 (base)**: Sets up Python environment
- **Stage 2 (builder)**: Installs build tools and dependencies
- **Stage 3 (runtime)**: Final image with only runtime dependencies (no build tools)

### 5.3 Building Your First Image

```bash
# Navigate to your project directory
cd sample_python_app

# Build the image
docker build -t sample-python-app:latest .

# Explanation:
# -t: Tag (name) the image as "sample-python-app:latest"
# . : Build context (current directory)

# Build with a specific tag (recommended for CD)
docker build -t sample-python-app:v1.0.0 .
docker build -t sample-python-app:$(git rev-parse --short HEAD) .
```

### 5.4 Running Your Container

```bash
# Run the container
docker run -p 8080:8080 sample-python-app:latest

# Explanation:
# -p 8080:8080: Map port 8080 on host to port 8080 in container
# Format: -p HOST_PORT:CONTAINER_PORT

# Test the application
curl http://localhost:8080/healthz

# Run in detached mode (background)
docker run -d -p 8080:8080 --name my-app sample-python-app:latest

# View logs
docker logs my-app

# Stop the container
docker stop my-app
```

## 6. Multi-Stage Builds Explained

### 6.1 Why Multi-Stage Builds?

**Problem with single-stage builds:**
- Build tools (compilers, build-essential) end up in final image
- Larger image size (slower to download, more storage)
- Security risk (more attack surface)

**Solution: Multi-stage builds**
- Use one stage for building
- Use another stage for runtime
- Only copy what's needed to final stage

### 6.2 Multi-Stage Build Example

```dockerfile
# Stage 1: Build stage
FROM python:3.12-slim AS builder
WORKDIR /app

# Install build dependencies
RUN apt-get update && \
    apt-get install -y build-essential gcc && \
    rm -rf /var/lib/apt/lists/*

# Install Python dependencies
COPY requirements.txt .
RUN pip install --user --no-cache-dir -r requirements.txt

# Stage 2: Runtime stage
FROM python:3.12-slim AS runtime
WORKDIR /app

# Copy only installed packages from builder
COPY --from=builder /root/.local /root/.local

# Copy application code
COPY app app

# Make sure scripts in .local are usable
ENV PATH=/root/.local/bin:$PATH

# Expose port
EXPOSE 8080

# Run application
CMD ["uvicorn", "app.api:app", "--host", "0.0.0.0", "--port", "8080"]
```

**Benefits:**
- Final image is much smaller (no build tools)
- Faster to download and deploy
- More secure (fewer packages)
- Faster container startup

## 7. Docker Registries and Amazon ECR

### 7.1 What is a Registry?

A registry is a storage and distribution system for Docker images. Think of it like:
- **GitHub** for code → **Docker Registry** for images
- Public registries: Docker Hub, GitHub Container Registry
- Private registries: Amazon ECR, Google Container Registry, Azure Container Registry

### 7.2 Amazon ECR (Elastic Container Registry)

**Why ECR for AWS deployments?**
- Integrated with AWS services (EKS, ECS, Lambda)
- Secure (IAM-based access control)
- Fast (same region as your services)
- Cost-effective (pay for storage and data transfer)

### 7.3 Setting Up ECR

**Step 1: Create ECR Repository**
```bash
# Using AWS CLI
aws ecr create-repository \
    --repository-name sample-python-app \
    --region us-east-1

# Output includes repository URI:
# 123456789012.dkr.ecr.us-east-1.amazonaws.com/sample-python-app
```

**Step 2: Authenticate Docker to ECR**
```bash
# Get login token and authenticate
aws ecr get-login-password --region us-east-1 | \
    docker login --username AWS --password-stdin \
    123456789012.dkr.ecr.us-east-1.amazonaws.com
```

**Step 3: Tag Your Image**
```bash
# Tag image with ECR repository URI
docker tag sample-python-app:latest \
    123456789012.dkr.ecr.us-east-1.amazonaws.com/sample-python-app:latest

# Tag with version
docker tag sample-python-app:latest \
    123456789012.dkr.ecr.us-east-1.amazonaws.com/sample-python-app:v1.0.0

# Tag with commit SHA (common in CD)
docker tag sample-python-app:latest \
    123456789012.dkr.ecr.us-east-1.amazonaws.com/sample-python-app:abc1234
```

**Step 4: Push Image to ECR**
```bash
# Push the image
docker push 123456789012.dkr.ecr.us-east-1.amazonaws.com/sample-python-app:latest
docker push 123456789012.dkr.ecr.us-east-1.amazonaws.com/sample-python-app:v1.0.0
```

### 7.4 Pulling Images from ECR

```bash
# Pull image from ECR
docker pull 123456789012.dkr.ecr.us-east-1.amazonaws.com/sample-python-app:v1.0.0

# Run container from ECR image
docker run -p 8080:8080 \
    123456789012.dkr.ecr.us-east-1.amazonaws.com/sample-python-app:v1.0.0
```

## 8. Docker Best Practices for CD

### 8.1 Image Tagging Strategy

**Good Practices:**
```bash
# Use semantic versioning
docker build -t my-app:v1.2.3 .

# Use commit SHA for traceability
docker build -t my-app:$(git rev-parse --short HEAD) .

# Use both
docker build -t my-app:v1.2.3-abc1234 .

# Never use only 'latest' in production
# 'latest' can change, making rollbacks difficult
```

**Bad Practices:**
```bash
# Don't rely only on 'latest'
docker build -t my-app:latest .  # ❌ Too vague

# Don't use random tags
docker build -t my-app:test123 .  # ❌ Not meaningful
```

### 8.2 .dockerignore File

Create a `.dockerignore` file to exclude unnecessary files from build context:

```dockerignore
# .dockerignore
# Exclude Python cache
__pycache__/
*.pyc
*.pyo
*.pyd
.Python

# Exclude virtual environments
venv/
env/
.venv

# Exclude Git
.git/
.gitignore

# Exclude IDE files
.vscode/
.idea/
*.swp

# Exclude tests (if not needed in production)
tests/
*.test.py

# Exclude documentation
docs/
README.md

# Exclude CI/CD files
.github/
.gitlab-ci.yml
```

**Benefits:**
- Faster builds (smaller context)
- Smaller images
- More secure (no sensitive files)

### 8.3 Layer Caching

Docker caches layers. Order instructions from least to most frequently changing:

```dockerfile
# ✅ Good: Dependencies change less frequently
FROM python:3.12-slim
WORKDIR /app
COPY requirements.txt .          # Copy requirements first
RUN pip install -r requirements.txt  # Install dependencies
COPY app app                      # Copy code last (changes more often)

# ❌ Bad: Code copied before dependencies
FROM python:3.12-slim
WORKDIR /app
COPY app app                      # Code changes frequently
COPY requirements.txt .
RUN pip install -r requirements.txt  # This runs every time code changes
```

### 8.4 Security Best Practices

```dockerfile
# ✅ Use specific base image tags (not 'latest')
FROM python:3.12-slim  # Good: specific version

# ✅ Run as non-root user
RUN useradd -m -u 1000 appuser
USER appuser

# ✅ Don't store secrets in image
# Use environment variables or secrets management
ENV DATABASE_URL=${DATABASE_URL}  # Set at runtime

# ✅ Keep base images updated
# Regularly rebuild to get security patches
FROM python:3.12-slim  # Check for updates regularly

# ✅ Use minimal base images
FROM python:3.12-slim  # Good: minimal
# FROM python:3.12      # Bad: includes unnecessary tools
```

### 8.5 Health Checks

Add health checks to your Dockerfile:

```dockerfile
# Add health check
HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
    CMD curl -f http://localhost:8080/healthz || exit 1

# Or use Python
HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
    CMD python -c "import requests; requests.get('http://localhost:8080/healthz')" || exit 1
```

## 9. Docker Compose for Local Development

Docker Compose helps manage multi-container applications:

```yaml
# docker-compose.yml
version: '3.8'

services:
  app:
    build: .
    ports:
      - "8080:8080"
    environment:
      - ENV=development
    volumes:
      - ./app:/app/app  # Mount code for hot reload
    healthcheck:
      test: ["CMD", "curl", "-f", "http://localhost:8080/healthz"]
      interval: 30s
      timeout: 10s
      retries: 3

  # Example: Add a database
  # db:
  #   image: postgres:15
  #   environment:
  #     POSTGRES_DB: myapp
  #     POSTGRES_USER: user
  #     POSTGRES_PASSWORD: password
```

**Usage:**
```bash
# Start services
docker-compose up

# Start in background
docker-compose up -d

# View logs
docker-compose logs -f

# Stop services
docker-compose down
```

## 10. Integrating Docker into CD Pipelines

### 10.1 CD Pipeline with Docker

Here's how Docker fits into a CD pipeline:

```yaml
# .github/workflows/cd.yml
name: Continuous Deployment

on:
  push:
    branches: [main]

jobs:
  build-and-push:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Configure AWS credentials
        uses: aws-actions/configure-aws-credentials@v4
        with:
          aws-access-key-id: ${{ secrets.AWS_ACCESS_KEY_ID }}
          aws-secret-access-key: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
          aws-region: us-east-1

      - name: Login to Amazon ECR
        id: login-ecr
        uses: aws-actions/amazon-ecr-login@v2

      - name: Build, tag, and push image
        env:
          ECR_REGISTRY: ${{ steps.login-ecr.outputs.registry }}
          ECR_REPOSITORY: sample-python-app
          IMAGE_TAG: ${{ github.sha }}
        run: |
          docker build -t $ECR_REGISTRY/$ECR_REPOSITORY:$IMAGE_TAG .
          docker push $ECR_REGISTRY/$ECR_REPOSITORY:$IMAGE_TAG
          docker tag $ECR_REGISTRY/$ECR_REPOSITORY:$IMAGE_TAG $ECR_REGISTRY/$ECR_REPOSITORY:latest
          docker push $ECR_REGISTRY/$ECR_REPOSITORY:latest
```

### 10.2 Building Images in CI/CD

**Best Practices:**
1. **Build once, deploy everywhere**: Build image once, use same image for all environments
2. **Tag with commit SHA**: Enables traceability and rollback
3. **Scan for vulnerabilities**: Add security scanning step
4. **Cache layers**: Use BuildKit for faster builds

**Example with security scanning:**
```yaml
- name: Build Docker image
  run: docker build -t my-app:${{ github.sha }} .

- name: Scan image for vulnerabilities
  run: |
    docker scout cves my-app:${{ github.sha }} || true
    # Or use Trivy:
    # trivy image my-app:${{ github.sha }}

- name: Push to ECR
  run: |
    docker push my-app:${{ github.sha }}
```

## 11. Troubleshooting Common Issues

### Issue 1: "Cannot connect to Docker daemon"
```bash
# Solution: Start Docker service
sudo systemctl start docker

# Or check if Docker Desktop is running (macOS/Windows)
```

### Issue 2: "Out of disk space"
```bash
# Clean up unused images, containers, volumes
docker system prune -a

# Remove specific unused images
docker image prune -a
```

### Issue 3: "Image build fails"
```bash
# Build with verbose output
docker build --progress=plain -t my-app .

# Build without cache to see full process
docker build --no-cache -t my-app .
```

### Issue 4: "Container exits immediately"
```bash
# Check logs
docker logs <container-id>

# Run interactively to debug
docker run -it my-app /bin/bash
```

## 12. Hands-On Exercises

### Exercise 1: Build and Run
1. Build the sample Python app image
2. Run it locally
3. Test the `/healthz` endpoint
4. View container logs

### Exercise 2: Multi-Stage Build
1. Create a simple single-stage Dockerfile
2. Build and check image size
3. Convert to multi-stage build
4. Compare image sizes

### Exercise 3: Push to ECR
1. Create ECR repository
2. Authenticate Docker
3. Build, tag, and push image
4. Pull and run image from ECR

## 13. Key Takeaways

- ✅ Containers package applications with dependencies for consistency
- ✅ Dockerfiles define how to build images
- ✅ Multi-stage builds create smaller, more secure images
- ✅ Registries store and distribute images (ECR for AWS)
- ✅ Tag images with versions/commit SHAs for traceability
- ✅ Use .dockerignore to exclude unnecessary files
- ✅ Order Dockerfile instructions for optimal caching
- ✅ Integrate Docker builds into CD pipelines

## 14. Next Steps

Now that you understand Docker, you're ready for:
- **Module: Kubernetes Basics for CD** - Deploy containers to Kubernetes
- **Module: Terraform for Kubernetes CD** - Automate infrastructure provisioning
- **Module: Complete CD Pipeline** - Put it all together

## 15. Instructor Notes

- Start with hands-on Docker commands before diving into Dockerfiles
- Use visual diagrams to explain container concepts
- Emphasize the "build once, run anywhere" benefit
- Show real-world examples of Docker in production
- Encourage students to experiment with Docker commands
- Highlight security best practices early


