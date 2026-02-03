<!-- Module: CD Fundamentals for Beginners -->
# Module: Continuous Deployment Fundamentals for Beginners

## 1. Teaching Objectives

By the end of this module, students will be able to:
- Understand the difference between Continuous Integration (CI), Continuous Delivery, and Continuous Deployment
- Identify the key stages of a CD pipeline
- Explain why Docker, Kubernetes, and Terraform are essential for modern CD
- Describe a real-world CD workflow from code commit to production

## 2. What is Continuous Deployment?

### 2.1 The Three Cs: CI, CD (Delivery), and CD (Deployment)

Let's clarify these often-confused terms:

**Continuous Integration (CI)**
- Developers frequently merge code changes into a shared repository
- Automated builds and tests run on every commit
- Goal: Catch integration issues early
- **Output**: Tested, buildable code (artifacts like Docker images)

**Continuous Delivery (CD)**
- Extends CI by automatically preparing code for release
- Code is always in a deployable state
- **Manual approval** required before deployment to production
- Goal: Fast, reliable releases with human oversight
- **Output**: Production-ready artifacts ready to deploy

**Continuous Deployment (CD)**
- Extends Continuous Delivery by **automatically deploying** to production
- No manual approval needed (after passing all tests)
- Every successful build can go to production
- Goal: Maximum automation and speed
- **Output**: Code automatically running in production

**Analogy**: Think of CI/CD like a factory assembly line:
- **CI** = Quality control station (testing)
- **Continuous Delivery** = Packaging station (ready to ship, but needs manager approval)
- **Continuous Deployment** = Automatic shipping (packages go out immediately after passing quality checks)

### 2.2 Why Continuous Deployment?

**Benefits:**
1. **Faster Time to Market**: Features reach users quickly
2. **Reduced Risk**: Small, frequent deployments are less risky than big releases
3. **Faster Feedback**: Get user feedback on new features immediately
4. **Improved Quality**: Automated testing catches bugs before production
5. **Less Manual Work**: Automation reduces human error

**When to Use Continuous Deployment:**
- ✅ Well-tested applications with comprehensive test coverage
- ✅ Mature DevOps practices and monitoring
- ✅ Teams comfortable with automated releases
- ✅ Non-critical applications or features

**When to Use Continuous Delivery (with manual approval):**
- ⚠️ Critical systems requiring compliance checks
- ⚠️ Financial or healthcare applications
- ⚠️ Teams new to automation
- ⚠️ Applications with complex deployment requirements

## 3. CD Pipeline Stages

A typical CD pipeline consists of these stages:

### Stage 1: Source Control
- **What**: Code is committed to Git repository
- **Trigger**: Developer pushes code or creates pull request
- **Example**: `git push origin main`

### Stage 2: Build
- **What**: Compile code, install dependencies, create artifacts
- **Output**: Docker images, application packages
- **Example**: Building a Docker image from your Python application

### Stage 3: Test
- **What**: Run automated tests (unit, integration, security)
- **Types**: 
  - Unit tests (test individual functions)
  - Integration tests (test components working together)
  - Security scans (vulnerability checks)
- **Example**: Running `pytest` on your Python code

### Stage 4: Package
- **What**: Create deployable artifacts
- **Output**: Tagged Docker images, versioned packages
- **Example**: Pushing Docker image to Amazon ECR with tag `v1.2.3`

### Stage 5: Deploy to Staging
- **What**: Deploy to a test environment that mirrors production
- **Purpose**: Final validation before production
- **Example**: Deploying to a staging Kubernetes cluster

### Stage 6: Integration Tests
- **What**: Test the deployed application in staging
- **Types**: Smoke tests, end-to-end tests, performance tests
- **Example**: Calling `/healthz` endpoint to verify deployment

### Stage 7: Deploy to Production
- **What**: Deploy to live production environment
- **For Continuous Deployment**: Automatic after all tests pass
- **For Continuous Delivery**: Requires manual approval
- **Example**: Deploying to production EKS cluster

### Stage 8: Verify & Monitor
- **What**: Monitor application health, metrics, logs
- **Purpose**: Ensure deployment succeeded and catch issues early
- **Example**: Checking application logs and metrics dashboards

