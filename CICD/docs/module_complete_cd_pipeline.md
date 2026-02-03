<!-- Module: Complete CD Pipeline -->
# Module: Complete Continuous Deployment Pipeline

## 1. Teaching Objectives

By the end of this module, students will be able to:
- Understand how Docker, Kubernetes, and Terraform work together in a CD pipeline
- Design an end-to-end CD pipeline architecture
- Implement a complete CD pipeline using GitHub Actions
- Deploy applications automatically from code commit to production
- Handle infrastructure provisioning and application deployment
- Implement verification and rollback strategies
- Troubleshoot common CD pipeline issues

## 2. End-to-End CD Pipeline Architecture

### 2.1 Pipeline Overview

A complete CD pipeline integrates all the tools we've learned:

```
Developer commits code
    ↓
GitHub/GitLab triggers CI/CD
    ↓
CI Stage:
  - Run tests
  - Build Docker image
  - Scan for vulnerabilities
  - Push image to ECR
    ↓
CD Stage:
  - Provision infrastructure (Terraform - EKS cluster)
  - Deploy application (Terraform - Kubernetes resources)
  - Run smoke tests
  - Monitor deployment
    ↓
Production running
```

### 2.2 Pipeline Components

**Source Control:**
- Git repository (GitHub, GitLab, Bitbucket)
- Triggers pipeline on push/merge

**CI/CD Platform:**
- GitHub Actions, GitLab CI, Jenkins, etc.
- Orchestrates the pipeline

**Container Registry:**
- Amazon ECR (or Docker Hub, GCR)
- Stores Docker images

**Infrastructure:**
- Terraform for provisioning
- AWS EKS cluster
- VPC, networking, security

**Application:**
- Kubernetes Deployment
- Running containers from ECR images

**Monitoring:**
- Health checks
- Logs and metrics
- Alerting

## 3. Complete Pipeline Implementation

### 3.1 Pipeline Structure

Our pipeline has two main stages:

1. **CI Stage**: Build and test
2. **CD Stage**: Deploy infrastructure and application

### 3.2 CI Stage (Continuous Integration)

```yaml
# .github/workflows/ci.yml
name: Continuous Integration

on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main]

jobs:
  test:
    runs-on: ubuntu-latest
    
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Set up Python
        uses: actions/setup-python@v4
        with:
          python-version: '3.12'

      - name: Install dependencies
        run: |
          python -m pip install --upgrade pip
          pip install -r requirements.txt
          pip install -r requirements-dev.txt

      - name: Run tests
        run: |
          pytest tests/ -v --cov=app --cov-report=xml

      - name: Upload coverage
        uses: codecov/codecov-action@v3
        with:
          file: ./coverage.xml

  build:
    runs-on: ubuntu-latest
    needs: test
    
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

      - name: Build Docker image
        env:
          ECR_REGISTRY: ${{ steps.login-ecr.outputs.registry }}
          ECR_REPOSITORY: sample-python-app
          IMAGE_TAG: ${{ github.sha }}
        run: |
          docker build -t $ECR_REGISTRY/$ECR_REPOSITORY:$IMAGE_TAG .
          docker tag $ECR_REGISTRY/$ECR_REPOSITORY:$IMAGE_TAG $ECR_REGISTRY/$ECR_REPOSITORY:latest

      - name: Scan image for vulnerabilities
        run: |
          docker scout cves $ECR_REGISTRY/$ECR_REPOSITORY:$IMAGE_TAG || true

      - name: Push image to ECR
        env:
          ECR_REGISTRY: ${{ steps.login-ecr.outputs.registry }}
          ECR_REPOSITORY: sample-python-app
          IMAGE_TAG: ${{ github.sha }}
        run: |
          docker push $ECR_REGISTRY/$ECR_REPOSITORY:$IMAGE_TAG
          docker push $ECR_REGISTRY/$ECR_REPOSITORY:latest
```

### 3.3 CD Stage (Continuous Deployment)

