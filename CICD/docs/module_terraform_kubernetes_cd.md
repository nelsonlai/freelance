<!-- Module: Terraform for Kubernetes CD -->
# Module: Terraform for Kubernetes Continuous Deployment

## 1. Teaching Objectives

By the end of this module, students will be able to:
- Understand Infrastructure as Code (IaC) and why Terraform matters
- Write basic Terraform configuration (HCL syntax)
- Provision an EKS cluster using Terraform
- Deploy Kubernetes resources using Terraform
- Manage Terraform state and understand its importance
- Integrate Terraform into CD pipelines
- Use Terraform variables and outputs effectively
- Understand Terraform modules for reusability

## 2. What is Infrastructure as Code (IaC)?

### 2.1 The Problem IaC Solves

**Traditional Infrastructure Management:**
- Manual clicking through cloud consoles
- Inconsistent configurations
- No version control
- Difficult to reproduce environments
- Hard to track changes
- Error-prone manual processes

**Infrastructure as Code:**
- Define infrastructure in code files
- Version controlled (Git)
- Reproducible and consistent
- Automated provisioning
- Trackable changes
- Reviewable (pull requests)

**Analogy**: 
- **Manual Infrastructure** = Hand-drawing blueprints each time
- **Infrastructure as Code** = CAD software with saved, versioned blueprints

### 2.2 What is Terraform?

**Terraform** = Open-source IaC tool by HashiCorp
- Declarative: Describe what you want, Terraform figures out how
- Multi-cloud: Works with AWS, Azure, GCP, Kubernetes, etc.
- State management: Tracks what infrastructure exists
- Plan before apply: See changes before making them

**Key Features:**
- ✅ **Declarative**: Define desired state, not steps
- ✅ **Idempotent**: Running multiple times produces same result
- ✅ **Stateful**: Remembers what was created
- ✅ **Provider-based**: Plugins for different services

### 2.3 Terraform vs Other Tools

| Tool | Type | Best For |
|------|------|----------|
| **Terraform** | Declarative IaC | Multi-cloud, infrastructure provisioning |
| **Ansible** | Procedural automation | Configuration management, orchestration |
| **CloudFormation** | Declarative (AWS only) | AWS-only projects |
| **Pulumi** | Imperative IaC | Using familiar programming languages |

## 3. Terraform Basics

### 3.1 Installation

**macOS:**
```bash
brew install terraform
```

**Linux:**
```bash
# Download from https://www.terraform.io/downloads
wget https://releases.hashicorp.com/terraform/1.6.0/terraform_1.6.0_linux_amd64.zip
unzip terraform_1.6.0_linux_amd64.zip
sudo mv terraform /usr/local/bin/
```

**Windows:**
- Download from https://www.terraform.io/downloads
- Extract and add to PATH

**Verify:**
```bash
terraform version
# Output: Terraform v1.6.0
```

### 3.2 HCL (HashiCorp Configuration Language)

Terraform uses HCL syntax. It's human-readable and structured:

```hcl
# Comments start with #

# Block type: resource
resource "aws_instance" "web" {
  # Arguments (key = value)
  ami           = "ami-0c55b159cbfafe1f0"
  instance_type = "t2.micro"
  
  # Nested blocks
  tags = {
    Name = "Web Server"
    Environment = "production"
  }
}
```

**Basic Structure:**
- **Blocks**: `resource`, `variable`, `output`, `provider`
- **Arguments**: `key = value` pairs
- **Expressions**: `"${var.name}"` for interpolation

### 3.3 Core Concepts

**Providers:**
- Plugins that interact with APIs (AWS, Kubernetes, etc.)
- Must be declared and configured

**Resources:**
- Infrastructure components (EC2 instance, EKS cluster, etc.)
- Most important block type

**Variables:**
- Input parameters for your configuration
- Make configurations reusable

**Outputs:**
- Values to display or use elsewhere
- Useful for getting resource information

**State:**
- Tracks what Terraform has created
- Stored in `terraform.tfstate` file
- Critical for managing infrastructure

### 3.4 Basic Terraform Workflow