### Stage 9: Rollback (if needed)
- **What**: Revert to previous version if issues detected
- **Trigger**: Automated alerts or manual decision
- **Example**: Rolling back to previous Docker image tag

## 4. Why Docker, Kubernetes, and Terraform for CD?

### 4.1 Docker: Containerization

**What Docker Does:**
- Packages your application and all its dependencies into a container
- Ensures your app runs the same way everywhere (development, staging, production)
- Makes deployments consistent and predictable

**Why Docker for CD:**
- ✅ **Consistency**: "Works on my machine" becomes "works everywhere"
- ✅ **Speed**: Containers start in seconds, not minutes
- ✅ **Isolation**: Each application runs in its own environment
- ✅ **Portability**: Run the same container on any platform
- ✅ **Versioning**: Tag images with versions (e.g., `myapp:v1.0.0`)

**Example**: Instead of manually installing Python, dependencies, and configuring the server, you build a Docker image once and deploy it everywhere.

### 4.2 Kubernetes: Container Orchestration

**What Kubernetes Does:**
- Manages containers at scale
- Handles deployment, scaling, and health monitoring
- Provides self-healing (restarts failed containers automatically)

**Why Kubernetes for CD:**
- ✅ **Automated Deployments**: Rolling updates without downtime
- ✅ **Scaling**: Automatically scale up/down based on demand
- ✅ **Self-Healing**: Restarts failed containers automatically
- ✅ **Service Discovery**: Containers can find each other automatically
- ✅ **Load Balancing**: Distributes traffic across multiple containers

**Example**: Deploy your application once, and Kubernetes ensures it stays running, scales when needed, and recovers from failures.

### 4.3 Terraform: Infrastructure as Code

**What Terraform Does:**
- Defines infrastructure (servers, networks, databases) as code
- Provisions and manages cloud resources automatically
- Ensures infrastructure is consistent and repeatable

**Why Terraform for CD:**
- ✅ **Reproducibility**: Same infrastructure every time
- ✅ **Version Control**: Track infrastructure changes in Git
- ✅ **Automation**: Provision infrastructure as part of CD pipeline
- ✅ **Multi-Cloud**: Same tool works with AWS, Azure, GCP
- ✅ **State Management**: Track what infrastructure exists

**Example**: Instead of manually clicking through AWS console to create an EKS cluster, you write Terraform code that creates it automatically and consistently.

### 4.4 How They Work Together

```
Developer commits code
    ↓
CI Pipeline builds Docker image
    ↓
Docker image pushed to registry (ECR)
    ↓
Terraform provisions/updates EKS cluster (if needed)
    ↓
Terraform deploys application to Kubernetes
    ↓
Kubernetes runs containers from Docker image
    ↓
Application is live in production
```

## 5. Real-World CD Workflow Example

Let's walk through a complete CD workflow for a Python web application:

### Scenario: Deploying a FastAPI Application

**Step 1: Developer Makes a Change**
```bash
# Developer writes code and commits
git add .
git commit -m "Add new greeting endpoint"
git push origin main
```

**Step 2: CI Pipeline Triggers**
```yaml
# GitHub Actions detects push and starts CI
name: CI
on:
  push:
    branches: [main]
jobs:
  build:
    - Build Docker image
    - Run tests
    - Scan for security vulnerabilities
    - Push image to ECR with tag: sha-abc123
```

**Step 3: CD Pipeline Triggers (after CI succeeds)**
```yaml
# CD pipeline automatically starts
name: CD
on:
  workflow_run:
    workflows: ["CI"]
    types: [completed]
jobs:
  deploy:
    - Pull Docker image from ECR
    - Use Terraform to ensure EKS cluster exists
    - Use Terraform to deploy app to Kubernetes
    - Run smoke tests
    - Monitor deployment
```

**Step 4: Infrastructure Provisioning (Terraform)**
```hcl
# Terraform ensures EKS cluster exists
resource "aws_eks_cluster" "app" {
  name     = "my-app-cluster"
  role_arn = aws_iam_role.cluster.arn
  # ... configuration
}

# Terraform deploys application
resource "kubernetes_deployment" "app" {
  metadata {
    name = "my-app"
  }
  spec {
    replicas = 3
    template {
      spec {
        container {
          image = "123456789.dkr.ecr.us-east-1.amazonaws.com/my-app:sha-abc123"
        }
      }
    }
  }
}
```

