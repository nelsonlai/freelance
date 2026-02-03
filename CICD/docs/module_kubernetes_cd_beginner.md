<!-- Module: Kubernetes Basics for CD -->
# Module: Kubernetes Basics for Continuous Deployment

## 1. Teaching Objectives

By the end of this module, students will be able to:
- Understand what Kubernetes is and why it's essential for CD
- Explain core Kubernetes concepts (Pods, Deployments, Services)
- Understand Amazon EKS and its benefits
- Deploy applications to Kubernetes
- Configure health checks and rolling updates
- Use Kubernetes for zero-downtime deployments
- Integrate Kubernetes into CD pipelines

## 2. What is Kubernetes?

### 2.1 The Problem Kubernetes Solves

**Without Kubernetes:**
- Manually managing containers on servers
- Difficult to scale applications
- No automatic recovery from failures
- Complex load balancing setup
- Manual deployment processes
- Hard to manage multiple environments

**With Kubernetes:**
- Automatic container orchestration
- Easy scaling (up/down)
- Self-healing (restarts failed containers)
- Built-in load balancing
- Rolling updates without downtime
- Consistent deployments across environments

### 2.2 Kubernetes in Simple Terms

**Analogy**: Think of Kubernetes as a smart manager for a restaurant:
- **Containers** = Individual chefs (workers)
- **Pods** = Kitchen stations (groups of chefs working together)
- **Deployments** = Recipe instructions (how many chefs, what they cook)
- **Services** = Waiters (route customer orders to available chefs)
- **Kubernetes** = Restaurant manager (ensures enough chefs, replaces sick ones, balances workload)

### 2.3 What Kubernetes Does

1. **Deployment**: Deploys your containers to nodes (servers)
2. **Scaling**: Automatically adds/removes containers based on demand
3. **Load Balancing**: Distributes traffic across containers
4. **Self-Healing**: Restarts failed containers, replaces unhealthy ones
5. **Rolling Updates**: Updates applications without downtime
6. **Service Discovery**: Containers can find each other automatically
7. **Configuration Management**: Manages secrets, configs, environment variables

## 3. Core Kubernetes Concepts

### 3.1 Cluster Architecture

A Kubernetes cluster consists of:

**Control Plane (Master Nodes):**
- **API Server**: Entry point for all commands
- **etcd**: Database storing cluster state
- **Scheduler**: Decides which node runs which pod
- **Controller Manager**: Manages cluster state

**Worker Nodes:**
- **Kubelet**: Agent running on each node
- **Container Runtime**: Runs containers (Docker, containerd)
- **Kube-proxy**: Network proxy for services

**Note**: In managed services like EKS, AWS manages the control plane for you.

### 3.2 Pods

**What is a Pod?**
- Smallest deployable unit in Kubernetes
- Contains one or more containers
- Containers in a pod share:
  - Network (same IP address)
  - Storage (shared volumes)
  - Resources (CPU, memory)

**Example Pod:**
```yaml
apiVersion: v1
kind: Pod
metadata:
  name: my-app-pod
spec:
  containers:
    - name: app
      image: sample-python-app:v1.0.0
      ports:
        - containerPort: 8080
```

**Key Points:**
- Pods are ephemeral (can be created/destroyed)
- Usually managed by Deployments (not created directly)
- Each pod gets its own IP address

### 3.3 Deployments

**What is a Deployment?**
- Manages a set of identical pods
- Ensures desired number of pods are running
- Handles rolling updates and rollbacks
- Most common way to deploy applications

**Example Deployment:**
```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: sample-python-app
spec:
  replicas: 3  # Run 3 copies of the app
  selector:
    matchLabels:
      app: sample-python-app
  template:
    metadata:
      labels:
        app: sample-python-app
    spec:
      containers:
        - name: api
          image: 123456789012.dkr.ecr.us-east-1.amazonaws.com/sample-python-app:v1.0.0
          ports:
            - containerPort: 8080
          env:
            - name: ENV
              value: production
```

