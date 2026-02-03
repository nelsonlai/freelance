<!-- Lab: CD Practical Exercise -->
# Lab: Continuous Deployment Practical Exercise

## Lab Overview

In this hands-on lab, you will deploy the sample Python application to Amazon EKS using Docker, Kubernetes, and Terraform. You'll build a complete CD pipeline that automatically deploys your application from code commit to production.

**Estimated Time:** 2-3 hours

**Prerequisites:**
- AWS account with appropriate permissions
- AWS CLI installed and configured
- Terraform installed (v1.6+)
- Docker installed
- kubectl installed
- Git installed

## Lab Objectives

By the end of this lab, you will have:
1. Built a Docker image for the Python application
2. Pushed the image to Amazon ECR
3. Provisioned an EKS cluster using Terraform
4. Deployed the application to Kubernetes using Terraform
5. Verified the deployment is working
6. Understood the complete CD workflow

## Part 1: Setup and Preparation

### Step 1.1: Clone the Repository

```bash
# Clone the repository
git clone <repository-url>
cd CICD/sample_python_app

# Verify you're in the right directory
ls -la
# Should see: app/, Dockerfile, requirements.txt, etc.
```

### Step 1.2: Configure AWS Credentials

```bash
# Configure AWS CLI (if not already done)
aws configure

# Enter your:
# - AWS Access Key ID
# - AWS Secret Access Key
# - Default region (e.g., us-east-1)
# - Default output format (json)

# Verify configuration
aws sts get-caller-identity
# Should show your AWS account ID and user ARN
```

### Step 1.3: Set Up Environment Variables

```bash
# Create a file for environment variables
cat > .env <<EOF
AWS_REGION=us-east-1
CLUSTER_NAME=my-eks-cluster
ECR_REPOSITORY_NAME=sample-python-app
APP_NAME=sample-python-app
NAMESPACE=default
EOF

# Source the variables
source .env
```

## Part 2: Docker Image Build and Push

### Step 2.1: Create ECR Repository

```bash
# Create ECR repository
aws ecr create-repository \
    --repository-name $ECR_REPOSITORY_NAME \
    --region $AWS_REGION

# Get repository URI
ECR_REPOSITORY_URI=$(aws ecr describe-repositories \
    --repository-names $ECR_REPOSITORY_NAME \
    --region $AWS_REGION \
    --query 'repositories[0].repositoryUri' \
    --output text)

echo "ECR Repository URI: $ECR_REPOSITORY_URI"
```

### Step 2.2: Authenticate Docker to ECR

```bash
# Get ECR login token and authenticate
aws ecr get-login-password --region $AWS_REGION | \
    docker login --username AWS --password-stdin $ECR_REPOSITORY_URI
```

### Step 2.3: Build Docker Image

```bash
# Build the image
docker build -t $ECR_REPOSITORY_NAME:latest .

# Tag with ECR URI
docker tag $ECR_REPOSITORY_NAME:latest $ECR_REPOSITORY_URI:latest

# Tag with a version (using git commit SHA if available)
GIT_SHA=$(git rev-parse --short HEAD 2>/dev/null || echo "v1.0.0")
docker tag $ECR_REPOSITORY_NAME:latest $ECR_REPOSITORY_URI:$GIT_SHA

# Verify images
docker images | grep $ECR_REPOSITORY_NAME
```

### Step 2.4: Push Image to ECR

```bash
# Push both tags
docker push $ECR_REPOSITORY_URI:latest
docker push $ECR_REPOSITORY_URI:$GIT_SHA

# Verify in ECR
aws ecr list-images \
    --repository-name $ECR_REPOSITORY_NAME \
    --region $AWS_REGION
```

**Checkpoint:** You should now have a Docker image in ECR. Verify by checking the ECR console or using the AWS CLI command above.

## Part 3: Provision EKS Cluster with Terraform

### Step 3.1: Navigate to EKS Terraform Directory

```bash
# Navigate to EKS infrastructure directory
cd infra/eks

# List files (should see main.tf, variables.tf, etc.)
ls -la
```

### Step 3.2: Review Terraform Configuration