```yaml
# .github/workflows/cd.yml
name: Continuous Deployment

on:
  workflow_run:
    workflows: ["Continuous Integration"]
    types:
      - completed
    branches: [main]

jobs:
  deploy:
    if: ${{ github.event.workflow_run.conclusion == 'success' }}
    runs-on: ubuntu-latest
    environment: production  # Requires approval if configured
    
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Configure AWS credentials
        uses: aws-actions/configure-aws-credentials@v4
        with:
          aws-access-key-id: ${{ secrets.AWS_ACCESS_KEY_ID }}
          aws-secret-access-key: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
          aws-region: us-east-1

      - name: Setup Terraform
        uses: hashicorp/setup-terraform@v3
        with:
          terraform_version: 1.6.0

      # Step 1: Ensure EKS cluster exists
      - name: Terraform Init (EKS)
        run: |
          cd infra/eks
          terraform init -input=false

      - name: Terraform Plan (EKS)
        run: |
          cd infra/eks
          terraform plan -out=tfplan-eks \
            -var="cluster_name=${{ vars.CLUSTER_NAME }}" \
            -var="aws_region=us-east-1"

      - name: Terraform Apply (EKS)
        run: |
          cd infra/eks
          terraform apply -auto-approve tfplan-eks

      # Step 2: Get EKS cluster info
      - name: Get EKS cluster endpoint
        id: get-cluster
        run: |
          cd infra/eks
          CLUSTER_NAME=$(terraform output -raw cluster_name)
          echo "cluster_name=$CLUSTER_NAME" >> $GITHUB_OUTPUT

      # Step 3: Update kubeconfig
      - name: Update kubeconfig
        run: |
          aws eks update-kubeconfig \
            --name ${{ steps.get-cluster.outputs.cluster_name }} \
            --region us-east-1

      # Step 4: Deploy application to Kubernetes
      - name: Terraform Init (K8s)
        run: |
          cd infra/k8s
          terraform init -input=false

      - name: Terraform Plan (K8s)
        run: |
          cd infra/k8s
          terraform plan -out=tfplan-k8s \
            -var="cluster_name=${{ steps.get-cluster.outputs.cluster_name }}" \
            -var="ecr_repository_url=${{ secrets.ECR_REGISTRY }}/sample-python-app" \
            -var="image_tag=${{ github.event.workflow_run.head_sha }}" \
            -var="environment=production"

      - name: Terraform Apply (K8s)
        run: |
          cd infra/k8s
          terraform apply -auto-approve tfplan-k8s

      # Step 5: Wait for deployment
      - name: Wait for deployment
        run: |
          kubectl rollout status deployment/sample-python-app -n default --timeout=5m

      # Step 6: Get service URL
      - name: Get service URL
        id: service-url
        run: |
          # Wait for LoadBalancer to be ready
          sleep 30
          SERVICE_URL=$(kubectl get service sample-python-app -o jsonpath='{.status.loadBalancer.ingress[0].hostname}')
          if [ -z "$SERVICE_URL" ]; then
            SERVICE_URL=$(kubectl get service sample-python-app -o jsonpath='{.status.loadBalancer.ingress[0].ip}')
          fi
          echo "url=http://$SERVICE_URL" >> $GITHUB_OUTPUT

      # Step 7: Smoke tests
      - name: Run smoke tests
        run: |
          SERVICE_URL=${{ steps.service-url.outputs.url }}
          max_attempts=10
          attempt=0
          
          while [ $attempt -lt $max_attempts ]; do
            if curl -f "$SERVICE_URL/healthz"; then
              echo "Smoke test passed!"
              exit 0
            fi
            echo "Attempt $((attempt+1)) failed, retrying..."
            sleep 10
            attempt=$((attempt+1))
          done
          
          echo "Smoke tests failed after $max_attempts attempts"
          exit 1

      # Step 8: Verify deployment
      - name: Verify deployment
        run: |
          kubectl get pods -l app=sample-python-app
          kubectl get service sample-python-app
          kubectl logs -l app=sample-python-app --tail=50
```

## 4. Pipeline Flow Explained

### 4.1 Trigger Events

**On Push to Main:**
- CI runs automatically
- If CI succeeds, CD runs automatically
- For Continuous Deployment (no approval needed)

**On Pull Request:**
- Only CI runs (no deployment)
- Validates code before merge

**Manual Trigger:**
- Can manually trigger CD for rollbacks or re-deployments

### 4.2 Stage Breakdown

**CI Stage:**
1. **Test**: Run unit and integration tests
2. **Build**: Create Docker image
3. **Scan**: Security vulnerability scanning
4. **Push**: Store image in ECR with commit SHA tag

**CD Stage:**
1. **Infrastructure**: Ensure EKS cluster exists (Terraform)
2. **Configure**: Set up kubectl access
3. **Deploy**: Deploy application to Kubernetes (Terraform)
4. **Verify**: Wait for pods to be ready
5. **Test**: Run smoke tests
6. **Monitor**: Check logs and metrics