**Key Features:**
- **Replicas**: Number of pod copies to run
- **Selector**: How to identify pods managed by this deployment
- **Template**: Specification for pods to create
- **Rolling Updates**: Automatically updates pods one at a time

### 3.4 Services

**What is a Service?**
- Exposes pods to network traffic
- Provides stable IP address and DNS name
- Load balances traffic across pods
- Types: ClusterIP, NodePort, LoadBalancer

**Example Service:**
```yaml
apiVersion: v1
kind: Service
metadata:
  name: sample-python-app
spec:
  type: LoadBalancer  # Creates AWS Load Balancer
  selector:
    app: sample-python-app  # Routes to pods with this label
  ports:
    - port: 80          # External port
      targetPort: 8080  # Container port
      protocol: TCP
```

**Service Types:**

| Type | Use Case | Access |
|------|----------|--------|
| **ClusterIP** | Internal only | Only within cluster |
| **NodePort** | External access via node IP | NodeIP:Port |
| **LoadBalancer** | External access (cloud) | Cloud load balancer URL |

### 3.5 ConfigMaps and Secrets

**ConfigMap**: Stores non-sensitive configuration data

```yaml
apiVersion: v1
kind: ConfigMap
metadata:
  name: app-config
data:
  environment: production
  log_level: info
  api_timeout: "30"
```

**Secret**: Stores sensitive data (passwords, API keys)

```yaml
apiVersion: v1
kind: Secret
metadata:
  name: app-secrets
type: Opaque
data:
  database_password: <base64-encoded-password>
  api_key: <base64-encoded-key>
```

**Using in Deployment:**
```yaml
spec:
  containers:
    - name: api
      envFrom:
        - configMapRef:
            name: app-config
        - secretRef:
            name: app-secrets
```

## 4. Amazon EKS (Elastic Kubernetes Service)

### 4.1 What is EKS?

**EKS** = Managed Kubernetes service on AWS
- AWS manages the Kubernetes control plane
- You manage worker nodes (or use Fargate)
- Fully compatible with standard Kubernetes
- Integrated with AWS services (IAM, VPC, ECR)

### 4.2 Why EKS?

**Benefits:**
- ✅ **Managed Control Plane**: AWS handles master nodes
- ✅ **High Availability**: Control plane across multiple AZs
- ✅ **Security**: Integrated with AWS IAM and VPC
- ✅ **Scalability**: Auto-scaling node groups
- ✅ **Integration**: Works with ECR, CloudWatch, ALB
- ✅ **Compliance**: Meets various compliance requirements

**Costs:**
- Control plane: ~$0.10/hour (~$73/month)
- Worker nodes: Pay for EC2 instances or Fargate
- Data transfer and storage costs

### 4.3 EKS Architecture

```
┌─────────────────────────────────────┐
│   AWS Managed Control Plane        │
│   (API Server, etcd, Scheduler)    │
└─────────────────────────────────────┘
              │
              │ Manages
              ▼
┌─────────────────────────────────────┐
│   Your Worker Nodes (EC2/Fargate)   │
│   ┌─────────┐  ┌─────────┐         │
│   │  Pod 1  │  │  Pod 2  │         │
│   └─────────┘  └─────────┘         │
└─────────────────────────────────────┘
```

### 4.4 EKS vs Self-Managed Kubernetes

| Feature | EKS | Self-Managed |
|---------|-----|--------------|
| Control Plane | AWS manages | You manage |
| Setup Time | Minutes | Days/Weeks |
| Maintenance | AWS handles updates | You handle updates |
| High Availability | Built-in | You configure |
| Cost | Control plane fee | Infrastructure only |
| Best For | Production, teams | Learning, full control |

## 5. Local Development with Kubernetes

### 5.1 Using kind (Kubernetes in Docker)

**kind** = Run Kubernetes locally using Docker containers

**Installation:**
```bash
# macOS
brew install kind

# Linux
curl -Lo ./kind https://kind.sigs.k8s.io/dl/v0.20.0/kind-linux-amd64
chmod +x ./kind
sudo mv ./kind /usr/local/bin/kind
```