```bash
# 1. Initialize (download providers)
terraform init

# 2. Plan (see what will be created)
terraform plan

# 3. Apply (create infrastructure)
terraform apply

# 4. Destroy (remove infrastructure)
terraform destroy
```

## 4. Terraform AWS Provider Setup

### 4.1 Provider Configuration

```hcl
# terraform.tf
terraform {
  required_version = ">= 1.6"
  
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 5.0"
    }
  }
}

provider "aws" {
  region = var.aws_region
  
  # Optional: Use AWS credentials from environment
  # AWS_ACCESS_KEY_ID and AWS_SECRET_ACCESS_KEY
  # Or use AWS CLI profile: shared_credentials_file = "~/.aws/credentials"
}
```

### 4.2 AWS Authentication

**Option 1: Environment Variables**
```bash
export AWS_ACCESS_KEY_ID=your-access-key
export AWS_SECRET_ACCESS_KEY=your-secret-key
export AWS_DEFAULT_REGION=us-east-1
```

**Option 2: AWS CLI Profile**
```bash
aws configure --profile myprofile
```

**Option 3: IAM Role (for EC2/ECS)**
- Use IAM roles attached to instances

### 4.3 Initialize Terraform

```bash
# Navigate to Terraform directory
cd infra/eks

# Initialize (downloads AWS provider)
terraform init

# Output shows providers downloaded
```

## 5. Provisioning EKS Cluster with Terraform

### 5.1 EKS Cluster Architecture

To create an EKS cluster, we need:
1. **VPC** (Virtual Private Cloud) - Network
2. **Subnets** - Network segments (public/private)
3. **Internet Gateway** - Internet access
4. **NAT Gateway** - Outbound internet for private subnets
5. **Security Groups** - Firewall rules
6. **IAM Roles** - Permissions
7. **EKS Cluster** - Kubernetes control plane
8. **Node Group** - Worker nodes

### 5.2 Complete EKS Terraform Configuration

**Step 1: VPC and Networking**

```hcl
# vpc.tf
# Create VPC
resource "aws_vpc" "main" {
  cidr_block           = "10.0.0.0/16"
  enable_dns_hostnames = true
  enable_dns_support   = true

  tags = {
    Name = "eks-vpc"
  }
}

# Internet Gateway
resource "aws_internet_gateway" "main" {
  vpc_id = aws_vpc.main.id

  tags = {
    Name = "eks-igw"
  }
}

# Public Subnets (for load balancers)
resource "aws_subnet" "public" {
  count = 2

  vpc_id                  = aws_vpc.main.id
  cidr_block              = "10.0.${count.index + 1}.0/24"
  availability_zone       = data.aws_availability_zones.available.names[count.index]
  map_public_ip_on_launch = true

  tags = {
    Name = "eks-public-${count.index + 1}"
    "kubernetes.io/role/elb" = "1"
  }
}

# Private Subnets (for worker nodes)
resource "aws_subnet" "private" {
  count = 2

  vpc_id            = aws_vpc.main.id
  cidr_block        = "10.0.${count.index + 10}.0/24"
  availability_zone = data.aws_availability_zones.available.names[count.index]

  tags = {
    Name = "eks-private-${count.index + 1}"
    "kubernetes.io/role/internal-elb" = "1"
  }
}

# NAT Gateway (for private subnet internet access)
resource "aws_eip" "nat" {
  count = 2

  domain = "vpc"

  tags = {
    Name = "eks-nat-eip-${count.index + 1}"
  }
}

resource "aws_nat_gateway" "main" {
  count = 2

  allocation_id = aws_eip.nat[count.index].id
  subnet_id     = aws_subnet.public[count.index].id

  tags = {
    Name = "eks-nat-${count.index + 1}"
  }
}

# Route Tables
resource "aws_route_table" "public" {
  vpc_id = aws_vpc.main.id

  route {
    cidr_block = "0.0.0.0/0"
    gateway_id = aws_internet_gateway.main.id
  }

  tags = {
    Name = "eks-public-rt"
  }
}

resource "aws_route_table" "private" {
  count = 2

  vpc_id = aws_vpc.main.id

  route {
    cidr_block     = "0.0.0.0/0"
    nat_gateway_id = aws_nat_gateway.main[count.index].id
  }

  tags = {
    Name = "eks-private-rt-${count.index + 1}"
  }
}

# Route Table Associations
resource "aws_route_table_association" "public" {
  count = 2

  subnet_id      = aws_subnet.public[count.index].id
  route_table_id = aws_route_table.public.id
}

resource "aws_route_table_association" "private" {
  count = 2

  subnet_id      = aws_subnet.private[count.index].id
  route_table_id = aws_route_table.private[count.index].id
}

# Data source for availability zones
data "aws_availability_zones" "available" {
  state = "available"
}
```