### 4.3 Image Tagging Strategy

```yaml
# Tag with commit SHA for traceability
IMAGE_TAG: ${{ github.sha }}

# Also tag as 'latest' for convenience
docker tag $IMAGE:$SHA $IMAGE:latest
```

**Benefits:**
- Every deployment is traceable to a commit
- Easy rollback (use previous SHA)
- No ambiguity about which version is deployed

## 5. Environment Management

### 5.1 Multiple Environments

Deploy to different environments:

```yaml
# Deploy to staging on develop branch
deploy-staging:
  if: github.ref == 'refs/heads/develop'
  environment: staging
  steps:
    - name: Deploy to staging
      run: |
        terraform apply -var="environment=staging" ...

# Deploy to production on main branch
deploy-production:
  if: github.ref == 'refs/heads/main'
  environment: production
  steps:
    - name: Deploy to production
      run: |
        terraform apply -var="environment=production" ...
```

### 5.2 Environment-Specific Configuration

**Using Terraform Variables:**
```hcl
# Different node sizes per environment
variable "node_desired_size" {
  default = {
    staging    = 1
    production = 3
  }
}
```

**Using Kubernetes Namespaces:**
```hcl
# Separate namespace per environment
resource "kubernetes_namespace" "app" {
  metadata {
    name = var.environment  # staging, production
  }
}
```

## 6. Verification and Monitoring

### 6.1 Smoke Tests

Quick health checks after deployment:

```python
# scripts/smoke_test.py
import requests
import sys

def test_health_endpoint(url):
    try:
        response = requests.get(f"{url}/healthz", timeout=5)
        response.raise_for_status()
        data = response.json()
        assert data["status"] == "ok"
        print(f"✓ Health check passed: {data}")
        return True
    except Exception as e:
        print(f"✗ Health check failed: {e}")
        return False

if __name__ == "__main__":
    url = sys.argv[1] if len(sys.argv) > 1 else "http://localhost:8080"
    success = test_health_endpoint(url)
    sys.exit(0 if success else 1)
```

### 6.2 Deployment Verification

```bash
# Check pod status
kubectl get pods -l app=sample-python-app

# Check deployment status
kubectl rollout status deployment/sample-python-app

# View logs
kubectl logs -l app=sample-python-app --tail=100

# Check service
kubectl get service sample-python-app

# Test endpoints
curl http://<service-url>/healthz
curl -X POST http://<service-url>/greet \
  -H "Content-Type: application/json" \
  -d '{"name": "Student"}'
```

### 6.3 Monitoring Integration

**CloudWatch Logs:**
```yaml
# Send logs to CloudWatch
- name: Setup CloudWatch logging
  run: |
    kubectl create configmap aws-logging \
      --from-literal=cluster-name=${{ steps.get-cluster.outputs.cluster_name }}
```

**Metrics:**
- Use Prometheus for Kubernetes metrics
- CloudWatch Container Insights for AWS metrics
- Application metrics via application code

## 7. Rollback Strategies

### 7.1 Automatic Rollback

Kubernetes can automatically rollback failed deployments:

```yaml
# In deployment spec
spec:
  progressDeadlineSeconds: 600  # 10 minutes
  revisionHistoryLimit: 10      # Keep 10 old revisions
```

If new pods don't become ready, Kubernetes can rollback automatically.

### 7.2 Manual Rollback

**Using Terraform:**
```bash
# Rollback to previous image tag
cd infra/k8s
terraform apply \
  -var="image_tag=previous-commit-sha" \
  -auto-approve
```

**Using kubectl:**
```bash
# Rollback deployment
kubectl rollout undo deployment/sample-python-app

# Rollback to specific revision
kubectl rollout undo deployment/sample-python-app --to-revision=2
```

### 7.3 Rollback Pipeline

Create a workflow for rollbacks:

```yaml
# .github/workflows/rollback.yml
name: Rollback

on:
  workflow_dispatch:
    inputs:
      image_tag:
        description: 'Image tag to rollback to'
        required: true

jobs:
  rollback:
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

      - name: Update kubeconfig
        run: |
          aws eks update-kubeconfig --name my-cluster --region us-east-1

      - name: Rollback deployment
        run: |
          cd infra/k8s
          terraform apply \
            -var="image_tag=${{ github.event.inputs.image_tag }}" \
            -auto-approve
```