**Create Cluster:**
```bash
# Create a cluster
kind create cluster --name my-cluster

# Check cluster
kubectl cluster-info --context kind-my-cluster

# Delete cluster
kind delete cluster --name my-cluster
```

### 5.2 Using minikube

**minikube** = Runs Kubernetes in a VM on your machine

**Installation:**
```bash
# macOS
brew install minikube

# Start cluster
minikube start

# Check status
minikube status

# Stop cluster
minikube stop
```

### 5.3 kubectl - Kubernetes Command Line Tool

**Installation:**
```bash
# macOS
brew install kubectl

# Linux
curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
chmod +x kubectl
sudo mv kubectl /usr/local/bin/
```

**Essential kubectl Commands:**
```bash
# Get cluster information
kubectl cluster-info

# List all pods
kubectl get pods

# List all deployments
kubectl get deployments

# List all services
kubectl get services

# Get detailed information
kubectl describe pod <pod-name>

# View logs
kubectl logs <pod-name>

# Execute command in pod
kubectl exec -it <pod-name> -- /bin/bash

# Apply YAML file
kubectl apply -f deployment.yaml

# Delete resource
kubectl delete deployment <deployment-name>

# Watch resources
kubectl get pods -w
```

## 6. Deploying Applications to Kubernetes

### 6.1 Complete Deployment Example

Let's deploy our sample Python app to Kubernetes:

**Step 1: Create Deployment**
```yaml
# deployment.yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: sample-python-app
  labels:
    app: sample-python-app
spec:
  replicas: 3
  selector:
    matchLabels:
      app: sample-python-app
  template:
    metadata:
      labels:
        app: sample-python-app
    spec:
      containers:
        - name: api
          image: 123456789012.dkr.ecr.us-east-1.amazonaws.com/sample-python-app:v1.0.0
          ports:
            - containerPort: 8080
              name: http
          env:
            - name: ENV
              value: production
            - name: PORT
              value: "8080"
          resources:
            requests:
              memory: "256Mi"
              cpu: "250m"
            limits:
              memory: "512Mi"
              cpu: "500m"
          livenessProbe:
            httpGet:
              path: /healthz
              port: 8080
            initialDelaySeconds: 30
            periodSeconds: 10
          readinessProbe:
            httpGet:
              path: /healthz
              port: 8080
            initialDelaySeconds: 5
            periodSeconds: 5
```

**Step 2: Create Service**
```yaml
# service.yaml
apiVersion: v1
kind: Service
metadata:
  name: sample-python-app
  labels:
    app: sample-python-app
spec:
  type: LoadBalancer
  selector:
    app: sample-python-app
  ports:
    - port: 80
      targetPort: 8080
      protocol: TCP
      name: http
```

**Step 3: Deploy**
```bash
# Apply deployment
kubectl apply -f deployment.yaml

# Apply service
kubectl apply -f service.yaml

# Check status
kubectl get deployments
kubectl get pods
kubectl get services

# Get service URL (for LoadBalancer)
kubectl get service sample-python-app
```

### 6.2 Understanding the Deployment

**Key Components Explained:**

1. **replicas: 3**
   - Run 3 identical pods
   - Provides redundancy and load distribution

2. **selector.matchLabels**
   - Identifies which pods belong to this deployment
   - Must match pod template labels

3. **resources (requests/limits)**
   - **requests**: Minimum resources guaranteed
   - **limits**: Maximum resources allowed
   - Helps Kubernetes schedule pods efficiently

4. **livenessProbe**
   - Checks if container is running
   - If fails, Kubernetes restarts the container

5. **readinessProbe**
   - Checks if container is ready to serve traffic
   - If fails, removes pod from service load balancer

## 7. Health Checks and Probes

### 7.1 Types of Probes

**Liveness Probe:**
- Answers: "Is the container alive?"
- If fails: Container is restarted
- Use for: Detecting deadlocks, hung processes

**Readiness Probe:**
- Answers: "Is the container ready to serve traffic?"
- If fails: Pod removed from service (no traffic)
- Use for: Startup time, temporary unavailability

**Startup Probe:**
- Answers: "Has the container started?"
- If fails: Container is restarted
- Use for: Slow-starting applications