```bash
# Review main configuration files
cat main.tf
cat variables.tf
cat outputs.tf

# Understand what will be created:
# - VPC with public and private subnets
# - Internet Gateway and NAT Gateways
# - Security Groups
# - IAM Roles
# - EKS Cluster
# - Node Group
```

### Step 3.3: Create terraform.tfvars

```bash
# Create variables file
cat > terraform.tfvars <<EOF
aws_region          = "$AWS_REGION"
cluster_name       = "$CLUSTER_NAME"
kubernetes_version = "1.28"
node_desired_size  = 2
node_max_size      = 4
node_min_size      = 1
node_instance_type = "t3.medium"
EOF

# Review the file
cat terraform.tfvars
```

### Step 3.4: Initialize Terraform

```bash
# Initialize Terraform (downloads providers)
terraform init

# Expected output:
# - Terraform has been successfully initialized!
# - Providers downloaded
```

### Step 3.5: Plan Infrastructure

```bash
# Review what will be created
terraform plan

# This will show:
# - Resources to be created
# - Estimated costs (if configured)
# - Any errors or warnings

# Review the plan carefully before proceeding
```

**Note:** Creating an EKS cluster takes 10-15 minutes and incurs costs (~$73/month for control plane + EC2 instances).

### Step 3.6: Apply Terraform Configuration

```bash
# Apply the configuration (creates EKS cluster)
terraform apply

# Type 'yes' when prompted
# This will take 10-15 minutes

# Monitor progress - you'll see resources being created:
# - VPC
# - Subnets
# - Internet Gateway
# - NAT Gateways
# - Security Groups
# - IAM Roles
# - EKS Cluster (this takes the longest)
# - Node Group
```

### Step 3.7: Get Cluster Information

```bash
# Get cluster name
terraform output cluster_name

# Get cluster endpoint
terraform output cluster_endpoint

# Get all outputs
terraform output

# Save cluster name for later
export CLUSTER_NAME=$(terraform output -raw cluster_name)
```

### Step 3.8: Configure kubectl

```bash
# Update kubeconfig to connect to EKS cluster
aws eks update-kubeconfig \
    --name $CLUSTER_NAME \
    --region $AWS_REGION

# Verify connection
kubectl cluster-info

# Check nodes
kubectl get nodes

# You should see 2 nodes (based on node_desired_size)
```

**Checkpoint:** You should now have a working EKS cluster. Verify by running `kubectl get nodes` and seeing 2 nodes in Ready state.

## Part 4: Deploy Application to Kubernetes

### Step 4.1: Navigate to Kubernetes Terraform Directory

```bash
# Navigate to Kubernetes resources directory
cd ../k8s

# List files
ls -la
```

### Step 4.2: Review Kubernetes Terraform Configuration

```bash
# Review the configuration
cat main.tf
cat variables.tf

# Understand what will be created:
# - Kubernetes namespace
# - ConfigMap
# - Deployment
# - Service (LoadBalancer)
```

### Step 4.3: Create terraform.tfvars for Kubernetes

```bash
# Get ECR repository URI (if not already set)
ECR_REPOSITORY_URI=$(aws ecr describe-repositories \
    --repository-names $ECR_REPOSITORY_NAME \
    --region $AWS_REGION \
    --query 'repositories[0].repositoryUri' \
    --output text)

# Get image tag
IMAGE_TAG=$(git rev-parse --short HEAD 2>/dev/null || echo "latest")

# Create variables file
cat > terraform.tfvars <<EOF
cluster_name        = "$CLUSTER_NAME"
namespace           = "default"
app_name            = "$APP_NAME"
ecr_repository_url  = "$ECR_REPOSITORY_URI"
image_tag           = "$IMAGE_TAG"
replicas            = 2
environment         = "production"
EOF

# Review
cat terraform.tfvars
```

### Step 4.4: Initialize Terraform for Kubernetes

```bash
# Initialize Terraform
terraform init

# This downloads the Kubernetes provider
```

### Step 4.5: Plan Kubernetes Deployment

```bash
# Review what will be created
terraform plan

# Should show:
# - kubernetes_namespace
# - kubernetes_config_map
# - kubernetes_deployment
# - kubernetes_service
```