**Step 2: IAM Roles**

```hcl
# iam.tf
# EKS Cluster Role
resource "aws_iam_role" "cluster" {
  name = "eks-cluster-role"

  assume_role_policy = jsonencode({
    Version = "2012-10-17"
    Statement = [
      {
        Action = "sts:AssumeRole"
        Effect = "Allow"
        Principal = {
          Service = "eks.amazonaws.com"
        }
      }
    ]
  })
}

# Attach EKS Cluster Policy
resource "aws_iam_role_policy_attachment" "cluster_AmazonEKSClusterPolicy" {
  policy_arn = "arn:aws:iam::aws:policy/AmazonEKSClusterPolicy"
  role       = aws_iam_role.cluster.name
}

# EKS Node Group Role
resource "aws_iam_role" "node" {
  name = "eks-node-group-role"

  assume_role_policy = jsonencode({
    Version = "2012-10-17"
    Statement = [
      {
        Action = "sts:AssumeRole"
        Effect = "Allow"
        Principal = {
          Service = "ec2.amazonaws.com"
        }
      }
    ]
  })
}

# Attach Node Group Policies
resource "aws_iam_role_policy_attachment" "node_AmazonEKSWorkerNodePolicy" {
  policy_arn = "arn:aws:iam::aws:policy/AmazonEKSWorkerNodePolicy"
  role       = aws_iam_role.node.name
}

resource "aws_iam_role_policy_attachment" "node_AmazonEKS_CNI_Policy" {
  policy_arn = "arn:aws:iam::aws:policy/AmazonEKS_CNI_Policy"
  role       = aws_iam_role.node.name
}

resource "aws_iam_role_policy_attachment" "node_AmazonEC2ContainerRegistryReadOnly" {
  policy_arn = "arn:aws:iam::aws:policy/AmazonEC2ContainerRegistryReadOnly"
  role       = aws_iam_role.node.name
}
```

**Step 3: Security Groups**

```hcl
# security-groups.tf
# Cluster Security Group
resource "aws_security_group" "cluster" {
  name        = "eks-cluster-sg"
  description = "Security group for EKS cluster"
  vpc_id      = aws_vpc.main.id

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }

  tags = {
    Name = "eks-cluster-sg"
  }
}

# Node Security Group
resource "aws_security_group" "node" {
  name        = "eks-node-sg"
  description = "Security group for EKS nodes"
  vpc_id      = aws_vpc.main.id

  ingress {
    from_port = 0
    to_port   = 65535
    protocol  = "tcp"
    self      = true
  }

  ingress {
    from_port       = 1025
    to_port         = 65535
    protocol        = "tcp"
    security_groups = [aws_security_group.cluster.id]
  }

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }

  tags = {
    Name = "eks-node-sg"
  }
}
```

**Step 4: EKS Cluster**

```hcl
# cluster.tf
resource "aws_eks_cluster" "main" {
  name     = var.cluster_name
  role_arn = aws_iam_role.cluster.arn
  version  = var.kubernetes_version

  vpc_config {
    subnet_ids              = concat(aws_subnet.public[*].id, aws_subnet.private[*].id)
    endpoint_private_access = true
    endpoint_public_access  = true
    security_group_ids      = [aws_security_group.cluster.id]
  }

  # Enable logging
  enabled_cluster_log_types = ["api", "audit", "authenticator", "controllerManager", "scheduler"]

  depends_on = [
    aws_iam_role_policy_attachment.cluster_AmazonEKSClusterPolicy,
  ]

  tags = {
    Name = var.cluster_name
  }
}
```