### 7.2 Probe Configuration

```yaml
livenessProbe:
  httpGet:
    path: /healthz
    port: 8080
  initialDelaySeconds: 30  # Wait 30s before first check
  periodSeconds: 10         # Check every 10s
  timeoutSeconds: 5        # Timeout after 5s
  successThreshold: 1      # 1 success = healthy
  failureThreshold: 3      # 3 failures = unhealthy

readinessProbe:
  httpGet:
    path: /healthz
    port: 8080
  initialDelaySeconds: 5
  periodSeconds: 5
  timeoutSeconds: 3
```

**Probe Types:**
- **httpGet**: HTTP GET request (most common)
- **tcpSocket**: TCP connection check
- **exec**: Execute command in container

## 8. Rolling Updates and Rollbacks

### 8.1 Rolling Updates

Kubernetes performs rolling updates by default:

1. Creates new pods with new version
2. Waits for new pods to be ready
3. Terminates old pods one at a time
4. Continues until all pods are updated

**Benefits:**
- Zero downtime
- Automatic rollback if new pods fail
- Gradual traffic migration

**Example Update:**
```bash
# Update image
kubectl set image deployment/sample-python-app \
  api=123456789012.dkr.ecr.us-east-1.amazonaws.com/sample-python-app:v2.0.0

# Watch rollout
kubectl rollout status deployment/sample-python-app

# Check rollout history
kubectl rollout history deployment/sample-python-app
```

### 8.2 Rollback

If something goes wrong, rollback is easy:

```bash
# Rollback to previous version
kubectl rollout undo deployment/sample-python-app

# Rollback to specific revision
kubectl rollout undo deployment/sample-python-app --to-revision=2

# View rollout history
kubectl rollout history deployment/sample-python-app
```

### 8.3 Update Strategy

Control how updates happen:

```yaml
spec:
  strategy:
    type: RollingUpdate
    rollingUpdate:
      maxSurge: 1        # Can have 1 extra pod during update
      maxUnavailable: 0   # Always have all pods available
```

**Strategies:**
- **RollingUpdate**: Gradual replacement (default)
- **Recreate**: Terminate all, then create new (downtime)

## 9. Scaling Applications

### 9.1 Manual Scaling

```bash
# Scale deployment to 5 replicas
kubectl scale deployment sample-python-app --replicas=5

# Check current replicas
kubectl get deployment sample-python-app
```

### 9.2 Horizontal Pod Autoscaler (HPA)

Automatically scale based on metrics:

```yaml
# hpa.yaml
apiVersion: autoscaling/v2
kind: HorizontalPodAutoscaler
metadata:
  name: sample-python-app-hpa
spec:
  scaleTargetRef:
    apiVersion: apps/v1
    kind: Deployment
    name: sample-python-app
  minReplicas: 2
  maxReplicas: 10
  metrics:
    - type: Resource
      resource:
        name: cpu
        target:
          type: Utilization
          averageUtilization: 70
```

**Apply HPA:**
```bash
kubectl apply -f hpa.yaml

# Check HPA status
kubectl get hpa
```

## 10. ConfigMaps and Secrets in Practice

### 10.1 Creating ConfigMaps

**From YAML:**
```yaml
apiVersion: v1
kind: ConfigMap
metadata:
  name: app-config
data:
  environment: production
  log_level: info
  api_timeout: "30"
  database_host: db.example.com
```

**From command line:**
```bash
kubectl create configmap app-config \
  --from-literal=environment=production \
  --from-literal=log_level=info
```

**From file:**
```bash
kubectl create configmap app-config --from-file=config.properties
```

### 10.2 Using ConfigMaps in Deployments

```yaml
spec:
  containers:
    - name: api
      envFrom:
        - configMapRef:
            name: app-config
      # Or individual values:
      env:
        - name: ENVIRONMENT
          valueFrom:
            configMapKeyRef:
              name: app-config
              key: environment
```

### 10.3 Creating Secrets

**From command line:**
```bash
# Create secret
kubectl create secret generic app-secrets \
  --from-literal=database_password=secret123 \
  --from-literal=api_key=key456
```