### Step 4.6: Deploy Application

```bash
# Deploy the application
terraform apply

# Type 'yes' when prompted

# This creates:
# - Namespace (if not default)
# - ConfigMap with configuration
# - Deployment with 2 replicas
# - Service (LoadBalancer) - this takes a few minutes
```

### Step 4.7: Verify Deployment

```bash
# Check deployment status
kubectl get deployment $APP_NAME

# Check pods (should see 2 pods running)
kubectl get pods -l app=$APP_NAME

# Watch pods until they're ready
kubectl get pods -l app=$APP_NAME -w

# Press Ctrl+C when pods are Running

# Check service
kubectl get service $APP_NAME

# Get service URL (LoadBalancer)
kubectl get service $APP_NAME -o jsonpath='{.status.loadBalancer.ingress[0].hostname}'

# If hostname is empty, try IP:
kubectl get service $APP_NAME -o jsonpath='{.status.loadBalancer.ingress[0].ip}'

# Save the URL
SERVICE_URL=$(kubectl get service $APP_NAME -o jsonpath='{.status.loadBalancer.ingress[0].hostname}')
if [ -z "$SERVICE_URL" ]; then
  SERVICE_URL=$(kubectl get service $APP_NAME -o jsonpath='{.status.loadBalancer.ingress[0].ip}')
fi
echo "Service URL: http://$SERVICE_URL"
```

**Note:** It may take 2-5 minutes for the LoadBalancer to be provisioned and get an external URL.

## Part 5: Test the Application

### Step 5.1: Test Health Endpoint

```bash
# Wait for LoadBalancer to be ready
echo "Waiting for LoadBalancer..."
sleep 60

# Test health endpoint
curl http://$SERVICE_URL/healthz

# Expected output:
# {"status":"ok","service":"Sample Python CI/CD API","version":"0.1.0","commit":"..."}
```

### Step 5.2: Test Greeting Endpoint

```bash
# Test greeting endpoint
curl -X POST http://$SERVICE_URL/greet \
  -H "Content-Type: application/json" \
  -d '{"name": "Student", "language": "en"}'

# Expected output:
# {"message":"Hello, Student! Welcome to the CI/CD workshop.","served_at":"..."}
```

### Step 5.3: View Application Logs

```bash
# View logs from all pods
kubectl logs -l app=$APP_NAME --tail=50

# View logs from specific pod
kubectl logs <pod-name> --tail=50

# Follow logs in real-time
kubectl logs -l app=$APP_NAME -f
```

### Step 5.4: Check Pod Status

```bash
# Get detailed pod information
kubectl describe pods -l app=$APP_NAME

# Check resource usage
kubectl top pods -l app=$APP_NAME
```

## Part 6: Update and Redeploy

### Step 6.1: Update Application

```bash
# Make a small change to the application
# Edit app/api.py and add a comment or change a message

# Rebuild and push new image
cd ../..  # Back to sample_python_app root

# Build new image
docker build -t $ECR_REPOSITORY_NAME:latest .

# Tag with new version
NEW_TAG=$(git rev-parse --short HEAD 2>/dev/null || echo "v1.0.1")
docker tag $ECR_REPOSITORY_NAME:latest $ECR_REPOSITORY_URI:$NEW_TAG
docker tag $ECR_REPOSITORY_NAME:latest $ECR_REPOSITORY_URI:latest

# Push new image
docker push $ECR_REPOSITORY_URI:$NEW_TAG
docker push $ECR_REPOSITORY_URI:latest
```

### Step 6.2: Update Deployment

```bash
# Navigate back to k8s directory
cd infra/k8s

# Update terraform.tfvars with new image tag
# Edit terraform.tfvars and change image_tag to $NEW_TAG

# Or use terraform apply with variable
terraform apply -var="image_tag=$NEW_TAG"

# Watch the rolling update
kubectl get pods -l app=$APP_NAME -w

# You should see:
# - Old pods terminating
# - New pods starting
# - Rolling update happening
```

### Step 6.3: Verify Update