**Step 5: Node Group**

```hcl
# node-groups.tf
resource "aws_eks_node_group" "main" {
  cluster_name    = aws_eks_cluster.main.name
  node_group_name = "${var.cluster_name}-node-group"
  node_role_arn   = aws_iam_role.node.arn
  subnet_ids      = aws_subnet.private[*].id

  scaling_config {
    desired_size = var.node_desired_size
    max_size     = var.node_max_size
    min_size     = var.node_min_size
  }

  instance_types = [var.node_instance_type]

  # Update configuration
  update_config {
    max_unavailable = 1
  }

  # Remote access (optional)
  # remote_access {
  #   ec2_ssh_key = var.ssh_key_name
  # }

  depends_on = [
    aws_iam_role_policy_attachment.node_AmazonEKSWorkerNodePolicy,
    aws_iam_role_policy_attachment.node_AmazonEKS_CNI_Policy,
    aws_iam_role_policy_attachment.node_AmazonEC2ContainerRegistryReadOnly,
  ]

  tags = {
    Name = "${var.cluster_name}-node-group"
  }
}
```

**Step 6: Variables**

```hcl
# variables.tf
variable "aws_region" {
  description = "AWS region"
  type        = string
  default     = "us-east-1"
}

variable "cluster_name" {
  description = "Name of the EKS cluster"
  type        = string
  default     = "my-eks-cluster"
}

variable "kubernetes_version" {
  description = "Kubernetes version"
  type        = string
  default     = "1.28"
}

variable "node_desired_size" {
  description = "Desired number of nodes"
  type        = number
  default     = 2
}

variable "node_max_size" {
  description = "Maximum number of nodes"
  type        = number
  default     = 4
}

variable "node_min_size" {
  description = "Minimum number of nodes"
  type        = number
  default     = 1
}

variable "node_instance_type" {
  description = "EC2 instance type for nodes"
  type        = string
  default     = "t3.medium"
}
```

**Step 7: Outputs**

```hcl
# outputs.tf
output "cluster_id" {
  description = "EKS cluster ID"
  value       = aws_eks_cluster.main.id
}

output "cluster_arn" {
  description = "EKS cluster ARN"
  value       = aws_eks_cluster.main.arn
}

output "cluster_endpoint" {
  description = "EKS cluster endpoint"
  value       = aws_eks_cluster.main.endpoint
}

output "cluster_security_group_id" {
  description = "Security group ID attached to the cluster"
  value       = aws_security_group.cluster.id
}

output "node_security_group_id" {
  description = "Security group ID attached to the nodes"
  value       = aws_security_group.node.id
}

output "vpc_id" {
  description = "VPC ID"
  value       = aws_vpc.main.id
}

output "cluster_name" {
  description = "EKS cluster name"
  value       = aws_eks_cluster.main.name
}
```

### 5.3 Deploying the EKS Cluster

```bash
# Navigate to EKS directory
cd infra/eks

# Initialize Terraform
terraform init

# Review plan
terraform plan

# Apply (creates cluster - takes 10-15 minutes)
terraform apply

# Get cluster info
terraform output cluster_endpoint
terraform output cluster_name
```

## 6. Deploying Kubernetes Resources with Terraform

### 6.1 Kubernetes Provider Setup

After creating the EKS cluster, configure the Kubernetes provider:

```hcl
# k8s/main.tf
terraform {
  required_version = ">= 1.6"
  
  required_providers {
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.23"
    }
    aws = {
      source  = "hashicorp/aws"
      version = "~> 5.0"
    }
  }
}

# Configure Kubernetes provider
provider "kubernetes" {
  host                   = data.aws_eks_cluster.main.endpoint
  cluster_ca_certificate = base64decode(data.aws_eks_cluster.main.certificate_authority[0].data)
  
  exec {
    api_version = "client.authentication.k8s.io/v1beta1"
    command     = "aws"
    args = [
      "eks",
      "get-token",
      "--cluster-name",
      data.aws_eks_cluster.main.name
    ]
  }
}

# Data source to get cluster info
data "aws_eks_cluster" "main" {
  name = var.cluster_name
}
```