**From YAML (base64 encoded):**
```yaml
apiVersion: v1
kind: Secret
metadata:
  name: app-secrets
type: Opaque
data:
  database_password: c2VjcmV0MTIz  # base64 encoded
  api_key: a2V5NDU2                # base64 encoded
```

**Encode values:**
```bash
echo -n 'secret123' | base64
# Output: c2VjcmV0MTIz
```

## 11. Ingress for External Access

### 11.1 What is Ingress?

Ingress provides HTTP/HTTPS routing to services:
- Single entry point for multiple services
- SSL/TLS termination
- Path-based routing
- Host-based routing

### 11.2 Ingress Example (AWS ALB)

```yaml
# ingress.yaml
apiVersion: networking.k8s.io/v1
kind: Ingress
metadata:
  name: sample-python-app-ingress
  annotations:
    kubernetes.io/ingress.class: alb
    alb.ingress.kubernetes.io/scheme: internet-facing
    alb.ingress.kubernetes.io/target-type: ip
spec:
  rules:
    - host: myapp.example.com
      http:
        paths:
          - path: /
            pathType: Prefix
            backend:
              service:
                name: sample-python-app
                port:
                  number: 80
```

## 12. Integrating Kubernetes into CD Pipelines

### 12.1 CD Pipeline with Kubernetes

```yaml
# .github/workflows/cd.yml
name: Deploy to Kubernetes

on:
  push:
    branches: [main]

jobs:
  deploy:
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

      - name: Deploy to Kubernetes
        run: |
          # Update image in deployment
          kubectl set image deployment/sample-python-app \
            api=${{ secrets.ECR_REGISTRY }}/sample-python-app:${{ github.sha }}

      - name: Verify deployment
        run: |
          kubectl rollout status deployment/sample-python-app
          kubectl get pods -l app=sample-python-app
```

### 12.2 Using kubectl in CI/CD

**Best Practices:**
1. Use service accounts with minimal permissions (RBAC)
2. Store kubeconfig as secret
3. Use `kubectl apply` for idempotent operations
4. Verify deployments with `kubectl rollout status`
5. Implement rollback on failure

## 13. Troubleshooting Common Issues

### Issue 1: Pods Not Starting
```bash
# Check pod status
kubectl get pods

# Describe pod for details
kubectl describe pod <pod-name>

# Check logs
kubectl logs <pod-name>
```

### Issue 2: Image Pull Errors
```bash
# Check if image exists
docker pull <image-name>

# Verify ECR authentication
aws ecr get-login-password --region us-east-1 | \
  docker login --username AWS --password-stdin <registry>
```

### Issue 3: Service Not Accessible
```bash
# Check service
kubectl get service <service-name>

# Check endpoints
kubectl get endpoints <service-name>

# Test from within cluster
kubectl run -it --rm debug --image=busybox --restart=Never -- wget -O- http://<service-name>
```

## 14. Key Takeaways

- ✅ Kubernetes orchestrates containers at scale
- ✅ Pods are the smallest deployable unit
- ✅ Deployments manage pod lifecycles
- ✅ Services expose pods to network traffic
- ✅ EKS provides managed Kubernetes on AWS
- ✅ Health checks ensure application reliability
- ✅ Rolling updates enable zero-downtime deployments
- ✅ ConfigMaps and Secrets manage configuration
- ✅ HPA enables automatic scaling

## 15. Next Steps

Now that you understand Kubernetes, you're ready for:
- **Module: Terraform for Kubernetes CD** - Automate Kubernetes infrastructure
- **Module: Complete CD Pipeline** - Integrate everything together
- **Lab: Practical Exercise** - Hands-on deployment

## 16. Instructor Notes

- Start with local Kubernetes (kind/minikube) before EKS
- Use visual diagrams to explain cluster architecture
- Emphasize declarative nature of Kubernetes (describe desired state)
- Show real-time updates with `kubectl get pods -w`
- Demonstrate rolling updates and rollbacks live
- Highlight the power of self-healing capabilities