## 8. Security Best Practices

### 8.1 Secrets Management

**GitHub Secrets:**
- Store AWS credentials as secrets
- Never commit secrets to code
- Use least privilege IAM roles

**Kubernetes Secrets:**
```hcl
# Create secrets via Terraform
resource "kubernetes_secret" "app" {
  metadata {
    name = "app-secrets"
  }
  data = {
    api_key = base64encode(var.api_key)
  }
}
```

### 8.2 IAM Roles

**For GitHub Actions:**
- Use IAM roles with minimal permissions
- Separate roles for different environments
- Use OIDC for authentication (better than access keys)

**For EKS:**
- Service accounts with IAM roles (IRSA)
- Node groups with appropriate permissions
- Cluster with least privilege access

### 8.3 Image Security

```yaml
# Scan images for vulnerabilities
- name: Scan image
  run: |
    docker scout cves $IMAGE:$TAG
    # Fail pipeline on high/critical vulnerabilities
```

## 9. Cost Optimization

### 9.1 Infrastructure Costs

**EKS:**
- Control plane: ~$73/month
- Worker nodes: Pay for EC2 instances
- NAT Gateways: ~$32/month each (use one for cost savings)

**Optimization:**
- Use smaller instance types for staging
- Auto-scale node groups
- Use Fargate for variable workloads

### 9.2 Pipeline Costs

**GitHub Actions:**
- Free for public repos
- 2000 minutes/month for private repos
- Use self-hosted runners for cost savings

## 10. Troubleshooting Common Issues

### Issue 1: Pipeline Fails at Terraform Apply

```bash
# Check Terraform state
cd infra/eks
terraform show

# Check for state lock
terraform force-unlock <lock-id>

# Verify AWS credentials
aws sts get-caller-identity
```

### Issue 2: Image Pull Errors

```bash
# Verify ECR authentication
aws ecr get-login-password --region us-east-1 | \
  docker login --username AWS --password-stdin <registry>

# Check image exists
aws ecr describe-images --repository-name sample-python-app
```

### Issue 3: Pods Not Starting

```bash
# Check pod events
kubectl describe pod <pod-name>

# Check logs
kubectl logs <pod-name>

# Check node resources
kubectl top nodes
```

### Issue 4: Service Not Accessible

```bash
# Check service endpoints
kubectl get endpoints sample-python-app

# Check service configuration
kubectl get service sample-python-app -o yaml

# Test from within cluster
kubectl run -it --rm debug --image=busybox --restart=Never -- \
  wget -O- http://sample-python-app/healthz
```

## 11. Advanced Patterns

### 11.1 Blue/Green Deployment

Deploy new version alongside old, then switch:

```hcl
# Deploy "green" version
resource "kubernetes_deployment" "app_green" {
  metadata {
    name = "sample-python-app-green"
  }
  # ... new version configuration
}

# Switch service to green
resource "kubernetes_service" "app" {
  selector = {
    app  = "sample-python-app"
    version = "green"  # Switch to green
  }
}
```

### 11.2 Canary Deployment

Gradually roll out to subset of users:

```hcl
# Main deployment (90% traffic)
resource "kubernetes_deployment" "app_main" {
  replicas = 9
  # ... current version
}

# Canary deployment (10% traffic)
resource "kubernetes_deployment" "app_canary" {
  replicas = 1
  # ... new version
}
```

### 11.3 Feature Flags

Use ConfigMaps for feature flags:

```hcl
resource "kubernetes_config_map" "features" {
  data = {
    new_feature_enabled = "true"
  }
}
```

## 12. Key Takeaways

- ✅ CD pipeline integrates Docker, Kubernetes, and Terraform
- ✅ CI builds and tests, CD deploys to production
- ✅ Infrastructure and application are deployed separately
- ✅ Verification and monitoring are critical
- ✅ Rollback strategies must be planned
- ✅ Security best practices are essential
- ✅ Cost optimization matters for production

## 13. Next Steps

Now that you understand the complete pipeline:
- **Lab: Practical Exercise** - Hands-on implementation
- Experiment with different deployment strategies
- Set up monitoring and alerting
- Practice rollback procedures

## 14. Instructor Notes

- Walk through the pipeline step-by-step
- Show real-time execution of a deployment
- Demonstrate rollback procedures
- Discuss trade-offs of different strategies
- Emphasize the importance of testing in staging first
- Show cost implications of infrastructure choices
- Practice troubleshooting common issues