### 6.2 Deploying Application with Terraform

**Namespace:**
```hcl
resource "kubernetes_namespace" "app" {
  metadata {
    name = var.namespace
  }
}
```

**ConfigMap:**
```hcl
resource "kubernetes_config_map" "app" {
  metadata {
    name      = "app-config"
    namespace = kubernetes_namespace.app.metadata[0].name
  }

  data = {
    environment = var.environment
    log_level   = "info"
  }
}
```

**Deployment:**
```hcl
resource "kubernetes_deployment" "app" {
  metadata {
    name      = var.app_name
    namespace = kubernetes_namespace.app.metadata[0].name
    labels = {
      app = var.app_name
    }
  }

  spec {
    replicas = var.replicas

    selector {
      match_labels = {
        app = var.app_name
      }
    }

    template {
      metadata {
        labels = {
          app = var.app_name
        }
      }

      spec {
        container {
          name  = "api"
          image = "${var.ecr_repository_url}:${var.image_tag}"

          port {
            container_port = 8080
            name           = "http"
          }

          env_from {
            config_map_ref {
              name = kubernetes_config_map.app.metadata[0].name
            }
          }

          resources {
            requests = {
              cpu    = "250m"
              memory = "256Mi"
            }
            limits = {
              cpu    = "500m"
              memory = "512Mi"
            }
          }

          liveness_probe {
            http_get {
              path = "/healthz"
              port = 8080
            }
            initial_delay_seconds = 30
            period_seconds        = 10
          }

          readiness_probe {
            http_get {
              path = "/healthz"
              port = 8080
            }
            initial_delay_seconds = 5
            period_seconds        = 5
          }
        }
      }
    }
  }
}
```

**Service:**
```hcl
resource "kubernetes_service" "app" {
  metadata {
    name      = var.app_name
    namespace = kubernetes_namespace.app.metadata[0].name
  }

  spec {
    type = "LoadBalancer"

    selector = {
      app = var.app_name
    }

    port {
      port        = 80
      target_port = 8080
      protocol    = "TCP"
      name        = "http"
    }
  }
}
```

**Variables for Kubernetes Resources:**
```hcl
# k8s/variables.tf
variable "cluster_name" {
  description = "EKS cluster name"
  type        = string
}

variable "namespace" {
  description = "Kubernetes namespace"
  type        = string
  default     = "default"
}

variable "app_name" {
  description = "Application name"
  type        = string
  default     = "sample-python-app"
}

variable "ecr_repository_url" {
  description = "ECR repository URL"
  type        = string
}

variable "image_tag" {
  description = "Docker image tag"
  type        = string
}

variable "replicas" {
  description = "Number of replicas"
  type        = number
  default     = 2
}

variable "environment" {
  description = "Environment name"
  type        = string
  default     = "production"
}
```

## 7. Terraform State Management

### 7.1 Understanding State

**What is State?**
- File (`terraform.tfstate`) that tracks created resources
- Maps Terraform configuration to real infrastructure
- Used to plan updates and destroy resources

**Why State Matters:**
- Without state, Terraform doesn't know what exists
- State enables Terraform to update existing resources
- Critical for team collaboration

### 7.2 Remote State (Best Practice)

Store state in S3 (or similar) for team access:

```hcl
# backend.tf
terraform {
  backend "s3" {
    bucket         = "my-terraform-state-bucket"
    key            = "eks/cluster/terraform.tfstate"
    region         = "us-east-1"
    encrypt        = true
    dynamodb_table = "terraform-state-lock"  # For state locking
  }
}
```

**Benefits:**
- Shared state across team
- State locking (prevent conflicts)
- Versioning (S3 versioning)
- Backup and recovery

### 7.3 State Commands

```bash
# Show current state
terraform show

# List resources in state
terraform state list

# Remove resource from state (doesn't delete it)
terraform state rm aws_instance.web

# Import existing resource into state
terraform import aws_instance.web i-1234567890abcdef0
```