**Step 5: Kubernetes Deployment**
- Kubernetes pulls Docker image from ECR
- Creates 3 pods (containers) running your application
- Exposes application via Service (load balancer)
- Monitors health and restarts if needed

**Step 6: Verification**
```bash
# Smoke test verifies deployment
curl https://my-app.example.com/healthz
# Response: {"status": "ok"}

# Monitor metrics
# - Request rate
# - Error rate
# - Response time
```

**Step 7: Rollback (if needed)**
```bash
# If issues detected, rollback to previous version
terraform apply -var="image_tag=sha-previous123"
```

## 6. Simple CD Pipeline Example

Here's a minimal CD pipeline configuration (GitHub Actions):

```yaml
name: Continuous Deployment

# Trigger when code is pushed to main branch
on:
  push:
    branches: [main]

jobs:
  deploy:
    runs-on: ubuntu-latest
    
    steps:
      # Step 1: Checkout code
      - name: Checkout code
        uses: actions/checkout@v4
      
      # Step 2: Build Docker image
      - name: Build Docker image
        run: |
          docker build -t my-app:${{ github.sha }} .
      
      # Step 3: Push to registry
      - name: Push to ECR
        run: |
          aws ecr get-login-password | docker login --username AWS --password-stdin $ECR_REGISTRY
          docker push my-app:${{ github.sha }}
      
      # Step 4: Deploy with Terraform
      - name: Deploy with Terraform
        run: |
          cd infra
          terraform init
          terraform apply -auto-approve \
            -var="image_tag=${{ github.sha }}"
      
      # Step 5: Verify deployment
      - name: Smoke test
        run: |
          sleep 30  # Wait for deployment
          curl -f https://my-app.example.com/healthz || exit 1
```

## 7. Key Concepts Summary

| Concept | Description | Why It Matters for CD |
|---------|-------------|----------------------|
| **Artifact** | Built, tested, deployable package (e.g., Docker image) | Consistent deployment unit |
| **Registry** | Storage for artifacts (e.g., Docker Hub, ECR) | Centralized, versioned storage |
| **Infrastructure as Code** | Defining infrastructure in code (Terraform) | Reproducible, versioned infrastructure |
| **Orchestration** | Managing containers at scale (Kubernetes) | Automated deployment and scaling |
| **Rolling Update** | Gradually replacing old version with new | Zero-downtime deployments |
| **Rollback** | Reverting to previous version | Quick recovery from issues |
| **Smoke Test** | Quick health check after deployment | Verify deployment succeeded |

## 8. Common CD Patterns

### Pattern 1: Blue/Green Deployment
- Maintain two identical production environments
- Deploy new version to "green" environment
- Switch traffic from "blue" to "green" when ready
- Keep "blue" as backup for quick rollback

### Pattern 2: Canary Deployment
- Deploy new version to small subset of users (e.g., 10%)
- Monitor metrics and user feedback
- Gradually increase to 50%, then 100% if all looks good
- Rollback if issues detected

### Pattern 3: Rolling Update (Kubernetes default)
- Gradually replace old pods with new ones
- Kubernetes manages the transition
- Maintains service availability during update

## 9. Classroom Discussion Questions

1. **When would you choose Continuous Deployment over Continuous Delivery?**
   - Consider: Team maturity, application criticality, test coverage

2. **What happens if a deployment fails halfway through?**
   - Discuss: Rollback strategies, monitoring, alerting

3. **How do you ensure deployments are safe?**
   - Consider: Testing, staging environments, feature flags

4. **What's the difference between deploying code and deploying infrastructure?**
   - Discuss: Application code vs. infrastructure code, when each changes

## 10. Next Steps

Now that you understand CD fundamentals, you're ready to dive deeper into:
- **Module: Docker for CD** - Learn to containerize applications
- **Module: Kubernetes Basics for CD** - Learn to deploy and manage containers
- **Module: Terraform for Kubernetes CD** - Learn to automate infrastructure
- **Module: Complete CD Pipeline** - Put it all together

## 11. Instructor Notes

- Use visual diagrams to illustrate pipeline flow
- Emphasize the "why" behind each tool choice
- Relate concepts to real-world scenarios students can relate to
- Encourage questions about their current deployment processes
- Highlight that CD is a journey, not a destination - start simple and improve over time