```bash
# Check deployment status
kubectl rollout status deployment/$APP_NAME

# Verify new version is running
curl http://$SERVICE_URL/healthz

# Check which image is running
kubectl get deployment $APP_NAME -o jsonpath='{.spec.template.spec.containers[0].image}'
```

## Part 7: Cleanup (Important!)

### Step 7.1: Destroy Kubernetes Resources

```bash
# Navigate to k8s directory
cd infra/k8s

# Destroy Kubernetes resources
terraform destroy

# Type 'yes' when prompted
# This removes:
# - Deployment
# - Service
# - ConfigMap
# - Namespace (if created)
```

### Step 7.2: Destroy EKS Cluster

```bash
# Navigate to eks directory
cd ../eks

# Destroy EKS cluster and all infrastructure
terraform destroy

# Type 'yes' when prompted
# WARNING: This will delete:
# - EKS Cluster
# - Node Group
# - VPC and all networking
# - Security Groups
# - IAM Roles (if not used elsewhere)

# This takes 10-15 minutes
```

### Step 7.3: Clean Up ECR Images (Optional)

```bash
# List images
aws ecr list-images \
    --repository-name $ECR_REPOSITORY_NAME \
    --region $AWS_REGION

# Delete images (optional)
# aws ecr batch-delete-image \
#     --repository-name $ECR_REPOSITORY_NAME \
#     --region $AWS_REGION \
#     --image-ids imageTag=latest

# Delete repository (optional)
# aws ecr delete-repository \
#     --repository-name $ECR_REPOSITORY_NAME \
#     --region $AWS_REGION \
#     --force
```

## Troubleshooting Guide

### Issue: Terraform Apply Fails

**Error: "Error creating EKS Cluster"**
- Check AWS credentials: `aws sts get-caller-identity`
- Verify IAM permissions
- Check if cluster name already exists

**Error: "Error creating Node Group"**
- Check subnet IDs are correct
- Verify IAM role permissions
- Check instance type availability in region

### Issue: Pods Not Starting

**Error: "ImagePullBackOff"**
- Verify ECR authentication: `aws ecr get-login-password`
- Check image exists in ECR
- Verify image tag is correct

**Error: "CrashLoopBackOff"**
- Check pod logs: `kubectl logs <pod-name>`
- Verify application starts correctly
- Check resource limits

### Issue: Service Not Accessible

**LoadBalancer Pending**
- Wait 2-5 minutes for AWS to provision
- Check security group allows traffic
- Verify subnets have proper tags

**Cannot Connect to Service**
- Check service endpoints: `kubectl get endpoints`
- Verify pods are running: `kubectl get pods`
- Test from within cluster

## Lab Completion Checklist

- [ ] Docker image built and pushed to ECR
- [ ] EKS cluster provisioned with Terraform
- [ ] kubectl configured to connect to cluster
- [ ] Application deployed to Kubernetes
- [ ] Service accessible via LoadBalancer
- [ ] Health endpoint responds correctly
- [ ] Greeting endpoint works
- [ ] Application updated and redeployed
- [ ] Rolling update observed
- [ ] Resources cleaned up (terraform destroy)

## Next Steps

After completing this lab:
1. Review the Terraform configurations
2. Experiment with different deployment strategies
3. Try deploying to multiple environments
4. Set up monitoring and logging
5. Implement the CD pipeline in GitHub Actions
6. Practice rollback procedures

## Additional Exercises

### Exercise 1: Scale the Application
```bash
# Scale deployment to 5 replicas
kubectl scale deployment $APP_NAME --replicas=5

# Watch pods scale
kubectl get pods -l app=$APP_NAME -w
```

### Exercise 2: Update Resources
```bash
# Edit deployment to change resources
kubectl edit deployment $APP_NAME

# Change CPU/memory requests and limits
# Save and watch pods restart
```

### Exercise 3: View Cluster Resources
```bash
# List all resources in cluster
kubectl get all

# View cluster information
kubectl cluster-info dump

# Check node resources
kubectl top nodes
```

## Instructor Notes

- Monitor students' progress through each checkpoint
- Help troubleshoot common issues
- Emphasize the importance of cleanup to avoid costs
- Discuss cost implications of running EKS
- Show how to monitor costs in AWS Console
- Encourage experimentation with different configurations