## 8. Terraform Modules

### 8.1 What are Modules?

Modules = Reusable Terraform configurations
- Package related resources together
- Make configurations reusable
- Share with others

### 8.2 Using Modules

**Example: EKS Module**
```hcl
# Use a module
module "eks" {
  source = "terraform-aws-modules/eks/aws"
  version = "~> 19.0"

  cluster_name    = "my-cluster"
  cluster_version = "1.28"

  vpc_id     = module.vpc.vpc_id
  subnet_ids = module.vpc.private_subnets

  node_groups = {
    main = {
      desired_size = 2
      max_size     = 4
      min_size     = 1
      instance_types = ["t3.medium"]
    }
  }
}
```

**Benefits:**
- Pre-built, tested configurations
- Faster development
- Best practices included
- Community maintained

## 9. Integrating Terraform into CD Pipelines

### 9.1 CD Pipeline with Terraform

```yaml
# .github/workflows/cd.yml
name: Deploy with Terraform

on:
  push:
    branches: [main]

jobs:
  deploy-infrastructure:
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

      - name: Setup Terraform
        uses: hashicorp/setup-terraform@v3
        with:
          terraform_version: 1.6.0

      - name: Terraform Init (EKS)
        run: |
          cd infra/eks
          terraform init

      - name: Terraform Plan (EKS)
        run: |
          cd infra/eks
          terraform plan -out=tfplan

      - name: Terraform Apply (EKS)
        run: |
          cd infra/eks
          terraform apply -auto-approve tfplan

      - name: Terraform Init (K8s)
        run: |
          cd infra/k8s
          terraform init

      - name: Terraform Apply (K8s)
        run: |
          cd infra/k8s
          terraform apply -auto-approve \
            -var="cluster_name=my-eks-cluster" \
            -var="image_tag=${{ github.sha }}" \
            -var="ecr_repository_url=${{ secrets.ECR_REGISTRY }}/sample-python-app"
```

### 9.2 Best Practices for CD

1. **Separate Infrastructure and Application**
   - Infrastructure (EKS) changes less frequently
   - Application (K8s resources) changes with each deployment

2. **Use Terraform Workspaces**
   - Separate state for different environments
   - `terraform workspace new staging`

3. **Plan Before Apply**
   - Review changes before applying
   - Use `terraform plan` in CI

4. **State Locking**
   - Prevent concurrent modifications
   - Use DynamoDB for S3 backend

5. **Variable Validation**
   - Validate inputs
   - Fail fast on invalid values

## 10. Troubleshooting

### Issue 1: Provider Not Found
```bash
# Solution: Run terraform init
terraform init
```

### Issue 2: State Locked
```bash
# Solution: Check for lock file or force unlock (careful!)
terraform force-unlock <lock-id>
```

### Issue 3: Resource Already Exists
```bash
# Solution: Import existing resource
terraform import aws_eks_cluster.main my-cluster-name
```

### Issue 4: Authentication Errors
```bash
# Solution: Verify AWS credentials
aws sts get-caller-identity
```

## 11. Key Takeaways

- ✅ Infrastructure as Code enables reproducible, versioned infrastructure
- ✅ Terraform is declarative and multi-cloud
- ✅ EKS cluster requires VPC, subnets, IAM roles, security groups
- ✅ Terraform can manage both infrastructure and Kubernetes resources
- ✅ State management is critical for team collaboration
- ✅ Modules enable code reuse and best practices
- ✅ Integrate Terraform into CD pipelines for automation

## 12. Next Steps

Now that you understand Terraform, you're ready for:
- **Module: Complete CD Pipeline** - Integrate everything together
- **Lab: Practical Exercise** - Hands-on deployment

## 13. Instructor Notes

- Start with simple resources before EKS
- Emphasize the declarative nature (describe what you want)
- Show `terraform plan` output to explain what will happen
- Demonstrate state importance with examples
- Use visual diagrams for EKS architecture
- Highlight cost implications (NAT gateways, EKS control plane)
- Show real-time updates during `terraform apply`


